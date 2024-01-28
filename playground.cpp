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
	if (((*field)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] == BLOCK ||
		(*field)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize] == BLOCK ||
		(*field)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] == HINDRANCE ||
		(*field)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize] == HINDRANCE) &&
		player->moveDir.x < 0)
	{
		player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize + 1) * kTileSize + player->size.x / 2;
		player->velocity.x = 0;
	}
	if (((*field)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] == BLOCK ||
		(*field)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize] == BLOCK ||
		(*field)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] == HINDRANCE ||
		(*field)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize] == HINDRANCE) &&
		player->moveDir.x > 0)
	{
		player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize) * kTileSize - player->size.x / 2;
		player->velocity.x = 0;
	}
	if (((*field)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] == BLOCK ||
		(*field)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] == BLOCK ||
		(*field)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] == HINDRANCE ||
		(*field)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] == HINDRANCE) &&
		player->moveDir.y < 0)
	{
		player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize + 1) * kTileSize + player->size.y / 2;
		player->velocity.y = 0;
	}
	if (((*field)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == BLOCK ||
		(*field)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == BLOCK ||
		(*field)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == HINDRANCE ||
		(*field)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == HINDRANCE) &&
		player->moveDir.y > 0)
	{
		player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize) * kTileSize - player->size.y / 2;
		player->velocity.y = 0;
		player->isGround = true;
	}

	for (int i = 0; i < box.size(); i++)
	{
		if (player->pos.x + player->size.x / 2 >= box[i]->pos.x - box[i]->size.x / 2 &&
			player->pos.x - player->size.x / 2 <= box[i]->pos.x + box[i]->size.x / 2 &&
			player->pos.y + player->size.y / 2 >= box[i]->pos.y - box[i]->size.y / 2 &&
			player->pos.y - player->size.y / 2 <= box[i]->pos.y + box[i]->size.y / 2 &&
			player->pos.y - box[i]->pos.y < -box[i]->size.y / 2)
		{
			if (((*field)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize + 1][int(player->pos.x + player->vertex[2].x) / kTileSize] == BLOCK ||
				(*field)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize + 1][int(player->pos.x + player->vertex[3].x) / kTileSize] == BLOCK ||
				(*field)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize + 1][int(player->pos.x + player->vertex[2].x) / kTileSize] == HINDRANCE ||
				(*field)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize + 1][int(player->pos.x + player->vertex[3].x) / kTileSize] == HINDRANCE) &&
				player->moveDir.y > 0)
			{
				player->pos.y = box[i]->pos.y - (box[i]->size.y / 2 * player->moveDir.y) - (player->size.y / 2 * player->moveDir.y);
				player->velocity.y = 0;
				player->isGround = true;
			}
		}
	}


	player->PosUpdate();

	GoalCheck();
	SpineHitCheck();
}

void Playground::CollisionWithBox()
{
	for (int i = 0; i < box.size(); i++)
	{
		if (((*field)[int(box[i]->pos.y + box[i]->vertex[0].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[0].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->vertex[2].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[2].x) / kTileSize] != AIR) &&
			box[i]->moveDir.x < 0)
		{
			box[i]->pos.x = (int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[0].x) / kTileSize + 1) * kTileSize + box[i]->size.x / 2;
			box[i]->velocity.x = 0;
		}
		if (((*field)[int(box[i]->pos.y + box[i]->vertex[1].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[1].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->vertex[3].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[3].x) / kTileSize] != AIR) &&
			box[i]->moveDir.x > 0)
		{
			box[i]->pos.x = (int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[1].x) / kTileSize) * kTileSize - box[i]->size.x / 2;
			box[i]->velocity.x = 0;
		}
		if (((*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[0].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[0].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[1].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[1].x) / kTileSize] != AIR) &&
			box[i]->moveDir.y < 0)
		{
			box[i]->pos.y = (int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[0].y) / kTileSize + 1) * kTileSize + box[i]->size.y / 2;
			box[i]->velocity.y = 0;
		}
		if (((*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[2].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[2].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[3].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[3].x) / kTileSize] != AIR) &&
			box[i]->moveDir.y > 0)
		{
			box[i]->pos.y = (int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[2].y) / kTileSize) * kTileSize - box[i]->size.y / 2;
			box[i]->velocity.y = 0;
		}
		box[i]->PosUpdate();
	}
}

