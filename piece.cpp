#include "piece.h"
#include "CSVLoader.h"
#include "CursorManager.h"
#include <Novice.h>
#include <cassert>


void Piece::PieceMove(const std::vector< std::vector<int>>* _field, const Vector2& _playerPos)
{
	Transform cursor;
	CursorManager::GetCursorPos(&cursor);

	if (Novice::IsTriggerMouse(0))
	{
		for (int i = 0; i < (*piece).size(); i++)
		{
			/// ピースを矩形の当たり判定で...
			if (piecePos[i].x < cursor.x &&
				piecePos[i].x + pieceSize[i].x * kTileSize * scale[i] > cursor.x &&
				piecePos[i].y < cursor.y &&
				piecePos[i].y + pieceSize[i].y * kTileSize * scale[i] > cursor.y &&
				isHave == -1)
			{
				p2mSub.x = (piecePos[i].x - cursor.x) / scale[i];
				p2mSub.y = (piecePos[i].y - cursor.y) / scale[i];

				/// クリックした位置にピースのブロックがあるか否か
				if ((*piece)[i][int(-p2mSub.y * scale[i] / (kTileSize * scale[i]))][int(-p2mSub.x * scale[i] / (kTileSize * scale[i]))] != 0)
				{
					piecePos[i].x = p2mSub.x + cursor.x;
					piecePos[i].y = p2mSub.y + cursor.y;

					scale[i] = kKeyScale[0];
					isHave = i;
					piecePrePos = piecePos[i];
				}
			}
		}
	}

	/// ピースつかんでるとき
	else if (Novice::IsPressMouse(0) && !Novice::IsTriggerMouse(0) && isHave != -1)
	{
		piecePos[isHave].x = cursor.x + p2mSub.x;
		piecePos[isHave].y = cursor.y + p2mSub.y;
	}

	else
	{
		if (isHave != -1)
		{
			int a = 0;
			a++;
		}

		for (int i = 0; i < (*piece).size(); i++)
		{
			bool isPlayerInside = false;			// ピース内にプレイヤーが入ってるか否か
			bool isHindranceBlockInside = false;	// ピース内にお邪魔ブロックが入っているか否か

			piecePos[i].x = float(int(piecePos[i].x / kTileSize + (int(piecePos[i].x) % kTileSize < kTileSize / 2 ? 0 : 1)) * kTileSize);
			piecePos[i].y = float(int(piecePos[i].y / kTileSize + (int(piecePos[i].y) % kTileSize < kTileSize / 2 ? 0 : 1)) * kTileSize);

			piecePosInMapchip[i].x = (int)piecePos[i].x / kTileSize;
			piecePosInMapchip[i].y = (int)piecePos[i].y / kTileSize;

			scale[i] = kKeyScale[1];

			for (int y = 0; y < (*piece)[i].size(); y++)
			{
				for (int x = 0; x < (*piece)[i][y].size(); x++)
				{
					/// 消えたとこを戻す
					if ((*piece)[i][y][x] == 2)	// 2:隣接部分で消えてるところ
						(*piece)[i][y][x] = 1;

					scanX = int((piecePos[i].x) / kTileSize) + x;
					scanY = int((piecePos[i].y) / kTileSize) + y;

					/// 操作中のブロックがフィールド内にないとき
					if (scanX < 0 ||
						scanY < 0 ||
						scanX >= kStageAreaWidth / kTileSize ||
						scanY >= kWindowHeight / kTileSize)
						continue;


					/*******************
						ピース設置判定
					*******************/

					/// お邪魔ブロック判定
					isHindranceBlockInside = HindranceBlockCheck(_field, scanX, scanY);

					/// プレイヤーと操作中のブロックが重なってるとき
					if (scanX == int(_playerPos.x) / kTileSize &&
						scanY == int(_playerPos.y) / kTileSize)
					{
						/// プレイヤーがブロックと重なってるとき
						if ((*piece)[i][int(_playerPos.y - piecePos[i].y) / kTileSize][int(_playerPos.x - piecePos[i].x) / kTileSize] == 1)
						{
							break;
						}
						isPlayerInside = true;
					}

					/// 操作中の位置にブロックがあるとき
					if ((*piece)[i][y][x] == 1)
					{
						/// ここまで来ていたらフィールド内に入っているのでスケールを等倍にする
						scale[i] = kKeyScale[0];
					}

				}
			}

			if (scale[i] != kKeyScale[0])
				piecePrePos = { kPieceStartKeyPos.x + i * kPieceStartMargin.x,kPieceStartKeyPos.y + i * kPieceStartMargin.y };

			/// ピースを置けなかったとき
			if (isHindranceBlockInside) //仮
				piecePos[i] = piecePrePos;
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
		/// ピースのｘ座標が重なっているか（ｙは除外
		if (piecePosInMapchip[_pieceNum].x <= piecePosInMapchip[i].x + pieceSize[i].x - 1 &&
			piecePosInMapchip[_pieceNum].x + pieceSize[_pieceNum].x - 1 >= piecePosInMapchip[i].x)
		{
			/// 上辺のー１または下辺の＋１に別のピースの下辺または上辺があるか
			if (piecePosInMapchip[i].y - 1 == piecePosInMapchip[_pieceNum].y + pieceSize[_pieceNum].y - 1 ||
				piecePosInMapchip[i].y + pieceSize[i].y - 1 == piecePosInMapchip[_pieceNum].y - 1)
			{
				/// 隣接している
				Novice::ScreenPrintf(1500, 800, "x");
				AdjacentPos(_pieceNum, i, 'x');
				isAdjacent = true;
			}
		}
		/// ピースのｙ座標が重なっているか（ｘは除外
		else if (piecePosInMapchip[_pieceNum].y <= piecePosInMapchip[i].y + pieceSize[i].y - 1 &&
			piecePosInMapchip[_pieceNum].y + pieceSize[_pieceNum].y - 1 >= piecePosInMapchip[i].y)
		{
			/// 左辺ー１または右辺＋１に別のピースの右辺または左辺があるか
			if (piecePosInMapchip[i].x - 1 == piecePosInMapchip[_pieceNum].x + pieceSize[_pieceNum].x - 1 ||
				piecePosInMapchip[i].x + pieceSize[i].x - 1 == piecePosInMapchip[_pieceNum].x - 1)
			{
				/// 隣接している
				Novice::ScreenPrintf(1500, 800, "y");
				AdjacentPos(_pieceNum, i, 'y');
				isAdjacent = true;
			}
		}
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
		}
		break;
	case 'y':
		if (piecePosInMapchip[_pieceNum1].y > piecePosInMapchip[_pieceNum2].y)
		{
			if (piecePosInMapchip[_pieceNum1].x > piecePosInMapchip[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum1].x - 1,piecePosInMapchip[_pieceNum1].y });
			else if (piecePosInMapchip[_pieceNum1].x < piecePosInMapchip[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum2].x - 1,piecePosInMapchip[_pieceNum1].y });
		}
		else if (piecePosInMapchip[_pieceNum1].y < piecePosInMapchip[_pieceNum2].y)
		{
			if (piecePosInMapchip[_pieceNum1].x > piecePosInMapchip[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum1].x - 1,piecePosInMapchip[_pieceNum2].y });
			else if (piecePosInMapchip[_pieceNum1].x < piecePosInMapchip[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum2].x - 1,piecePosInMapchip[_pieceNum2].y });
		}
		else if (piecePosInMapchip[_pieceNum1].y == piecePosInMapchip[_pieceNum2].y)
		{
			if (piecePosInMapchip[_pieceNum1].x < piecePosInMapchip[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum2].x - 1,piecePosInMapchip[_pieceNum2].y });
			else if (piecePosInMapchip[_pieceNum1].x > piecePosInMapchip[_pieceNum2].x)
				adjacentPos.push_back({ piecePosInMapchip[_pieceNum1].x - 1,piecePosInMapchip[_pieceNum1].y });
		}
		break;
	default:
		assert(_dir == 'x' || _dir == 'y');
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

			temp1 = adjacentPos[i].x - piecePosInMapchip[_pieceNum1].x;
			temp2 = adjacentPos[i].x - piecePosInMapchip[_pieceNum2].x;

			/// ｙ座標比較
			if (piecePosInMapchip[_pieceNum1].y < piecePosInMapchip[_pieceNum2].y)
			{
				/// ピースの端一個手前まで
				while (temp1 + count1 < (*piece)[_pieceNum1][(*piece)[_pieceNum1].size() - 1].size() - 1 &&
					temp2 + count2 < (*piece)[_pieceNum2][0].size() - 1)
				{
					(*piece)[_pieceNum1][(*piece)[_pieceNum1].size() - 1][temp1 + count1++] = 2;
					(*piece)[_pieceNum2][0][temp2 + count2++] = 2;
				}
			}
			else if (piecePosInMapchip[_pieceNum1].y > piecePosInMapchip[_pieceNum2].y)
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
			temp1 = adjacentPos[i].y - piecePosInMapchip[_pieceNum1].y;
			temp2 = adjacentPos[i].y - piecePosInMapchip[_pieceNum2].y;

			/// ｘ座標比較
			if (piecePosInMapchip[_pieceNum1].x > piecePosInMapchip[_pieceNum2].x)
			{
				/// ピースの端一個手前まで
				while (temp1 + count1 < (*piece)[_pieceNum1].size() - 1 &&
					temp2 + count2 < (*piece)[_pieceNum2].size() - 1)
				{
					(*piece)[_pieceNum1][temp1 + count1++][0] = 2;
					(*piece)[_pieceNum2][temp2 + count2++][(*piece)[_pieceNum2][temp2 + count2].size() - 1] = 2;
				}
			}
			else if (piecePosInMapchip[_pieceNum1].x < piecePosInMapchip[_pieceNum2].x)
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
					if ((*_collision)[temp.y][temp.x] != 1)
						(*_collision)[temp.y][temp.x] = i + kTileKinds;
				}
			}
		}
	}
}

