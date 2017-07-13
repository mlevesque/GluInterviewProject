//
//  TableData.h
//  CocosTest
//
//  Created by Michael Levesque on 7/10/17.
//
//

#ifndef TableData_h
#define TableData_h

#include <unordered_map>
#include <string>

/**
 * Data for a single table arrangement.
 */
struct TableArrangement {
    // constructor and destructor
    TableArrangement (const std::string& name, const unsigned width, const unsigned height);
    ~TableArrangement (void);
    
    // unique name used for lookup in the map
    const std::string name;
    
    // dimensions of the arrangement
    const unsigned width;
    const unsigned height;
    
    // calculated number of tables in the arrangement. Calculated by the number
    // of "true" vales in placements array
    unsigned numberOfTables;
    
    // dynamic array of table placements. Should be of size width*height
    bool* placements;
    
    // returns if table is present in arrangement at placement coordinates.
    bool HasTableAt (const unsigned x, const unsigned y);
};


// the container for table arrangements
typedef std::unordered_map<std::string, TableArrangement*> TableArrangementMap;


// Literals that represent the keys in the JSON file
#define KEY_NUMBER_OF_TABLES "numberOfTablesToPlace"
#define KEY_TABLE_ARARNGEMENTS "tableArrangements"
#define KEY_TA_NAME "name"
#define KEY_TA_WIDTH "width"
#define KEY_TA_HEIGHT "height"
#define KEY_TA_DATA "data"


/**
 * Container of all table data. This data is loaded and populated into this from a JSON file.
 */
class TableData {
private:
    // json filename
    const char* m_filename;
    
    // from json, the number of individual tables that should be placed in the layout
    unsigned m_numberOfTablesToPlace;
    
    // mapping of all table arrangements from the json file
    TableArrangementMap m_tableArrangementMap;
    
    // memory clean up
    void ClearArrangementData (void);
    
public:
    // constructor
    TableData (const char* jsonFileName);
    
    // destructor
    ~TableData (void);
    
    // reloads the json and refreshes the data
    void Reload (void);
    
    // getters
    unsigned GetNumberOfTablesToPlace (void);
    TableArrangementMap& GetTableArrangementMap (void);
};

#endif /* TableData_h */
