#pragma once

class KeyManager
{
public:

	static	void	GetKeyState();
	static	char	GetKeys(int _index) { return keys[_index]; };
	static	char	GetPreKeys(int _index) { return preKeys[_index]; };
	static	char*	GetKeysPtr() { return keys; };
	static	char*	GetpreKeysPtr() { return preKeys; };
private:
	static	char	keys[256];
	static	char	preKeys[256];
};
