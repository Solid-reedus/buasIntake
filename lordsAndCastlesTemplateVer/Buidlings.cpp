#include "Buidlings.h"


/// basebuilding region

void BaseBuilding::UnsetUnwalkableTiles()
{
	if (m_ptrUnwalkableTiles && !m_ptrUnwalkableTiles->empty())
	{
		for (int x = m_gridPos.x; x < m_gridPos.x + m_width; x++)
		{
			for (int y = m_gridPos.y; y < m_gridPos.y + m_height; y++)
			{
				m_ptrUnwalkableTiles->erase(std::remove(m_ptrUnwalkableTiles->begin(), m_ptrUnwalkableTiles->end(), vector2Int(x, y)), m_ptrUnwalkableTiles->end());
			}
		}
	}
}

void BaseBuilding::ResetUnwalkableTiles(int p_newRelativePosX1, int p_newRelativePosY1,
	int p_newRelativePosX2, int p_newRelativePosY2)
{
	UnsetUnwalkableTiles();

	for (int x = m_gridPos.x + p_newRelativePosX1; x < m_gridPos.x + p_newRelativePosX2; x++)
	{
		for (int y = m_gridPos.y + p_newRelativePosY1; y < m_gridPos.y + p_newRelativePosY2; y++)
		{
			m_ptrUnwalkableTiles->push_back(vector2Int(x, y));
		}
	}

}

void BaseBuilding::SetCustomEntryPos(vector2Int p_newPos)
{
	if (m_ptrUnwalkableTiles)
	{
		if (!m_ptrUnwalkableTiles->empty())
		{
			m_ptrUnwalkableTiles->erase(std::remove(m_ptrUnwalkableTiles->begin(), m_ptrUnwalkableTiles->end(), m_EntryPos), m_ptrUnwalkableTiles->end());
		}
		m_ptrUnwalkableTiles->push_back(p_newPos);
	}
}

vector2Int BaseBuilding::GetEntryPos()
{
	return m_EntryPos;
}

vector2 BaseBuilding::GetPos()
{
	return m_pos;
}

vector2Int BaseBuilding::GetGridPos()
{
	return m_gridPos;
}

/// basebuilding region end



/// idlebuilding region

IdleBuilding::IdleBuilding()
{
	m_spriteSheet = nullptr;
	m_ptrUnwalkableTiles = nullptr;
	m_ptrRelativeWidth = nullptr;
	m_ptrRelativeHeight = nullptr;
	m_gridPos = vector2Int();
	m_width = 0;
	m_height = 0;
}

IdleBuilding::IdleBuilding(SpriteSheet* p_spriteSheet, vector2Int p_gridPos, uint8_t p_width, uint8_t p_height,
	std::vector<vector2Int>* p_ptrUnwalkableTiles, float* p_ptrRelativeWidth, float* p_ptrRelativeHeight)
{
	m_spriteSheet = p_spriteSheet;

	m_gridPos = p_gridPos;
	m_width = p_width;
	m_height = p_height;
	// texture size is the biggest from m_width and m_height
	m_textureSize = (m_width > m_height) ? m_width : m_height;

	m_ptrRelativeWidth = p_ptrRelativeWidth;
	m_ptrRelativeHeight = p_ptrRelativeHeight;

	m_ptrUnwalkableTiles = p_ptrUnwalkableTiles;

	for (int x = m_gridPos.x; x < m_gridPos.x + m_width; x++)
	{
		for (int y = m_gridPos.y; y < m_gridPos.y + m_height; y++)
		{
			m_ptrUnwalkableTiles->push_back(vector2Int(x, y));
		}
	}

	// entry pos
	m_EntryPos = vector2Int(p_gridPos.x, p_gridPos.y + m_height);
	m_ptrUnwalkableTiles->push_back(m_EntryPos);
}

IdleBuilding::~IdleBuilding()
{

}

void IdleBuilding::Update(float p_deltaTime)
{

}

