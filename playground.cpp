#include "playground.h"

#include "PhilliaFunction/Phill.h"	
#include "CSVLoader.h"
#include <Novice.h>
#include "definition.h"

#include "piece.h"
#include "player.h"
#include "box.h"


void Playground::CollisionWithPlayer()
{
	if (((*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] == 1 ||
		(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize] == 1) &&
		player->moveDir.x < 0)
	{
		player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize + 1) * kTileSize + player->size.x / 2;
		player->velocity.x = 0;
	}
	if (((*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] == 1 ||
		(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize] == 1) &&
		player->moveDir.x > 0)
	{
		player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize) * kTileSize - player->size.x / 2;
		player->velocity.x = 0;
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] == 1 ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] == 1) &&
		player->moveDir.y < 0)
	{
		player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize + 1) * kTileSize + player->size.y / 2;
		player->velocity.y = 0;
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == 1 ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == 1) &&
		player->moveDir.y > 0)
	{
		player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize) * kTileSize - player->size.y / 2;
		player->velocity.y = 0;
		player->isGround = true;
	}


}


void Playground::PiecePlayerCollision()
{
	piece->moveDir = { 0,0 };
	Vector2 collisionDir = { 0,0 };
	int collidedNum = -1;

	if (((*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] >= kTileKinds ||
		(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize] >= kTileKinds) &&
		player->moveDir.x < 0)
	{
		collisionDir.x = player->moveDir.x;
		collidedNum =
			(*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] >= kTileKinds ?
			(*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - kTileKinds))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize + 1) * kTileSize + player->size.x / 2;
			player->velocity.x = 0;
		}
	}
	if (((*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] >= kTileKinds ||
		(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize] >= kTileKinds) &&
		player->moveDir.x > 0)
	{
		collisionDir.x = player->moveDir.x;
		collidedNum =
			(*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] >= kTileKinds ?
			(*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - kTileKinds))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize) * kTileSize - player->size.x / 2;
			player->velocity.x = 0;
		}
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] >= kTileKinds ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] >= kTileKinds) &&
		player->moveDir.y < 0)
	{
		collisionDir.y = player->moveDir.y;
		collidedNum =
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] >= kTileKinds ?
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - kTileKinds))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize + 1) * kTileSize + player->size.y / 2;
			player->velocity.y = 0;
		}
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] >= kTileKinds ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] >= kTileKinds) &&
		player->moveDir.y > 0)
	{
		collisionDir.y = player->moveDir.y;
		collidedNum =
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] >= kTileKinds ?
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - kTileKinds))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize) * kTileSize - player->size.y / 2;
			player->velocity.y = 0;
			player->isGround = true;
		}
	}
}

void Playground::BoxPieceCollision()
{
	intVec2 check;
	check.x = (int)piece->moveDir.x;
	check.y = (int)piece->moveDir.y;

	for (int i = 0; i < (*piece->piece).size(); i++)
	{
		for (int y = 0; y < (*piece->piece)[i].size(); y++)
		{
			for (int x = 0; x < (*piece->piece)[i][y].size(); x++)
			{
				if (piece->piecePosInMapchip[i].x < kStageAreaWidth / kTileSize &&
					(*piece->piece)[i][y][x] == 1)
				{
					bool isExit = false;

					for (int j = 0; j < box.size(); j++)
					{
						if (box[j]->posInMapchip.x == piece->piecePosInMapchip[i].x + x + check.x &&
							box[j]->posInMapchip.y == piece->piecePosInMapchip[i].y + y + check.y)
						{
							if (box[j]->CanMove(collision, piece->moveDir))
							{
								box[j]->pos.x += piece->moveDir.x * kTileSize;
								box[j]->pos.y += piece->moveDir.y * kTileSize;
								box[j]->moveDir = piece->moveDir;
							}
							else
							{
								piece->piecePos[i].x -= piece->moveDir.x * kTileSize;
								piece->piecePos[i].y -= piece->moveDir.y * kTileSize;
							}
							isExit = true;
							break;
						}

					}
					if (isExit)
						break;
				}

			}
		}
	}
}

void Playground::BoxBoxCollision()
{
	for (int i = 0; i < box.size() - 1; i++)
	{
		for (int j = i + 1; j < box.size(); j++)
		{
			if (i == j)
				continue;

			if (box[i]->posInMapchip.x == box[j]->posInMapchip.x &&
				box[i]->posInMapchip.y == box[j]->posInMapchip.y)
			{
				if (box[i]->moveDir.x != 0 || box[i]->moveDir.y != 0)
				{
					box[i]->pos.x -= box[i]->moveDir.x * kTileSize + box[i]->moveDir.x * box[i]->size.x / 2;
					box[i]->pos.y -= box[i]->moveDir.y * kTileSize + box[i]->moveDir.y * box[i]->size.y / 2;
					box[i]->velocity = { 0,0 };
				}
				else if (box[j]->moveDir.x != 0 || box[j]->moveDir.y != 0)
				{
					box[j]->pos.x -= box[j]->moveDir.x * kTileSize;
					box[j]->pos.y -= box[j]->moveDir.y * kTileSize;
					box[j]->velocity = { 0,0 };
				}
			}

			/*if (box[i]->pos.x - box[i]->size.x / 2 < box[j]->pos.x + box[j]->size.x / 2 - 1 &&
				box[i]->pos.x + box[i]->size.x / 2 - 1 > box[j]->pos.x - box[j]->size.x / 2 &&
				box[i]->pos.y - box[i]->size.y / 2 < box[j]->pos.y + box[j]->size.y / 2 - 1 &&
				box[i]->pos.y + box[i]->size.y / 2 - 1 > box[j]->pos.y - box[j]->size.y / 2)
			{
				if (box[i]->moveDir.x != 0 || box[i]->moveDir.y != 0)
				{
					box[i]->pos.x -= box[i]->moveDir.x * kTileSize;
					box[i]->pos.y -= box[i]->moveDir.y * kTileSize;
					box[i]->velocity = { 0,0 };
				}
				else if (box[j]->moveDir.x != 0 || box[j]->moveDir.y != 0)
				{
					box[j]->pos.x -= box[j]->moveDir.x * kTileSize;
					box[j]->pos.y -= box[j]->moveDir.y * kTileSize;
					box[j]->velocity = { 0,0 };
				}
			}*/
		}
	}
}


