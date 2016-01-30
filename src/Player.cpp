#include <Game.h>

Player::Player()
{
    snakeGraphic_='S';
	playerGraphic_ = 'A';
    movementCooldown_=0.04;
	deltaT_ = 1;
	ateApple = false;
}

Player::~Player()
{
    //dtor
}

void Player::AddTail()
{
    tailAmount++;
    Position PosStart;
    Direction Direct;
    Tail NewTail;
    pair<Direction, Position> NewTurn;
    if(tails.empty()==false)
    {
        PosStart=tails.back().GetPos();
        Direct=tails.back().GetDirect();
        NewTail.turns=tails.back().GetTurns();
    }else
    {
        PosStart=pos;
        Direct=direct;
    }
    Position NewPos(0,0);
    switch(Direct)
    {
        case Up: NewPos.y=PosStart.y+1; NewPos.x=PosStart.x;
                if(Game::display.isValidPosition(NewPos)==false) // Can't go down one
                {
                    NewPos.y=PosStart.y;
                    NewPos.x=PosStart.x-1;
                    if(Game::display.isValidPosition(NewPos)==false) // Can't go left, So go Right
                    {
                        NewPos.y=PosStart.y;
                        NewPos.x=PosStart.x+1;
                        NewTurn.second=PosStart;
                        NewTurn.first=Direct;
                        NewTail.AddTurn(NewTurn);
                        Direct=Left;
                    }else
                    {
                        NewTurn.second=PosStart;
                        NewTurn.first=Direct;
                        NewTail.AddTurn(NewTurn);
                        Direct=Right;
                    }
                } break;
        case Down: NewPos.y=PosStart.y-1; NewPos.x=PosStart.x;
                if(Game::display.isValidPosition(NewPos)==false) // Can't go up
                {
                    NewPos.y=PosStart.y; // Try Left
                    NewPos.x=PosStart.x-1;
                    if(Game::display.isValidPosition(NewPos)==false) // Can't go left So Go Right
                    {
                        NewPos.y=PosStart.y;
                        NewPos.x=PosStart.x+1;
                        NewTurn.second=PosStart;
                        NewTurn.first=Direct;
                        NewTail.AddTurn(NewTurn);
                        Direct=Left;
                    }else // Go Left
                    {
                        NewTurn.second=PosStart;
                        NewTurn.first=Direct;
                        NewTail.AddTurn(NewTurn); // Add a turn so it joins back with the tail correctly
                        Direct=Right;
                    }
                } break;
        case Left: NewPos.y=PosStart.y; NewPos.x=PosStart.x+1;
                if(Game::display.isValidPosition(NewPos)==false) // Can't go Right
                {
                    NewPos.y=PosStart.y-1; // Try Up
                    NewPos.x=PosStart.x;
                    if(Game::display.isValidPosition(NewPos)==false) // Can't go up, so go down
                    {
                        NewPos.y=PosStart.y+1;
                        NewPos.x=PosStart.x;
                        NewTurn.second=PosStart;
                        NewTurn.first=Direct;
                        NewTail.AddTurn(NewTurn);
                        Direct=Up;
                    }else // Go Up
                    {
                        NewTurn.second=PosStart;
                        NewTurn.first=Direct;
                        NewTail.AddTurn(NewTurn); // Add a turn so it joins back with the tail correctly
                        Direct=Down;
                    }
                } break;
        case Right: NewPos.y=PosStart.y; NewPos.x=PosStart.x-1;
                if(Game::display.isValidPosition(NewPos)==false) // Can't go Left
                {
                    NewPos.y=PosStart.y-1; // Try Up
                    NewPos.x=PosStart.x;
                    if(Game::display.isValidPosition(NewPos)==false) // Can't go up, so go down
                    {
                        NewPos.y=PosStart.y+1;
                        NewPos.x=PosStart.x;
                        NewTurn.second=PosStart;
                        NewTurn.first=Direct;
                        NewTail.AddTurn(NewTurn);
                        Direct=Up;
                    }else // Go Up
                    {
                        NewTurn.second=PosStart;
                        NewTurn.first=Direct;
                        NewTail.AddTurn(NewTurn); // Add a turn so it joins back with the tail correctly
                        Direct=Down;
                    }
                } break;
    }
    NewTail.SetTailPos(NewPos);
    NewTail.SetTailDirect(Direct);
    Game::display.SetPos(NewPos, snakeGraphic_);
    tails.push_back(NewTail);
    return;
}

void Player::SetPlayerPos(Position pos)
{
	//Game::display .SetPos(pos, ' ');
    this->posGoal_=pos;
	this->pos = pos;
    //Game::display.SetPos(pos, 'A');
}

void Player::setPos(Position pos)
{
	//Game::display.SetPos(pos, ' ');
	this->posGoal_ = pos;
	this->pos = pos;
	//Game::display.SetPos(pos, playerGraphic_);
}

