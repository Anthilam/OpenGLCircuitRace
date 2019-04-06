/*
	Racing game project - BRT class
	Modelize the Besan�on Racing Track (fictive)
	2019
	Nicolas Bouchard, Timoth�e Guy, Timoth�e Laurent
*/

#ifndef ____BRT____
#define ____BRT____

#include <vector>

#include "Bleachers.h"
#include "Checker.h"
#include "Patch.h"
#include "StraightLine.h"
#include "Turn.h"

using namespace std;

class BRT {

protected:
	Checker checker;
	vector<Patch> patches;
	vector<StraightLine> lines;
	vector<Turn> turns;
	vector<Bleachers> bleachers;
	vector<Tree> trees;
	vector<Spectator> spectators;

public:
	/* Constructors */
	BRT(void);

	/* getters */
	vector<StraightLine> getLines(void);
	vector<Turn> getTurns(void);
	Checker getChecker(void);
	vector<Patch> getPatches(void);
	vector<Tree> getTrees(void);
	vector<Bleachers> getBleachers(void);
	vector<Spectator> getSpectators(void);

	/* update */
	void update(void);

	/* drawer */
	void draw(void);
	void drawBoundingBoxes(void);
};

#endif // BRT