void Playground::CollisionPlayerWithBox()
{
	for (int i = 0; i < box.size(); i++)
	{
		if (player->pos.x - player->size.x / 2.0f <= box[i]->pos.x + box[i]->size.x / 2.0f &&
			player->pos.x + player->size.x / 2.0f >= box[i]->pos.x - box[i]->size.x / 2.0f &&
			player->pos.y - player->size.y / 2.0f <= box[i]->pos.y + box[i]->size.y / 2.0f &&
			player->pos.y + player->size.y / 2.0f >= box[i]->pos.y - box[i]->size.y / 2.0f)
		{
			player->isOnBox = true;

			/// プレイヤーが箱の上辺より下にいるとき
			if (player->pos.y > box[i]->pos.y - box[i]->size.y / 2.0f && player->moveDir.x != 0)
			{
				box[i]->velocity.x = player->velocity.x;
				box[i]->pos.x += box[i]->velocity.x;
				box[i]->moveDir.x = player->moveDir.x;
			}
			else if (player->moveDir.y > 0 && player->pos.y - box[i]->pos.y < -box[i]->size.y / 2)
			{
				player->pos.y = box[i]->pos.y - (box[i]->size.y / 2 * player->moveDir.y) - (player->size.y / 2 * player->moveDir.y);
				box[i]->velocity.y = player->velocity.y;
				player->isGround = true;
			}
		}
	}
}

void Playground::CollisionPlayerWithPiece()
{
	piece->moveDir = { 0,0 };
	Vector2 collisionDir = { 0,0 };
	int collidedNum = -1;
	int collidedBoxNum = -1;

	collidedNum = piece->PixelCollisionWithObj(player->pos, player->vertex, collisionDir);

	if (collidedNum != -1)
	{
		piece->MoveOnCollision(collisionDir, collidedNum + kTileKinds, player->velocity);

		if (collisionDir.x < 0)
			player->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + kTileSize + player->vertex[1].x + 1;
		if (collisionDir.x > 0)
			player->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + player->vertex[0].x - 1;
		if (collisionDir.y < 0)
			player->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + kTileSize + player->vertex[2].y + 1;
		if (collisionDir.y > 0)
			player->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + player->vertex[0].y - 1;
	}
	else
	{
		for (int i = 0; i < box.size(); i++)
		{
			if (player->pos.x + player->size.x / 2 >= box[i]->pos.x - box[i]->size.x / 2 &&
				player->pos.x - player->size.x / 2 <= box[i]->pos.x + box[i]->size.x / 2 &&
				player->pos.y + player->size.y / 2 >= box[i]->pos.y - box[i]->size.y / 2 &&
				player->pos.y - player->size.y / 2 <= box[i]->pos.y + box[i]->size.y / 2 ||
				player->isOnBox)
			{
				Vector2 localPos = box[i]->pos;
				localPos.x += box[i]->velocity.x;
				localPos.y += box[i]->velocity.y;

				collidedBoxNum = i;

				collidedNum = piece->PixelCollisionWithObj(localPos, box[i]->vertex, collisionDir);
				break;
			}
		}
		if (collidedNum != -1)
		{
			piece->MoveOnCollision(collisionDir, collidedNum + kTileKinds, box[collidedBoxNum]->velocity);

			if (collisionDir.x < 0)
				box[collidedBoxNum]->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + kTileSize + box[collidedBoxNum]->vertex[1].x + 1;
			if (collisionDir.x > 0)
				box[collidedBoxNum]->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + box[collidedBoxNum]->vertex[0].x - 1;
			if (collisionDir.y < 0)
				box[collidedBoxNum]->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + kTileSize + box[collidedBoxNum]->vertex[2].y + 1;
			if (collisionDir.y > 0)
				box[collidedBoxNum]->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + box[collidedBoxNum]->vertex[0].y - 1;

		}
	}

	CollisionReset();
	piece->FieldCollision(collision);
}

void Playground::CollisionPieceWithBox()
{
	for (int i = 0; i < box.size(); i++)
	{
		Vector2 collisionDir = { 0,0 };
		int collidedNum = piece->PixelCollisionWithObj(box[i]->pos, box[i]->vertex, collisionDir);

		if (collidedNum != -1)
		{
			if (collisionDir.x < 0)
				box[i]->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + kTileSize + box[i]->vertex[1].x + 1;
			if (collisionDir.x > 0)
				box[i]->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + box[i]->vertex[0].x - 1;
			if (collisionDir.y < 0)
				box[i]->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + kTileSize + box[i]->vertex[2].y + 1;
			if (collisionDir.y > 0)
			{
				box[i]->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + box[i]->vertex[0].y - 1;
				box[i]->velocity.y = 0;
			}
		}
	}
}

