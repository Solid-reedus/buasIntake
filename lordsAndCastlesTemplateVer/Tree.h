#ifndef TREE
#define TREE

#include "Tile.h"
#include "GlobalVars.h"
#include "vectorHeader.h"
#include "baseHeader.h"
#include "PerspectiveMath.h"

class Tree
{
	public:
	Tree();
	Tree(SpriteSheet* p_spriteSheetIdle, SpriteSheet* p_spriteSheetTimber, vector2Int p_gridPos, std::vector<vector2Int>* p_ptrUnwalkableTiles,
		float* p_ptrRelativeWidth, float* p_ptrRelativeHeight);
	~Tree();
	void Update(float p_deltaTime);

	private:
	SpriteSheet* m_spriteSheetIdle, *m_spriteSheetTimber;
	vector2Int m_gridPos;
	std::vector<vector2Int>* m_ptrUnwalkableTiles;
	float* m_ptrRelativeWidth, *m_ptrRelativeHeight;

	// all the timber varables are used for when the tree should timber (fall over)
	bool treeTimbers = false;
	float m_tickAnimTime = 0.0f;
	float m_timberDuration = 1200;

};

#endif
