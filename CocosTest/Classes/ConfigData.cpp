//
//  ConfigData.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/13/17.
//
//

#include "ConfigData.h"

/**
 * Constructor
 */
ConfigData::ConfigData (const char* filename)
: m_jsonLoader(filename) {
}

/**
 * Reloads the JSON file.
 */
void ConfigData::Reload (void) {
    m_jsonLoader.Reload();
}

/**
 * Returns the grid width value from the parsed JSON file.
 */
unsigned ConfigData::GetGridWidth (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["gridWidth"].GetUint();
}

/**
 * Returns the grid height value from the parsed JSON file.
 */
unsigned ConfigData::GetGridHeight (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["gridHeight"].GetUint();
}

/**
 * Returns the tile width value from the parsed JSON file.
 */
float ConfigData::GetTileWidth (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["tileWidth"].GetFloat();
}

/**
 * Returns the tile height value from the parsed JSON file.
 */
float ConfigData::GetTileHeight (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["tileHeight"].GetFloat();
}

/**
 * Returns the offset point value from the parsed JSON file.
 */
cocos2d::Point ConfigData::GetOffset (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return cocos2d::Point ((*d)["gridOffsetX"].GetFloat(), (*d)["gridOffsetY"].GetFloat());
}

/**
 * Returns the player speed value from the parsed JSON file.
 */
float ConfigData::GetPlayerSpeed (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["playerSpeed"].GetFloat();
}
