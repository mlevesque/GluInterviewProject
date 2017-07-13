//
//  Actor.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/12/17.
//
//

#include "Actor.h"

void Actor::ExecuteAction (void) {
    // we will use the path at the bottom of the list. W won't pop it until after the action is complete.
    ActorPath path = m_queuedPaths.front();
    
    // we will create a sequence of move to actions for each point in the path
    cocos2d::Vector<cocos2d::FiniteTimeAction*> moves;
    for (ActorPath::iterator i = path.begin(); i != path.end(); ++i) {
        moves.pushBack(cocos2d::MoveTo::create(m_speed, *i));
    }
    
    // add callback to determine when actions are done
    moves.pushBack(cocos2d::CallFunc::create(std::bind(&Actor::OnActionCompleted,this)));
    
    auto seq = cocos2d::Sequence::create (moves);
    m_sprite->runAction(seq);
}

void Actor::OnActionCompleted (void) {
    // pop the path action from the queue
    m_queuedPaths.pop_front();
    
    // if there is still more in the queue, then start the next one
    if (m_queuedPaths.size() > 0) {
        ExecuteAction();
    }
}

Actor::Actor (cocos2d::Sprite* sprite)
: m_sprite(sprite) {
}

Actor::~Actor (void) {
    ClearActions();
}

void Actor::QueuePathAction (ActorPath& path) {
    bool currentlyRunning = IsCurrentlyRunningActions();
    m_queuedPaths.push_back(path);
    if (!currentlyRunning) {
        ExecuteAction();
    }
}

bool Actor::IsCurrentlyRunningActions (void) {
    return m_queuedPaths.size() > 0;
}

void Actor::ClearActions (void) {
    m_queuedPaths.clear();
    m_sprite->stopAllActions();
}

void Actor::SetSpeed (const float speed) {
    m_speed = speed;
}

float Actor::GetSpeed (void) {
    return m_speed;
}

/**
 * Returns the position of where the Actor should be once it finishes all its actions. If there are no actions,
 * then this will just return the actor's current position.
 */
cocos2d::Point Actor::GetWhereActorWillBeAfterActions (void) {
    if (m_queuedPaths.size() > 0) {
        ActorPath path = m_queuedPaths.back();
        if (path.size() > 0) {
            return path.back();
        }
    }
    return m_sprite->getPosition();
}