bool Piece::HindranceBlockCheck(const std::vector<std::vector<int>>* _field, int _x, int _y)
{
	if ((*_field)[_y][_x] == 3)	return true;
	return false;
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

bool Piece::IsInPiece(int _checkX, int _checkY, int _pieceNum)
{
	bool isHitEdges[4] = { false,0,0,0 };

	int x = _checkX - piecePosInMapchip[_pieceNum].x;
	int y = _checkY - piecePosInMapchip[_pieceNum].y;

	if (x < 0 ||
		y < 0 ||
		x >= pieceSize[_pieceNum].x ||
		y >= pieceSize[_pieceNum].y ||
		(*piece)[_pieceNum][y][x] == 1/*||
		(*piece)[_pieceNum][y][x] == 2*/
		)
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
				if (y - move < 0)
				{//pieceの端を超えた時
					isExit = true;
					break;
				}
				if ((*piece)[_pieceNum][y - move][x] != 0)
				{//走査中にpieceのブロックにあたったとき
					isHitEdges[0] = true;
				}

				break;
			case 1://左
				if (x - move < 0)
				{
					isExit = true;
					break;
				}
				if ((*piece)[_pieceNum][y][x - move] != 0)
				{
					isHitEdges[1] = true;
				}
				break;
			case 2://下
				if (y + move >= (*piece)[_pieceNum].size())
				{
					isExit = true;
					break;
				}
				if ((*piece)[_pieceNum][y + move][x] != 0)
				{
					isHitEdges[2] = true;
				}
				break;
			case 3://右
				if (x + move >= (*piece)[_pieceNum][y].size())
				{
					isExit = true;
					break;
				}
				if ((*piece)[_pieceNum][y][x + move] != 0)
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

void Piece::MoveOnCollision(const Vector2& _collisionDir, int _collidedNum)
{
	piecePos[_collidedNum - kTileKinds].x += _collisionDir.x * kTileSize;
	piecePos[_collidedNum - kTileKinds].y += _collisionDir.y * kTileSize;
}

Piece::Piece()
{
	pieceTexture = Novice::LoadTexture("./img/pieceBlock.png");
}

void Piece::Init()
{
	piece = CSV_Loader::GetPointerPiece();

	piecePos.resize(piece->size());
	piecePosInMapchip.resize(piece->size());
	pieceSize.resize(piece->size());
	scale.resize(piece->size());

	for (int i = 0; i < (*piece).size(); i++)
	{
		pieceSize[i] = { 0,0 };
		piecePos[i] = { kPieceStartKeyPos.x + i * kPieceStartMargin.x,kPieceStartKeyPos.y + i * kPieceStartMargin.y };
		scale[i] = 1.0f;

		for (int j = 0; j < (*piece)[i].size(); j++)
		{
			if (pieceSize[i].x < (*piece)[i][j].size())
				pieceSize[i].x = (float)(*piece)[i][j].size();
		}
		if (pieceSize[i].y < (*piece)[i].size())
			pieceSize[i].y = (float)(*piece)[i].size();
	}

	isHave = -1;
	p2mSub = { 0,0 };
}

void Piece::Update(const std::vector< std::vector<int>>* _field, std::vector< std::vector<int>>* _collision, const Vector2& _playerPos)
{
	adjacentPos.clear();
	adjacentDir.clear();

	PieceMove(_field, _playerPos);
	FieldCollision(_collision);
}

void Piece::Draw()
{
	//DrawPieceShadow();

	for (int i = 0; i < (*piece).size(); i++)
	{
		//Novice::ScreenPrintf(0, 1020 + i * 20, "%.1f,%.1f", pieceSize[i].x, pieceSize[i].y);
		//Novice::ScreenPrintf(900, 900 + i * 20, "%d,%d", piecePosInMapchip[i].x, piecePosInMapchip[i].y);

		for (int y = 0; y < (*piece)[i].size(); y++)
		{
			for (int x = 0; x < (*piece)[i][y].size(); x++)
			{
				if ((*piece)[i][y][x] == 1)
					Phill::DrawQuadPlus(int(piecePos[i].x + x * kTileSize * scale[i]), int(piecePos[i].y + y * kTileSize * scale[i]), int(kTileSize * scale[i]) - 1, int(kTileSize * scale[i]) - 1, 1.0f, 1.0f, 0.0f, (i % 7) * 120, 0, 120, 120, pieceTexture, 0xffffffda, PhillDrawMode::DrawMode_LeftTop);
			}
		}
	}

	for (int i = 0; i < adjacentPos.size(); i++)
	{
		//Novice::ScreenPrintf(1400, 720 + i * 20, "%d,%d", adjacentPos[i].x, adjacentPos[i].y);
		Novice::DrawBox(int(adjacentPos[i].x * kTileSize), int(adjacentPos[i].y * kTileSize), kTileSize, kTileSize, 0, RED, kFillModeWireFrame);
	}
}

