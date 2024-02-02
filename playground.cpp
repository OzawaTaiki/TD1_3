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
		if (!box[i]->isDraw)
			continue;

		if (player->pos.x + player->size.x / 2 >= box[i]->pos.x - box[i]->size.x / 2 &&
			player->pos.x - player->size.x / 2 <= box[i]->pos.x + box[i]->size.x / 2 &&
			player->pos.y + player->size.y / 2 >= box[i]->pos.y - box[i]->size.y / 2 &&
			player->pos.y - player->size.y / 2 <= box[i]->pos.y + box[i]->size.y / 2 &&
			player->pos.y - box[i]->pos.y < -box[i]->size.y / 2)
		{
			if (((*field)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize + 1][int(player->pos.x + player->vertex[2].x) / kTileSize] == BLOCK ||
				(*field)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize + 1][int(player->pos.x + player->vertex[3].x) / kTileSize] == BLOCK ||
				(*field)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize + 1][int(player->pos.x + player->vertex[2].x) / kTileSize] == HINDRANCE ||
				(*field)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize + 1][int(player->pos.x + player->vertex[3].x) / kTileSize] == HINDRANCE ||
				(*field)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize + 1][int(player->pos.x + player->vertex[2].x) / kTileSize] == SPINE ||
				(*field)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize + 1][int(player->pos.x + player->vertex[3].x) / kTileSize] == SPINE) &&
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
		if (!box[i]->isDraw)
			continue;

		/// 左の判定
		if (((*field)[int(box[i]->pos.y + box[i]->vertex[0].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[0].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->vertex[2].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[2].x) / kTileSize] != AIR) &&
			box[i]->moveDir.x < 0)
		{
			box[i]->pos.x = (int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[0].x) / kTileSize + 1) * kTileSize + box[i]->size.x / 2;
			box[i]->velocity.x = 0;
			box[i]->isLockedX = true;
		}
		/// 右の判定
		if (((*field)[int(box[i]->pos.y + box[i]->vertex[1].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[1].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->vertex[3].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[3].x) / kTileSize] != AIR) &&
			box[i]->moveDir.x > 0)
		{
			box[i]->pos.x = (int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[1].x) / kTileSize) * kTileSize - box[i]->size.x / 2;
			box[i]->velocity.x = 0;
			box[i]->isLockedX = true;
		}
		/// 上の判定
		if (((*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[0].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[0].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[1].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[1].x) / kTileSize] != AIR) &&
			box[i]->moveDir.y < 0)
		{
			box[i]->pos.y = (int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[0].y) / kTileSize + 1) * kTileSize + box[i]->size.y / 2;
			box[i]->velocity.y = 0;
			box[i]->isLockedY = true;
		}
		/// 下の判定
		if (((*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[2].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[2].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[3].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[3].x) / kTileSize] != AIR) &&
			box[i]->moveDir.y > 0)
		{
			box[i]->pos.y = (int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[2].y) / kTileSize) * kTileSize - box[i]->size.y / 2;
			box[i]->velocity.y = 0;
			box[i]->moveDir.y = 0;
			box[i]->isLockedY = true;
		}
		box[i]->PosUpdate();
	}
}

