#ifndef TREE
#define TREE

#include "Tile.h"
#include "GlobalVars.h"
#include "vectorHeader.h"
#include "baseHeader.h"
#include "PerspectiveMath.h"
#include "vGameObject.h"

enum TreeStates
{
	treestateNone,
	treestateIdle,
	treestateTimber,
	treestateGone,
};

class Tree : public vGameObject
{
	public:
	Tree();
	Tree(SpriteSheet* p_spriteSheetIdle, SpriteSheet* p_spriteSheetTimber, vector2Int p_gridPos, std::vector<vector2Int>* p_ptrUnwalkableTiles,
		float* p_ptrRelativeWidth, float* p_ptrRelativeHeight);
	~Tree();
	void Update(float p_deltaTime) override;
	void Render() override;

	vector2 GetPos() override;
	vector2Int GetGridPos() override;

	// GetGridPosition is const because 
	// methods used by lambdas need to be const
	vector2Int GetGridPosition() const;
	void Timber();

	bool occupied = false;

	private:
	// m_spriteSheetIdle and m_spriteSheetTimber are both ptr's
	// to external data
	// tree has 2 SpriteSheets beacause of frame dips
	// m_spriteSheetIdle has a lot less transparent pixels so its read faster
	SpriteSheet* m_spriteSheetIdle, *m_spriteSheetTimber;
	vector2Int m_gridPos;
	// m_ptrUnwalkableTiles, m_ptrRelativeWidth and m_ptrRelativeHeight
	// are ptr's to external data
	std::vector<vector2Int>* m_ptrUnwalkableTiles;
	float* m_ptrRelativeWidth, * m_ptrRelativeHeight;

	TreeStates m_state = treestateIdle;
	float m_tickAnimTime = 0.0f;
	float m_timberDuration = 1200.0f;
	float m_growTime = 10000.0f;
};

#endif
