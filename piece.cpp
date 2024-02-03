﻿#include "piece.h"
#include "CSVLoader.h"
#include "CursorManager.h"
#include <Novice.h>

void Piece::PieceMove(const std::vector< std::vector<int>>* _field, const Vector2& _playerPos, std::vector<Box*> _box)
{
	Transform cursor;
	CursorManager::GetCursorPos(&cursor);

	if (Novice::IsTriggerMouse(0))
	{
		for (int i = 0; i < (*piece).size(); i++)
		{
			/// ピースを矩形の当たり判定で...
			if (pos[i].x < cursor.x &&
				pos[i].x + size[i].x * kTileSize * scale[i] > cursor.x &&
				pos[i].y < cursor.y &&
				pos[i].y + size[i].y * kTileSize * scale[i] > cursor.y &&
				isHave == -1)
			{
				p2mSub.x = (pos[i].x - cursor.x) / scale[i];
				p2mSub.y = (pos[i].y - cursor.y) / scale[i];

				/// クリックした位置にピースのブロックがあるか否か
				if ((*piece)[i][int(-p2mSub.y * scale[i] / (kTileSize * scale[i]))][int(-p2mSub.x * scale[i] / (kTileSize * scale[i]))] != 0 /*&& !IsInPiece(_playerPos, i)*/)
				{
					piecePrePos = pos[i];

					pos[i].x = p2mSub.x + cursor.x;
					pos[i].y = p2mSub.y + cursor.y;

					scale[i] = kKeyScale[0];
					isHave = i;
				}
			}
		}
	}

	/// ピースつかんでるとき
	else if (Novice::IsPressMouse(0) && !Novice::IsTriggerMouse(0) && isHave != -1)
	{
		pos[isHave].x = cursor.x + p2mSub.x;
		pos[isHave].y = cursor.y + p2mSub.y;

		for (int i = 0; i < (*piece).size(); i++)
		{
			if (i == isHave || scale[i] == kKeyScale[1])
				continue;

			mapchipKeyPos.x = float((int)pos[i].x % kTileSize);
			mapchipKeyPos.y = float((int)pos[i].y % kTileSize);
		}
	}

	else
	{
		if (isHave != -1)
		{
			//piecePos[isHave].x = float(int(piecePos[isHave].x / kTileSize + (int(piecePos[isHave].x) % kTileSize < kTileSize / 2 ? 0 : 1)) * kTileSize);
			//piecePos[isHave].y = float(int(piecePos[isHave].y / kTileSize + (int(piecePos[isHave].y) % kTileSize < kTileSize / 2 ? 0 : 1)) * kTileSize);
			int a = 0; a++;
		}

		for (int i = 0; i < (*piece).size(); i++)
		{
			bool isPlayerOverlap = false;			// ピース内にプレイヤーが入ってるか否か
			bool isHindranceBlockInside = false;	// ピース内にお邪魔ブロックが入っているか否か

			piecePosInMapchip[i].x = (int)pos[i].x / kTileSize;
			piecePosInMapchip[i].y = (int)pos[i].y / kTileSize;

			scale[i] = kKeyScale[1];

			for (int y = 0; y < (*piece)[i].size(); y++)
			{
				for (int x = 0; x < (*piece)[i][y].size(); x++)
				{
					scanX = int((pos[i].x) / kTileSize) + x;
					scanY = int((pos[i].y) / kTileSize) + y;

					/// 操作中のブロックがフィールド内にないとき
					if (scanX < 0 ||
						scanY < 0 ||
						scanX >= kStageAreaWidth / kTileSize ||
						scanY >= kWindowHeight / kTileSize)
					{
						if ((*piece)[i][y][x] == 2)	// 2:隣接部分で消えてるところ
							(*piece)[i][y][x] = 1;
						continue;
					}


					/*******************
						ピース設置判定
					*******************/
					/// お邪魔ブロック判定
					if (!isHindranceBlockInside && (*piece)[i][y][x] == 1)
						isHindranceBlockInside = HindranceBlockCheck(_field, scanX, scanY);

					/// プレイヤーと操作中のブロックが重なってるとき
					if (isHave != -1 &&
						scanX == int(_playerPos.x) / kTileSize &&
						scanY == int(_playerPos.y) / kTileSize)
					{
						/// プレイヤーがブロックと重なってるとき
						/*if ((*piece)[i][int(_playerPos.y - pos[i].y) / kTileSize][int(_playerPos.x - pos[i].x) / kTileSize] == 1)
						{
							isPlayerOverlap = true;
							break;
						}*/
					}

					/// 操作中の位置にブロックがあるとき
					if ((*piece)[i][y][x] != 0)
					{
						/// ここまで来ていたらフィールド内に入っているのでスケールを等倍にする
						scale[i] = kKeyScale[0];
					}

					/// 消えたとこを戻す
					if ((*piece)[i][y][x] == 2)	// 2:隣接部分で消えてるところ
						(*piece)[i][y][x] = 1;
				}
			}

			if (scale[i] != kKeyScale[0])
				piecePrePos = { kPieceStartKeyPos.x + i * kPieceStartMargin.x,kPieceStartKeyPos.y + i * kPieceStartMargin.y };

			/// ピースを置けなかったとき
			if (isPlayerOverlap || isHindranceBlockInside)
				pos[i] = piecePrePos;
		}

		isHave = -1;

		/// ピース隣接関係の処理
		for (int i = 0; i < (*piece).size(); i++)
			/// ピースがフィールド内に入ってるとき
			if (scale[i] == kKeyScale[0])
				Adjacent(i);
	}
}


