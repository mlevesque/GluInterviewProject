//
//  ConfigData.h
//  CocosTest
//
//  Created by Michael Levesque on 7/13/17.
//
//

#ifndef ConfigData_h
#define ConfigData_h

#include "JSONLoader.h"
#include "cocos2d.h"

/**
 * This takes care of loading a config JSON file to get various data for a scene.
 */
class ConfigData {
private:
    // for loading the JSON file
    JSONLoader m_jsonLoader;
    
public:
    // constructor
    ConfigData (const char* filename);
    
    // reloading JSON file
    void Reload (void);
    
    // getters straight from parsed JSON file
    unsigned GetGridWidth (void);
    unsigned GetGridHeight (void);
    float GetTileWidth (void);
    float GetTileHeight (void);
    cocos2d::Point GetOffset (void);
    float GetPlayerSpeed (void);
};

#endif /* ConfigData_h */
