//
//  Actor.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/12/17.
//
//

#include "Actor.h"

/**
 * Creates a sequence of actions for the next path in the queue. This will not remove that path from the queue
 * until the sequence has completed.
 */
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
    
    auto seq = cocos2d::Sequence::create(moves);
    m_sprite->runAction(seq);
}

/**
 * Called when a sequence hits the last action, which is teh callback action. It will pop the the path that the
 * sequence was animating from the queue. If there are more paths in the queue, then it will start a sequence
 * for the next one.
 */
void Actor::OnActionCompleted (void) {
    // pop the path action from the queue
    m_queuedPaths.pop_front();
    
    // if there is still more in the queue, then start the next one
    if (m_queuedPaths.size() > 0) {
        ExecuteAction();
    }
}

/**
 * Constructor.
 */
Actor::Actor (cocos2d::Sprite* sprite)
: m_sprite(sprite) {
}

/**
 * Destructor. Makes sure to stop all current actions.
 */
Actor::~Actor (void) {
    ClearActions();
}

/**
 * Queues the given path to the action queue of this actor. If the queue was previously empty, then this
 * will start moving along the path.
 */
void Actor::QueuePathAction (ActorPath& path) {
    bool currentlyRunning = IsCurrentlyRunningActions();
    m_queuedPaths.push_back(path);
    if (!currentlyRunning) {
        ExecuteAction();
    }
}

/**
 * Returns if the Actor is currently animating along a path.
 */
bool Actor::IsCurrentlyRunningActions (void) {
    return m_queuedPaths.size() > 0;
}

/**
 * Clears the action queue and stops whatever one is currently animating.
 */
void Actor::ClearActions (void) {
    m_queuedPaths.clear();
    m_sprite->stopAllActions();
}

/**
 * Returns the sprite for this Actor.
 */
cocos2d::Sprite* Actor::GetSprite (void) {
    return m_sprite;
}

/**
 * Sets the speed of the actor to the given value. This determines how fast the Actor animates along a path.
 */
void Actor::SetSpeed (const float speed) {
    m_speed = speed;
}

/**
 * Returns the speed for this Actor.
 */
float Actor::GetSpeed (void) {
    return m_speed;
}

/**
 * Returns the position of where the Actor should be once it finishes all its actions. If there are no actions,
 * then this will just return the actor's current position. This can be uses to get a proper starting position
 * for a path that will be queued up after any other queued paths this Actor has.
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