void Piece::Adjacent(int _pieceNum)
{
	bool isAdjacent = false;

	for (int i = _pieceNum + 1; i < piece->size(); i++)
	{
		if (/// 仮想サイズ適用時に衝突している
			pos[_pieceNum].x + adjacencyCheckVertex[_pieceNum][0].x < pos[i].x + adjacencyCheckVertex[i][3].x &&
			pos[_pieceNum].x + adjacencyCheckVertex[_pieceNum][3].x > pos[i].x + adjacencyCheckVertex[i][0].x &&
			pos[_pieceNum].y + adjacencyCheckVertex[_pieceNum][0].y < pos[i].y + adjacencyCheckVertex[i][3].y &&
			pos[_pieceNum].y + adjacencyCheckVertex[_pieceNum][3].y > pos[i].y + adjacencyCheckVertex[i][0].y &&
			/// 実際のサイズのときに衝突していない
			pos[_pieceNum].x                         > pos[i].x + size[i].x * kTileSize ||
			pos[_pieceNum].x + size[i].x * kTileSize < pos[i].x                         ||
			pos[_pieceNum].y                         > pos[i].y + size[i].y * kTileSize ||
			pos[_pieceNum].y + size[i].y * kTileSize < pos[i].y)
		{
			float xOverlap =
				min(pos[_pieceNum].x + adjacencyCheckVertex[_pieceNum][3].x, pos[i].x + adjacencyCheckVertex[i][3].x)
				- max(pos[_pieceNum].x + adjacencyCheckVertex[_pieceNum][0].x, pos[i].x + adjacencyCheckVertex[i][0].x);

			float yOverlap =
				min(pos[_pieceNum].y + adjacencyCheckVertex[_pieceNum][3].y, pos[i].y + adjacencyCheckVertex[i][3].y)
				- max(pos[_pieceNum].y + adjacencyCheckVertex[_pieceNum][0].y, pos[i].y + adjacencyCheckVertex[i][0].y);

			if (xOverlap < yOverlap)
			{
				AdjacentPos(_pieceNum, i, 'y');
				isAdjacent = true;
			}
			else
			{
				AdjacentPos(_pieceNum, i, 'x');
				isAdjacent = true;
			}
		}
		/*/// ピースのｘ座標が重なっているか（ｙは除外
		if (piecePosInMapchip[_pieceNum].x <= piecePosInMapchip[i].x + size[i].x - 1 &&
			piecePosInMapchip[_pieceNum].x + size[_pieceNum].x - 1 >= piecePosInMapchip[i].x)
		{
			/// 上辺のー１または下辺の＋１に別のピースの下辺または上辺があるか
			if (piecePosInMapchip[i].y - 1 == piecePosInMapchip[_pieceNum].y + size[_pieceNum].y - 1 ||
				piecePosInMapchip[i].y + size[i].y - 1 == piecePosInMapchip[_pieceNum].y - 1)
			{
				/// 隣接している
				AdjacentPos(_pieceNum, i, 'x');
				isAdjacent = true;
			}
		}
		/// ピースのｙ座標が重なっているか（ｘは除外
		else if (piecePosInMapchip[_pieceNum].y <= piecePosInMapchip[i].y + size[i].y - 1 &&
			piecePosInMapchip[_pieceNum].y + size[_pieceNum].y - 1 >= piecePosInMapchip[i].y)
		{
			/// 左辺ー１または右辺＋１に別のピースの右辺または左辺があるか
			if (piecePosInMapchip[i].x - 1 == piecePosInMapchip[_pieceNum].x + size[_pieceNum].x - 1 ||
				piecePosInMapchip[i].x + size[i].x - 1 == piecePosInMapchip[_pieceNum].x - 1)
			{
				/// 隣接している
				AdjacentPos(_pieceNum, i, 'y');
				isAdjacent = true;
			}
		}*/

		/// 隣接してるとき
		if (isAdjacent)
		{
			AdjacentPieceDelete(_pieceNum, i);
			break;
		}
	}
}

