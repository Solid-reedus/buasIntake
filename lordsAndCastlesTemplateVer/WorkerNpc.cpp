#include "WorkerNpc.h"

//std::future<std::vector<vector2Int>>futurePath;

// NOTE
// Ideally we would want the futurePaths vector to be replaced by a futurePath property
// on the WorkerNpc class, but std::future does not have a copy constructor which prevents
// us from making it part of WorkerNpc.
std::map<WorkerNpc*, std::future<std::vector<vector2Int>>> futurePaths;
std::mutex futurePathsMutex;

WorkerNpc::WorkerNpc()
{
    m_spriteSheet = nullptr;
    m_ptrMapArray = nullptr;
    m_ptrRelativeWidth = nullptr;
    m_ptrRelativeHeight = nullptr;
    m_ptrUnwalkableTiles = nullptr;
    m_ptrRecource = nullptr;

    m_pos = vector2();
    m_workStation = vector2Int();
    m_stockPile = vector2Int();

    m_workTime = 0;
    m_increaseRecourceAmount = 0;
}

/*
WorkerNpc::WorkerNpc(const WorkerNpc& a) {
    m_spriteSheet = a.m_spriteSheet;
    m_ptrMapArray = a.m_ptrMapArray;
    m_ptrRelativeWidth = a.m_ptrRelativeWidth;
    m_ptrRelativeHeight = a.m_ptrRelativeHeight;
    m_ptrUnwalkableTiles = a.m_ptrUnwalkableTiles;
    m_ptrRecource = a.m_ptrRecource;

    m_pos = a.m_pos;
    m_workStation = a.m_workStation;
    m_stockPile = a.m_stockPile;

    m_workTime = a.m_workTime;
    m_increaseRecourceAmount = a.m_increaseRecourceAmount;

    m_state = a.m_state;
}
*/

WorkerNpc::WorkerNpc(SpriteSheet* p_spriteSheet, Tile** p_ptrMapArray, std::vector<vector2Int>* p_ptrUnwalkableTiles,
    vector2Int p_startPos, const vector2Int p_workStation, const vector2Int p_stockPile, BaseBuilding* p_ptrWorkStation,
    const float p_workTime, float* p_ptrRelativeWidth, float* p_ptrRelativeHeight,
    uint16_t* p_refRecource, uint16_t p_increaseRecourceAmount)
{
	m_spriteSheet = p_spriteSheet;
    m_ptrMapArray = p_ptrMapArray;
    m_ptrUnwalkableTiles = p_ptrUnwalkableTiles;
    m_ptrWorkStation = p_ptrWorkStation;

	m_gridPos = p_startPos;

    m_ptrRecource = p_refRecource;
    m_increaseRecourceAmount = p_increaseRecourceAmount;

    m_ptrRelativeWidth = p_ptrRelativeWidth;
    m_ptrRelativeHeight = p_ptrRelativeHeight;

	m_pos = vector2(p_startPos.x, p_startPos.y);

	m_workStation = p_workStation;
	m_stockPile = p_stockPile;

	m_workTime = p_workTime;

	m_state = npcStateIdle;

    FindPathAsync(p_workStation, npcStateWalkToWork);
}


WorkerNpc::~WorkerNpc()
{
	
}


void WorkerNpc::Update(float p_deltaTime)
{
	m_tickTime += p_deltaTime;
	m_tickAnimTime += p_deltaTime;

	if (m_tickTime > TICK_INTERVAL)
	{
		Tick(m_tickTime);
		m_tickTime = 0;
	}
	if (m_tickAnimTime > ANIM_TICK_INTERVAL)
	{
		m_tickAnimTime = 0;
		m_spritesheetColIndex++;

        //m_spriteSheet->RenderFrom(p_xPos, p_yPos, p_width, p_height, m_row, m_col);
		if (m_spritesheetColIndex >= m_spriteSheet->RowColCount(static_cast<uint8_t>(m_lookDir)))
		{
			m_spritesheetColIndex = 0;
		}
	}

    if (!(m_state == npcStateWorking))
    {
        float isoX, isoY;
        FloatCartesianToIsometric(m_pos.x, m_pos.y, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, *m_ptrRelativeWidth, *m_ptrRelativeHeight);
        m_spriteSheet->RenderFrom(static_cast<int>(isoX), static_cast<int>(isoY) - NPC_HEIGHT / 2, NPC_WIDTH, NPC_HEIGHT, static_cast<uint8_t>(m_lookDir), m_spritesheetColIndex);
    }

}



