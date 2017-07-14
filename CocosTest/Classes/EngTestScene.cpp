#include "EngTestScene.h"

#include <ctime>

USING_NS_CC;

/**
 * Constructor.
 */
EngTestScene::EngTestScene ()
: m_playerActor(NULL),
  m_gridLayout(NULL),
  m_configData("config.json"),
  m_tableData("tableConfig.json") {
}

/**
 * Required for building the Cocos2d scene.
 */
Scene* EngTestScene::createScene () {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EngTestScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

/**
 * Initializes the scene, loads data, builds the layout, sets up input, and creates the menu.
 */
bool EngTestScene::init () {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }
    
    // get origin and visible size
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // set random generator seed
    srand(time(0));
    
    // load data
    ReloadData();
    
    // set background
    auto bgSprite = Sprite::create("bg.png");
    bgSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bgSprite, 0);
    
    // create layout
    ReloadScene();
    
    // setup touch input
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(EngTestScene::OnTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(EngTestScene::OnTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // setup close menu button
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(EngTestScene::OnMenuClose, this));
    closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                                 origin.y + closeItem->getContentSize().height / 2));
    
    // setup scramble menu button
    auto scrambleItem = MenuItemImage::create(
                                            "RefreshNormal.png",
                                            "RefreshSelected.png",
                                            CC_CALLBACK_1(EngTestScene::OnMenuScramble, this));
    scrambleItem->setPosition(Point(origin.x + visibleSize.width - scrambleItem->getContentSize().width / 2,
                                    origin.y + closeItem->getContentSize().height + scrambleItem->getContentSize().height / 2));
    
    // create the menu
    auto menu = Menu::create(closeItem, scrambleItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

/**
 * Reopens and reparses the JSON files.
 */
void EngTestScene::ReloadData (void) {
    m_configData.Reload();
    m_tableData.Reload();
}

/**
 * Cleans up the scene, removing sprites and deleting allocated stuff.
 */
void EngTestScene::ClearScene (void) {
    // clear sprites
    if (m_playerActor) {
        m_playerActor->ClearActions();
        this->removeChild(m_playerActor->GetSprite(), true);
        delete m_playerActor;
    }
    for (std::list<cocos2d::Sprite*>::iterator i = m_gridSprites.begin(); i != m_gridSprites.end(); ++i) {
        this->removeChild(*i, true);
    }
    m_gridSprites.clear();
    
    // clear grid layout
    delete m_gridLayout;
}

/**
 * Clears the tiles and player sprite from the old scene, then creates a new one. Table placement will
 * be randomized.
 */
void EngTestScene::ReloadScene (void) {
    // clear old scene
    ClearScene();
    
    // create grid layout
    unsigned gridWidth = m_configData.GetGridWidth();
    unsigned gridHeight = m_configData.GetGridHeight();
    cocos2d::Point offset = m_configData.GetOffset();
    float tileWidth = m_configData.GetTileWidth();
    float tileHeight = m_configData.GetTileHeight();
    m_gridLayout = new GridLayout(gridWidth, gridHeight, offset, tileWidth, tileHeight);
    
    // build tables
    TablesToPlaceList tablesToPlace = GenerateTablePlacements(gridWidth,
                                                              gridHeight,
                                                              m_tableData.GetNumberOfTablesToPlace(),
                                                              m_tableData.GetTableArrangementMap());
    SetTileTableCollisions(tablesToPlace);
    BuildTileSprites();
    
    // create player sprite
    CreatePlayerSprite();
}

/**
 * Takes a given list of tables to place and marks all tiles the tables are loacted at as IMPASSABLE.
 */
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
                    m_gridLayout->SetTileValue(GridPoint(pos.x + x, pos.y + y), IMPASSABLE);
                }
                ++index;
            }
        }
    }
}

/**
 * Builds all sprites for tiles using the tile values from the grid layout, where IMPASSABLE is a table and
 * anything else is a node. This is currently very limited to these two tile types. If we wish to expand this
 * in the future, then we may need to introduce tile types to the grid layout.
 */
