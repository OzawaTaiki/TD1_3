#include "playground.h"

#include "PhilliaFunction/Phill.h"
#include "CSVLoader.h"
#include <Novice.h>
#include "definition.h"

#include "piece.h"
#include "player.h"
#include "box.h"
#include "ResourceManager.h"


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

	GoalCheck();
	SpineHitCheck();

	player->PosUpdate();
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
			//box[i]->moveSound->SoundEnable();
		}
		/// 右の判定
		if (((*field)[int(box[i]->pos.y + box[i]->vertex[1].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[1].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->vertex[3].y) / kTileSize][int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[3].x) / kTileSize] != AIR) &&
			box[i]->moveDir.x > 0)
		{
			box[i]->pos.x = (int(box[i]->pos.x + box[i]->velocity.x + box[i]->vertex[1].x) / kTileSize) * kTileSize - box[i]->size.x / 2;
			box[i]->velocity.x = 0;
			box[i]->isLockedX = true;
			//box[i]->moveSound->SoundEnable();
		}
		/// 上の判定
		if (((*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[0].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[0].x) / kTileSize] != AIR ||
			(*field)[int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[1].y) / kTileSize][int(box[i]->pos.x + box[i]->vertex[1].x) / kTileSize] != AIR) &&
			box[i]->moveDir.y < 0)
		{
			box[i]->pos.y = (int(box[i]->pos.y + box[i]->velocity.y + box[i]->vertex[0].y) / kTileSize + 1) * kTileSize + box[i]->size.y / 2;
			box[i]->velocity.y = 0;
			box[i]->isLockedY = true;
			//box[i]->moveSound->SoundEnable();
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
			//box[i]->moveSound->SoundEnable();
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
				//box[i]->moveSound->SoundEnable();
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
	Vector2 collisionDir = { 0,0 };
	int collidedNum = -1;
	//int collidedBoxNum = -1;

	collidedNum = piece->PixelCollisionWithObj(player->pos, player->vertex, player->moveDir, collisionDir);

	if (collidedNum != -1)
	{
		if (!plpi)
			piece->MoveOnCollision(collisionDir, collidedNum + kTileKinds, player->velocity);
		else
		{
			if (collisionDir.x < 0)
				player->pos.x = piece->pos[collidedNum].x + piece->runX * kTileSize + kTileSize + player->vertex[1].x;
			if (collisionDir.x > 0)
				player->pos.x = piece->pos[collidedNum].x + piece->runX * kTileSize + player->vertex[0].x;
			if (collisionDir.y < 0)
				player->pos.y = piece->pos[collidedNum].y + piece->runY * kTileSize + kTileSize + player->vertex[2].y;
			if (collisionDir.y > 0)
			{
				player->pos.y = piece->pos[collidedNum].y + piece->runY * kTileSize + player->vertex[0].y;
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
					player->pos.x = piece->pos[collidedNum].x + piece->runX * kTileSize + kTileSize + player->vertex[1].x;
				if (collisionDir.x > 0)
					player->pos.x = piece->pos[collidedNum].x + piece->runX * kTileSize + player->vertex[0].x;
				if (collisionDir.y < 0)
					player->pos.y = piece->pos[collidedNum].y + piece->runY * kTileSize + kTileSize + player->vertex[2].y;
				if (collisionDir.y > 0)
					player->pos.y = piece->pos[collidedNum].y + piece->runY * kTileSize + player->vertex[0].y;
			}
		}
		/// piece-player間に箱があるときの処理
		else
		{
			for (int i = 0; i < box.size(); i++)
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
						piece->MoveOnCollision(collisionDir, collidedNum + kTileKinds, box[i]->velocity);


						/*if (collisionDir.x < 0)
							piece->pos[collidedNum].x = box[i]->pos.x - piece->runX * kTileSize - box[i]->size.x / 2 - kTileSize;
						if (collisionDir.x > 0)
							piece->pos[collidedNum].x = box[i]->pos.x - piece->runX * kTileSize + box[i]->size.x / 2;
						if (collisionDir.y < 0)
							piece->pos[collidedNum].y = box[i]->pos.y + piece->runY * kTileSize + kTileSize + box[i]->vertex[2].y;
						if (collisionDir.y > 0)
							piece->pos[collidedNum].y = box[i]->pos.y - piece->runY * kTileSize + box[i]->size.y / 2;

						piece->moveDir[collidedNum].x = collisionDir.x;
						piece->moveDir[collidedNum].y = collisionDir.y;*/
					}
				}
			}
		}
	}
	if (plpi && piece->isLockedY)
	{
		player->velocity.y = 0;
	}
	plpi = true;
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
				Vector2 prePos = box[i]->pos;

				if (collisionDir.x < 0)
					box[i]->pos.x = piece->pos[collidedNum].x + piece->runX * kTileSize + kTileSize + box[i]->vertex[1].x + 1;
				if (collisionDir.x > 0)
					box[i]->pos.x = piece->pos[collidedNum].x + piece->runX * kTileSize + box[i]->vertex[0].x;
				if (isFill(box[i]->pos, box[i]->vertex))
					box[i]->pos.x = prePos.x;

				if (collisionDir.y < 0)
					box[i]->pos.y = piece->pos[collidedNum].y + piece->runY * kTileSize + kTileSize + box[i]->vertex[2].y + 1;
				if (collisionDir.y > 0 && !box[i]->isLockedY)
				{
					box[i]->pos.y = piece->pos[collidedNum].y + piece->runY * kTileSize + box[i]->vertex[0].y - 1;
					box[i]->velocity.y = 0;
				}
				if (isFill(box[i]->pos, box[i]->vertex))
					box[i]->pos.y = prePos.y;
				//box[i]->moveSound->SoundEnable();
				box[i]->moveDir.x = collisionDir.x * -1;
				box[i]->moveDir.y = collisionDir.y * -1;
			}
			else
			{
				if (collisionDir.x < 0)
					piece->pos[collidedNum].x = box[i]->pos.x - box[i]->size.x / 2 - (piece->runX + 1) * kTileSize;
				if (collisionDir.x > 0)
					piece->pos[collidedNum].x = box[i]->pos.x + box[i]->size.x / 2 - piece->runX * kTileSize;
				if (collisionDir.y < 0)
					piece->pos[collidedNum].y = box[i]->pos.y - box[i]->size.y / 2 - (piece->runY + 1) * kTileSize;
				if (collisionDir.y > 0)
					piece->pos[collidedNum].y = box[i]->pos.y + box[i]->size.y / 2 - piece->runY * kTileSize;
			}
		}
		else
		{
			collidedNum = piece->PixelCollisionWithObjOutSide(box[i]->pos, box[i]->vertex, collisionDir);

			if (collidedNum != -1)
			{
				if (!pibo)
				{
					Vector2 prePos = box[i]->pos;
					if (collisionDir.x < 0)
						box[i]->pos.x = piece->pos[collidedNum].x + piece->runX * kTileSize + kTileSize + box[i]->vertex[1].x + 1;
					if (collisionDir.x > 0)
						box[i]->pos.x = piece->pos[collidedNum].x + piece->runX * kTileSize + box[i]->vertex[0].x;
					if (isFill(box[i]->pos, box[i]->vertex))
						box[i]->pos.x = prePos.x;

					if (collisionDir.y < 0)
						box[i]->pos.y = piece->pos[collidedNum].y + piece->runY * kTileSize + kTileSize + box[i]->vertex[2].y + 1;
					if (collisionDir.y > 0)
					{
						box[i]->pos.y = piece->pos[collidedNum].y + piece->runY * kTileSize + box[i]->vertex[0].y - 1;
						box[i]->velocity.y = 0;
					}
					if (isFill(box[i]->pos, box[i]->vertex))
						box[i]->pos.y = prePos.y;

					//box[i]->moveSound->SoundEnable();
					box[i]->moveDir.x = collisionDir.x * -1;
					box[i]->moveDir.y = collisionDir.y * -1;
				}
				else
				{
					if (collisionDir.x < 0)
						piece->pos[collidedNum].x = box[i]->pos.x - box[i]->size.x / 2 - (piece->runX + 1) * kTileSize;
					if (collisionDir.x > 0)
						piece->pos[collidedNum].x = box[i]->pos.x + box[i]->size.x / 2 - piece->runX * kTileSize;
					if (collisionDir.y < 0)
						piece->pos[collidedNum].y = box[i]->pos.y - box[i]->size.y / 2 - (piece->runY + 1) * kTileSize;
					if (collisionDir.y > 0)
						piece->pos[collidedNum].y = box[i]->pos.y + box[i]->size.y / 2 - piece->runY * kTileSize;
				}
			}
		}
	}
	pibo = true;
}


