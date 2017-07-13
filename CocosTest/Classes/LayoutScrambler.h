//
//  LayoutScrambler.h
//  CocosTest
//
//  Created by Michael Levesque on 7/10/17.
//
//

#ifndef LayoutScrambler_h
#define LayoutScrambler_h

#include <string>
#include <list>
#include <unordered_map>
#include "GridLayout.h" // for GridPoint
#include "TableData.h"

/**
 * Defines a sub section of the grid layout. Used when finding places to place table arrangements.
 */
struct Sector {
    // constuctors
    Sector (const int x, const int y, const unsigned width, const unsigned height);
    Sector (const Sector& s);
    
    // offset of sector form origin of grid
    const int x;
    const int y;
    
    // dimensions of the sector
    const unsigned width;
    const unsigned height;
    
    // operator overloads
    Sector operator=(const Sector& s);
};

/**
 * Data of what table arrangement to place and where when generating table placements.
 */
struct TableToPlace {
    // constructor
    TableToPlace (const TableArrangement* tableArrangement, const GridPoint& position);
    
    // pointer to the table arrangement
    const TableArrangement* tableArrangement;
    
    // the position to place the table on the grid
    const GridPoint position;
};

// this is the type of list that will be outputting when generating table placements
typedef std::list<TableToPlace> TablesToPlaceList;

// method that generates a list of placements
TablesToPlaceList GenerateTablePlacements (const unsigned gridWidth, const unsigned gridHeight,
                                          const unsigned numberOfTablesToPlace, const TableArrangementMap& tableArrangementMap);

#endif /* LayoutScrambler_h */
