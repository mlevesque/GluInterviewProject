//
//  ConfigData.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/13/17.
//
//

#include "ConfigData.h"

ConfigData::ConfigData (const char* filename)
: m_jsonLoader(filename) {
}

void ConfigData::Reload (void) {
    m_jsonLoader.Reload();
}

unsigned ConfigData::GetGridWidth (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["gridWidth"].GetUint();
}

unsigned ConfigData::GetGridHeight (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["gridHeight"].GetUint();
}

float ConfigData::GetTileWidth (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["tileWidth"].GetFloat();
}

float ConfigData::GetTileHeight (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["tileHeight"].GetFloat();
}

cocos2d::Point ConfigData::GetOffset (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return cocos2d::Point ((*d)["gridOffsetX"].GetFloat(), (*d)["gridOffsetY"].GetFloat());
}

float ConfigData::GetPlayerSpeed (void) {
    rapidjson::Document* d = m_jsonLoader.GetDocument ();
    return (*d)["playerSpeed"].GetFloat();
}
