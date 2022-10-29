//
//  World.hpp
//  SeminarProjectManu
//
//  Created by Manuel Telleria on 12.06.18.
//  Copyright © 2018 Manuel Telleria. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>

#include <iostream>
#include <vector>

#include "Point.hpp"
#include "Vector2.hpp"
#include "Particle.hpp"
#include "Line.hpp"
#include "Trace.hpp"
using namespace std;




#define SCALE 40

class World{
public:
    Point *worldArray;      // Array of points that span the mathematical space
    Vector2 *fieldAray;    // array of vectors that define the vector field inside the mathematical space.
    vector<Particle> particleVector; // vector of particles in world.
    vector<Line> lineVector;  // vector of lines in world.
    vector<Trace> traceVector; // vector of traces in the world.
    
    World(int WORLSIZE);
    ~World();
    
};


#endif /* World_hpp */