void Playground::CollisionWithPiece()
{

}

void Playground::CollisionReset()
{
	collision->clear();
	collision = new std::vector<std::vector<int>>(*field);
}


void Playground::GoalCheck()
{
	if (
		(*field)[int(player->pos.y) / kTileSize][int(player->pos.x) / kTileSize] == 2 ||
		(*field)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] == 2 ||
		(*field)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] == 2 ||
		(*field)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == 2 ||
		(*field)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == 2
		)
	{
		isClear = true;
	}
}

void Playground::SpineHitCheck()
{
	if (
		(*field)[int(player->pos.y) / kTileSize][int(player->pos.x) / kTileSize] == 5 ||
		(*field)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] == 5 ||
		(*field)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] == 5 ||
		(*field)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == 5 ||
		(*field)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == 5
		)
	{
		player->isAlive = false;
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
	/// ctrl + enter でコマ送りモード
	if (_keys[DIK_RETURN] && !_preKeys[DIK_RETURN] && _keys[DIK_LCONTROL])
		frameSlow = frameSlow ? false : true;

	/// コマ送りモードは入力しながらenter
	if (!frameSlow || _keys[DIK_RETURN] && !_preKeys[DIK_RETURN])
	{
		CollisionReset();
		piece->Update(field, collision, player->pos);
		for (int i = 0; i < box.size(); i++)
			box[i]->Update();
		player->Update(_keys, _preKeys);

		/// 衝突判定たち
		CollisionWithPlayer();
		CollisionWithBox();
		CollisionPlayerWithBox();
		CollisionPlayerWithPiece();
		CollisionPieceWithBox();
		CollisionPlayerWithBox();
		CollisionPlayerWithPiece();
		//CollisionWithBox();
		//CollisionPlayerWithPiece();
		//CollisionWithBox();
	}


	//if ((*collision)[int(player->pos.y + player->vertex[2].y + 1) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] != 0 ||
	//	(*collision)[int(player->pos.y + player->vertex[3].y + 1) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] != 0)
	//{
	//	player->isGround = true;
	//}
	//else player->isGround = false;
	////無駄なことしてる自覚はあるが現状これしか思いつかないので
	//for (int i = 0; i < box.size(); i++)
	//{
	//	if (player->pos.x - player->size.x / 2 < box[i]->pos.x + box[i]->size.x / 2 - 1 &&
	//		player->pos.x + player->size.x / 2 - 1 > box[i]->pos.x - box[i]->size.x / 2)
	//	{
	//		if ((player->pos.y + player->size.y / 2 - 1) - (box[i]->pos.y - box[i]->size.y / 2) <= 0 &&
	//			(player->pos.y + player->size.y / 2 - 1) - (box[i]->pos.y - box[i]->size.y / 2) >= -1.5f)
	//			player->isGround = true;
	//	}
	//}

	if (_keys[DIK_R] && _preKeys[DIK_R] || !player->isAlive)
	{
		isClear = true;
		selectStage--;
	}

	/// shift + enter で次のステージ
	if (isClear || _keys[DIK_RETURN] && !_preKeys[DIK_RETURN] && _keys[DIK_LSHIFT])
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
				if ((*field)[y][x] == 1)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 7 * 64, 0, 64, 64, blockTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				else if ((*field)[y][x] == 2)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, goalTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				else if ((*field)[y][x] == 3)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, obstacleTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);
				else if ((*field)[y][x] == 5)///とげ
					Novice::DrawBox(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 0, 0x2020d0ff, kFillModeSolid);

				else if ((*field)[y][x] != 9 /*&& (*field)[y][x] != 0*/)
					Novice::DrawBox(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 0, kTileColor_[(*field)[y][x]], kFillModeSolid);
			}
			Novice::ScreenPrintf(1000 + x * 20, y * 20, "%d", (*collision)[y][x]);
		}
	}

	for (int i = 0; i < box.size(); i++)
		box[i]->Draw();
	piece->Draw();
	player->Draw();
}
