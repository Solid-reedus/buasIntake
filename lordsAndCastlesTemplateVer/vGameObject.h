#ifndef V_GAMEOBJECT
#define V_GAMEOBJECT

#include "VectorHeader.h"

class vGameObject
{
	public:
	virtual ~vGameObject() {};

	// class needs to override this
	// update should be execuded every frame
	// render only when the gameobject should be rendered
	virtual void Update(float p_deltaTime) = 0;
	virtual void Render() = 0;

	virtual vector2 GetPos() = 0;
	virtual vector2Int GetGridPos() = 0;

	// each gameobject has a position
	// m_pos is relative to the camera
	// m_gridPos is relative to the isometric grid
	protected:
	vector2 m_pos;
	vector2Int m_gridPos;
};


#endif