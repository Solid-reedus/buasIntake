#ifndef WORKER_NPC
#define WORKER_NPC

#include "PerspectiveMath.h"
#include "vectorHeader.h"
#include "vGameObject.h"
#include "GlobalVars.h"
#include "Buidlings.h"
#include "template.h"
#include "Tree.h"
#include "Node.h"
#include "Tile.h"

#include <algorithm>
#include <future>
#include <mutex>
#include <map>

const int NPC_WIDTH = 68;
const int NPC_HEIGHT = 92;

// this enum is used for what row the 
// spritesheet row it should use
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
    npcWork = 8,
};

// this is a flag that is used to detirmine what
// direction the npc is headed
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

// baseNpc is a base class that adds pathfinding
// and varables to determine what to render and where
class BaseNpc : public vGameObject 
{
    public:
    virtual ~BaseNpc() {}  // Virtual destructor

    virtual void Update(float p_deltaTime) = 0;
    virtual void Tick(float p_deltaTime) = 0;
    std::vector<vector2Int> FindPath(vector2Int p_target);

    vector2 GetPos() override;
    vector2Int GetGridPos() override;

    protected:

    void Walk();
    void CheckForNewLookDir(uint8_t p_dir);


    Tile** m_ptrMapArray;
    std::vector<vector2Int>* m_ptrUnwalkableTiles;

    NpcLookDir m_lookDir = npcWalkTL;
    uint8_t m_dirFlags = dirNone;

    std::vector<vector2Int> m_path;

    float* m_ptrRelativeWidth, * m_ptrRelativeHeight;
    NpcCurrentState m_state = npcStateNone, m_nextState = npcStateNone;

    float m_workTime, m_tickTime = 0.0f, m_workingTimer = 0.0f, m_tickAnimTime = 0.0f, walkSpeed = 0.13f;
    float waitTime = 1000;
};

// worker npc's are npc's that have a workstation and work at set
// worksatation. they will then drop off the recource and go back to 
// their workstation
class WorkerNpc : public BaseNpc
{
    public:
    WorkerNpc();
    //WorkerNpc(const WorkerNpc&);
    WorkerNpc(SpriteSheet* p_spriteSheet, Tile** p_ptrMapArray, std::vector<vector2Int>* p_ptrUnwalkableTiles,
        vector2Int p_startPos, const vector2Int p_workStation, const vector2Int p_stockPile, BaseBuilding* p_ptrWorkStation,
        const float p_workTime, float* p_ptrRelativeWidth, float* p_ptrRelativeHeight,
        uint32_t* p_refRecource, uint32_t p_increaseRecourceAmount);
    ~WorkerNpc();

    //general npc update
    void Update(float p_deltaTime) override;
    void Render() override;
    void Tick(float p_deltaTime) override;


    private:
    void FindPathAsync(const vector2Int p_target, const NpcCurrentState p_newState);

    SpriteSheet* m_spriteSheet;
    BaseBuilding* m_ptrWorkStation;

    // worker npc's loop is
    // 1 - go to workstation
    // 2 - work
    // 3 - go to stockpile or granary
    // 4 - repeat
    vector2Int m_workStation, m_stockPile;
    uint8_t m_spritesheetColIndex = 0;

    uint32_t* m_ptrRecource;
    uint32_t m_increaseRecourceAmount;
};

// wood cutter npc's will search for trees and cut them
// they will then wait till they regrow
class WoodCutterNpc : public BaseNpc
{
    public:
    WoodCutterNpc::WoodCutterNpc();
    WoodCutterNpc::WoodCutterNpc(SpriteSheet* p_spriteSheet, Tile** p_ptrMapArray, std::vector<vector2Int>* p_ptrUnwalkableTiles,
        vector2Int p_startPos, const vector2Int p_stockPile, const float p_workTime, float* p_ptrRelativeWidth,
        float* p_ptrRelativeHeight, uint32_t* p_refRecource, uint32_t p_increaseRecourceAmount, std::vector<Tree*>* p_ptrTrees);

    WoodCutterNpc::~WoodCutterNpc();

    //general npc update
    void Update(float p_deltaTime) override;
    void Render() override;
    void Tick(float p_deltaTime) override;

    private:
    void FindPathAsync(const vector2Int p_target, const NpcCurrentState p_newState);

    void FindClosestTree();

    SpriteSheet* m_spriteSheet;

    vector2Int m_stockPile;
    uint8_t m_spritesheetColIndex = 0;

    uint32_t* m_ptrRecource;
    uint32_t m_increaseRecourceAmount;

    std::vector<Tree*>* m_ptrTrees;
    Tree* m_ptrCurrentTree = nullptr;
};

#endif