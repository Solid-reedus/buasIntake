#ifndef WORKER_NPC
#define WORKER_NPC

#include "PerspectiveMath.h"
#include "vectorHeader.h"
#include "GlobalVars.h"
#include "template.h"
#include "Node.h"
#include "Tile.h"
#include <map>
#include "Buidlings.h"
#include <future>
#include <mutex>


/*
const int NPC_WIDTH = 40;
const int NPC_HEIGHT = 54;
*/

const int NPC_WIDTH = 68;
const int NPC_HEIGHT = 92;


enum NpcLookDir
{
    npcWalkTL = 0,
    npcWalkT = 1,
    npcWalkTR = 2,
    npcWalkR = 3,
    npcWalkBR = 4,
    npcWalkB = 5,
    npcWalkBL = 6,
    npcWalkL = 7,
};

enum NpcDirection
{
    dirNone = 0,
    dirTop = 1,
    dirDown = 2,
    dirRight = 4,
    dirLeft = 8
};

enum NpcCurrentState
{
    npcStateNone = 0,
    npcStateIdle = 1,
    npcStateWorking = 2,
    npcStateWalkToWork = 3,
    npcStateWalkToStoc = 4,
};

class WorkerNpc
{
	public:
    WorkerNpc();
    //WorkerNpc(const WorkerNpc&);
	WorkerNpc(SpriteSheet* p_spriteSheet, Tile** p_ptrMapArray, std::vector<vector2Int>* p_ptrUnwalkableTiles,
        vector2Int p_startPos, const vector2Int p_workStation, const vector2Int p_stockPile, BaseBuilding* p_ptrWorkStation,
        const float p_workTime, float* p_ptrRelativeWidth, float* p_ptrRelativeHeight, 
        uint16_t* p_refRecource, uint16_t p_increaseRecourceAmount);
	~WorkerNpc();

    //general npc update
    void Update(float p_deltaTime);
    void Tick(float p_deltaTime);

	private:
    //fill the m_path with positions to walk too
    void FindPath(const vector2Int p_target);
    std::vector<vector2Int> FindPath2(vector2Int p_target);
    void FindPathAsync(const vector2Int p_target, const NpcCurrentState p_newState);
    //check what dir the npc should look
    void Walk();
    void CheckForNewLookDir(uint8_t p_dir);

	// ptr to spritesheet and render based on relative pos and rotation
	SpriteSheet* m_spriteSheet;
    NpcLookDir m_lookDir = npcWalkTL;

    //std::atomic<NpcCurrentState> m_state = npcStateNone;
    NpcCurrentState m_state = npcStateNone, m_nextState = npcStateNone;

    std::vector<vector2Int> m_path;

    uint8_t m_dirFlags = dirNone;
    vector2 m_pos;
    vector2Int m_gridPos;

    BaseBuilding* m_ptrWorkStation;

    // m_ptrMapArray and m_ptrUnwalkableTiles are for checking for walkable tiles
    Tile** m_ptrMapArray;
    std::vector<vector2Int>* m_ptrUnwalkableTiles;

    vector2Int m_workStation, m_stockPile;
    float m_workTime, m_tickTime = 0.0f, m_workingTimer = 0.0f, m_tickAnimTime = 0.0f, walkSpeed = 0.13f;
    uint8_t m_spritesheetColIndex = 0;

    uint16_t* m_ptrRecource;
    uint16_t m_increaseRecourceAmount;

    float* m_ptrRelativeWidth, *m_ptrRelativeHeight;
};

#endif