void Playground::CollisionPlayerWithBox()
{
	for (int i = 0; i < box.size(); i++)
	{
		if (!box[i]->isDraw)
			continue;

		if (player->pos.x - player->size.x / 2.0f < box[i]->pos.x + box[i]->size.x / 2.0f &&
			player->pos.x + player->size.x / 2.0f > box[i]->pos.x - box[i]->size.x / 2.0f &&
			player->pos.y - player->size.y / 2.0f < box[i]->pos.y + box[i]->size.y / 2.0f &&
			player->pos.y + player->size.y / 2.0f > box[i]->pos.y - box[i]->size.y / 2.0f)
		{
			box[i]->isOnPlayer = true;

			if (!plbo)
			{
				if (player->pos.y > box[i]->pos.y - box[i]->size.y / 2.0f && player->moveDir.x != 0)
				{
					box[i]->velocity.x = player->velocity.x;
					box[i]->moveDir.x = player->moveDir.x;
				}
				else if (player->moveDir.y > 0 && player->pos.y - box[i]->pos.y < -box[i]->size.y / 2)
				{
					box[i]->velocity.y = player->velocity.y;
					box[i]->moveDir.y = player->moveDir.y;

				}
				box[i]->PosUpdate();
			}
			else
			{
				if (player->pos.y > box[i]->pos.y - box[i]->size.y / 2.0f && player->moveDir.x != 0)
				{
					if (player->moveDir.x < 0)
						player->pos.x = box[i]->pos.x + box[i]->size.x / 2 + player->size.x / 2 + 1;
					if (player->moveDir.x > 0)
						player->pos.x = box[i]->pos.x - box[i]->size.x / 2 - player->size.x / 2 - 1;
				}
				else if (player->moveDir.y > 0 && player->pos.y - box[i]->pos.y < -box[i]->size.y / 2)
				{
					if (player->moveDir.y < 0 && player->pos.y > box[i]->pos.y + box[i]->size.y / 2.0f)
						player->pos.y = box[i]->pos.y + box[i]->size.y / 2 + player->size.y / 2;
					if (player->moveDir.y > 0 && player->pos.y < box[i]->pos.y - box[i]->size.y / 2.0f)
						player->pos.y = box[i]->pos.y - box[i]->size.y / 2 - player->size.y / 2;
				}
			}
			//box[i]->isOnPlayer = true;
			//
			//if (box[i]->isLockedX || box[i]->isLockedY)
			//{
			//	if (box[i]->isLockedX)
			//	{
			//		if (player->moveDir.x < 0)
			//			player->pos.x = box[i]->pos.x + box[i]->size.x / 2 + player->size.x / 2 + 1;
			//		if (player->moveDir.x > 0)
			//			player->pos.x = box[i]->pos.x - box[i]->size.x / 2 - player->size.x / 2 - 1;
			//	}
			//	if (box[i]->isLockedY)
			//	{
			//		if (player->moveDir.y < 0 && player->pos.y > box[i]->pos.y + box[i]->size.y / 2.0f)
			//			player->pos.y = box[i]->pos.y + box[i]->size.y / 2 + player->size.y / 2;
			//		if (player->moveDir.y > 0 && player->pos.y < box[i]->pos.y - box[i]->size.y / 2.0f)
			//			player->pos.y = box[i]->pos.y - box[i]->size.y / 2 - player->size.y / 2;
			//	}
			//}
			//else
			//{/// プレイヤーが箱の上辺より下にいるとき
			//	if (player->pos.y > box[i]->pos.y - box[i]->size.y / 2.0f && player->moveDir.x != 0)
			//	{
			//		box[i]->velocity.x = player->velocity.x;
			//		box[i]->pos.x += box[i]->velocity.x;
			//		box[i]->moveDir.x = player->moveDir.x;
			//	}
			//	else if (player->moveDir.y > 0 && player->pos.y - box[i]->pos.y < -box[i]->size.y / 2)
			//	{
			//		player->pos.y = box[i]->pos.y - (box[i]->size.y / 2 * player->moveDir.y) - (player->size.y / 2 * player->moveDir.y);
			//		box[i]->velocity.y = player->velocity.y;
			//	}
			//	//box[i]->Clamp();
			//	//CollisionWithBox();
			//}
		}
	}
	plbo = true;
}

