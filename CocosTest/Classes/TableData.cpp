//
//  TableData.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/10/17.
//
//

#include "TableData.h"
#include "JSONLoader.h"

///// TABLE ARRANGEMENT METHODS /////
/**
 * Constructor. Will allocate the placement array.
 */
TableArrangement::TableArrangement (const std::string& name, const unsigned width, const unsigned height)
: name(name), width(width), height(height) {
    placements = new bool[width*height];
}

/**
 * Destructor. Cleans up allocated array.
 */
TableArrangement::~TableArrangement (void) {
    delete[] placements;
}

/**
 * Returns if a table is present in the placement array at the given coordinates. Treats placement
 * like a 2D grid, row major. If the given coordinates lie outside the dimentions of the placement
 * grid, then this will return false.
 */
bool TableArrangement::HasTableAt (const unsigned x, const unsigned y) {
    // if out of bounds
    if (x >= width || y >= height) {
        return false;
    }
    return placements[y * width + x];
}


///// TABLE DATA METHODS /////
/**
 * Empties the table arrangements map and cleans up allocated memory through their destructors.
 */
void TableData::ClearArrangementData (void) {
    for (TableArrangementMap::iterator i = m_tableArrangementMap.begin(); i != m_tableArrangementMap.end(); ++i) {
        delete (*i).second;
    }
    m_tableArrangementMap.clear();
}

/**
 * Constructor. Sets the json filename and starts loading the json data.
 */
TableData::TableData (const char* jsonFileName)
: m_filename(jsonFileName), m_numberOfTablesToPlace(0) {
}

/**
 * Destructor.
 */
TableData::~TableData (void) {
    ClearArrangementData();
}

/**
 * Clears the current data and reloads it from the json file.
 */
void TableData::Reload (void) {
    // clear old data
    ClearArrangementData();
    
    // Note that there is no error checking for any of this. Probably something that
    // should be added at some point.
    
    // load the json data
    JSONLoader loader (m_filename);
    rapidjson::Document* d = loader.GetDocument();
    
    // get number of tables to place
    m_numberOfTablesToPlace = (*d)[KEY_NUMBER_OF_TABLES].GetUint();
    
    // get table arrangement data
    auto arr = (*d)[KEY_TABLE_ARARNGEMENTS].GetArray();
    for (auto i = arr.begin(); i != arr.end(); ++i) {
        std::string name = (*i)[KEY_TA_NAME].GetString();
        unsigned width = (*i)[KEY_TA_WIDTH].GetUint();
        unsigned height = (*i)[KEY_TA_HEIGHT].GetUint();
        auto data = (*i)[KEY_TA_DATA].GetArray();
        TableArrangement* ta = new TableArrangement(name, width, height);
        ta->placements = new bool[width*height];
        memset (ta->placements, false, sizeof(bool) * width * height);
        unsigned index = 0;
        unsigned tableCount = 0;
        for (auto j = data.begin(); j != data.end() || index < width*height; ++j) {
            if ((*j).GetInt() == 1) {
                ta->placements[index] = true;
                tableCount++;
            }
            index++;
        }
        ta->numberOfTables = tableCount;
        m_tableArrangementMap[name] = ta;
    }
}

/**
 * Returns the number of tables that should be placed in the layout.
 */
unsigned TableData::GetNumberOfTablesToPlace (void) {
    return m_numberOfTablesToPlace;
}

/**
 * Returns the map of all Table Arrangements configurations.
 */
TableArrangementMap& TableData::GetTableArrangementMap (void) {
    return m_tableArrangementMap;
}