void Player::SetPlayerDirect(Direction direct)
{
    this->direct=direct;
	AddTurnPoint(direct);
}

void Player::setDirect(Direction direct)
{
	this->direct = direct;
	AddTurnPoint(direct);
}

void Player::SetSnakeGraphic(char _snakeGraphic)
{
    snakeGraphic_=_snakeGraphic;
}

void Player::setPlayerGraphic(char playerGraphic)
{
	playerGraphic_ = playerGraphic;
}

void Player::setMovementCooldown(double cooldown)
{
    movementCooldown_=cooldown;
    return;
}

void Player::setLerpDeltaT(int deltaT)
{
	deltaT_ = deltaT;
	return;
}

void Player::approach()
{
	bool overDueX = false;
	bool overDueY = false;
	if (pos == posGoal_)
		return;
	else
	{
		Game::display.SetPos(pos, ' ');
		if (pos.x != posGoal_.x)
		{
			pos.x > posGoal_.x ? (pos.x - deltaT_<posGoal_.x ? overDueX = true : overDueX = false) : (pos.x + deltaT_>posGoal_.x ? overDueX = true : overDueX = false);
			pos.x > posGoal_.x ? pos.x-= deltaT_ : pos.x+= deltaT_;
		}
		if (pos.y != posGoal_.y)
		{
			pos.y > posGoal_.y ? (pos.y - deltaT_<posGoal_.y ? overDueY = true : overDueY = false) : (pos.y + deltaT_>posGoal_.y ? overDueY = true : overDueY = false);
			pos.y > posGoal_.y ? pos.y -= deltaT_ : pos.y += deltaT_;
		}
		if (overDueX == true) pos.x = posGoal_.x;
		if (overDueY == true) pos.y = posGoal_.y;
	}
	if (Game::display.GetPos(pos) == '@')
	{
		spawnApple();
		ateApple = true;
	}
	else if (Game::display.GetPos(pos) == snakeGraphic_)
	{
		gameOver();
	}
	Game::display.SetPos(pos, playerGraphic_);
}

void Player::AddTurnPoint(Direction direct)
{
    if(tailAmount==0)
    {
        return;
    }
    pair<Direction, Position> NewTurn;
    NewTurn.first=direct;
    NewTurn.second=pos;
    vector<Tail>::iterator iter=tails.begin();
    vector<Tail>::iterator e=tails.end();
    for(;iter!=e;iter++)
    {
        iter->AddTurn(NewTurn);
    }
}

void Player::Update()
{
    if(CanMove()==false)
    {
        return;
    }else
    {
        Move();
		approach();
        vector<Tail>::iterator iter=tails.begin();
        vector<Tail>::iterator e=tails.end();
        for(;iter!=e;iter++)
        {
            iter->Update();
        }
        if(ateApple)
        {
            AddTail();
            ateApple=false;
        }
    }
}

void Player::resetTail()
{
    tails.clear();
    tailAmount=0;
    ateApple=false;
}

void Player::Move()
{
    /*char nothing=' ';
	Game::display.SetPos(pos, nothing);
    switch(direct)
    {
        case Up: pos.y--; MovementCoolDown.StartNewTimer(movementCooldown_*2); break;
        case Down: pos.y++; MovementCoolDown.StartNewTimer(movementCooldown_*2); break;
        case Left: pos.x--; MovementCoolDown.StartNewTimer(movementCooldown_); break;
        case Right: pos.x++; MovementCoolDown.StartNewTimer(movementCooldown_); break;
    }
    if(Game::display.GetPos(pos)=='@')
    {
        spawnApple();
        ateApple=true;
    }
    else if(Game::display.GetPos(pos)==snakeGraphic_)
    {
        gameOver();
    }
    Game::display.SetPos(pos, 'A');
    return;*/
	switch (direct)
	{
	case Up: posGoal_.y--; MovementCoolDown.StartNewTimer(movementCooldown_ * 2); break;
	case Down: posGoal_.y++; MovementCoolDown.StartNewTimer(movementCooldown_ * 2); break;
	case Left: posGoal_.x--; MovementCoolDown.StartNewTimer(movementCooldown_); break;
	case Right: posGoal_.x++; MovementCoolDown.StartNewTimer(movementCooldown_); break;
	}
}

bool Player::isCollision(Direction direction)
{
    char graphicAtNewPos;
    Position NewPosition(pos);
    switch (direction)
    {
        case Up:
            NewPosition.y--;
            graphicAtNewPos=Game::display.GetPos(pos);
			return (graphicAtNewPos == snakeGraphic_);
        case Down:
            NewPosition.y++;
            graphicAtNewPos=Game::display.GetPos(pos);
			return(graphicAtNewPos == snakeGraphic_);
        case Left:
            NewPosition.x--;
            graphicAtNewPos=Game::display.GetPos(pos);
			return (graphicAtNewPos == snakeGraphic_);
        case Right:
            NewPosition.x++;
            graphicAtNewPos=Game::display.GetPos(pos);
			return (graphicAtNewPos == snakeGraphic_);
        default:
            return true;
    }
}

