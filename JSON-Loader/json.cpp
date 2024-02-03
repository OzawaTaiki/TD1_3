#include "json.h"

#define _CLOSE 0
#define _OPEN 1

JsonL::JsonL(const char* _path)
{
	Load(_path);
}
void JsonL::Load(const char* _path)
{
	FILE* fp = nullptr;

	fopen_s(&fp, _path, "rt");
	if (fp == nullptr) return;

	char buffer[1024]{};

	char	key[256]{};
	char	cValue[256]{};
	char	ciValue[64]{};

	int isInt = 0;
	int startJson = 0;
	int isValue = 0;
	int isCharValue = 0;
	int isInValue = 0;
	int valueSpan = _CLOSE;
	int keySpan = _CLOSE;

	while (fgets(buffer, sizeof(buffer), fp) != 0)
	{
		isInt = 0;
		isInValue = 0;
		valueSpan = 0;
		for (int i = 0; i < sizeof buffer; i++)
		{
			// 値部分かどうか...
			if (isValue == 0)
			{
				// キー受付開始
				if (buffer[i] == '\"' && keySpan == _CLOSE)
				{
					keySpan = i + 1;
					continue;
				}

				// キー受付終了
				if (buffer[i] == '\"' && keySpan != _CLOSE)
				{
					key[i - keySpan] = '\0';
					keySpan = _CLOSE;
					continue;
				}

				// 現在の文字がキーである場合
				if (keySpan != _CLOSE)
				{
					key[i - keySpan] = buffer[i];
				}

				if (buffer[i] == ':')
				{
					isValue = 1;
					continue;
				}
			}
			else
			{
				if (buffer[i] == '\"')
				{
					if (valueSpan == _CLOSE)
					{
						valueSpan = i + 1;
						isCharValue = 1;
					}
					else
					{
						cValue[i - valueSpan] = '\0';
						isCharValue = 0;
						isInt = 2;
						valueSpan = _CLOSE;
					}
					continue;
				}
				// 数字である時
				else if (buffer[i] >= 48 && buffer[i] <= 57 && isCharValue == 0)
				{
					if (valueSpan == _CLOSE) valueSpan = i;
					isInValue = 1;
					ciValue[i - valueSpan] = buffer[i];
					continue;
				}
				else if (isInValue == 1)
				{
					// 数字の終わり
					ciValue[i - valueSpan] = '\0';
					isInt = 1;
					isValue = 0;
					isInValue = 0;
				}
				if (buffer[i] == ',')
				{
					isValue = 0;
					continue;
				}

				// 値が文字列の場合
				if (isCharValue) cValue[i - valueSpan] = buffer[i];
			}

			// Json開始
			if (buffer[i] == '{')
			{
				startJson = _OPEN;
				continue;
			}

			// Json終了
			if (buffer[i] == '}' && startJson == _OPEN)
			{
				startJson = _CLOSE;
				continue;
			}


			if (buffer[i] == '\0' || buffer[i] == '\n') // 行末時
				break;
		}
		if (isInt == 1) data[key] = ciValue;
		else if (isInt == 2) data[key] = cValue;
	}
	
	fclose(fp);
}