void Playground::GoalCheck()
{
	if (
		(*collision)[int(player->pos.y) / kTileSize][int(player->pos.x) / kTileSize] == 2 ||
		(*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] == 2 ||
		(*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] == 2 ||
		(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == 2 ||
		(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == 2
		)
	{
		isClear = true;
	}
}

Playground::Playground()
{
	piece = new Piece;
	player = new Player;

	blockTexture = Novice::LoadTexture("./img/block.png");
	goalTexture = Novice::LoadTexture("./img/goal.png");
	obstacleTexture = Novice::LoadTexture("./img/obstacleBlock.png");
}

void Playground::Init(int _stageNo)
{
	CSV_Loader::LoadFromCSV_s(stageFilePath[_stageNo], '\n');
	selectStage = _stageNo;

	field = CSV_Loader::GetPointerMapchip();
	collision = new std::vector<std::vector<int>>(*field);

	box.clear();
	piece->Init();
	for (int y = 0; y < field->size(); y++)
	{
		for (int x = 0; x < field->size(); x++)
		{
			if ((*field)[y][x] == 4)
			{
				box.push_back(new Box(x, y));
				(*field)[y][x] = 0;
			}
			else if ((*field)[y][x] >= 10)
			{
				piece->PiecePosInit(x, y);
				(*field)[y][x] %= 10;
			}
			else (*collision)[y][x] = (*field)[y][x];
		}
	}

	isClear = false;


	player->Init(selectStage);
}

void Playground::Update(const char* _keys, const char* _preKeys)
{
	collision->clear();
	collision = new std::vector<std::vector<int>>(*field);

	piece->Update(field, collision, player->pos);
	for (int i = 0; i < box.size(); i++)
		//if (_keys[DIK_SPACE] && !_preKeys[DIK_SPACE])
		box[i]->Update();
	player->Update(_keys, _preKeys);

	CollisionWithPlayer();
	PiecePlayerCollision();
	for (int i = 0; i < box.size(); i++)
	{
		box[i]->CollisionWithPlayer(player->pos, player->size, player->velocity, player->isGround);
		box[i]->CollisionWithField(collision);
		box[i]->PosUpdate();
	}
	BoxBoxCollision();
	player->MoveDirUpdate();
	BoxPieceCollision();
	player->PosUpdate();

	if ((*collision)[int(player->pos.y + player->vertex[2].y + 1) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] != 0 ||
		(*collision)[int(player->pos.y + player->vertex[3].y + 1) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] != 0)
	{
		player->isGround = true;
	}
	else player->isGround = false;
	//無駄なことしてる自覚はあるが現状これしか思いつかないので
	for (int i = 0; i < box.size(); i++)
	{
		if (player->pos.x - player->size.x / 2 < box[i]->pos.x + box[i]->size.x / 2 - 1 &&
			player->pos.x + player->size.x / 2 - 1 > box[i]->pos.x - box[i]->size.x / 2)
		{
			if ((player->pos.y + player->size.y / 2 - 1) - (box[i]->pos.y - box[i]->size.y / 2) <= 0 &&
				(player->pos.y + player->size.y / 2 - 1) - (box[i]->pos.y - box[i]->size.y / 2) >= -1.5f)
				player->isGround = true;
		}
	}
	GoalCheck();

	if (_keys[DIK_R] && _preKeys[DIK_R])
	{
		isClear = true;
		selectStage--;
	}

	if (isClear || _keys[DIK_RETURN] &&!_preKeys[DIK_RETURN] && _keys[DIK_LSHIFT])
	{
		selectStage++;
		if (selectStage >= kMaxStage)
			selectStage = 0;
		Init(selectStage);
	}
}

void Playground::Draw()
{
	for (int y = 0; y < (*field).size(); y++)
	{
		for (int x = 0; x < (*field)[y].size(); x++)
		{
			if ((*field)[y][x] != 9)
			{

				if ((*field)[y][x] != 9 && (*field)[y][x] != 2)
					Novice::DrawBox(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 0, kTileColor_[(*field)[y][x]], kFillModeSolid);
				if ((*field)[y][x] == 1)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 7 * 64, 0, 64, 64, blockTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				if ((*field)[y][x] == 2)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, goalTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				if ((*field)[y][x] == 3)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, obstacleTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);
			}
			//Novice::ScreenPrintf(1000 + x * 20, y * 20, "%d", (*collision)[y][x]);

		}
	}

	for (int i = 0; i < box.size(); i++)
		box[i]->Draw();
	piece->Draw();
	player->Draw();
}
