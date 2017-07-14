#include "EngTestScene.h"

#include <ctime>

USING_NS_CC;

static const int kGridWidth = 10;
static const int kGridHeight = 5;

EngTestScene::EngTestScene()
:
    m_playerActor(NULL),
    m_gridLayout(NULL),
    m_configData("config.json"),
    m_tableData("tableConfig.json")
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
    
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(EngTestScene::menuCloseCallback, this));
//    
//	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Point::ZERO);
//    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = LabelTTF::create("Hello World", "Arial", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Point(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);

    // add "EngTestScene" splash screen"
//    auto sprite = Sprite::create("bg.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    
    // Add a node grid
//    for (int x = 0 ; x < kGridWidth ; ++x)
//    {
//        mNodePositions.push_back(std::vector<NodePosition>());
//        for (int y = 0 ; y < kGridHeight ; ++y)
//        {
//            auto nodeSprite = Sprite::create("node.png");
//            mNodePositions[x].push_back(NodePosition(nodeSprite->getBoundingBox().size.width *x, nodeSprite->getBoundingBox().size.height*y));
//            nodeSprite->setPosition(mNodePositions[x][y]);
//            nodeSprite->setAnchorPoint(cocos2d::Point(0,0));
//            this->addChild(nodeSprite);
//        }
//    }
    
    // Add some tables
//    for (auto it : mTableLocations)
//    {
//        auto tableSprite = Sprite::create("table.png");
//        tableSprite->setPosition(mNodePositions[it.x][it.y]);
//        
//        std::cout << "Coordinates: " << it.x << ", " << it.y << " -> " << tableSprite->getBoundingBox().size.width << std::endl;
//        tableSprite->setAnchorPoint(cocos2d::Point(0,0));
//        this->addChild(tableSprite);
//    }
//    
//    // Add the character
//    auto characterSprite = Sprite::create("flo.png");
//    characterSprite->setPosition(mCharacterPosition);
//    characterSprite->setAnchorPoint(cocos2d::Point(0,0));
//    this->addChild(characterSprite);
    
    
    
//    auto listener1 = EventListenerTouchOneByOne::create();
//    
//    // trigger when you push down
//    listener1->onTouchBegan = [](Touch* touch, Event* event){
//        // your code
//        std::cout << "TOUCH: " << touch->getLocation().x << std::endl;
//        return true; // if you are consuming it
//    };
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    
    
    
    
    //JSONLoader jsonLoader ("GameObjectsConfig.json");
//    std::cout << jsonLoader.GetDocument()["node"]["assetFile"].GetString() << std::endl;
//    
//    
//    GridLayout layout(10, 10, cocos2d::Point (0.f, 0.f), 1.f, 1.f);
//    for (int a = 0; a < 9; ++a) {
//        layout.SetTileValue(GridPoint(4, a), IMPASSABLE);
//    }
//    for (int a = 1; a < 5; ++a) {
//        layout.SetTileValue(GridPoint(a, 8), IMPASSABLE);
//    }
//    
//    PathFind pf (&layout);
//    pf.FindPath(GridPoint(3,0), GridPoint(9,0));
//    std::list<cocos2d::Point> path = pf.GetFinalPath();
    