void Piece::AdjacentPos(int _pieceNum1, int _pieceNum2, char _dir)
{
	adjacentDir.push_back(_dir);
	switch (_dir)
	{
	case 'x':
		/// 二つのピースのｘ座標を比較
		if (pos[_pieceNum1].x > pos[_pieceNum2].x)
		{
			/// ｙ座標比較
			if (pos[_pieceNum1].y < pos[_pieceNum2].y)
				adjacentPos.push_back({ int(pos[_pieceNum1].x + mapchipKeyPos.x) / kTileSize,
					int(pos[_pieceNum2].y + mapchipKeyPos.y) / kTileSize - 1 });
			else if (pos[_pieceNum1].y > pos[_pieceNum2].y)
				adjacentPos.push_back({ int(pos[_pieceNum1].x + mapchipKeyPos.x) / kTileSize,
					int(pos[_pieceNum1].y + mapchipKeyPos.y) / kTileSize - 1 });
		}
		else if (pos[_pieceNum1].x < pos[_pieceNum2].x)
		{
			if (pos[_pieceNum1].y < pos[_pieceNum2].y)
				adjacentPos.push_back({ int(pos[_pieceNum2].x + mapchipKeyPos.x) / kTileSize,
					int(pos[_pieceNum2].y + mapchipKeyPos.y) / kTileSize - 1 });
			else if (pos[_pieceNum1].y > pos[_pieceNum2].y)
				adjacentPos.push_back({ int(pos[_pieceNum2].x + mapchipKeyPos.x) / kTileSize,
					int(pos[_pieceNum1].y + mapchipKeyPos.y) / kTileSize - 1 });
		}
		else if (pos[_pieceNum1].x == pos[_pieceNum2].x)
		{
			if (pos[_pieceNum1].y < pos[_pieceNum2].y)
				adjacentPos.push_back({ int(pos[_pieceNum2].x + mapchipKeyPos.x) / kTileSize,
					int(pos[_pieceNum2].y + mapchipKeyPos.y) / kTileSize - 1 });
			else if (pos[_pieceNum1].y > pos[_pieceNum2].y)
				adjacentPos.push_back({ int(pos[_pieceNum1].x + mapchipKeyPos.x) / kTileSize,
					int(pos[_pieceNum1].y + mapchipKeyPos.y) / kTileSize - 1 });
		}
		/*/// 二つのピースのｘ座標を比較
		if (piecePosInMapchip[_pieceNum1].x > piecePosInMapchip[_pieceNum2].x)
		{
			/// ｙ座標比較
			if (piecePosInMapchip[_pieceNum1].y < piecePosInMapchip[_pieceNum2].y)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum1].x,piecePosInMapchip[_pieceNum2].y - 1 });
			else if (piecePosInMapchip[_pieceNum1].y > piecePosInMapchip[_pieceNum2].y)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum1].x,piecePosInMapchip[_pieceNum1].y - 1 });
		}
		else if (piecePosInMapchip[_pieceNum1].x < piecePosInMapchip[_pieceNum2].x)
		{
			if (piecePosInMapchip[_pieceNum1].y < piecePosInMapchip[_pieceNum2].y)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum2].x,piecePosInMapchip[_pieceNum2].y - 1 });
			else if (piecePosInMapchip[_pieceNum1].y > piecePosInMapchip[_pieceNum2].y)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum2].x,piecePosInMapchip[_pieceNum1].y - 1 });
		}
		else if (piecePosInMapchip[_pieceNum1].x == piecePosInMapchip[_pieceNum2].x)
		{
			if (piecePosInMapchip[_pieceNum1].y < piecePosInMapchip[_pieceNum2].y)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum2].x,piecePosInMapchip[_pieceNum2].y - 1 });
			else if (piecePosInMapchip[_pieceNum1].y > piecePosInMapchip[_pieceNum2].y)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum1].x,piecePosInMapchip[_pieceNum1].y - 1 });
		}*/
		break;
	case 'y':
		if (pos[_pieceNum1].y > pos[_pieceNum2].y)
		{
			if (pos[_pieceNum1].x > pos[_pieceNum2].x)
				adjacentPos.push_back({ int(pos[_pieceNum1].x + mapchipKeyPos.x) / kTileSize - 1 ,
					int(pos[_pieceNum1].y + mapchipKeyPos.y) / kTileSize });
			else if (pos[_pieceNum1].x < pos[_pieceNum2].x)
				adjacentPos.push_back({ int(pos[_pieceNum2].x + mapchipKeyPos.x) / kTileSize - 1 ,
					int(pos[_pieceNum1].y + mapchipKeyPos.y) / kTileSize });
		}
		else if (pos[_pieceNum1].y < pos[_pieceNum2].y)
		{
			if (pos[_pieceNum1].x > pos[_pieceNum2].x)
				adjacentPos.push_back({ int(pos[_pieceNum1].x + mapchipKeyPos.x) / kTileSize - 1 ,
					int(pos[_pieceNum2].y + mapchipKeyPos.y) / kTileSize });
			else if (pos[_pieceNum1].x < pos[_pieceNum2].x)
				adjacentPos.push_back({ int(pos[_pieceNum2].x + mapchipKeyPos.x) / kTileSize - 1 ,
					int(pos[_pieceNum2].y + mapchipKeyPos.y) / kTileSize });
		}
		else if (pos[_pieceNum1].y == pos[_pieceNum2].y)
		{
			if (pos[_pieceNum1].x < pos[_pieceNum2].x)
				adjacentPos.push_back({ int(pos[_pieceNum2].x + mapchipKeyPos.x) / kTileSize - 1 ,
					int(pos[_pieceNum2].y + mapchipKeyPos.y) / kTileSize });
			else if (pos[_pieceNum1].x > pos[_pieceNum2].x)
				adjacentPos.push_back({ int(pos[_pieceNum1].x + mapchipKeyPos.x) / kTileSize - 1 ,
					int(pos[_pieceNum1].y + mapchipKeyPos.y) / kTileSize });
		}
		/*if (pos[_pieceNum1].y > pos[_pieceNum2].y)
		{
			if (pos[_pieceNum1].x > pos[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum1].x - 1,piecePosInMapchip[_pieceNum1].y });
			else if (pos[_pieceNum1].x < pos[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum2].x - 1,piecePosInMapchip[_pieceNum1].y });
		}
		else if (pos[_pieceNum1].y < pos[_pieceNum2].y)
		{
			if (pos[_pieceNum1].x > pos[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum1].x - 1,piecePosInMapchip[_pieceNum2].y });
			else if (pos[_pieceNum1].x < pos[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum2].x - 1,piecePosInMapchip[_pieceNum2].y });
		}
		else if (pos[_pieceNum1].y == pos[_pieceNum2].y)
		{
			if (pos[_pieceNum1].x < pos[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum2].x - 1,piecePosInMapchip[_pieceNum2].y });
			else if (pos[_pieceNum1].x > pos[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum1].x - 1,piecePosInMapchip[_pieceNum1].y });
		}*/
		break;
	default:
		break;
	}
	for (int i = 0; i < adjacentPos.size(); i++)
	{
		/// 同じデータが含まれていた時でーた消す
		if (adjacentPos.back().x == adjacentPos[i].x &&
			adjacentPos.back().y == adjacentPos[i].y &&
			adjacentPos.size() - 1 != i)
		{
			adjacentPos.pop_back();
			break;
		}
	}
}

