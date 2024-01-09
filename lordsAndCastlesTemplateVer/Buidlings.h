#pragma once

#include "Tile.h"
#include "GlobalVars.h"
#include "vectorHeader.h"
#include "baseHeader.h"
#include "PerspectiveMath.h"
#include "vGameObject.h"

enum BuildingCurrentState
{
	bldnStateNone = 0,
	bldnStateIdle = 1,
	bldnStateActive = 2
};

// this is a base class 
// it allows the buildings for abstraction and ease of use
class BaseBuilding : public vGameObject
{
	public:
	virtual ~BaseBuilding() {}

	//class needs to override this
	//virtual void Update(float p_deltaTime) = 0;

	// additive methods
	void UnsetUnwalkableTiles();
	void ResetUnwalkableTiles(int p_newRelativePosX1, int p_newRelativePosY1,
		int p_newRelativePosX2, int p_newRelativePosY2);
	void SetCustomEntryPos(vector2Int p_newPos);
	vector2Int GetEntryPos();

	vector2 GetPos() override;
	vector2Int GetGridPos() override;

	// these varables get added to each class that implements BaseBuilding
	protected:
	// points to pre existing memory
	SpriteSheet* m_spriteSheet;
	vector2Int m_gridPos, m_EntryPos;
	// m_textureSize is used for mesuring how big the texture should render
	uint8_t m_width, m_height, m_textureSize;
	// points to pre existing memory
	std::vector<vector2Int>* m_ptrUnwalkableTiles;
	// these ptr's point to relatative positions for rendering
	// these point to pre existing memory
	float* m_ptrRelativeWidth, *m_ptrRelativeHeight;

};

// this building only render 1 sprite 
class IdleBuilding : public BaseBuilding
{
	public:
	IdleBuilding();
	IdleBuilding(SpriteSheet* p_spriteSheet, vector2Int p_gridPos, uint8_t p_width, uint8_t p_height, 
		std::vector<vector2Int>* p_ptrUnwalkableTiles, float* p_ptrRelativeWidth, float* p_ptrRelativeHeight);
	~IdleBuilding();
	void Update(float p_deltaTime) override;
	void Render() override;

	private:
};

// this building will either be idle (render 1 sprite) or animated
// based on the state of the building
class IdleAnimBuidling : public BaseBuilding
{
	public:
	IdleAnimBuidling();
	IdleAnimBuidling(SpriteSheet* p_spriteSheet, vector2Int p_gridPos, uint8_t p_width, uint8_t p_height, float p_workDuration,
		std::vector<vector2Int>* p_ptrUnwalkableTiles, float* p_ptrRelativeWidth, float* p_ptrRelativeHeight);

	~IdleAnimBuidling();

	void Update(float p_deltaTime) override;
	void Render() override;


	void SetBuildingState(BuildingCurrentState p_state);

	private:
	BuildingCurrentState m_state;
	float m_tickAnimTime = 0.0f;
	float m_workDuration;
};


// this building will always be animated and must have atleast 1 row and 2 collums 
class AnimatedBuilding : public BaseBuilding
{
	public:
	AnimatedBuilding();
	AnimatedBuilding(SpriteSheet* p_spriteSheet, vector2Int p_gridPos, uint8_t p_width, uint8_t p_height, float p_workDuration,
		std::vector<vector2Int>* p_ptrUnwalkableTiles, float* p_ptrRelativeWidth, float* p_ptrRelativeHeight, 
		float p_animSpeed = 0.1f);
	~AnimatedBuilding();


	void Update(float p_deltaTime) override;
	void Render() override;

	void SetBuildingState(BuildingCurrentState p_state);


	private:
	uint8_t m_spritesheetColIndex = 0;
	BuildingCurrentState m_state;
	float m_tickAnimTime = 0.0f;
	float m_workDuration, m_animSpeed;
};


