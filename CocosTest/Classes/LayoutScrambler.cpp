//
//  LayoutScrambler.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/10/17.
//
//

#include "LayoutScrambler.h"

///// SECTOR METHODS /////
/**
 * Constructor. Sets all const values.
 */
Sector::Sector (const int x, const int y, const unsigned width, const unsigned height)
: x(x), y(y), width(width), height(height) {
}

/**
 * Copy constructor.
 */
Sector::Sector (const Sector& s)
: x(s.x), y(s.y), width(s.width), height(s.height) {
}

/**
 * Assignment operator.
 */
Sector Sector::operator=(const Sector& s) {
    return Sector(s);
}


///// TABLE TO PLACE METHODS /////
/**
 * Constructor. Sets const values.
 */
TableToPlace::TableToPlace (const TableArrangement* tableArrangement, const GridPoint& position)
: tableArrangement(tableArrangement), position(position) {
}


///// TABLES TO PLACE ALGORITHM /////
/**
 * Will add a sector with the given data to the given vector, but only if the sector is big enough.
 */
void AddSectorIfBigEnough (const int x, const int y, const unsigned width, const unsigned height, std::vector<Sector>& sectorList) {
    // the smallest a valid sector can be is 2x2, because the small table arrangement is 1x1 an we add a row and column
    // buffer to that, so if the sector is smaller, then don't add it
    if (width >= 2 && height >= 2) {
        sectorList.push_back(Sector (x, y, width, height));
    }
}

/**
 * Method for quickly removing a sector from the list by just copying the last element over at the given
 * index and pops the last element off.
 */
void RemoveSector (const int index, std::vector<Sector>& sectorList) {
    sectorList[index] = sectorList[sectorList.size() - 1];
    sectorList.pop_back();
}

/**
 * Generates a list of all tables that can fit in the given sector and don't exceed the number of remaining
 * tables.
 */
std::vector<TableArrangement*> GetTablesThatFit (Sector& sector, unsigned remainingTables, const TableArrangementMap& tableArrangementMap) {
    std::vector<TableArrangement*> result;
    for (TableArrangementMap::const_iterator i = tableArrangementMap.begin(); i != tableArrangementMap.end(); ++i) {
        TableArrangement* tableArr = (*i).second;
        if (tableArr->width < sector.width && tableArr->height < sector.height && tableArr->numberOfTables <= remainingTables) {
            result.push_back(tableArr);
        }
    }
    return result;
}

/**
 * Generates a list of what tables to place and where. It will be up to the caller to use this information to make the
 * tables and place them.
 */
TablesToPlaceList GenerateTablePlacements (const unsigned gridWidth, const unsigned gridHeight,
                                          const unsigned numberOfTablesToPlace, const TableArrangementMap& tableArrangementMap) {
    // create an initial sector
    std::vector<Sector> sectorList;
    AddSectorIfBigEnough(0, 0, gridWidth, gridHeight, sectorList);
    
    // loop until we either exhaust all available sectors or have placed all our tables.
    unsigned remainingTables = numberOfTablesToPlace;
    TablesToPlaceList result;
    while (sectorList.size() > 0 && remainingTables > 0) {
        // randomly choose a sector to place in and remove from list
        int index = rand() % sectorList.size();
        Sector sector = sectorList[index];
        RemoveSector(index, sectorList);
        
        // get all tables that can fit
        std::vector<TableArrangement*> tableList = GetTablesThatFit(sector, remainingTables, tableArrangementMap);
        
        // if no tables are found, then nothing more we can do with this sector
        if (tableList.size() == 0) {
            continue;
        }
        
        // randomly choose a table and randomly place it
        TableArrangement* table = tableList[rand() % tableList.size()];
        GridPoint pos = GridPoint(sector.x + 1 + rand() % (sector.width - table->width), sector.y + rand() % (sector.height - table->height));
        result.push_back(TableToPlace(table, pos));
        
        // update how many tables we have left to try to place
        remainingTables -= table->numberOfTables;
        
        // now we break up the sector into the smaller surrounding sectors and add them to the sector list
        int posX[4] = {sector.x, pos.x - 1, static_cast<int>(pos.x + table->width), static_cast<int>(sector.x + sector.width)};   // -1 due to column buffer
        int posY[4] = {sector.y, pos.y, static_cast<int>(pos.y + table->height + 1), static_cast<int>(sector.y + sector.height)}; // +1 due to row buffer
        for (unsigned x = 0; x < 3; ++x) {
            for (unsigned y = 0; y < 3; ++y) {
                //don't include the middle sector
                if (x != 1 || y != 1) {
                    AddSectorIfBigEnough(posX[x], posY[y], posX[x+1] - posX[x], posY[y+1] - posY[y], sectorList);
                }
            }
        }
    } // end while
    
    return result;
}