void Piece::AdjacentPieceDelete(int _pieceNum1, int _pieceNum2)
{
	for (int i = 0; i < adjacentDir.size(); i++)
	{
		int count1 = 1;
		int count2 = 1;
		int temp1;
		int temp2;

		switch (adjacentDir[i])
		{
		case 'x':

			temp1 = adjacentPos[i].x - int(pos[_pieceNum1].x + mapchipKeyPos.x) / kTileSize;
			temp2 = adjacentPos[i].x - int(pos[_pieceNum2].x + mapchipKeyPos.x) / kTileSize;

			/// ｙ座標比較
			if (pos[_pieceNum1].y < pos[_pieceNum2].y)
			{
				/// ピースの端一個手前まで
				while (temp1 + count1 < (*piece)[_pieceNum1][(*piece)[_pieceNum1].size() - 1].size() - 1 &&
					temp2 + count2 < (*piece)[_pieceNum2][0].size() - 1)
				{
					(*piece)[_pieceNum1][(*piece)[_pieceNum1].size() - 1][temp1 + count1++] = 2;
					(*piece)[_pieceNum2][0][temp2 + count2++] = 2;
				}
			}
			else if (pos[_pieceNum1].y > pos[_pieceNum2].y)
			{
				/// ピースの端一個手前まで
				while (temp1 + count1 < (*piece)[_pieceNum1][0].size() - 1 &&
					temp2 + count2 < (*piece)[_pieceNum2][(*piece)[_pieceNum2].size() - 1].size() - 1)
				{
					(*piece)[_pieceNum1][0][temp1 + count1++] = 2;
					(*piece)[_pieceNum2][(*piece)[_pieceNum2].size() - 1][temp2 + count2++] = 2;
				}
			}
			break;
		case 'y':
			temp1 = adjacentPos[i].y - int(pos[_pieceNum1].y + mapchipKeyPos.y) / kTileSize;
			temp2 = adjacentPos[i].y - int(pos[_pieceNum2].y + mapchipKeyPos.y) / kTileSize;

			/// ｘ座標比較
			if (pos[_pieceNum1].x > pos[_pieceNum2].x)
			{
				/// ピースの端一個手前まで
				while (temp1 + count1 < (*piece)[_pieceNum1].size() - 1 &&
					temp2 + count2 < (*piece)[_pieceNum2].size() - 1)
				{
					(*piece)[_pieceNum1][temp1 + count1++][0] = 2;
					(*piece)[_pieceNum2][temp2 + count2++][(*piece)[_pieceNum2][temp2 + count2].size() - 1] = 2;
				}
			}
			else if (pos[_pieceNum1].x < pos[_pieceNum2].x)
			{
				/// ピースの端一個手前まで
				while (temp1 + count1 < (*piece)[_pieceNum1].size() - 1 &&
					temp2 + count2 < (*piece)[_pieceNum2].size() - 1)
				{
					(*piece)[_pieceNum1][temp1 + count1++][(*piece)[_pieceNum1][temp1 + count1].size() - 1] = 2;
					(*piece)[_pieceNum2][temp2 + count2++][0] = 2;
				}
			}
			break;
		default:
			break;
		}
	}
}