void EngTestScene::BuildTileSprites (void) {
    // note that this is just using whether a tile is impassable or not to create either a table or node.
    // if we wanted to add new tile types, we would been a better way to do this
    for (unsigned y = 0; y < m_gridLayout->GetGridHeight(); ++y) {
        for (unsigned x = 0; x < m_gridLayout->GetGridWidth(); ++x) {
            cocos2d::Sprite* tileSprite;
            if (m_gridLayout->IsTileImpassable(GridPoint(x, y))) {
                tileSprite = Sprite::create("table.png");
            }
            else {
                tileSprite = Sprite::create("node.png");
            }
            cocos2d::Point pos = m_gridLayout->ConvertTileSpaceToWorldSpace(GridPoint(x, y));
            tileSprite->setPosition(pos);
            tileSprite->setAnchorPoint(cocos2d::Point(0, 0));
            this->addChild(tileSprite);
            m_gridSprites.push_back(tileSprite);
        }
    }
}

/**
 * Creates the Flo sprite and places her into a non collidable tile.
 */
void EngTestScene::CreatePlayerSprite (void) {
    // create player
    auto playerSprite = Sprite::create("flo.png");
    playerSprite->setAnchorPoint(cocos2d::Point(0.5f, 0));
    m_playerActor = new Actor(playerSprite);
    m_playerActor->SetSpeed(m_configData.GetPlayerSpeed ());
    
    // now position player on first found free tile
    bool found = false;
    for (int y = 0; y < m_gridLayout->GetGridHeight(); ++y) {
        for (int x = 0; x < m_gridLayout->GetGridWidth(); ++x) {
            GridPoint tilePos(x, y);
            if (!m_gridLayout->IsTileImpassable(tilePos)) {
                cocos2d::Point pos = m_gridLayout->ConvertTileSpaceToWorldSpace(tilePos, true);
                playerSprite->setPosition(pos);
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
        playerSprite->setPosition(m_gridLayout->ConvertTileSpaceToWorldSpace(GridPoint(0, 0), true));
    }
    
    // now add to the scene
    this->addChild(playerSprite);
}

/**
 * Touch Began event callback. Added because the event dispatcher would fail and assert if this didn't exist in the
 * listener.
 */
bool EngTestScene::OnTouchBegan (cocos2d::Touch* touch, cocos2d::Event* event) {
    return true;
}

/**
 * Touch Ended event callback. Will initiate a pathfind if the touch location is within the grid and is not over an
 * IMPASSABLE tile. If a path is found, this will queue the path to the player so that she will move to the touch
 * position.
 */
void EngTestScene::OnTouchEnded (cocos2d::Touch* touch, cocos2d::Event* event) {
    // do nothing if touch position is on a non walkable tile
    GridPoint touchPoint = m_gridLayout->ConvertWorldSpaceToTileSpace(touch->getLocation());
    if (m_gridLayout->IsTileImpassable(touchPoint)) {
        return;
    }
    
    // start pathfinding
    PathFind pathFind(m_gridLayout);
    GridPoint start = m_gridLayout->ConvertWorldSpaceToTileSpace(m_playerActor->GetWhereActorWillBeAfterActions());
    pathFind.FindPath(start, touchPoint);
    if (!pathFind.DidFindPath()) {
        return;
    }
    
    // queue action
    ActorPath path = ConvertTileSpacePathToWorldSpace(pathFind.GetFinalPath(), *m_gridLayout);
    m_playerActor->QueuePathAction(path);
}

/**
 * Menu Button pressed event for the layout scrambler menu button. This will reload the data and scene to make a new
 * layout.
 */
void EngTestScene::OnMenuScramble (Object* pSender) {
    ReloadData();
    ReloadScene();
}

/**
 * Menu Button pressed event for the close menu button. This will close the app.
 */
void EngTestScene::OnMenuClose (Object* pSender) {
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}
