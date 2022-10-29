//
//  Vector2.hpp
//  SeminarProjectManu
//
//  Created by Manuel Telleria on 09.03.18.
//  Copyright © 2018 Manuel Telleria. All rights reserved.
//

#ifndef Vector2_hpp
#define Vector2_hpp

#include <math.h>


const double pi = 3.141592653589793;


class Vector2{
    
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
    
    double MagnitudeSqr(){
        double magnitude = (x*x)+(y*y);
        return magnitude;
    }
    double Magnitude(){
        double magnitude = sqrt(MagnitudeSqr());
        return magnitude;
    }
    double EuelerAngle(){
        double angle = atan2(y,x)*180/pi;
        return angle;
    }
    
    double dot(Vector2 vector){
        double product = (x*vector.x)+(y*vector.y);
        return product;
    }
    
    void Add(Vector2 vector){
        x = x + vector.x;
        y = y + vector.y;
    }
    void Substract(Vector2 vector){
        x = x - vector.x;
        y = y - vector.y;
    }
    void Invert(){
        x = -x;
        y = -y;
    }
    void Mirror(){
        x = -x;
    }
    void Conjugate(){
        y = -y;
    }
    void Multiply(double factor){
        x = x*factor;
        y = y*factor;
    }
    void Normalize(){
        double magnitude = Magnitude();
        if (magnitude > 0)
        {
            y = y / magnitude;
            x = x / magnitude;
        }
    }
    void FlipComponents(){
        double tempX = x;
        
        x = y;
        y = tempX;
    }
    void Perpendicularize(){
        double tempX = x;
        
        x = y;
        y = -tempX;
    }
    
    
    Vector2(double xComponent, double yComponent);
    Vector2();
    ~Vector2();
};

#endif /* Vector2_hpp */