void Piece::FieldCollision(std::vector<std::vector<int>>* _collision)
{
	for (int i = 0; i < (*piece).size(); i++)
	{
		for (int y = 0; y < (*piece)[i].size(); y++)
		{
			for (int x = 0; x < (*piece)[i][y].size(); x++)
			{
				intVec2 temp = { piecePosInMapchip[i].x + x,piecePosInMapchip[i].y + y };

				if ((*piece)[i][y][x] == 1 &&
					temp.x >= 0 &&
					temp.x < kStageAreaWidth / kTileSize &&
					temp.y >= 0 &&
					temp.y < kWindowHeight / kTileSize)
				{
					if ((*_collision)[temp.y][temp.x] != 1 && (*_collision)[temp.y][temp.x] != 5)
						(*_collision)[temp.y][temp.x] = i + kTileKinds;
				}
			}
		}
	}
}

bool Piece::HindranceBlockCheck(const std::vector<std::vector<int>>* _field, int _x, int _y)
{
	_x = 0;
	_y = 0;

	if ((*_field)[_y][_x] == HINDRANCE)	return true;
	return false;
}

int Piece::PixelCollisionWithObj(const Vector2& _pos, const Vector2* _vertex, Vector2& _collisionDir)
{
	int hitPieceNum = -1;
	Vector2 localPos = _pos;

	Vector2 o2pSub[4];

	runX = 0;
	runY = 0;

	for (int i = 0; i < (*piece).size(); i++)
	{
		bool isExit = false;
		if (!IsInPiece(_pos, i) || isHave == i)
			continue;

		for (int k = 0; k < 4; k++)
		{
			o2pSub[k].x = _pos.x + _vertex[k].x - pos[i].x;
			o2pSub[k].y = _pos.y + _vertex[k].y - pos[i].y;

			if (!(o2pSub[k].x > 0 &&
				o2pSub[k].y > 0 &&
				o2pSub[k].x < size[i].x * kTileSize &&
				o2pSub[k].y < size[i].y * kTileSize))
				isExit = true;
		}
		if (isExit)
			continue;

		/// 上向き
		if ((*piece)[i][int(o2pSub[0].y) / kTileSize][int(o2pSub[0].x) / kTileSize] == 1 &&
			(*piece)[i][int(o2pSub[1].y) / kTileSize][int(o2pSub[1].x) / kTileSize] == 1)
		{
			_collisionDir.y = -1;
			localPos.y = pos[i].y + int(o2pSub[1].y) * kTileSize + kTileSize + _vertex[2].y + 1;
			runY = int(o2pSub[1].y) / kTileSize;
			hitPieceNum = i;
		}
		/// 下向き
		if ((*piece)[i][int(o2pSub[2].y) / kTileSize][int(o2pSub[2].x) / kTileSize] == 1 &&
			(*piece)[i][int(o2pSub[3].y) / kTileSize][int(o2pSub[3].x) / kTileSize] == 1)
		{
			_collisionDir.y = 1;
			localPos.y = pos[i].y + int(o2pSub[1].y) * kTileSize + _vertex[0].y - 1;
			runY = int(o2pSub[2].y) / kTileSize;
			hitPieceNum = i;
		}


		/// 左向き
		if ((*piece)[i][int(o2pSub[0].y) / kTileSize][int(o2pSub[0].x) / kTileSize] == 1 &&
			(*piece)[i][int(o2pSub[2].y) / kTileSize][int(o2pSub[2].x) / kTileSize] == 1)
		{
			_collisionDir.x = -1;
			localPos.x = pos[i].x + int(o2pSub[2].x) / kTileSize * kTileSize + kTileSize + _vertex[1].x + 1;
			runX = int(o2pSub[2].x) / kTileSize;
			hitPieceNum = i;
		}
		/// 右向き
		if ((*piece)[i][int(o2pSub[1].y) / kTileSize][int(o2pSub[1].x) / kTileSize] == 1 &&
			(*piece)[i][int(o2pSub[3].y) / kTileSize][int(o2pSub[3].x) / kTileSize] == 1)
		{
			_collisionDir.x = 1;
			localPos.x = pos[i].x + int(o2pSub[2].x) / kTileSize * kTileSize + _vertex[0].x - 1;
			runX = int(o2pSub[1].x) / kTileSize;
			hitPieceNum = i;
		}

	}
	return hitPieceNum;
}

