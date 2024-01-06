#include "Tree.h"

Tree::Tree()
{
	m_gridPos = vector2Int();
	m_spriteSheetIdle = nullptr;
	m_spriteSheetTimber = nullptr;
	m_ptrUnwalkableTiles = nullptr;
	m_ptrRelativeWidth = nullptr;
	m_ptrRelativeHeight = nullptr;
}

Tree::Tree(SpriteSheet* p_spriteSheetIdle, SpriteSheet* p_spriteSheetTimber, vector2Int p_gridPos, std::vector<vector2Int>* p_ptrUnwalkableTiles,
	float* p_ptrRelativeWidth, float* p_ptrRelativeHeight)
{
	m_spriteSheetIdle = p_spriteSheetIdle;
	m_spriteSheetTimber = p_spriteSheetTimber;


	m_gridPos = p_gridPos;
	m_ptrRelativeWidth = p_ptrRelativeWidth;
	m_ptrRelativeHeight = p_ptrRelativeHeight;

	m_ptrUnwalkableTiles = p_ptrUnwalkableTiles;

	m_ptrUnwalkableTiles->push_back(m_gridPos);

};

Tree::~Tree()
{

};

void Tree::Update(float p_deltaTime)
{
	if (!treeTimbers)
	{
		int isoX, isoY;
		// tree has a  - 17 and - 5 because the tree spritesheet also contains it timbering
		// which offsets the tree inside the spritesheet
		CartesianToIsometric(m_gridPos.x - 17, m_gridPos.y - 5, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
		m_spriteSheetIdle->RenderFrom(isoX, isoY, TILE_WIDTH * 6, TILE_HEIGHT * 10, 0, 0);
	}
	else
	{
		//m_spriteSheetTimber
	}
}