void WorkerNpc::Tick(float p_deltaTime)
{
    if (!m_path.empty())
    {
        //printf("path %d \n", m_path.size());
    }
    else
    {
        //printf("empty \n");
    }

    printf("state %d \n", m_state);

	//update stuff
	switch (m_state)
	{
		case npcStateIdle:
		{
            std::lock_guard<std::mutex> lock(futurePathsMutex);
            if (futurePaths.find(this) != futurePaths.end() && futurePaths[this]._Is_ready() && m_path.empty())
            {
                m_path = futurePaths[this].get();
                futurePaths.erase(this);
                m_state = m_nextState;
            }
			break;
            // futurePathsMutex automatically unlocked because lock_guard is destroyed.
		}
		case npcStateWalkToWork:
		{
			//reached target
			if (m_path.empty())
			{
                if (IdleAnimBuidling* animB = dynamic_cast<IdleAnimBuidling*>(m_ptrWorkStation))
                {
                    animB->SetBuildingState(bldnStateActive);
                }
                else if (AnimatedBuilding* animB = dynamic_cast<AnimatedBuilding*>(m_ptrWorkStation))
                {
                    animB->SetBuildingState(bldnStateActive);
                }

				m_state = npcStateWorking;
			}
			else
			{
				Walk();
			}
			break;
		}
		case npcStateWalkToStoc:
		{
			//reached target
			if (m_path.empty())
			{
                *m_ptrRecource += m_increaseRecourceAmount;
				//m_state = npcStateWalkToWork;
                m_state = npcStateIdle;
                FindPathAsync(m_workStation, npcStateWalkToWork);
				//FindPath(m_workStation);
			}
			else
			{
				Walk();
			}
			break;
		}
		case npcStateWorking:
		{
            //printf("working \n");
            m_workingTimer += p_deltaTime;
			//worker has worked enough
            printf("m_workingTimer = %f \n", m_workingTimer);

			if (m_workingTimer > m_workTime)
			{
                

                printf("done working \n");
				m_workingTimer = 0;
				//m_state = npcStateWalkToStoc;
				//FindPath(m_stockPile);

                m_state = npcStateIdle;
                FindPathAsync(m_stockPile, npcStateWalkToStoc);
			}
			break;
		}
		case npcStateNone:
		default:
        {
            printf("error: m_state is npcStateNone \n");
		    break;
        }
	}
}

