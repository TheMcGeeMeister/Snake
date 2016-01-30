#pragma once
#include <Player.h>

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	Player& getPlayerRef(int id);
	
	int createPlayer();
	void createPlayer(int id);
	int addPlayer(Player&);
	void addPlayer(Player&, int id);
	void update();
private:
	map<int, Player> players_;
	int playerAmount_;
};

