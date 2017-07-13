//
//  GridLayout.h
//  CocosTest
//
//  Created by Michael Levesque on 7/7/17.
//
//

#ifndef GridLayout_h
#define GridLayout_h

#include "CCGeometry.h" // for cocos2d::Point

// value that represents an impassable tile
#define IMPASSABLE -1

/**
 * Simple grid point for specifying coordinates on a grid layout.
 */
struct GridPoint {
    // constructor
    GridPoint (int x = 0, int y = 0);
    
    // coordinate values
    int x;
    int y;
    
    // operators
    bool operator ==(const GridPoint &b) const;
};

/**
 * GridLayout class defines the grid dimensions and values. Used for pathfinding and
 * for converting between world space and tile space.
 */
class GridLayout {
private:
    // the dimensions of the grid
    const unsigned m_width;
    const unsigned m_height;
    
    // world position offset from origin to start of the grid
    const cocos2d::Point m_offset;
    
    // tile dimensions
    const float m_tileWidth;
    const float m_tileHeight;
    
    // array that represents the pathing values, row major
    int* m_gridValues;
    
    // calculates the 1d array index from the tile coordinates
    int CalculateArrayIndex (const GridPoint& p) const;
    
public:
    // constructor
    GridLayout (const unsigned width, const unsigned height, const cocos2d::Point& offset, const float tileWidth, const float tileHeight);
    
    // destructor for cleaning up the array
    ~GridLayout (void);
    
    // getters for dimensions
    const unsigned GetGridWidth (void) const;
    const unsigned GetGridHeight (void) const;
    const float GetTileWidth (void) const;
    const float GetTileHeight (void) const;
    
    // returns the pathing value at a certain tile space
    int GetTileValue (const GridPoint& p) const;
    
    // returns if the given tile location is marked as impassable
    bool IsTileImpassable (const GridPoint& p) const;
    
    // sets the tile value at the given tile coordinates
    bool SetTileValue (const GridPoint& p, const int value);
    
    // conversions between world space and tile space
    GridPoint ConvertWorldSpaceToTileSpace (const cocos2d::Point& p) const;
    cocos2d::Point ConvertTileSpaceToWorldSpace (const GridPoint& p, const bool getCenter = false) const;
    
    // takes a tile space point and returns if it lies inside the grid layout or not
    bool IsInsideGrid (const GridPoint& p) const;
};

#endif /* GridLayout_h */
