//
//  PathFind.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/8/17.
//
//

#include "PathFind.h"

///// NODE METHODS /////
/**
 * Constructor for the pathfinding node.
 */
PathFind::Node::Node (const GridPoint p)
: point(p), parent(0), g(MAXFLOAT), h(0.f), f(0.f) {
}

/**
 * Functor for comparing nodes so that they can be sorted by cost in the open list during pathing.
 */
bool PathFind::Node::operator() (const Node* a, const Node* b) const {
    // adding a tie-breaker in order to try to get better routes
    if (a->f == b->f) {
        return a->h > b->h;
    }
    return a->f > b->f;
}


///// PATHFIND PRIVATE METHODS /////
/**
 * Allocates a node for pathing using the given key and grid point position.
 */
PathFind::Node* PathFind::CreateNode (const unsigned key, const GridPoint& p) {
    PathFind::Node* node = new PathFind::Node (p);
    
    // set key for node
    node->key = key;
    
    // compute h(n)
    node->h = CalculateHeuristic(p);
    
    // insert into created nodes map
    m_createdNodes[node->key] = node;
    
    return node;
}

/**
 * Calculates an estimated distance from the given point to the goal point, using Manhattan Distance.
 */
float PathFind::CalculateHeuristic (const GridPoint& point) {
    return abs (point.x - m_goalPosition.x) + abs (point.y - m_goalPosition.y);
}

/**
 * Returns a generated unique key so that the given node can be inserted into a map container. The key is
 * generated based on the coordinates for the node. We are doing a simple key generation by storing the x
 * in the first 16 bits and the y in the later 16 bits.
 *
 * Note that this limits our grid sizes to 2^16-1, or 65,535.
 */
unsigned PathFind::GenerateKey (const unsigned x, const unsigned y) {
    return x | (y << 16);
}

/**
 * Adds all new neighbors of the given node into the open list.
 */
void PathFind::AddNeighborsToOpenList (Node* node) {
    // try to add all neighbors
    AddNodeToOpenListIfValid (GridPoint (node->point.x - 1, node->point.y), node); // left
    AddNodeToOpenListIfValid (GridPoint (node->point.x + 1, node->point.y), node); // right
    AddNodeToOpenListIfValid (GridPoint (node->point.x, node->point.y - 1), node); // down
    AddNodeToOpenListIfValid (GridPoint (node->point.x, node->point.y + 1), node); // up
}

/**
 * This will create new node with the given grid position, but only if that position is traversable and hasn't
 * already been created, then calculates the cost and adds it to the open list.
 */
void PathFind::AddNodeToOpenListIfValid (const GridPoint& point, Node* prevNode) {
    // disregard if impassable
    if (m_layout->IsTileImpassable (point)) {
        return;
    }
    
    // disregard if in closed list
    unsigned key = GenerateKey (point.x, point.y);
    if (m_closedList.count (key) > 0) {
        return;
    }
    
    // get node if it already exists, or create a new one
    Node* node;
    if (m_createdNodes.count (key) > 0) {
        node = m_createdNodes[key];
    }
    else {
        // create and add to open list
        node = CreateNode (key, point);
        m_openList.insert (node);
    }
    
    // calculate g(n)
    float g = m_layout->GetTileValue(point);
    g += prevNode ? prevNode->g : 0.f;
    
    // if this g(n) is better than what the node's g(n) currently is, then update node
    if (g < node->g) {
        node->parent = prevNode;
        node->g = g;
        node->f = node->g + node->h;
    }
}

/**
 * Destroys all allocated nodes and clears the pathing containers.
 */
void PathFind::ClearNodes (void) {
    // deallocate all nodes
    for (std::unordered_map<unsigned, PathFind::Node*>::iterator i = m_createdNodes.begin(); i != m_createdNodes.end(); ++i) {
        delete i->second;
    }
    
    // clear lists
    m_openList.clear();
    m_closedList.clear();
    m_createdNodes.clear();
}

/**
 * Builds the list of world space points from the given node which should represent the last node of the path.
 * This will use the parent pointer of the node to traverse the path backwards and will push each point to the
 * front of the list.
 */
void PathFind::BuildFinalPath (Node* node) {
    Node* ptr = node;
    while (ptr) {
        m_finalPath.push_front(ptr->point);
        ptr = ptr->parent;
    }
}


///// PATHFIND PUBLIC METHODS /////
/**
 * Constructor. Takes in a pointer to a GridLayout, which is used for pathfinding.
 */
PathFind::PathFind (const GridLayout* layout)
: m_layout(layout), m_success(false) {
}

/**
 * Destructor. Clean up lists.
 */
PathFind::~PathFind (void) {
    ClearNodes();
}

/**
 * Performs A* to find a path from the given start position to the given goal position. The input
 * points should be in tile space. This will then add the final path (if it is found) into a list
 * that can be retrieved by calling GetFinalPath.
 */
void PathFind::FindPath (const GridPoint& startPosition, const GridPoint& goalPosition) {
    // clear out the final path list in case we are re-pathing
    m_finalPath.clear();
    
    // store the start and goal positions
    m_startPosition = startPosition;
    m_goalPosition = goalPosition;
    
    // first make sure that our starting and goal positions are traversable. If not, then we can't
    // path
    if (m_layout->IsTileImpassable(m_startPosition) || m_layout->IsTileImpassable(m_goalPosition)) {
        m_success = false;
        return;
    }
    
    // add starting position to open list
    AddNodeToOpenListIfValid(m_startPosition, 0);
    
    // now keep working with the nodes with the best cost in teh open list until we eventually get to
    // the goal position, or if we exhaust all nodes in the open list
    while (m_openList.size() > 0) {
        // pop node with best cost in open list. This should be the top of the open list since it is
        // sorted by cost
        std::set<Node*>::iterator iter = m_openList.begin();
        Node* node = *iter;
        
        // if this node is our goal node, then we are done
        if (node->point == m_goalPosition) {
            m_success = true;
            BuildFinalPath(node);
            ClearNodes();
            return;
        }
        
        // remove from open list and add to closed list
        m_openList.erase(iter);
        m_closedList[node->key] = node;
        
        // add neighbors to the open list
        AddNeighborsToOpenList(node);
    } // end while we have things in open list
    
    // if we have reached this point, then that means we couldn't find a path
    m_success = false;
    ClearNodes();
}

/**
 * Returns if the pathfinding is successful. If pathfinding could not find a path, then this will
 * return false. If pathfinding hasn't yet been performed, then this will return false.
 */
bool PathFind::DidFindPath (void) {
    return m_success;
}

/**
 * Returns the list of world space points that make up the final path. If a path could not be found
 * or pathing has not yet started, then this will be empty.
 */
std::list<GridPoint>& PathFind::GetFinalPath (void) {
    return m_finalPath;
}