void Playground::CollisionPlayerWithPiece()
{
	piece->moveDir = { 0,0 };
	Vector2 collisionDir = { 0,0 };
	int collidedNum = -1;
	//int collidedBoxNum = -1;

	collidedNum = piece->PixelCollisionWithObj(player->pos, player->vertex, collisionDir);

	if (collidedNum != -1)
	{
		if (!plpi)
			piece->MoveOnCollision(collisionDir, collidedNum + kTileKinds, player->velocity);
		else
		{
			if (collisionDir.x < 0)
				player->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + kTileSize + player->vertex[1].x;
			if (collisionDir.x > 0)
				player->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + player->vertex[0].x;
			if (collisionDir.y < 0)
				player->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + kTileSize + player->vertex[2].y;
			if (collisionDir.y > 0)
			{
				player->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + player->vertex[0].y;
				player->isGround = true;
			}
		}
	}
	else
	{
		collisionDir = { 0,0 };
		collidedNum = piece->PixelCollisionWithObjOutSide(player->pos, player->vertex, collisionDir);

		if (collidedNum != -1)
		{
			if (!plpi)
				piece->MoveOnCollision(collisionDir, collidedNum + kTileKinds, player->velocity);

			else
			{
				if (collisionDir.x < 0)
					player->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + kTileSize + player->vertex[1].x;
				if (collisionDir.x > 0)
					player->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + player->vertex[0].x;
				if (collisionDir.y < 0)
					player->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + kTileSize + player->vertex[2].y;
				if (collisionDir.y > 0)
					player->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + player->vertex[0].y;
			}
		}
		/// piece-player間に箱があるときの処理
		else
		{
			int i;
			for (i = 0; i < box.size(); i++)
			{
				if (player->pos.x - player->size.x / 2.0f <= box[i]->pos.x + box[i]->size.x / 2.0f &&
					player->pos.x + player->size.x / 2.0f >= box[i]->pos.x - box[i]->size.x / 2.0f &&
					player->pos.y - player->size.y / 2.0f <= box[i]->pos.y + box[i]->size.y / 2.0f &&
					player->pos.y + player->size.y / 2.0f >= box[i]->pos.y - box[i]->size.y / 2.0f ||
					box[i]->isOnPlayer)
				{
					collisionDir = { 0,0 };
					collidedNum = piece->PixelCollisionWithObj(box[i]->pos, box[i]->vertex, collisionDir);

					if (collidedNum != -1)
					{
						if (collisionDir.x < 0)
							piece->piecePos[collidedNum].x = box[i]->pos.x - piece->runX * kTileSize - box[i]->size.x / 2 - kTileSize;
						if (collisionDir.x > 0)
							piece->piecePos[collidedNum].x = box[i]->pos.x - piece->runX * kTileSize + box[i]->size.x / 2;
						if (collisionDir.y < 0)
							piece->piecePos[collidedNum].y = box[i]->pos.y + piece->runY * kTileSize + kTileSize + box[i]->vertex[2].y;
						if (collisionDir.y > 0)
							piece->piecePos[collidedNum].y = box[i]->pos.y - piece->runY * kTileSize + box[i]->size.y / 2;
					}
				}
			}
		}
	}
	plpi = true;
	//CollisionReset();
	//piece->FieldCollision(collision);
}

