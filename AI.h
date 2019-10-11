#ifndef AI_H
#define AI_H

#include "Players.h"
class AI : public Players {
private:
	int difficulty;

public:
	AI();
	void setShips(int);
};
#endif

