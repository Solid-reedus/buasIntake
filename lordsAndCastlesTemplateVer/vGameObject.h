#ifndef V_GAMEOBJECT
#define V_GAMEOBJECT

#include "VectorHeader.h"

class vGameObject
{
	public:
	virtual ~vGameObject() {};

	//class needs to override this
	virtual void Update(float p_deltaTime) = 0;
	virtual void Render() = 0;

	virtual vector2 GetPos() = 0;
	virtual vector2Int GetGridPos() = 0;

	protected:
	vector2 m_pos;
	vector2Int m_gridPos;
};


#endif