int Piece::PixelCollisionWithObjOutSide(const Vector2& _pos, const Vector2* _vertex, Vector2& _collisionDir)
{
	int hitPieceNum = -1;
	Vector2 o2pSub[4];

	Vector2 pieceHitEdge = { 0,0 };
	bool isContinue[4] = { false,0,0,0 };

	runX = 0;
	runY = 0;

	for (int i = 0; i < (*piece).size(); i++)
	{
		if (IsInPiece(_pos, i) || isHave == i)
			continue;

		Vector2 hitBlockPos[4];

		for (int k = 0; k < 4; k++)
		{
			isContinue[k] = false;
			o2pSub[k].x = _pos.x + _vertex[k].x - pos[i].x;
			o2pSub[k].y = _pos.y + _vertex[k].y - pos[i].y;

			hitBlockPos[k].x = float(int(o2pSub[k].x) / kTileSize * kTileSize) + pos[i].x;
			hitBlockPos[k].y = float(int(o2pSub[k].y) / kTileSize * kTileSize) + pos[i].y;

			if (o2pSub[k].x > 0 &&
				o2pSub[k].y > 0 &&
				o2pSub[k].x < size[i].x * kTileSize &&
				o2pSub[k].y < size[i].y * kTileSize)
				isContinue[k] = true;
		}

		float xOverlap = min(_pos.x + _vertex[1].x, pos[i].x + size[i].x * kTileSize) - max(_pos.x + _vertex[0].x, pos[i].x);
		float yOverlap = min(_pos.y + _vertex[2].y, pos[i].y + size[i].y * kTileSize) - max(_pos.y + _vertex[0].y, pos[i].y);

		if (xOverlap < yOverlap && moveDir.x != 0)
		{
			if (_pos.x + _vertex[0].x < pos[i].x)
				pieceHitEdge.x = -1;//left
			else
				pieceHitEdge.x = 1;//right
		}
		else if (moveDir.y != 0)
		{
			if (_pos.y + _vertex[0].y < pos[i].y)
				pieceHitEdge.y = -1;//up
			else
				pieceHitEdge.y = 1;//bottom
		}

		/// 上向き objの上辺にpieceが当たった
		if ((isContinue[0] && (*piece)[i][int(o2pSub[0].y) / kTileSize][int(o2pSub[0].x) / kTileSize] == 1 ||
			isContinue[1] && (*piece)[i][int(o2pSub[1].y) / kTileSize][int(o2pSub[1].x) / kTileSize] == 1)
			&& o2pSub[2].y > size[i].y * kTileSize
			&& moveDir.y > 0
			&& pieceHitEdge.y == 1)
		{
			_collisionDir.y = -1;
			runY = int(o2pSub[1].y) / kTileSize;
			hitPieceNum = i;
		}
		/// 下向き
		if ((isContinue[2] && (*piece)[i][int(o2pSub[2].y) / kTileSize][int(o2pSub[2].x) / kTileSize] == 1 ||
			isContinue[3] && (*piece)[i][int(o2pSub[3].y) / kTileSize][int(o2pSub[3].x) / kTileSize] == 1)
			&& o2pSub[0].y < 0
			&& moveDir.y < 0
			&& pieceHitEdge.y == -1)
		{
			_collisionDir.y = 1;
			runY = int(o2pSub[2].y) / kTileSize;
			hitPieceNum = i;
		}
		/// 左向き
		if ((isContinue[0] && (*piece)[i][int(o2pSub[0].y) / kTileSize][int(o2pSub[0].x) / kTileSize] == 1 ||
			isContinue[2] && (*piece)[i][int(o2pSub[2].y) / kTileSize][int(o2pSub[2].x) / kTileSize] == 1)
			&& o2pSub[1].x > size[i].x * kTileSize
			&& moveDir.x > 0
			&& pieceHitEdge.x == 1)
		{
			_collisionDir.x = -1;
			runX = int(o2pSub[2].x) / kTileSize;
			hitPieceNum = i;
		}
		/// 右向き objの右辺にpieceが当たった
		if ((isContinue[1] && (*piece)[i][int(o2pSub[1].y) / kTileSize][int(o2pSub[1].x) / kTileSize] == 1 ||
			isContinue[3] && (*piece)[i][int(o2pSub[3].y) / kTileSize][int(o2pSub[3].x) / kTileSize] == 1)
			&& o2pSub[0].x < 0
			&& moveDir.x < 0
			&& pieceHitEdge.x == -1)
		{
			_collisionDir.x = 1;
			runX = int(o2pSub[1].x) / kTileSize;
			hitPieceNum = i;
		}
	}
	return hitPieceNum;
}