void Playground::CollisionPieceWithBox()
{
	for (int i = 0; i < box.size(); i++)
	{
		if (!box[i]->isDraw)
			continue;
		Vector2 collisionDir = { 0,0 };
		int collidedNum = piece->PixelCollisionWithObj(box[i]->pos, box[i]->vertex, collisionDir);

		if (collidedNum != -1)
		{
			if (!pibo)
			{
				//if (collisionDir.y != 1)
				//piece->MoveOnCollision(collisionDir, collidedNum + kTileKinds, box[i]->velocity);

				if (collisionDir.x < 0)
					box[i]->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + kTileSize + box[i]->vertex[1].x + 1;
				if (collisionDir.x > 0)
					box[i]->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + box[i]->vertex[0].x;
				if (collisionDir.y < 0)
					box[i]->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + kTileSize + box[i]->vertex[2].y + 1;
				if (collisionDir.y > 0 && !box[i]->isLockedY)
				{
					box[i]->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + box[i]->vertex[0].y - 1;
					box[i]->velocity.y = 0;
				}
				box[i]->moveDir.x = collisionDir.x * -1;
				box[i]->moveDir.y = collisionDir.y * -1;
			}
			else
			{
				if (collisionDir.x < 0)
					piece->piecePos[collidedNum].x = box[i]->pos.x - box[i]->size.x / 2 - (piece->runX + 1) * kTileSize;
				if (collisionDir.x > 0)
					piece->piecePos[collidedNum].x = box[i]->pos.x + box[i]->size.x / 2 - piece->runX * kTileSize;
				if (collisionDir.y < 0)
					piece->piecePos[collidedNum].y = box[i]->pos.y - box[i]->size.y / 2 - (piece->runY + 1) * kTileSize;
				if (collisionDir.y > 0)
					piece->piecePos[collidedNum].y = box[i]->pos.y + box[i]->size.y / 2 - piece->runY * kTileSize;
			}

			/* /// 埋まってないとき
			if (!isFill(check, box[i]->vertex))
			{
				box[i]->pos = check;
			}
			 埋まってるとき
			else
			{
				box[i]->isLockedX = true;
				box[i]->isLockedY = true;

				if (collisionDir.x < 0)
					piece->piecePos[collidedNum].x = box[i]->pos.x - box[i]->size.x / 2 - (piece->runX + 1) * kTileSize;
				if (collisionDir.x > 0)
					piece->piecePos[collidedNum].x = box[i]->pos.x + box[i]->size.x / 2 - piece->runX * kTileSize;
				if (collisionDir.y < 0)
					piece->piecePos[collidedNum].y = box[i]->pos.y - box[i]->size.y / 2 - (piece->runY + 1) * kTileSize;
				if (collisionDir.y > 0)
					piece->piecePos[collidedNum].y = box[i]->pos.y + box[i]->size.y / 2 - piece->runY * kTileSize;
			}*/
		}
		else
		{
			collidedNum = piece->PixelCollisionWithObjOutSide(box[i]->pos, box[i]->vertex, collisionDir);

			if (collidedNum != -1)
			{
				if (!pibo)
				{
					//if (collisionDir.y != 1)
					if (collisionDir.x < 0)
						piece->piecePos[collidedNum].x = box[i]->pos.x - box[i]->size.x / 2 - (piece->runX + 1) * kTileSize;
					if (collisionDir.x > 0)
						piece->piecePos[collidedNum].x = box[i]->pos.x + box[i]->size.x / 2 - piece->runX * kTileSize;
					if (collisionDir.y < 0)
						piece->piecePos[collidedNum].y = box[i]->pos.y - box[i]->size.y / 2 - (piece->runY + 1) * kTileSize;
					if (collisionDir.y > 0)
						piece->piecePos[collidedNum].y = box[i]->pos.y + box[i]->size.y / 2 - piece->runY * kTileSize;

					//piece->MoveOnCollision(collisionDir, collidedNum + kTileKinds, box[i]->velocity);

				}
				else
				{
					if (collisionDir.x < 0)
						box[i]->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + kTileSize + box[i]->vertex[1].x + 1;
					if (collisionDir.x > 0)
						box[i]->pos.x = piece->piecePos[collidedNum].x + piece->runX * kTileSize + box[i]->vertex[0].x;
					if (collisionDir.y < 0)
						box[i]->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + kTileSize + box[i]->vertex[2].y + 1;
					if (collisionDir.y > 0)
					{
						box[i]->pos.y = piece->piecePos[collidedNum].y + piece->runY * kTileSize + box[i]->vertex[0].y - 1;
						box[i]->velocity.y = 0;
					}
				}

				/*if (!isFill(check, box[i]->vertex))
				{
					box[i]->pos = check;
				}
				else
				{
					box[i]->isLockedY = true;
					box[i]->isLockedX = true;

					if (collisionDir.x < 0)
						piece->piecePos[collidedNum].x = box[i]->pos.x - box[i]->size.x / 2 - (piece->runX + 1) * kTileSize;
					if (collisionDir.x > 0)
						piece->piecePos[collidedNum].x = box[i]->pos.x + box[i]->size.x / 2 + (piece->runX - 1) * kTileSize;
					if (collisionDir.y < 0)
						piece->piecePos[collidedNum].y = box[i]->pos.y - box[i]->size.y / 2 - (piece->runY + 1) * kTileSize;
					if (collisionDir.y > 0)
						piece->piecePos[collidedNum].y = box[i]->pos.y + box[i]->size.y / 2 + (piece->runY - 1) * kTileSize;
				}*/
			}
		}
	}
	pibo = true;
}

