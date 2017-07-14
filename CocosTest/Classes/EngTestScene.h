#ifndef __ENGTEST_SCENE_H__
#define __ENGTEST_SCENE_H__

#include "cocos2d.h"
#include <base/CCGeometry.h>
#include "JSONLoader.h"
#include "GridLayout.h"
#include "PathFind.h"
#include "TableData.h"
#include "LayoutScrambler.h"
#include "Actor.h"
#include "Utils.h"
#include "ConfigData.h"

class EngTestScene : public cocos2d::Layer
{
public:
    
    EngTestScene();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(EngTestScene);
    
private:
    
    TableData m_tableData;
    ConfigData m_configData;
    GridLayout* m_gridLayout;
    Actor* m_playerActor;
    std::list<cocos2d::Sprite*> m_gridSprites;
    
    void ReloadData (void);
    void ClearScene (void);
    void ReloadScene (void);
    
    void SetTileTableCollisions (TablesToPlaceList& tables);
    void BuildTileSprites (void);
    void CreatePlayerSprite (void);
    
    bool OnTouchBegan (cocos2d::Touch* touch, cocos2d::Event* event);
    void OnTouchEnded (cocos2d::Touch* touch, cocos2d::Event* event);
    void OnMenuClose (Object* pSender);
    void OnMenuScramble (Object* pSender);
    
    
    typedef cocos2d::Point NodePosition;
    typedef cocos2d::Point GridCoordinate;
    
    // World position of all the level nodes
    std::vector<std::vector<NodePosition> > mNodePositions;
    
    // Location of the tables (in grid positions
    std::vector<GridCoordinate> mTableLocations;
    
    // Location of the character in world space
    cocos2d::Point mCharacterPosition;
};

#endif // __ENGTEST_SCENE_H__
