//
//  PathFind.h
//  CocosTest
//
//  Created by Michael Levesque on 7/8/17.
//
//

#ifndef PathFind_h
#define PathFind_h

#include <list>             // for final path
#include <set>              // for open list
#include <unordered_map>    // for closed list
#include "GridLayout.h"

/**
 * This class performs A* pathfinding and stores the results.
 */
class PathFind {
private:
    // pointer to the grid layout to use with pathfinding
    const GridLayout* m_layout;
    
    // for storing the start and goal positions
    GridPoint m_startPosition;
    GridPoint m_goalPosition;
    
    // stores whether or not pathfinding successfully found a path
    bool m_success;
    
    // the list of the final path
    std::list<GridPoint> m_finalPath;
    
    /**
     * Definition of a node used during pathing
     */
    struct Node {
        // constructor. Just initializes member variables and sets the grid point
        Node (const GridPoint p);
        
        // stored key that is used when inserting into maps
        unsigned key;
        
        // pointer to the parent node for the path from this point
        Node* parent;
        
        // accumulated cost of this node and all nodes before it in the path so far
        float g;
        
        // heuristic estimated cost from this node to the goal
        float h;
        
        // sum of the overall cost
        float f;
        
        // the coordinates of the tile this node represents
        const GridPoint point;
        
        // functor for sorting in the open list
        bool operator() (const Node* a, const Node* b) const;
    };
    
    // containers keeping track of nodes while pathing
    std::set<Node*> m_openList;
    std::unordered_map<unsigned, Node*> m_closedList;
    std::unordered_map<unsigned, Node*> m_createdNodes;
    
    // allocates a node for pathing with the given key and grid point.
    Node* CreateNode (const unsigned key, const GridPoint& p);
    
    // heuristic calculation for a node
    float CalculateHeuristic (const GridPoint& point);
    
    // creates unique key for coordinates so that it can be inserted into an unordered map
    unsigned GenerateKey (const unsigned x, const unsigned y);
    
    // adds all new neighbors of the given node to the open list
    void AddNeighborsToOpenList (Node* node);
    void AddNodeToOpenListIfValid (const GridPoint& point, Node* prevNode);
    
    // destroys all nodes
    void ClearNodes (void);
    
    // builds the resulting path list from the given goal node
    void BuildFinalPath (Node* node);
    
public:
    // constructor / destructor
    PathFind (const GridLayout* layout);
    ~PathFind (void);
    
    // performs the pathfinding
    void FindPath (const GridPoint& startPosition, const GridPoint& goalPosition);
    
    // returns if a path was found
    bool DidFindPath (void);
    
    // getter for the list of the final path
    std::list<GridPoint>& GetFinalPath (void);
};

#endif /* PathFind_h */
