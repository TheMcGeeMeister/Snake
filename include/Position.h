#ifndef POSITION_H
#define POSITION_H
#include <utility>

using namespace std;

class Position
{
    public:
        Position(int y, int x);
        Position();
        virtual ~Position();
        void SetX(int x);
        void SetY(int y);
        int x;
        int y;
        void operator=(const Position&);
		bool operator==(const Position&);
        bool operator<(const Position&) const;
        pair<int, int> operator()();
        void operator()(int, int);

    protected:
    private:
};

#endif // POSITION_H