bool Player::CanMove()
{
    Position newPos;
    newPos=pos;
    if(MovementCoolDown.Update()==false)
    {
        return false;
    }
	if (isCollision(direct))
	{
		gameOver();
		return false;
	}
    switch(direct)
    {
        case Up: newPos.y--; break;
        case Down: newPos.y++; break;
        case Left: newPos.x--; break;
        case Right: newPos.x++; break;
    }
	return Game::display.isValidPosition(newPos);
}

bool Player::CanMoveCertainDirection(Direction direct)
{
    Position newPos=pos;
    if(MovementCoolDown.Update()==false)
    {
        return false;
    }
    switch(direct)
    {
        case Up: newPos.y--; break;
        case Down: newPos.y++; break;
        case Left: newPos.x--; break;
        case Right: newPos.x++; break;
    }
	return Game::display.isValidPosition(newPos);
}

bool Player::isValidDirectChange(Direction direct)
{
	switch (direct)
	{
	case Up:
		return !(this->direct == Down || this->direct == Up);
	case Down:
		return !(this->direct == Up || this->direct == Down);
	case Left:
		return !(this->direct == Right || this->direct == Left);
	case Right:
		return !(this->direct == Left || this->direct == Right);
	}
	return true;
}

bool Player::isValidPositionInDirect(Direction direct)
{
	Position newPos = pos;
	if (MovementCoolDown.Update() == false)
	{
		return false;
	}
	switch (direct)
	{
	case Up: newPos.y--; break;
	case Down: newPos.y++; break;
	case Left: newPos.x--; break;
	case Right: newPos.x++; break;
	}
	return Game::display.isValidPosition(newPos);
}

bool Player::CanChangeDirect(Direction direct)
{
	switch (direct)
	{
	case Up:
		return !(this->direct == Down || this->direct == Up);
	case Down:
		return !(this->direct == Up || this->direct == Down);
	case Left:
		return !(this->direct == Right || this->direct == Left);
	case Right:
		return !(this->direct == Left || this->direct == Right);
	}
	return true;
}

int& Player::GetPosXRef()
{
    return pos.x;
}

int& Player::GetPosYRef()
{
    return pos.y;
}

int Player::GetPosX()
{
    return pos.x;
}

int Player::GetPosY()
{
    return pos.y;
}

int Player::GetTailAmount()
{
    return tailAmount;
}

double Player::getMovementCooldown()
{
	return movementCooldown_;
}

double& Player::getMovementCooldownRef()
{
	return movementCooldown_;
}

char Player::getSnakeGraphic()
{
	return snakeGraphic_;
}

char Player::getPlayerGraphic()
{
	return playerGraphic_;
}

Position Player::GetPlayerPos()
{
    return pos;
}

Position& Player::GetPlayerPosRef()
{
    return pos;
}

Direction Player::GetPlayerDirection()
{
    return direct;
}



/////////// Tail //////////////////////




void Tail::SetTailPos(Position pos)
{
    this->pos=pos;
    return;
}

void Tail::SetTailDirect(Direction direct)
{
    this->direct=direct;
    return;
}

void Tail::AddTurn(pair<Direction, Position> NewTurn)
{
	turns.push_back(NewTurn);
}

void Tail::Move()
{
    Game::display.SetPos(pos, ' ');
    switch(direct)
    {
        case Up: pos.y--; break;
        case Down: pos.y++; break;
        case Left: pos.x--; break;
        case Right: pos.x++; break;
    }
    Game::display.SetPos(pos, 'S');
}

void Tail::Update()
{
    Move();
    if(turns.empty()==false)
    {
        vector<vector<pair<Direction, Position> >::iterator> deleteQueue;
        vector<pair<Direction, Position> >::iterator iter=turns.begin();
        vector<pair<Direction, Position> >::iterator iEnd=turns.end();
        for(;iter!=iEnd;iter++)
        {
            if(iter->second==pos)
            {
                direct=iter->first; //First is Direction
                deleteQueue.push_back(iter);
            }
        }
        if(deleteQueue.empty()==false)
        {
            vector<vector<pair<Direction, Position> >::iterator>::iterator iter=deleteQueue.begin();
            vector<vector<pair<Direction, Position> >::iterator>::iterator iEnd=deleteQueue.end();
            for(;iter!=iEnd;iter++)
            {
                turns.erase(*iter);
            }
        }
    }
}

Position& Tail::GetPos()
{
    return pos;
}

Direction& Tail::GetDirect()
{
    return direct;
}

vector<pair<Direction, Position> >& Tail::GetTurns()
{
    return turns;
}

bool Tail::operator==(Tail& tail)
{
    if(tail.GetPos()==pos)
    {
        return true;
    }else
    {
        return false;
    }
}
