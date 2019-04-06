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
	vector<TrackPart*> track;
	vector<Bleachers> bleachers;
	vector<Tree> trees;
	vector<Spectator> spectators;

public:
	/* Constructors */
	BRT(void);

	/* getters */
	vector<TrackPart*> *getTrack(void);
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

	void resetIsColliding(void);
};

#endif // BRT