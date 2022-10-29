
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

