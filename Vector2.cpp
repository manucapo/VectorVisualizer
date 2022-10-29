//
//  Vector2.cpp
//  SeminarProjectManu
//
//  Created by Manuel Telleria on 09.03.18.
//  Copyright © 2018 Manuel Telleria. All rights reserved.
//

#include "Vector2.hpp"

Vector2::Vector2(double xComponent, double yComponent){
    this->x = xComponent;
    this->y = yComponent;
}

Vector2::Vector2(){
    this->x = 0;
    this->y = 0;
}

Vector2::~Vector2(){
}