void IdleBuilding::Render()
{
	float isoX, isoY;
	FloatCartesianToIsometric((m_gridPos.x - m_textureSize / 1.25f) + 0.5f, m_gridPos.y - 0.5f, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
	m_spriteSheet->RenderFrom(static_cast<int>(isoX), static_cast<int>(isoY), static_cast<int>(TILE_WIDTH * m_textureSize / 1.25f), static_cast<int>(TILE_HEIGHT * m_textureSize * 1.25f), 0, 0);
}

/// idlebuilding region end




/// idle anim building region 

IdleAnimBuidling::IdleAnimBuidling()
{
	m_spriteSheet = nullptr;
	m_ptrUnwalkableTiles = nullptr;
	m_ptrRelativeWidth = nullptr;
	m_ptrRelativeHeight = nullptr;
	m_gridPos = vector2Int();
	m_width = 0;
	m_height = 0;
	m_workDuration = 0;
	m_state = bldnStateNone;
}

IdleAnimBuidling::IdleAnimBuidling(SpriteSheet* p_spriteSheet, vector2Int p_gridPos, uint8_t p_width, uint8_t p_height, float p_workDuration,
	std::vector<vector2Int>* p_ptrUnwalkableTiles, float* p_ptrRelativeWidth, float* p_ptrRelativeHeight)
{
	m_spriteSheet = p_spriteSheet;

	m_gridPos = p_gridPos;
	m_width = p_width;
	m_height = p_height;

	// texture size is the biggest from m_width and m_height
	m_textureSize = (m_width > m_height) ? m_width : m_height;

	m_state = bldnStateIdle;
	m_workDuration = p_workDuration;

	m_ptrRelativeWidth = p_ptrRelativeWidth;
	m_ptrRelativeHeight = p_ptrRelativeHeight;

	m_ptrUnwalkableTiles = p_ptrUnwalkableTiles;

	for (int x = m_gridPos.x; x < m_gridPos.x + m_width; x++)
	{
		for (int y = m_gridPos.y; y < m_gridPos.y + m_height; y++)
		{
			m_ptrUnwalkableTiles->push_back(vector2Int(x, y));
		}
	}

	// entry pos
	m_EntryPos = vector2Int(p_gridPos.x, p_gridPos.y + m_height);
	m_ptrUnwalkableTiles->push_back(m_EntryPos);
}

void IdleAnimBuidling::Update(float p_deltaTime)
{
	//float isoX, isoY;

	switch (m_state)
	{
	case bldnStateIdle:
	{
		
		//float isoX, isoY;
		//FloatCartesianToIsometric((m_gridPos.x - m_textureSize / 1.25f) + 0.5f, m_gridPos.y - 0.5f, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
		//m_spriteSheet->RenderFrom(static_cast<int>(isoX), static_cast<int>(isoY), static_cast<int>(TILE_WIDTH * m_textureSize / 1.25f), static_cast<int>(TILE_HEIGHT * m_textureSize * 1.25f), 0, 0);
		break;
	}
	case bldnStateActive:
	{
		//m_workDuration
		m_tickAnimTime += p_deltaTime;

		//if the animation is done the return to idle
		if (m_tickAnimTime > m_workDuration)
		{
			m_state = bldnStateIdle;
			m_tickAnimTime = 0;
		}
		//else
		//{
		//	int currentframe = m_tickAnimTime * m_spriteSheet->RowColCount(0) / m_workDuration;
		//	FloatCartesianToIsometric((m_gridPos.x - m_textureSize / 1.25f) + 0.5f, m_gridPos.y - 0.5f, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
		//	m_spriteSheet->RenderFrom(static_cast<int>(isoX), static_cast<int>(isoY), static_cast<int>(TILE_WIDTH * m_textureSize / 1.25f), static_cast<int>(TILE_HEIGHT * m_textureSize * 1.25f), 0, currentframe);
		//
		//}

		break;
	}

		default:
		case bldnStateNone:
		break;
	}
}

void IdleAnimBuidling::Render()
{
	float isoX, isoY;

	switch (m_state)
	{
	case bldnStateIdle:
	{

		//float isoX, isoY;
		FloatCartesianToIsometric((m_gridPos.x - m_textureSize / 1.25f) + 0.5f, m_gridPos.y - 0.5f, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
		m_spriteSheet->RenderFrom(static_cast<int>(isoX), static_cast<int>(isoY), static_cast<int>(TILE_WIDTH * m_textureSize / 1.25f), static_cast<int>(TILE_HEIGHT * m_textureSize * 1.25f), 0, 0);
		break;
	}
	case bldnStateActive:
	{
		int currentframe = m_tickAnimTime * m_spriteSheet->RowColCount(0) / m_workDuration;
		FloatCartesianToIsometric((m_gridPos.x - m_textureSize / 1.25f) + 0.5f, m_gridPos.y - 0.5f, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
		m_spriteSheet->RenderFrom(static_cast<int>(isoX), static_cast<int>(isoY), static_cast<int>(TILE_WIDTH * m_textureSize / 1.25f), static_cast<int>(TILE_HEIGHT * m_textureSize * 1.25f), 0, currentframe);
		break;
	}

		default:
		case bldnStateNone:
		break;
	}
}

void IdleAnimBuidling::SetBuildingState(BuildingCurrentState p_state)
{
	m_state = p_state;
}

IdleAnimBuidling::~IdleAnimBuidling()
{

}

/// idle anim building region end




/// animatedbuilding region 

AnimatedBuilding::AnimatedBuilding()
{
	m_spriteSheet = nullptr;
	m_ptrUnwalkableTiles = nullptr;
	m_ptrRelativeWidth = nullptr;
	m_ptrRelativeHeight = nullptr;
	m_gridPos = vector2Int();
	m_width = 0;
	m_height = 0;
	m_workDuration = 0;
	m_animSpeed = 0;
	m_state = bldnStateNone;
}

AnimatedBuilding::AnimatedBuilding(SpriteSheet* p_spriteSheet, vector2Int p_gridPos, uint8_t p_width, uint8_t p_height, float p_workDuration,
	std::vector<vector2Int>* p_ptrUnwalkableTiles, float* p_ptrRelativeWidth, float* p_ptrRelativeHeight,
	float p_animSpeed)
{
	m_spriteSheet = p_spriteSheet;

	m_gridPos = p_gridPos;
	m_width = p_width;
	m_height = p_height;

	// texture size is the biggest from m_width and m_height
	m_textureSize = (m_width > m_height) ? m_width : m_height;

	m_state = bldnStateIdle;
	m_workDuration = p_workDuration;
	m_animSpeed = p_animSpeed;

	m_ptrRelativeWidth = p_ptrRelativeWidth;
	m_ptrRelativeHeight = p_ptrRelativeHeight;

	m_ptrUnwalkableTiles = p_ptrUnwalkableTiles;

	for (int x = m_gridPos.x; x < m_gridPos.x + m_width; x++)
	{
		for (int y = m_gridPos.y; y < m_gridPos.y + m_height; y++)
		{
			m_ptrUnwalkableTiles->push_back(vector2Int(x, y));
		}
	}

	// entry pos
	m_EntryPos = vector2Int(p_gridPos.x, p_gridPos.y + m_height);
	m_ptrUnwalkableTiles->push_back(m_EntryPos);
}

void AnimatedBuilding::Update(float p_deltaTime)
{
	//float isoX, isoY;

	switch (m_state)
	{
	case bldnStateIdle:
	{
		m_tickAnimTime += p_deltaTime;

		if (m_tickAnimTime >= m_animSpeed)
		{
			m_spritesheetColIndex++;
			if (m_spritesheetColIndex > m_spriteSheet->RowColCount(static_cast<uint8_t>(bldnStateIdle)))
			{
				m_spritesheetColIndex = 0;
			}
			m_tickAnimTime = 0;
		}
		break;
	}
	case bldnStateActive:
	{
		//m_workDuration
		m_tickAnimTime += p_deltaTime;

		//if the animation is done the return to idle
		if (m_tickAnimTime > m_workDuration)
		{
			m_state = bldnStateIdle;
			m_tickAnimTime = 0;
		}
		//else
		//{
		//	int currentframe = m_tickAnimTime * m_spriteSheet->RowColCount(static_cast<int>(bldnStateActive)) / m_workDuration;
		//
		//	printf("animated building frame %d \n", currentframe);
		//
		//	FloatCartesianToIsometric((m_gridPos.x - m_textureSize / 1.25f) + 0.5f, m_gridPos.y - 0.5f, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
		//	m_spriteSheet->RenderFrom(static_cast<int>(isoX), static_cast<int>(isoY), 
		//		static_cast<int>(TILE_WIDTH * m_textureSize / 1.25f), 
		//		static_cast<int>(TILE_HEIGHT * m_textureSize * 1.25f), 0, currentframe);
		//}

		break;
	}

	default:
	case bldnStateNone:
		break;
	}
}

void AnimatedBuilding::Render()
{
	float isoX, isoY;

	switch (m_state)
	{
	case bldnStateIdle:
	{
		FloatCartesianToIsometric((m_gridPos.x - m_textureSize / 1.25f) + 0.5f, m_gridPos.y - 0.5f, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
		m_spriteSheet->RenderFrom(static_cast<int>(isoX), static_cast<int>(isoY),
			static_cast<int>(TILE_WIDTH * m_textureSize / 1.25f),
			static_cast<int>(TILE_HEIGHT * m_textureSize * 1.25f),
			static_cast<uint8_t>(bldnStateIdle), m_spritesheetColIndex);

		break;
	}
	case bldnStateActive:
	{
		int currentframe = m_tickAnimTime * m_spriteSheet->RowColCount(static_cast<int>(bldnStateActive)) / m_workDuration;
		FloatCartesianToIsometric((m_gridPos.x - m_textureSize / 1.25f) + 0.5f, m_gridPos.y - 0.5f, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
		m_spriteSheet->RenderFrom(static_cast<int>(isoX), static_cast<int>(isoY),
			static_cast<int>(TILE_WIDTH * m_textureSize / 1.25f),
			static_cast<int>(TILE_HEIGHT * m_textureSize * 1.25f), 0, currentframe);
		break;
	}

	default:
	case bldnStateNone:
	break;
	}
}

void AnimatedBuilding::SetBuildingState(BuildingCurrentState p_state)
{
	m_state = p_state;
	m_tickAnimTime = 0;
}

AnimatedBuilding::~AnimatedBuilding()
{

}

/// animatedbuilding region end
