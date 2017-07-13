//
//  Actor.h
//  CocosTest
//
//  Created by Michael Levesque on 7/12/17.
//
//

#ifndef Actor_h
#define Actor_h

#include "cocos2d.h"
#include <list>

typedef std::list<cocos2d::Point> ActorPath;

class Actor {
private:
    // the sprite that represents the actor
    cocos2d::Sprite* m_sprite;
    
    // how fast the actor moves
    float m_speed;
    
    // queued list of pathing actions the actor is waiting to do
    std::list<ActorPath> m_queuedPaths;
    
    void ExecuteAction (void);
    void OnActionCompleted (void);
    
public:
    Actor (cocos2d::Sprite* sprite);
    ~Actor (void);
    
    void QueuePathAction (ActorPath& path);
    bool IsCurrentlyRunningActions (void);
    void ClearActions (void);
    
    cocos2d::Sprite* GetSprite (void);
    
    void SetSpeed (const float speed);
    float GetSpeed (void);
    
    cocos2d::Point GetWhereActorWillBeAfterActions (void);
};

#endif /* Actor_h */
