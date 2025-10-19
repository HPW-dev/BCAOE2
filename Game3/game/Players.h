#pragma once
#include <string>
#include <vector>
using namespace std;

struct Player
{
	int food{};
	int gold{};
	int stone{};
	int wood{};
	bool botornotbot{};
	string Nickname{};
};

inline vector <Player> Players;