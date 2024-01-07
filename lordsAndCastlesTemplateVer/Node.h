

#ifndef NODE	
#define NODE	

#include "vectorHeader.h"

class Node
{
    public:
    vector2Int pos;
    uint16_t step;

    Node()
    {
        pos;
        dis = NULL;
        disFromStart = NULL;
        step = 0;
    }
    Node(vector2Int m_pos, vector2Int m_startPos, vector2Int m_endPos)
    {
        pos = m_pos;
        int a = calculateEuclideanDistance(m_pos, m_startPos);
        int b = calculateEuclideanDistance(m_pos, m_endPos);
        dis = a + b;
    }

    // this variant of the node constructor is used for the second phase of the pathfinding
    // when a path is found found and the shortest path should be chosen based on
    // which node has the lowest m_step
    Node(vector2Int m_pos, vector2Int m_startPos, vector2Int m_endPos, uint16_t m_step)
    {
        step = m_step;
        pos = m_pos;
        int a = calculateEuclideanDistance(m_pos, m_startPos);
        int b = calculateEuclideanDistance(m_pos, m_endPos);
        dis = a + b;
    }

    int GetDis() const
    {
        return dis;
    }
    int GetDisFromStart() const
    {
        return disFromStart;
    }

    bool operator==(const Node& other) const
    {
        return pos == other.pos;
    }


    private:
    int dis;
    int disFromStart;

    // this method returns the euclidean distance from 2 dementional round vectors
    // (kinda like drawing a straight line on a piece of paper and measuring it)
    int calculateEuclideanDistance(vector2Int pos1, vector2Int pos2)
    {
        double delta_x = pos2.x * 100 - pos1.x * 100;
        double delta_y = pos2.y * 100 - pos1.y * 100;
        double distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);
        return distance;
    }
};


#endif 