void Piece::DrawPieceShadow()
{
	if (isHave != -1)
	{
		for (int y = 0; y < (*piece)[isHave].size(); y++)
		{
			for (int x = 0; x < (*piece)[isHave][y].size(); x++)
			{
				if (int((scanX + x) * kTileSize * scale[isHave]) / kTileSize >= 0 &&
					int((scanX + x) * kTileSize * scale[isHave]) / kTileSize < kStageAreaWidth &&
					int((scanY + y) * kTileSize * scale[isHave]) / kTileSize >= 0 &&
					int((scanY + y) * kTileSize * scale[isHave]) / kTileSize < kWindowHeight)

					Novice::DrawBox(int((scanX + x) * kTileSize * scale[isHave]), int(+(scanY + y) * kTileSize * scale[isHave]), int(kTileSize * scale[isHave]) - 1, int(kTileSize * scale[isHave]) - 1, 0, (*piece)[isHave][y][x] == 0 ? 0 : 0xff, kFillModeSolid);
			}
		}
	}
}

bool Piece::IsInPiece(const Vector2& _pos, int _pieceNum)
{
	bool isHitEdges[4] = { false,0,0,0 };

	Vector2 o2pSub;
	o2pSub.x = _pos.x - pos[_pieceNum].x;
	o2pSub.y = _pos.y - pos[_pieceNum].y;

	intVec2 base;
	base.x = (int)o2pSub.x / kTileSize;
	base.y = (int)o2pSub.y / kTileSize;

	if (o2pSub.x < 0 ||
		o2pSub.y < 0 ||
		o2pSub.x >= size[_pieceNum].x * kTileSize ||
		o2pSub.y >= size[_pieceNum].y * kTileSize ||
		(*piece)[_pieceNum][base.y][base.x] == 1)
		return false;

	for (int dir = 0; dir < 4; dir++)
	{
		int move = 0;			//判定移動分
		bool isExit = false;	//強制退場用フラグ
		while (!isHitEdges[dir])
		{
			switch (dir)
			{
			case 0://上
				if (base.y - move < 0)
				{//pieceの端を超えた時
					isExit = true;
					break;
				}
				if ((*piece)[_pieceNum][base.y - move][base.x] != 0)
				{//走査中にpieceのブロックにあたったとき
					isHitEdges[0] = true;
				}

				break;
			case 1://左
				if (base.x - move < 0)
				{
					isExit = true;
					break;
				}
				if ((*piece)[_pieceNum][base.y][base.x - move] != 0)
				{
					isHitEdges[1] = true;
				}
				break;
			case 2://下
				if (base.y + move >= (*piece)[_pieceNum].size())
				{
					isExit = true;
					break;
				}
				if ((*piece)[_pieceNum][base.y + move][base.x] != 0)
				{
					isHitEdges[2] = true;
				}
				break;
			case 3://右
				if (base.x + move >= (*piece)[_pieceNum][base.y].size())
				{
					isExit = true;
					break;
				}
				if ((*piece)[_pieceNum][base.y][base.x + move] != 0)
				{
					isHitEdges[3] = true;
				}
				break;
			default:
				break;
			}
			move++;
			if (isExit)
				break;
		}
		if (!isHitEdges[dir])//中になかったら即抜け
			return false;

	}
	return true;
}


