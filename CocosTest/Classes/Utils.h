//
//  Utils.h
//  CocosTest
//
//  Created by Michael Levesque on 7/12/17.
//
//

#ifndef Utils_h
#define Utils_h

#include <list>
#include "Actor.h"
#include "GridLayout.h"

ActorPath ConvertTileSpacePathToWorldSpace (const std::list<GridPoint>& path, const GridLayout& layout);

#endif /* Utils_h */
