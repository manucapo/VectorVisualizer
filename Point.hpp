//
//  Point.hpp
//  SeminarProjectManu
//
//  Created by Manuel Telleria on 09.03.18.
#pragma once

#include <math.h>

class Point{
    double x;
    double y;
    
public:
    
    void setX(double value){
        x = value;
    }
    void setY(double value){
        y = value;
        
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    
    double calcualteDistance(double xPosition, double yPosition){
        double result;
        result = sqrt(pow((xPosition-x),2)+pow(yPosition-y,2));
        return result;
    }
    
    
    Point(double xCoord, double yCoord);
    Point();
    ~Point();
    
    
};

