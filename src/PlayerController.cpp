#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "PlayerController.h"


PlayerController::PlayerController()
{
}


PlayerController::~PlayerController()
{
}

int PlayerController::addPlayer(Player& newPlayer)
{
	int newId = playerAmount_++;
	while (players_.find(newId) != players_.end())
	{
		newId++;
	}
	players_[newId] = newPlayer;
	return newId;
}

void PlayerController::addPlayer(Player& newPlayer, int id)
{
	if (players_.find(id) == players_.end())
	{
		return;
	}
	players_[id] = newPlayer;
}

int PlayerController::createPlayer()
{
	int newId = playerAmount_++;
	while (players_.find(newId) != players_.end())
	{
		newId++;
	}
	Player newPlayer;
	newPlayer.setPos(Game::display.getRandomValidPosition());
	players_[newId] = newPlayer;
	return newId;
}

void PlayerController::createPlayer(int id)
{
	if (players_.find(id) != players_.end())
		return;
	Player newPlayer;
	newPlayer.setPos(Game::display.getRandomValidPosition());
	players_[id] = newPlayer;
	return;
}

void PlayerController::update()
{
	for (auto iter : players_)
	{
		iter.second.Update();
	}
}

Player& PlayerController::getPlayerRef(int id)
{
	if (players_.find(id) == players_.end())
	{
		createPlayer(id);
		return players_[id];
	}
	else
	{
		return players_[id];
	}
}

#endif
