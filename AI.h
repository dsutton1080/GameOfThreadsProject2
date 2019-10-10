#ifndef AI_H
#define AI_H

#include "Players.h"
class AI : public Players {
private:
	std::string difficulty;

public:
	AI();
	void randomShipPlacement(int numShips);
};
#endif