//void Playground::CollisionBoxWithBox()
//{
//	for (int i = 0; i < box.size(); i++)
//	{
//		if (!box[i]->isDraw)
//			continue;
//		for (int k = i; k < box.size(); k++)
//		{
//			if (!box[k]->isDraw || i == k)
//				continue;
//			if (box[i]->pos.x - box[i]->size.x / 2 < box[k]->pos.x + box[k]->size.x / 2 &&
//				box[i]->pos.x + box[i]->size.x / 2 > box[k]->pos.x - box[k]->size.x / 2 &&
//				box[i]->pos.y - box[i]->size.y / 2 < box[k]->pos.y + box[k]->size.y / 2 &&
//				box[i]->pos.y + box[i]->size.y / 2 > box[k]->pos.y - box[k]->size.y / 2)
//			{
//				Vector2 check = box[k]->pos;
//				box[i]->isOnBox = k;
//				box[k]->isOnBox = i;
//
//				if (box[i]->moveDir.x < 0 && box[i]->pos.x - box[k]->pos.x < box[i]->size.x / 2 + box[k]->size.x / 2)
//					check.x = box[i]->pos.x + box[i]->size.x / 2 + box[k]->size.x / 2;
//				else if (box[i]->moveDir.x > 0 && box[k]->pos.x - box[i]->pos.x < box[i]->size.x / 2 + box[k]->size.x / 2)
//					check.x = box[i]->pos.x - box[i]->size.x / 2 - box[k]->size.x / 2;
//
//				else if (box[i]->moveDir.y < 0 && box[i]->pos.y - box[k]->pos.y < box[i]->size.y / 2 + box[k]->size.y / 2)
//					check.y = box[i]->pos.y + box[i]->size.y / 2 + box[k]->size.y / 2;
//				else if (box[i]->moveDir.y > 0 && box[k]->pos.y - box[i]->pos.y < box[i]->size.y / 2 + box[k]->size.y / 2)
//				{
//					check.y = box[i]->pos.y + box[i]->size.y / 2 + box[k]->size.y / 2;
//					//box[k]->isLockedY = true;
//					box[i]->velocity.y = 0;
//					//box[i]->pos.y = box[k]->pos.y - box[k]->size.y / 2 - box[i]->size.y / 2;
//				}
//
//				if (!isFill(check, box[k]->vertex))
//				{
//					box[k]->pos = check;
//				}
//				box[i]->moveDir = { 0,0 };
//			}
//		}
//	}
//}

void Playground::CollisionWithPiece()
{
	Vector2 hindCheckPos;
	Vector2 collisionDir = { 0,0 };

	for (int i = 0; i < hindrancePos.size(); i++)
	{
		hindCheckPos.x = float(hindrancePos[i].x * kTileSize);
		hindCheckPos.y = float(hindrancePos[i].y * kTileSize);

		int	collidedNum = piece->PixelCollisionWithObjOutSide(hindCheckPos, hindranceVertex, collisionDir);

		if (collidedNum != -1)
		{
			if (collisionDir.x < 0)
				piece->piecePos[i].x = hindCheckPos.x - piece->pieceSize[i].x * kTileSize;
			if (collisionDir.x > 0)
				piece->piecePos[i].x = hindCheckPos.x + piece->pieceSize[i].x * kTileSize;

		}
	}
}

