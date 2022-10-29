#pragma once

#include <stdio.h>
#include <iostream>


#include "Point.hpp"
#include "Vector2.hpp"



class Particle : public Point{
    
    double forceConstant = 0;
    double charge = 0;
    double decayExponent = 0;
    
    
public:
    
    double getCharge(){
        return charge;
    }
    
    void setCharge(double amount){
        charge = amount;
    }
    
    double getForceConstant(){
        return forceConstant;
    }
    
    void setForceConstant(double amount){
        forceConstant = amount;
    }
    
    void setDecayExponent(double amount){
        decayExponent = amount;
    }
    double getDecayExponent(){
        return decayExponent;
    }

    
    Vector2 calcualteResultingForceVector(double xPosition, double yPosition){
        
        Vector2 unitVector(xPosition - getX(),yPosition - getY());
        double distance;
        double force;
        
        unitVector.Normalize();
        
        distance = calcualteDistance(xPosition, yPosition);
        
        if (distance > 0){
            if (decayExponent < 0){
                decayExponent = 0;
            }
        force = forceConstant*(charge/pow(distance,decayExponent));
        } else {
            force = 0;
        }
        unitVector.setY(unitVector.getY());
        unitVector.Multiply(force);
        
        return unitVector;
        
    }
    
    Particle();
    ~Particle();

};

