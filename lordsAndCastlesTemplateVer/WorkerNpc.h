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

// this flag is used to detirmine in what direction the npc is going 
// it is then used to render the correct row of frames to the corosponding dir
enum NpcDirection
{
    dirNone = 0,
    dirTop = 1,
    dirDown = 2,
    dirRight = 4,
    dirLeft = 8
};

// this enum is used for the statemachine
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
    std::vector<vector2Int> FindPath(vector2Int p_target);
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

    // m_gridPos is the possition based on the cartesian map
    // m_pos is relative to the isometric position
    // cartesian and isometric views are explained in the PerspectiveMath.h file
    vector2Int m_gridPos;
    vector2 m_pos;

    // the building the npc is tied to
    BaseBuilding* m_ptrWorkStation;

    // m_ptrMapArray and m_ptrUnwalkableTiles are for checking for walkable tiles
    Tile** m_ptrMapArray;
    std::vector<vector2Int>* m_ptrUnwalkableTiles;


    vector2Int m_workStation, m_stockPile;
    float m_workTime, m_tickTime = 0.0f, m_workingTimer = 0.0f, m_tickAnimTime = 0.0f, walkSpeed = 0.13f;
    uint8_t m_spritesheetColIndex = 0;

    // m_ptrRecource and m_increaseRecourceAmount are tied to the
    // players recources
    uint16_t* m_ptrRecource;
    uint16_t m_increaseRecourceAmount;

    float* m_ptrRelativeWidth, *m_ptrRelativeHeight;
};

#endif