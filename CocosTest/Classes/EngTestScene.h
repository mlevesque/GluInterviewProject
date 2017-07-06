#ifndef __ENGTEST_SCENE_H__
#define __ENGTEST_SCENE_H__

#include "cocos2d.h"
#include <base/CCGeometry.h>

class EngTestScene : public cocos2d::Layer
{
public:
    
    EngTestScene();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(EngTestScene);
    
private:
    
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
