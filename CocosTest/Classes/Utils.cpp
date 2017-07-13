//
//  Utils.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/12/17.
//
//

#include "Utils.h"

/**
 * Converts tile space path generated from pathfinding into world space path using the given layout for
 * conversion and returns the converted list.
 */
ActorPath ConvertTileSpacePathToWorldSpace (const std::list<GridPoint>& path, const GridLayout& layout) {
    ActorPath result;
    for (std::list<GridPoint>::const_iterator i = path.begin(); i != path.end(); ++i) {
        result.push_back(layout.ConvertTileSpaceToWorldSpace(*i));
    }
    return result;
}