void Playground::CollisionWithPiece()
{
	Vector2 hindCheckPos;
	Vector2 collisionDir = { 0,0 };

	for (int i = 0; i < hindrancePos.size(); i++)
	{
		hindCheckPos.x = float(hindrancePos[i].x * kTileSize);
		hindCheckPos.y = float(hindrancePos[i].y * kTileSize);
		collisionDir = { 0,0 };

		int	collidedNum = piece->PixelCollisionWithObjOutSide(hindCheckPos, hindranceVertex, collisionDir);

		if (collidedNum != -1)
		{
			if (collisionDir.x < 0)
				piece->pos[collidedNum].x = hindCheckPos.x - piece->size[collidedNum].x * kTileSize;
			if (collisionDir.x > 0)
				piece->pos[collidedNum].x = hindCheckPos.x + kTileSize;
			if (collisionDir.y < 0)
			{
				piece->pos[collidedNum].y = hindCheckPos.y - piece->size[collidedNum].y * kTileSize;
				piece->isLockedY = true;
			}
			if (collisionDir.y > 0)
			{
				piece->pos[collidedNum].y = hindCheckPos.y + kTileSize;
				piece->isLockedY = true;
			}
		}
	}
}

void Playground::CollisionPieceWithPiece()
{
	piece->CollisionPieceWithPiece();
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
		(*field)[int(player->pos.y) / kTileSize][int(player->pos.x) / kTileSize] == GOAL ||
		(*field)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] == GOAL ||
		(*field)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] == GOAL ||
		(*field)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == GOAL ||
		(*field)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == GOAL
		)
	{
		isClear = true;
		//TODO : 確定後
		//goalSound = new Sound(/*path*/, 0.5f);
		//goalSound->SoundEnable();
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

void Playground::LoadFromJSON()
{
	scrollBarSize.width = atoi((*json_scr)["barWidth"]);
	scrollBarSize.height = atoi((*json_scr)["barHeight"]);
	scrollboxSize.width = atoi((*json_scr)["boxWidth"]);
	scrollboxSize.height = atoi((*json_scr)["boxHeight"]);
	scrollboxMargin = atoi((*json_scr)["boxMargin"]);
	scrollbarPosition.x = atoi((*json_scr)["barX"]);
	scrollbarPosition.y = atoi((*json_scr)["barY"]);
	scrollMarginTop = atoi((*json_scr)["MarginTop"]);
}

void Playground::ScrollCalculation()
{
	// ナイトウが追加
	float value = scrollBar->GetValue();
	increaseY_scroll = int(value * (-512));
	Novice::ScreenPrintf(1300, 15, "%4d", increaseY_scroll);
}

Playground::Playground()
{
	piece = new Piece;
	player = new Player;

	blockTexture = ResourceManager::Handle("blockTex");
	goalTexture = ResourceManager::Handle("goalTex");
	//obstacleTexture = ResourceManager::Handle("");
	backGroundTexture = ResourceManager::Handle("backGround");
	togeTexture = ResourceManager::Handle("togeTex");

	hindranceVertex[0] = { 0,0 };
	hindranceVertex[1] = { kTileSize,0 };
	hindranceVertex[2] = { 0,kTileSize };
	hindranceVertex[3] = { kTileSize,kTileSize };

	/// - - - ナイトウが勝手に実装 はじめ - - - ///
	json_scr = JSON_Manager::GetJSON("plygro-scroll");
	scrSpr.srcPos = Transform(0, 0);
	scrSpr.srcSize = Size(1, 1);
	scrSpr.trgSize = Size(14, 54);
	scrSpr.textureHandle = ResourceManager::Handle("white1x1");

	scrollBar = new Scroller(&scrSpr);
	LoadFromJSON();
	// スクロールバー初期化
	scrollBar->SetBarSize(Size(scrollBarSize.width, scrollBarSize.height - scrollboxSize.height - scrollboxMargin)); // 54はスクロールボックスの縦幅 80は縦マージンx2
	scrollBar->SetBoxSize(scrollboxSize);
	scrollBar->SetPosition(Transform(scrollbarPosition.x, scrollbarPosition.y + scrollboxSize.height / 2 + scrollboxMargin / 2)); // 27はずらすため 40は縦マージン

	/// - - - ナイトウが勝手に実装 おわり - - - ///

	//TODO : 確定後
	// 要検討事項 ： goalは判定時にインスタンスを作り，鳴らしたらデリートするべきか
	//				ここでインスタンスを作って判定時にフラグを立てるか
	//BGM = new Sound(path, 0.5f, true);
	//goalSound = nullptr;
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
				//if (box.empty())
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
	//TODO : 確定後
	//BGM->SoundEnable();
}

void Playground::Update(const char* _keys, const char* _preKeys)
{
	// ナイトウが勝手に追加 (二行)
	scrollBar->UpdateStatus();
	ScrollCalculation();

	/// ctrl + enter でコマ送りモード
	if (_keys[DIK_RETURN] && !_preKeys[DIK_RETURN] && _keys[DIK_LCONTROL])
		frameSlow = frameSlow ? false : true;

	/// コマ送りモードは入力しながらenter
	if (!frameSlow || _keys[DIK_RETURN] && !_preKeys[DIK_RETURN])
	{

		plbo = false;
		plpi = false;
		pibo = false;

		piece->Update(player->pos, player->vertex, box, hindrancePos, hindranceVertex, increaseY_scroll);
		for (int i = 0; i < box.size(); i++)
			box[i]->Update();
		player->Update(_keys, _preKeys, piece->isHave);

		/// 衝突判定たち
		CollisionWithPlayer();
		CollisionPlayerWithBox();
		CollisionWithBox();
		CollisionPlayerWithPiece();
		//CollisionWithPiece();
		CollisionPieceWithBox();
		CollisionWithBox();
		CollisionPieceWithBox();
		CollisionPieceWithPiece();
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
	if (BGM != nullptr)			BGM->PlayAudio(true, 300);
	if (goalSound != nullptr)	goalSound->PlayAudio();

	Novice::DrawSprite(0, 0, backGroundTexture, 1, 1, 0, 0xd0d0d0d0);

	for (int y = 0; y < (*field).size(); y++)
	{
		for (int x = 0; x < (*field)[y].size(); x++)
		{
			if ((*field)[y][x] != 9)
			{
				if ((*field)[y][x] == BLOCK)
					Phill::DrawQuadPlus(int(x * kTileSize), int(y * kTileSize), kTileSize, kTileSize, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, blockTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				else if ((*field)[y][x] == GOAL)
					Phill::DrawQuadPlus(int(x * kTileSize), int((y - 1) * kTileSize), kTileSize * 2, kTileSize * 2, 1.0f, 1.0f, 0.0f, 0, 0, 128, 128, goalTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				//else if ((*field)[y][x] == HINDRANCE)///お邪魔
					//Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, obstacleTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);
				else if ((*field)[y][x] == SPINE)///とげ
					Phill::DrawQuadPlus(int(x * kTileSize), int(y * kTileSize), kTileSize, kTileSize, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, togeTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				//else if ((*field)[y][x] != 0)
					//Novice::DrawBox(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 0, kTileColor_[(*field)[y][x]], kFillModeSolid);
			}
			//Novice::ScreenPrintf(1000 + x * 20, y * 20, "%d", (*collision)[y][x]);
		}
	}

	for (int i = 0; i < box.size(); i++)
		box[i]->Draw(i, piece->warningIconVisible);
	piece->Draw(increaseY_scroll);
	player->Draw();

	Novice::DrawBox(kStageAreaWidth, 0, kWindowWidth, kWindowHeight, 0, 0xa0, kFillModeSolid);
	// ナイトウが勝手に追加
	scrollBar->Draw();
}
