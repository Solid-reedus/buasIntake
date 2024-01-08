#ifndef TREE
#define TREE

#include "Tile.h"
#include "GlobalVars.h"
#include "vectorHeader.h"
#include "baseHeader.h"
#include "PerspectiveMath.h"

enum TreeStates
{
	treestateNone,
	treestateIdle,
	treestateTimber,
	treestateGone,
};

class Tree
{
	public:
	Tree();
	Tree(SpriteSheet* p_spriteSheetIdle, SpriteSheet* p_spriteSheetTimber, vector2Int p_gridPos, std::vector<vector2Int>* p_ptrUnwalkableTiles,
		float* p_ptrRelativeWidth, float* p_ptrRelativeHeight);
	~Tree();
	void Update(float p_deltaTime);

	// GetGridPosition is const because 
	// methods used by lambdas need to be const
	vector2Int GetGridPosition() const;
	void Timber();

	bool occupied = false;

	private:
	SpriteSheet* m_spriteSheetIdle, * m_spriteSheetTimber;
	vector2Int m_gridPos;
	std::vector<vector2Int>* m_ptrUnwalkableTiles;
	float* m_ptrRelativeWidth, * m_ptrRelativeHeight;

	TreeStates m_state = treestateIdle;
	float m_tickAnimTime = 0.0f;
	float m_timberDuration = 1200;
	float m_growTime = 10000;
};

#endif
