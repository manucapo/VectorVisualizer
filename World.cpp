//
//  World.cpp
//  SeminarProjectManu
//
//  Created by Manuel Telleria on 12.06.18.
//  Copyright © 2018 Manuel Telleria. All rights reserved.
//

#include <iostream>
#include "World.hpp"

World::World(int WORLDSIZE){
    worldArray =   new Point[WORLDSIZE * WORLDSIZE];
    fieldAray  = new Vector2[WORLDSIZE * WORLDSIZE];
}


World::~World(){
    delete[] worldArray;
    delete[] fieldAray;
}

