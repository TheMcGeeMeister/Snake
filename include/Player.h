#ifndef PLAYER_H
#define PLAYER_H
#include <Position.h>
#include <Timer.h>
#include <Direction.h>
#include <Vector>
#include <Display.h>
#include <Game.h>

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
        void SetSnakeGraphic(char);
        void SetMovementCooldown(double);
        void AddTail();
        void AddTurnPoint(Direction direct);
        void Update();
        void Move();
        void resetTail();
        bool CanMove();
        bool CanMoveCertainDirection(Direction direct);
        bool CanChangeDirect(Direction direct);
        bool isCollision(Direction);
        int GetTailAmount();
        int GetPosX();
        int GetPosY();
        int& GetPosXRef();
        int& GetPosYRef();
        double GetMovementCooldown();
        double& GetMovementCooldownRef();
        char GetSnakeGraphic();
        Position GetPlayerPos();
        Position& GetPlayerPosRef();
        Direction GetPlayerDirection();



        Timer MovementCoolDown;
    protected:
    private:
        int tailAmount;
        int amountAte;
        double movementCooldown_;
        bool ateApple;
        char snakeGraphic_;
        Position pos;
        Direction direct;
        vector<Tail> tails;
};

#endif // PLAYER_H
