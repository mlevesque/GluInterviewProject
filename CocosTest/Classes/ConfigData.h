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

class ConfigData {
private:
    JSONLoader m_jsonLoader;
    
public:
    ConfigData (const char* filename);
    
    void Reload (void);
    unsigned GetGridWidth (void);
    unsigned GetGridHeight (void);
    float GetTileWidth (void);
    float GetTileHeight (void);
    cocos2d::Point GetOffset (void);
    float GetPlayerSpeed (void);
};

#endif /* ConfigData_h */
