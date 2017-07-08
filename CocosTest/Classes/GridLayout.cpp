//
//  GridLayout.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/7/17.
//
//

#include "GridLayout.h"

/**
 * Constructor for the GridPoint struct
 */
GridPoint::GridPoint (int x, int y)
: x(x), y(y) {}


/**
 * Returns the index value for the tile value array from the given tile coordinates.
 */
int GridLayout::CalculateArrayIndex (const GridPoint& p) {
    return p.y * m_width + p.x;
}

/**
 * Constructor. Sets constants and allocates memory for the tile values array.
 */
GridLayout::GridLayout (const unsigned width, const unsigned height, const cocos2d::Point& offset, const float tileWidth, const float tileHeight)
: m_width(width), m_height(height), m_offset(offset), m_tileWidth(tileWidth), m_tileHeight(tileHeight) {
    // build array of tile values
    unsigned size =m_width * m_height;
    m_gridValues = new int[size];
    
    // default array values to zero
    memset(m_gridValues, 0, sizeof(int) * size);
}

/**
 * Destructor. Cleans up array memory.
 */
GridLayout::~GridLayout (void) {
    // clean up memory
    delete[] m_gridValues;
}

/**
 * Returns the width of the grid layout.
 */
const unsigned GridLayout::GetGridWidth (void) {
    return m_width;
}

/**
 * Returns the height of the grid layout.
 */
const unsigned GridLayout::GetGridHeight (void) {
    return m_height;
}

/**
 * Returns the width of a grid tile.
 */
const float GridLayout::GetTileWidth (void) {
    return m_tileWidth;
}

/**
 * Returns the height of a grid tile.
 */
const float GridLayout::GetTileHeight (void) {
    return m_tileHeight;
}

/**
 * Returns the tile value of a tile at the given coordinates. If the coordinates lie outside of the grid
 * layout, then this will return the impassable value.
 */
int GridLayout::GetTileValue (const GridPoint& p) {
    // check if out of bounds
    if (!IsInsideGrid(p)) {
        return IMPASSABLE;
    }
    
    // return the tile value
    return m_gridValues[CalculateArrayIndex(p)];
}

/**
 * Sets the given value at the given tile coordinates. This returns true if it successfully set the value.
 * This returns false if the coordinates are inavlid (out of bounds).
 */
bool GridLayout::SetTileValue (const GridPoint& p, const int value) {
    // check if out of bounds
    if (!IsInsideGrid(p)) {
        return false;
    }
    
    // set the value and return success
    m_gridValues[CalculateArrayIndex(p)] = value;
    return true;
}

/**
 * Returns a tile space coordinate conversion from the given world space coordinates.
 */
GridPoint GridLayout::ConvertWorldSpaceToTileSpace (const cocos2d::Point& p) {
    return GridPoint (int((p.x - m_offset.x) / m_tileWidth), int((p.y - m_offset.y) / m_tileHeight));
}

/**
 * Returns a world space coordinate conversion from the given tile space coordinates.
 */
cocos2d::Point GridLayout::ConvertTileSpaceToWorldSpace (const GridPoint& p, const bool getCenter) {
    cocos2d::Point result (float(p.x) * m_tileWidth + m_offset.x, float(p.y) * m_tileHeight + m_offset.y);
    if (getCenter) {
        result.x += m_tileWidth * 0.5f;
        result.y += m_tileHeight * 0.5f;
    }
    return result;
}

/**
 * Returns true if the given tile space coordinates lies within the grid layout.
 * Returns false otherwise.
 */
bool GridLayout::IsInsideGrid (const GridPoint& p) {
    return p.x >= 0 && p.y >= 0 && p.x < m_width && p.y < m_height;
}
