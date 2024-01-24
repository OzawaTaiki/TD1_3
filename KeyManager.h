#pragma once

class KeyManager
{
public:

	static	void	GetKeyState();
	static	char	GetKeys(int index) { return keys[index]; };
	static	char	GetPreKeys(int index) { return preKeys[index]; };

private:
	static	char	keys[256];
	static	char	preKeys[256];
};
