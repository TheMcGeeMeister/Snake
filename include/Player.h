#ifndef PLAYER_H
#define PLAYER_H
#include <Game.h>
#include <Position.h>
#include <Timer.h>
#include <Direction.h>
#include <Vector>

using namespace std;

extern void gameOver();
extern void spawnApple();


class Tail
{
    public:
        void SetTailPos(Position pos);
        void SetTailDirect(Direction direct);
        void AddTurn(pair<Direction, Position>);
        void Move();
        void Update();
        Position& GetPos();
        Direction& GetDirect();

        vector<pair<Direction, Position> >& GetTurns();

        bool operator==(Tail&);

        vector<pair<Direction, Position> > turns;
    private:
        void CanMove();
        Position pos;
        Direction direct;
};


class Player
{
    public:
        Player();
        virtual ~Player();
        void SetPlayerPos(Position pos);
        void SetPlayerDirect(Direction direct);
		void setPos(Position pos);
		void setDirect(Direction direct);
        void SetSnakeGraphic(char);
		void setPlayerGraphic(char);
        void setMovementCooldown(double);
		void setPosGoal(Position goal);
		void setLerpDeltaT(int deltaT);
		void approach();
        void AddTail();
        void AddTurnPoint(Direction direct);
        void Update();
        void Move();
        void resetTail();
        bool CanMove();
        bool CanMoveCertainDirection(Direction direct);
        bool CanChangeDirect(Direction direct);
		bool isValidPositionInDirect(Direction direct);
		bool isValidDirectChange(Direction direct);
        bool isCollision(Direction);
        int GetTailAmount();
        int GetPosX();
        int GetPosY();
        int& GetPosXRef();
        int& GetPosYRef();
        double getMovementCooldown();
        double& getMovementCooldownRef();
        char GetSnakeGraphic();
		char getSnakeGraphic();
		char getPlayerGraphic();
        Position GetPlayerPos();
        Position& GetPlayerPosRef();
        Direction GetPlayerDirection();

        Timer MovementCoolDown;
    protected:
    private:
        int tailAmount;
        int amountAte;
		int deltaT_;
        double movementCooldown_;
        bool ateApple;
        char snakeGraphic_;
		char playerGraphic_;
        Position pos;
		Position posGoal_;
        Direction direct;
        vector<Tail> tails;
};

#endif // PLAYER_H
