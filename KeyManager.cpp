#include "KeyManager.h"
#include <Novice.h>

char KeyManager::keys[256] = {};
char KeyManager::preKeys[256] = {};

void KeyManager::GetKeyState()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
}
