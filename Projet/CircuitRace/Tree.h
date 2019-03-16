/*
	Racing game project - Tree class
	Represents a tree (background element)
	2019
	Nicolas Bouchard, Timoth�e Guy, Timoth�e Laurent
*/

#ifndef ____TREE____
#define ____TREE____

class Tree {

private:
	float wTrunk;
	float hTrunk;
	float wLeaves;
	float hLeaves;

public:

	/* Constructors */
	Tree(float wTrunkMin, float wTrunkMax, float hTrunkMin, float hTrunkMax, float wLeavesMin, float wLeavesMax, float hLeavesMin, float hLeavesMax);
	Tree(float wTrunk, float hTrunk, float wLeaves, float hLeaves);
	Tree(Tree *t1);

	/* Destructor */
	~Tree(void);

	/* Print */
	void print(void);

	/* Getters */
	float getWTrunk(void);
	float getHTrunk(void);
	float getWLeaves(void);
	float getHLeaves(void);
};

#endif // Tree