void Piece::MoveOnCollision(const Vector2& _collisionDir, int _collidedNum, const Vector2& _velocity)
{
	velocity = _velocity;

	//piecePosInMapchip[_collidedNum - kTileKinds].x += (int)_collisionDir.x;
	//piecePosInMapchip[_collidedNum - kTileKinds].y += (int)_collisionDir.y;

	if (_collisionDir.x != 0)
		pos[_collidedNum - kTileKinds].x += velocity.x;
	if (_collisionDir.y != 0)
		pos[_collidedNum - kTileKinds].y += velocity.y;

	moveDir.x = _collisionDir.x;
	moveDir.y = _collisionDir.y;
}

Piece::Piece()
{
	pieceTexture = Novice::LoadTexture("./img/pieceBlock.png");
}

void Piece::PiecePosInit(int _x, int _y)
{
	pos[0] = { float(_x * kTileSize) ,float(_y * kTileSize) };
}

void Piece::Init()
{
	piece = CSV_Loader::GetPointerPiece();

	pos.resize(piece->size());
	piecePosInMapchip.resize(piece->size());
	size.resize(piece->size());
	scale.resize(piece->size());
	adjacencyCheckVertex.resize(piece->size(), std::vector<Vector2>(4));

	for (int i = 0; i < (*piece).size(); i++)
	{
		size[i] = { 0,0 };
		pos[i] = { kPieceStartKeyPos.x + i * kPieceStartMargin.x,kPieceStartKeyPos.y + i * kPieceStartMargin.y };
		scale[i] = 1.0f;

		for (int j = 0; j < (*piece)[i].size(); j++)
		{
			if (size[i].x < (*piece)[i][j].size())
				size[i].x = (float)(*piece)[i][j].size();
		}
		if (size[i].y < (*piece)[i].size())
			size[i].y = (float)(*piece)[i].size();

		adjacencyCheckVertex[i][0] = { -kAdjacencyCheckSize.x, -kAdjacencyCheckSize.y };
		adjacencyCheckVertex[i][1] = { size[i].x * kTileSize + kAdjacencyCheckSize.x,-kAdjacencyCheckSize.y };
		adjacencyCheckVertex[i][2] = { -kAdjacencyCheckSize.x, size[i].y * kTileSize + kAdjacencyCheckSize.y };
		adjacencyCheckVertex[i][3] = { size[i].x * kTileSize + kAdjacencyCheckSize.x, size[i].y * kTileSize + kAdjacencyCheckSize.y };
	}

	isHave = -1;
	p2mSub = { 0,0 };
	velocity = { 0,0 };
	moveDir = { 0,0 };
	mapchipKeyPos = { 0,0 };
	isLockedY = false;
}

void Piece::Update(const std::vector< std::vector<int>>* _field, const Vector2& _playerPos, const std::vector<Box*> _box)
{
	isLockedY = false;
	moveDir = { 0,0 };
	adjacentPos.clear();
	adjacentDir.clear();

	PieceMove(_field, _playerPos, _box);
	//FieldCollision(_collision);
}

void Piece::Draw()
{
	//DrawPieceShadow();

	for (int i = 0; i < (*piece).size(); i++)
	{
		Novice::ScreenPrintf(int(pos[i].x), int(pos[i].y) + i * 20, "%.1f,%.1f", pos[i].x, pos[i].y);
		//Novice::ScreenPrintf(0, 1020 + i * 20, "%.1f,%.1f", pieceSize[i].x, pieceSize[i].y);
		//Novice::ScreenPrintf(900, 900 + i * 20, "%d,%d", piecePosInMapchip[i].x, piecePosInMapchip[i].y);

		for (int y = 0; y < (*piece)[i].size(); y++)
		{
			for (int x = 0; x < (*piece)[i][y].size(); x++)
			{
				if ((*piece)[i][y][x] == 1)
					Phill::DrawQuadPlus(int(pos[i].x + x * kTileSize * scale[i]), int(pos[i].y + y * kTileSize * scale[i]), int(kTileSize * scale[i]) - 1, int(kTileSize * scale[i]) - 1, 1.0f, 1.0f, 0.0f, (i % 7) * 120, 0, 120, 120, pieceTexture, 0xffffffda, PhillDrawMode::DrawMode_LeftTop);
			}
		}
	}

	for (int i = 0; i < adjacentPos.size(); i++)
	{
		//Novice::ScreenPrintf(1400, 720 + i * 20, "%d,%d", adjacentPos[i].x, adjacentPos[i].y);
		Novice::DrawBox(int(adjacentPos[i].x * kTileSize + mapchipKeyPos.x), int(adjacentPos[i].y * kTileSize + mapchipKeyPos.y), kTileSize, kTileSize, 0, RED, kFillModeWireFrame);
	}
}