//    for (std::list<cocos2d::Point>::iterator iter = path.begin(); iter != path.end(); ++iter) {
//        std::cout << " -> (" << (*iter).x << "," << (*iter).y << ")";
//    }
//    std::cout << std::endl;
    
    
    
    //////////////////////////////
    // 1. super init first
    if (!Layer::init ()) {
        return false;
    }
    
    // get origin and visible size
    Size visibleSize = Director::getInstance ()->getVisibleSize ();
    Point origin = Director::getInstance ()->getVisibleOrigin ();
    
    // set random generator seed
    srand (time (0));
    
    // load data
    ReloadData ();
    
    // set background
    auto bgSprite = Sprite::create ("bg.png");
    bgSprite->setPosition (Point (visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild (bgSprite, 0);
    
    // create layout
    ReloadScene ();
    
    // setup touch input
    auto listener = EventListenerTouchOneByOne::create ();
    listener->setSwallowTouches (true);
    listener->onTouchBegan = CC_CALLBACK_2 (EngTestScene::OnTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2 (EngTestScene::OnTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority (listener, this);
    
    // setup close menu button
    auto closeItem = MenuItemImage::create (
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(EngTestScene::OnMenuClose, this));
    closeItem->setPosition (Point (origin.x + visibleSize.width - closeItem->getContentSize ().width / 2,
                                   origin.y + closeItem->getContentSize ().height / 2));
    
    // setup scramble menu button
    auto scrambleItem = MenuItemImage::create (
                                            "RefreshNormal.png",
                                            "RefreshSelected.png",
                                            CC_CALLBACK_1(EngTestScene::OnMenuScramble, this));
    scrambleItem->setPosition (Point (origin.x + visibleSize.width - scrambleItem->getContentSize ().width / 2,
                                      origin.y + closeItem->getContentSize ().height + scrambleItem->getContentSize ().height / 2));
    
    // create the menu
    auto menu = Menu::create (closeItem, scrambleItem, NULL);
    menu->setPosition (Point::ZERO);
    this->addChild (menu, 1);
    
    return true;
}


void EngTestScene::ReloadData (void) {
    m_configData.Reload ();
    m_tableData.Reload ();
}

void EngTestScene::ClearScene (void) {
    // clear sprites
    if (m_playerActor) {
        m_playerActor->ClearActions ();
        this->removeChild (m_playerActor->GetSprite ());
        delete m_playerActor;
    }
    for (std::list<cocos2d::Sprite*>::iterator i = m_gridSprites.begin (); i != m_gridSprites.end (); ++i) {
        this->removeChild (*i);
    }
    m_gridSprites.clear ();
    
    // clear grid layout
    delete m_gridLayout;
}

void EngTestScene::ReloadScene (void) {
    // clear old scene
    ClearScene();
    
    // create grid layout
    unsigned gridWidth = m_configData.GetGridWidth ();
    unsigned gridHeight = m_configData.GetGridHeight ();
    cocos2d::Point offset = m_configData.GetOffset ();
    float tileWidth = m_configData.GetTileWidth ();
    float tileHeight = m_configData.GetTileHeight ();
    m_gridLayout = new GridLayout (gridWidth, gridHeight, offset, tileWidth, tileHeight);
    
    // build tables
    TablesToPlaceList tablesToPlace = GenerateTablePlacements(gridWidth, gridHeight, m_tableData.GetNumberOfTablesToPlace(), m_tableData.GetTableArrangementMap());
    SetTileTableCollisions (tablesToPlace);
    BuildTileSprites ();
    
    // create player sprite
    CreatePlayerSprite ();
}

void EngTestScene::SetTileTableCollisions (TablesToPlaceList& tables) {
    for (TablesToPlaceList::iterator i = tables.begin(); i != tables.end(); ++i) {
        GridPoint pos = (*i).position;
        unsigned width = (*i).tableArrangement->width;
        unsigned height = (*i).tableArrangement->height;
        bool* placements = (*i).tableArrangement->placements;
        unsigned index = 0;
        for (unsigned y = 0; y < height; ++y) {
            for (unsigned x = 0; x < width; ++x) {
                if (placements[index]) {
                    m_gridLayout->SetTileValue (GridPoint (pos.x + x, pos.y + y), IMPASSABLE);
                }
                ++index;
            }
        }
    }
}

void EngTestScene::BuildTileSprites (void) {
    // note that this is just using whether a tile is impassable or not to create either a table or node.
    // if we wanted to add new tile types, we would been a better way to do this
    for (unsigned y = 0; y < m_gridLayout->GetGridHeight (); ++y) {
        for (unsigned x = 0; x < m_gridLayout->GetGridWidth (); ++x) {
            cocos2d::Sprite* tileSprite;
            if (m_gridLayout->IsTileImpassable (GridPoint (x, y))) {
                tileSprite = Sprite::create ("table.png");
            }
            else {
                tileSprite = Sprite::create ("node.png");
            }
            cocos2d::Point pos = m_gridLayout->ConvertTileSpaceToWorldSpace (GridPoint (x, y));
            tileSprite->setPosition (pos);
            tileSprite->setAnchorPoint (cocos2d::Point (0, 0));
            this->addChild (tileSprite);
            m_gridSprites.push_back (tileSprite);
        }
    }
}

void EngTestScene::CreatePlayerSprite (void) {
    // create player
    auto playerSprite = Sprite::create ("flo.png");
    playerSprite->setAnchorPoint (cocos2d::Point (0.5f, 0));
    m_playerActor = new Actor (playerSprite);
    m_playerActor->SetSpeed (m_configData.GetPlayerSpeed ());
    
    // now position player on first found free tile
    bool found = false;
    for (int y = 0; y < m_gridLayout->GetGridHeight(); ++y) {
        for (int x = 0; x < m_gridLayout->GetGridWidth(); ++x) {
            GridPoint tilePos (x, y);
            if (!m_gridLayout->IsTileImpassable (tilePos)) {
                cocos2d::Point pos = m_gridLayout->ConvertTileSpaceToWorldSpace (tilePos, true);
                playerSprite->setPosition (pos);
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    
    // if for some reason no free tile could be found, then just place at starting tile
    if (!found) {
        playerSprite->setPosition (m_gridLayout->ConvertTileSpaceToWorldSpace (GridPoint (0, 0), true));
    }
    
    // now add to the scene
    this->addChild (playerSprite);
}

bool EngTestScene::OnTouchBegan (cocos2d::Touch* touch, cocos2d::Event* event) {
    return true;
}

void EngTestScene::OnTouchEnded (cocos2d::Touch* touch, cocos2d::Event* event) {
    // do nothing if touch position is on a non walkable tile
    GridPoint touchPoint = m_gridLayout->ConvertWorldSpaceToTileSpace(touch->getLocation());
    if (m_gridLayout->IsTileImpassable(touchPoint)) {
        return;
    }
    
    // start pathfinding
    PathFind pathFind (m_gridLayout);
    GridPoint start = m_gridLayout->ConvertWorldSpaceToTileSpace(m_playerActor->GetWhereActorWillBeAfterActions());
    pathFind.FindPath(start, touchPoint);
    if (!pathFind.DidFindPath()) {
        return;
    }
    
    // queue action
    ActorPath path = ConvertTileSpacePathToWorldSpace(pathFind.GetFinalPath(), *m_gridLayout);
    m_playerActor->QueuePathAction(path);
}

void EngTestScene::OnMenuScramble (Object* pSender) {
    ReloadData ();
    ReloadScene ();
}

void EngTestScene::OnMenuClose (Object* pSender) {
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}
