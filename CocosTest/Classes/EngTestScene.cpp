#include "EngTestScene.h"

USING_NS_CC;

static const int kGridWidth = 10;
static const int kGridHeight = 5;

EngTestScene::EngTestScene()
:
    mNodePositions(),
    mTableLocations(),
    mCharacterPosition(0,0)
{
    mTableLocations.push_back(GridCoordinate(1,1));
    mTableLocations.push_back(GridCoordinate(2,2));
    mTableLocations.push_back(GridCoordinate(2,3));
    mTableLocations.push_back(GridCoordinate(3,3));
    mTableLocations.push_back(GridCoordinate(4,3));
    mTableLocations.push_back(GridCoordinate(5,3));
    mTableLocations.push_back(GridCoordinate(6,3));
    mTableLocations.push_back(GridCoordinate(7,3));
    mTableLocations.push_back(GridCoordinate(7,2));
    mTableLocations.push_back(GridCoordinate(7,1));
    mTableLocations.push_back(GridCoordinate(7,0));
}

Scene* EngTestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EngTestScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EngTestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(EngTestScene::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "EngTestScene" splash screen"
    auto sprite = Sprite::create("bg.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    // Add a node grid
    for (int x = 0 ; x < kGridWidth ; ++x)
    {
        mNodePositions.push_back(std::vector<NodePosition>());
        for (int y = 0 ; y < kGridHeight ; ++y)
        {
            auto nodeSprite = Sprite::create("node.png");
            mNodePositions[x].push_back(NodePosition(nodeSprite->getBoundingBox().size.width *x, nodeSprite->getBoundingBox().size.height*y));
            nodeSprite->setPosition(mNodePositions[x][y]);
            nodeSprite->setAnchorPoint(cocos2d::Point(0,0));
            this->addChild(nodeSprite);
        }
    }
    
    // Add some tables
    for (auto it : mTableLocations)
    {
        auto tableSprite = Sprite::create("table.png");
        tableSprite->setPosition(mNodePositions[it.x][it.y]);
        tableSprite->setAnchorPoint(cocos2d::Point(0,0));
        this->addChild(tableSprite);
    }
    
    // Add the character
    auto characterSprite = Sprite::create("flo.png");
    characterSprite->setPosition(mCharacterPosition);
    characterSprite->setAnchorPoint(cocos2d::Point(0.5,0.2));
    this->addChild(characterSprite);
    
    return true;
}


void EngTestScene::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
