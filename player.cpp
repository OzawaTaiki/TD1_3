#include "player.h"

#include "PhilliaFunction/Phill.h"
#include <Novice.h>
#include "definition.h"
#include "ResourceManager.h"

void Player::Move(const char* _keys, const char* _preKeys, int _isHave)
{
	int moveX = 0;
	if (_preKeys[DIK_1])
		moveX = 0;
#ifdef _DEBUG
	if (_keys[DIK_LSHIFT])
	{
		if (_keys[DIK_A] && !_preKeys[DIK_A])
			moveX = -1;
		if (_keys[DIK_D] && !_preKeys[DIK_D])
			moveX = 1;
	}
	else
	{
#endif // _DEBUG
		isAnimation = false;
		if (_isHave == -1)
		{
			if (_keys[DIK_A])
			{
				moveX = -1;
				drawDir = -1;
				isAnimation = true;
				//moveSound->SoundEnable();
			}
			if (_keys[DIK_D])
			{
				moveX = 1;
				drawDir = 1;
				isAnimation = true;
				//moveSound->SoundEnable();
			}
		}

#ifdef _DEBUG
	}
#endif // _DEBUG

	velocity.x = moveX * kMoveSpd;
}

void Player::Jump(const char* _keys, const char* _preKeys, int _isHave)
{
	if (_isHave == -1)
		if ((_keys[DIK_W] /*&& !_preKeys[DIK_W]*/ || _keys[DIK_SPACE] && !_preKeys[DIK_SPACE]) && isGround)
		{
			velocity.y = kJumpVelocity;
			isGround = false;
			//jumpSound->SoundEnable();
		}
}

void Player::Gravity()
{
	velocity.y += acceleratiion.y;
}

void Player::MoveDirUpdate()
{
	moveDir = { 0,0 };
	if (velocity.x < 0)
		moveDir.x = -1;
	else if (velocity.x > 0)
		moveDir.x = 1;

	if (velocity.y < 0)
		moveDir.y = -1;
	else if (velocity.y > 0)
		moveDir.y = 1;
}

void Player::Clamp()
{
	if (pos.x + velocity.x < size.x / 2)
		velocity.x = size.x / 2 - pos.x;
	if (pos.x + velocity.x >= kStageAreaWidth - size.x / 2)
		velocity.x = pos.x - (kStageAreaWidth - size.x / 2);
	if (pos.y + velocity.y < size.y / 2)
		velocity.y = size.y / 2 - pos.y;
	if (pos.y + velocity.y >= kStageAreaHeight - size.y / 2)
	{
		velocity.y = 0;
		isAlive = false;
	}

	if (velocity.y > kMaxVeloY)
		velocity.y = kMaxVeloY;
}

Player::Player()
{
	pos = { 64,64 };
	size = { 54,60 };
	velocity = { 0,0 };
	acceleratiion = { 0,0.5f };
	moveDir = { 0,0 };
	GHSize = { 64, 80 };
	drawSize = GHSize;
	isAlive = true;
	isGround = false;
	isOnBox = false;
	isAddVelo = false;

	vertex[0] = { -size.x / 2,-size.y / 2 };
	vertex[1] = { size.x / 2 - 1,-size.y / 2 };
	vertex[2] = { -size.x / 2,size.y / 2 - 1 };
	vertex[3] = { size.x / 2 - 1,size.y / 2 - 1 };

	color = 0xffffffff;

	drawDir = 1;
	isAnimation = false;
	cntUp = 0;
	animationCurrentIndex = 0;

	playerTexture = ResourceManager::Handle("playerTex");

	//moveSound = new Sound(ResourceManager::Handle("playerMoveSound"), 0.5f);
	//jumpSound = new Sound(ResourceManager::Handle("playerJumpSound"), 0.5f);
}

void Player::PosUpdate()
{
	if (!isAddVelo)
	{
		pos.x += velocity.x;
		pos.y += velocity.y;
		isAddVelo = true;
	}
}

void Player::Init(int _stageNo)
{
	pos = { float(startPos[_stageNo].x * kTileSize + kTileSize / 2),float(startPos[_stageNo].y * kTileSize + kTileSize / 2) };
	velocity = { 0,0 };
	acceleratiion = { 0,0.5f };
	moveDir = { 0,0 };
	drawSize = GHSize;
	isAlive = true;
	isGround = false;
	color = 0xffffffff;
	drawDir = 1;
	cntUp = 0;
	animationCurrentIndex = 0;
	isAnimation = false;
}

void Player::Update(const char* _keys, const char* _preKeys, int _isHave)
{
	isOnBox = false;
	isAddVelo = false;

	Move(_keys, _preKeys, _isHave);
	Jump(_keys, _preKeys, _isHave);
	Gravity();
	Clamp();
	MoveDirUpdate();

	if (isAnimation)
		cntUp++;
	else
	{
		cntUp = 0;
		animationCurrentIndex = 0;
	}
	if (cntUp % kGoNextCnt == 0 && cntUp != 0)
	{
		cntUp = 0;
		animationCurrentIndex++;
		if (animationCurrentIndex >= kAnimationIndex)
			animationCurrentIndex = 0;
	}
}

void Player::Draw(bool _isOverlap)
{

	if (moveSound != nullptr)		moveSound->PlayAudio();
	if (jumpSound != nullptr)		jumpSound->PlayAudio();

	if (_isOverlap)
		color = 0xff0000ff;
	else color = 0xffffffff;

	Phill::DrawQuadPlus(int(pos.x), int(pos.y + 2), int(GHSize.x * drawDir), int(GHSize.y),
		1.0f, 1.0f, 0.0f,
		GHSize.x * animationCurrentIndex, 0,
		int(GHSize.x), int(GHSize.y),
		playerTexture, color, PhillDrawMode::DrawMode_Center);

	//Novice::ScreenPrintf(int(pos.x - 20), int(pos.y - 40), "%d,%d", int(pos.x), int(pos.y));
	/*for (int i = 0; i < 4; i++)
	{
		Novice::ScreenPrintf(1600, 900 + i * 20, "%.1f,%.1f", pos.x + vertex[i].x, pos.y + vertex[i].y);
		Novice::ScreenPrintf(1720, 900 + i * 20, "%d,%d", int(pos.x + vertex[i].x) / kTileSize, int(pos.y + vertex[i].y) / kTileSize);
	}*/
}