void Playground::CollisionReset()
{
	collision->clear();
	collision = new std::vector<std::vector<int>>(*field);
}

bool Playground::isFill(const Vector2& _pos, const Vector2* _vertex)
{
	for (int i = 0; i < 4; i++)
	{
		if (_pos.x + _vertex[i].x >= kStageAreaWidth ||
			_pos.x + _vertex[i].x < 0 ||
			_pos.y + _vertex[i].y >= kStageAreaHeight ||
			_pos.y + _vertex[i].y < 0)
			return true;


		if ((*field)[int(_pos.y + _vertex[i].y) / kTileSize][int(_pos.x + _vertex[i].x) / kTileSize] != AIR ||
			_pos.x + _vertex[i].x < 0 ||
			_pos.x + _vertex[i].x > kStageAreaWidth + _vertex[i].x ||
			_pos.y + _vertex[i].y < 0 ||
			_pos.y + _vertex[i].y >kStageAreaHeight + _vertex[i].y)
		{
			return true;
		}
	}
	return false;
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

	hindranceVertex[0] = { 0,0 };
	hindranceVertex[1] = { kTileSize,0 };
	hindranceVertex[2] = { 0,kTileSize };
	hindranceVertex[3] = { kTileSize,kTileSize };
}

void Playground::Init(int _stageNo)
{
	CSV_Loader::LoadFromCSV_s(stageFilePath[_stageNo], '\n');
	selectStage = _stageNo;

	field = CSV_Loader::GetPointerMapchip();
	collision = new std::vector<std::vector<int>>(*field);

	hindrancePos.clear();
	box.clear();
	piece->Init();
	for (int y = 0; y < field->size(); y++)
	{
		for (int x = 0; x < (*field)[y].size(); x++)
		{
			if ((*field)[y][x] == BOX)
			{
				(*field)[y][x] = 0;
				if (box.empty())
					box.push_back(new Box(x, y));
			}
			else if ((*field)[y][x] == HINDRANCE)
			{
				hindrancePos.push_back(intVec2(x, y));
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
		plbo = false;
		plpi = false;
		pibo = false;

		CollisionReset();
		piece->Update(field, collision, player->pos, box);
		for (int i = 0; i < box.size(); i++)
			box[i]->Update();
		player->Update(_keys, _preKeys);

		/// 衝突判定たち
		CollisionWithPlayer();
		CollisionPlayerWithBox();
		CollisionWithBox();
		CollisionPlayerWithPiece();
		CollisionWithPiece();///みかん
		CollisionPieceWithBox();
		CollisionWithBox();
		CollisionPieceWithBox();
		CollisionPlayerWithBox();
		CollisionPlayerWithPiece();

		//CollisionWithPlayer();
		//CollisionWithBox();
		////CollisionBoxWithBox();
		//CollisionPlayerWithBox();
		//CollisionPlayerWithPiece();
		//CollisionPieceWithBox();
		//CollisionPlayerWithBox();
		//CollisionPlayerWithPiece();
		//CollisionWithPiece();
	}


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
					Phill::DrawQuadPlus(int(x * kTileSize), int(y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 7 * 64, 0, 64, 64, blockTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				else if ((*field)[y][x] == 2)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, goalTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				else if ((*field)[y][x] == 3)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, obstacleTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);
				else if ((*field)[y][x] == 5)///とげ
					Novice::DrawBox(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 0, 0x2020d0ff, kFillModeSolid);

				else if ((*field)[y][x] != 9 /*&& (*field)[y][x] != 0*/)
					Novice::DrawBox(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 0, kTileColor_[(*field)[y][x]], kFillModeSolid);
			}
			//Novice::ScreenPrintf(1000 + x * 20, y * 20, "%d", (*collision)[y][x]);
		}
	}

	for (int i = 0; i < box.size(); i++)
		box[i]->Draw(i);
	piece->Draw();
	player->Draw();

	Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0, 0x80, kFillModeSolid);
}