void WorkerNpc::FindPath(const vector2Int p_target)
{
    //this vector is used to check what node is yet to be explored
    std::vector<Node> nodesToDo;

    vector2Int gridPos = vector2Int(static_cast<int>(m_pos.x), (static_cast<int>(m_pos.y)));
    nodesToDo.push_back(Node(gridPos, gridPos, p_target));

    //this map keeps track of explored nodes
    std::map<vector2Int, Node> nodeMap;
    (nodeMap)[gridPos] = Node(gridPos, gridPos, p_target);

    bool foundPath = false;

    uint16_t currentStep = 0;

    while (!nodesToDo.empty())
    {
        // get the node with the lowest distance 
        auto lowestNode = std::min_element(nodesToDo.begin(), nodesToDo.end(),
            [&nodeMap](const Node& val1, const Node& val2)
            {
                // check if val1 and val2 are in nodemap
                // if so they wont be the lowest
                bool val1IsInMap = nodeMap.find(val1.pos) != nodeMap.end();
                bool val2IsInMap = nodeMap.find(val2.pos) != nodeMap.end();

                // if val1IsInMap is in the map it will return val2IsInMap
                if (val1IsInMap && !val2IsInMap)
                {
                    return false;
                }
                // if val2IsInMap is in the map it will return val1IsInMap
                else if (!val1IsInMap && val2IsInMap)
                {
                    return true;
                }
                // otherwise combare which is the lowest
                return val1.GetDis() < val2.GetDis();
            });


        Node* currentnode = &*lowestNode;
        vector2Int pos = currentnode->pos;
        Node node = *currentnode;

        nodesToDo.erase(lowestNode);

        //printf("lowest node x = %d and y = %d \n", pos.x, pos.y);

        for (size_t x = pos.x - 1; x <= pos.x + 1; x++)
        {
            for (size_t y = pos.y - 1; y <= pos.y + 1; y++)
            {
                // if it is it self skip this loop iteration
                if (x == pos.x && y == pos.y)
                {
                    continue;
                }
                // if out of bounds then skip this loop iteration
                else if (x <= 1 || y <= 1 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
                {
                    continue;
                }
                // if current node is the end node break
                else if (x == p_target.x && y == p_target.y)
                {
                    (nodeMap)[p_target] = Node(p_target, gridPos, p_target);
                    foundPath = true;
                    break;
                }
                // if the nodemap already contains x and y
                // then skip this loop iteration
                else if (nodeMap.find(vector2Int(x, y)) != nodeMap.end())
                {
                    continue;
                }
                // if the node is on a unwalkable tile then skip this iteration
                else if (m_ptrUnwalkableTiles->size() && 
                    std::find(m_ptrUnwalkableTiles->begin(), m_ptrUnwalkableTiles->end(), 
                    vector2Int(x, y)) != m_ptrUnwalkableTiles->end())
                {
                    continue;
                }
                // if all of there other statements are false and
                // the node is walkable check further if node is allowed
                // to be added
                else if(m_ptrMapArray[x + (y * MAP_HEIGHT)]->tileFlags & tlfwalkable)
                {
                    currentStep++;
                    nodesToDo.push_back(Node(vector2Int(x, y), gridPos, p_target, currentStep));
                }
            }

            // if foundPath is true, break early
            //no reason to stay here
            if (foundPath)
            {
                break;
            }
        }

        // add worked on node to nodemap so it can be checked off as a done node
        (nodeMap)[pos] = node;

        // if foundPath is true, break early
        //no reason to stay here
        if (foundPath)
        {
            break;
        }
    }

    // if the path is found find the shortest path
    if (foundPath)
    {
        bool foundUsablePath = false;

        // this vector is the final path that wil be returned
        // it needs to be deleted outside of Findpath otherwise a 
        // memory leak will occur
        std::vector<Node> path = std::vector<Node>();
        std::vector<Node*> illegalNodes;


        // this vector keeps track of possible nodes that will be add
        std::vector<Node*> possibleNextNode;

        // it pushes the end position first
        // the path will be filled from the end to front
        path.push_back((nodeMap)[p_target]);

        while (!foundUsablePath)
        {
            Node currentNode = path[path.size() - 1];

            for (size_t x = currentNode.pos.x - 1; x <= currentNode.pos.x + 1; x++)
            {
                for (size_t y = currentNode.pos.y - 1; y <= currentNode.pos.y + 1; y++)
                {
                    // if its on it self then skip this loop iteration
                    if (x == currentNode.pos.x && y == currentNode.pos.y)
                    {
                        continue;
                    }
                    // if it us out of bound skip this loop iteration
                    else if (x < 1 || y < 1 || x > MAP_WIDTH || y > MAP_HEIGHT)
                    {
                        continue;
                    }
                    // if its on the starting place then break loop
                    else if (x == gridPos.x && y == gridPos.y)
                    {
                        foundUsablePath = true;
                        break;
                    }
                    // if the position is noted down on the nodemap then check
                    // if path already contains it if both are false
                    // then add it to the path
                    else if (nodeMap.find(vector2Int(x, y)) != nodeMap.end())
                    {
                        bool isAlreadyInPath = false;
                        for (const Node n : path)
                        {
                            if (n.pos.x == x && n.pos.y == y)
                            {
                                isAlreadyInPath = true;
                                break;
                            }
                        }
                        if (!isAlreadyInPath)
                        {
                            possibleNextNode.push_back(&(nodeMap)[vector2Int(x, y)]);
                        }
                    }
                }
                if (foundUsablePath)
                {
                    break;
                }
            }


            // if the route isnt complete add a new node to the path
            if (!foundUsablePath)
            {
                auto lowest = std::min_element(possibleNextNode.begin(), possibleNextNode.end(),
                    [](const Node* val1, const Node* val2)
                    {
                        return val1->step < val2->step;
                    });


                Node* node = *lowest;

                for (Node* n : possibleNextNode)
                {
                    // if n is already in illegalNodes then skip this iteration
                    if (n->pos == node->pos)
                    {
                        continue;
                    }
                    else
                    {
                        illegalNodes.push_back(n);
                    }
                }

                // push the lowest node that isnt already in the list
                path.push_back(*node);
                //clear the list so the selection is only 1 tile from the currentNode
                possibleNextNode.clear();

            }
        }


        // found path
        std::reverse(path.begin(), path.end());
        m_path.clear();
        for (const Node &n : path)
        {
            m_path.push_back(n.pos);
        }
        printf("path count %d \n", path.size());
        return;
    }
    else
    {
        m_state = npcStateIdle;
        printf("no path found \n");
        return;
    }
}

std::vector<vector2Int> WorkerNpc::FindPath2(vector2Int p_target)
{
    std::vector<vector2Int> newPath;
    //this vector is used to check what node is yet to be explored
    std::vector<Node> nodesToDo;

    vector2Int gridPos = vector2Int(static_cast<int>(m_pos.x), (static_cast<int>(m_pos.y)));
    nodesToDo.push_back(Node(gridPos, gridPos, p_target));

    //this map keeps track of explored nodes
    std::map<vector2Int, Node> nodeMap;
    (nodeMap)[gridPos] = Node(gridPos, gridPos, p_target);

    bool foundPath = false;

    uint16_t currentStep = 0;

    while (!nodesToDo.empty())
    {
        // get the node with the lowest distance 
        auto lowestNode = std::min_element(nodesToDo.begin(), nodesToDo.end(),
            [&nodeMap](const Node& val1, const Node& val2)
            {
                // check if val1 and val2 are in nodemap
                // if so they wont be the lowest
                bool val1IsInMap = nodeMap.find(val1.pos) != nodeMap.end();
                bool val2IsInMap = nodeMap.find(val2.pos) != nodeMap.end();

                // if val1IsInMap is in the map it will return val2IsInMap
                if (val1IsInMap && !val2IsInMap)
                {
                    return false;
                }
                // if val2IsInMap is in the map it will return val1IsInMap
                else if (!val1IsInMap && val2IsInMap)
                {
                    return true;
                }
                // otherwise combare which is the lowest
                return val1.GetDis() < val2.GetDis();
            });


        Node* currentnode = &*lowestNode;
        vector2Int pos = currentnode->pos;
        Node node = *currentnode;

        nodesToDo.erase(lowestNode);

        //printf("lowest node x = %d and y = %d \n", pos.x, pos.y);

        for (size_t x = pos.x - 1; x <= pos.x + 1; x++)
        {
            for (size_t y = pos.y - 1; y <= pos.y + 1; y++)
            {
                // if it is it self skip this loop iteration
                if (x == pos.x && y == pos.y)
                {
                    continue;
                }
                // if out of bounds then skip this loop iteration
                else if (x <= 1 || y <= 1 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
                {
                    continue;
                }
                // if current node is the end node break
                else if (x == p_target.x && y == p_target.y)
                {
                    (nodeMap)[p_target] = Node(p_target, gridPos, p_target);
                    foundPath = true;
                    break;
                }
                // if the nodemap already contains x and y
                // then skip this loop iteration
                else if (nodeMap.find(vector2Int(x, y)) != nodeMap.end())
                {
                    continue;
                }
                // if the node is on a unwalkable tile then skip this iteration
                else if (m_ptrUnwalkableTiles->size() &&
                    std::find(m_ptrUnwalkableTiles->begin(), m_ptrUnwalkableTiles->end(),
                        vector2Int(x, y)) != m_ptrUnwalkableTiles->end())
                {
                    continue;
                }
                // if all of there other statements are false and
                // the node is walkable check further if node is allowed
                // to be added
                else if (m_ptrMapArray[x + (y * MAP_HEIGHT)]->tileFlags & tlfwalkable)
                {
                    currentStep++;
                    nodesToDo.push_back(Node(vector2Int(x, y), gridPos, p_target, currentStep));
                }
            }

            // if foundPath is true, break early
            //no reason to stay here
            if (foundPath)
            {
                break;
            }
        }

        // add worked on node to nodemap so it can be checked off as a done node
        (nodeMap)[pos] = node;

        // if foundPath is true, break early
        //no reason to stay here
        if (foundPath)
        {
            break;
        }
    }


    // if the path is found find the shortest path
    if (foundPath)
    {
        bool foundUsablePath = false;

        // this vector is the final path that wil be returned
        // it needs to be deleted outside of Findpath otherwise a 
        // memory leak will occur
        std::vector<Node> path = std::vector<Node>();
        std::vector<Node*> illegalNodes;


        // this vector keeps track of possible nodes that will be add
        std::vector<Node*> possibleNextNode;

        // it pushes the end position first
        // the path will be filled from the end to front
        path.push_back((nodeMap)[p_target]);

        while (!foundUsablePath)
        {
            Node currentNode = path[path.size() - 1];

            for (size_t x = currentNode.pos.x - 1; x <= currentNode.pos.x + 1; x++)
            {
                for (size_t y = currentNode.pos.y - 1; y <= currentNode.pos.y + 1; y++)
                {
                    // if its on it self then skip this loop iteration
                    if (x == currentNode.pos.x && y == currentNode.pos.y)
                    {
                        continue;
                    }
                    // if it us out of bound skip this loop iteration
                    else if (x < 1 || y < 1 || x > MAP_WIDTH || y > MAP_HEIGHT)
                    {
                        continue;
                    }
                    // if its on the starting place then break loop
                    else if (x == gridPos.x && y == gridPos.y)
                    {
                        foundUsablePath = true;
                        break;
                    }
                    // if the position is noted down on the nodemap then check
                    // if path already contains it if both are false
                    // then add it to the path
                    else if (nodeMap.find(vector2Int(x, y)) != nodeMap.end())
                    {
                        bool isAlreadyInPath = false;
                        for (const Node n : path)
                        {
                            if (n.pos.x == x && n.pos.y == y)
                            {
                                isAlreadyInPath = true;
                                break;
                            }
                        }
                        if (!isAlreadyInPath)
                        {
                            possibleNextNode.push_back(&(nodeMap)[vector2Int(x, y)]);
                        }
                    }
                }
                if (foundUsablePath)
                {
                    break;
                }
            }


            // if the route isnt complete add a new node to the path
            if (!foundUsablePath)
            {
                auto lowest = std::min_element(possibleNextNode.begin(), possibleNextNode.end(),
                    [](const Node* val1, const Node* val2)
                    {
                        return val1->step < val2->step;
                    });


                Node* node = *lowest;

                for (Node* n : possibleNextNode)
                {
                    // if n is already in illegalNodes then skip this iteration
                    if (n->pos == node->pos)
                    {
                        continue;
                    }
                    else
                    {
                        illegalNodes.push_back(n);
                    }
                }

                // push the lowest node that isnt already in the list
                path.push_back(*node);
                //clear the list so the selection is only 1 tile from the currentNode
                possibleNextNode.clear();

            }
        }


        // found path
        std::reverse(path.begin(), path.end());
        //m_path.clear();
        for (const Node& n : path)
        {
            newPath.push_back(n.pos);
        }
        return newPath;
        printf("path count %d \n", path.size());
        //return;
    }
    else
    {
        m_state = npcStateIdle;
        printf("no path found \n");
        return newPath;
    }
}

void WorkerNpc::FindPathAsync(const vector2Int p_target, const NpcCurrentState p_newState) 
{
    std::lock_guard<std::mutex> lock(futurePathsMutex);
    futurePaths[this] = std::async(std::launch::async, &WorkerNpc::FindPath2, *this, p_target);
    m_nextState = p_newState;
    // futurePathsMutex automatically unlocked because lock_guard is destroyed.
}


void WorkerNpc::Walk()
{
	if (!m_path.empty())
	{
		vector2 direction = vector2(m_path.front().x, m_path.front().y) - m_pos;
		double magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		vector2 normalizedDirection(direction.x / magnitude, direction.y / magnitude);


		uint8_t dir = dirNone;

		if (normalizedDirection.y > 0.4)
		{
			dir |= dirDown;
		}
		else if (normalizedDirection.y < -0.4)
		{
			dir |= dirTop;
		}

		if (normalizedDirection.x > 0.4)
		{
			dir |= dirRight;
		}
		else if (normalizedDirection.x < -0.4)
		{
			dir |= dirLeft;
		}

		CheckForNewLookDir(dir);

		if (magnitude > 0.1)
		{
			m_pos += normalizedDirection * walkSpeed;
		}
		if (magnitude < 0.3)
		{
			m_path.erase(m_path.begin());
		}
	}
}

void WorkerNpc::CheckForNewLookDir(uint8_t p_dir)
{
	switch (p_dir)
	{
		//top
		case dirTop:
		{
			m_lookDir = npcWalkTR;
			break;
		}
		// top right
		case dirTop | dirRight:
		{
			m_lookDir = npcWalkR;
			break;
		}
		//right
		case dirRight:
		{
			m_lookDir = npcWalkBR;
			break;
		}
		//bottom right
		case dirDown | dirRight:
		{
			m_lookDir = npcWalkB;
			break;
		}
		//bottom
		case dirDown:
		{
			m_lookDir = npcWalkBL;
			break;
		}
		//bottom left
		case dirDown | dirLeft:
		{
			m_lookDir = npcWalkL;
			break;
		}
		//left
		case dirLeft:
		{
			m_lookDir = npcWalkTL;
			break;
		}
		//top left
		case dirTop | dirLeft:
		{
			m_lookDir = npcWalkT;
			break;
		}
		default:
		break;
	}
}