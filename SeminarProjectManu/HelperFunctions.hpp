//
//  HelperFunctions.hpp
//  SeminarProjectManu
//
//  Created by Manuel Telleria on 25.06.18.
//  Copyright © 2018 Manuel Telleria. All rights reserved.
//

#ifndef HelperFunctions_hpp
#define HelperFunctions_hpp


#include <iostream>
#include <math.h>
#include <string>                                        // C++ string engine
#include <vector>                                        // C++ vector lists
#include <SFML/Graphics.hpp>                             // Graphics library core functionality.
#include "exprtk.hpp"                                    // External expression evaluator code.
#include "Vector2.hpp"
#include "Point.hpp"
#include "World.hpp"
#include "Evaluator.hpp"
#include "Particle.hpp"


#define WORLDSIZE 800       // defines default render window size in pixels.
#define SCALE 40    // defines default amount of pixesl per unit.
#define VECTORMULTIPLIER 1  // defines default vector magnitude scaling.

Evaluator *Evaluator::instancePtr = 0; // SINGLETON INSTANCE POINTER INIT.

void CreateParticle(Particle *tempParticle,shared_ptr<World> world, double charge, double forceConstant, double decayExponent, double x, double y);
void CreateCustomParticle(string *inputString,float *userInputFloat, Particle *tempParticle,shared_ptr<World> world);
void SFMLSetUp(Point worldArray[], Vector2 fieldArray[],vector<Particle> particleVector, bool normalizeFieldDisplay, int scale , float vectorScale); 

void CreateParticle(Particle *tempParticle,shared_ptr<World> world, double charge, double forceConstant, double decayExponent, double x, double y){
    tempParticle->setCharge(charge);
    tempParticle->setForceConstant(forceConstant);
    tempParticle->setDecayExponent(decayExponent);
    tempParticle->setX(x);
    tempParticle->setY(y);
    world->particleVector.push_back(*tempParticle);
    
}

void CreateCustomParticle(string *inputString,float *userInputFloat, Particle *tempParticle,shared_ptr<World> world){
    cout << "Enter particle X postion : \n" << endl;
    getline(cin,*inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setX(*userInputFloat);
    cout << "Enter particle Y postion : \n" << endl;
    getline(cin,*inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setY(*userInputFloat);
    cout << "Enter particle force constant : \n" << endl;
    getline(cin,*inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setForceConstant(*userInputFloat);
    cout << "Enter particle charge : \n" << endl;
    getline(cin,*inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setCharge(*userInputFloat);
    cout << "Enter particle decay exponent : \n" << endl;
    getline(cin,*inputString);
    stringstream(*inputString) >> *userInputFloat;
    tempParticle->setDecayExponent(*userInputFloat);
    world->particleVector.push_back(*tempParticle);
}

void SFMLSetUp(Point worldArray[], Vector2 fieldArray[],vector<Particle> particleVector, bool normalizeFieldDisplay, int scale, float vectorScale){
    sf::ContextSettings settings;
    sf::VideoMode desktopVideoMode;
    
    desktopVideoMode = sf::VideoMode::getDesktopMode();
    settings.antialiasingLevel =4;
    
    
    sf::RectangleShape xAxisLine;                // X AXIS DISPLAY LINE
    xAxisLine.setPosition((WORLDSIZE / 2)-1, 0);
    xAxisLine.setFillColor(sf::Color::Black);
    xAxisLine.setSize(sf::Vector2f(2,WORLDSIZE));
    
    sf::RectangleShape yAxisLine;               // Y AXIS DISPLAY LINE
    yAxisLine.setPosition(0, (WORLDSIZE / 2)-1);
    yAxisLine.setFillColor(sf::Color::Black);
    yAxisLine.setSize(sf::Vector2f(WORLDSIZE,2));
    
    std::vector<sf::RectangleShape> gridDrawQeue(WORLDSIZE * WORLDSIZE);
    std::vector<sf::RectangleShape> vectorDrawQeue(WORLDSIZE * WORLDSIZE);
    std::vector<sf::CircleShape> particleDrawQeue;
    std::vector<sf::CircleShape> vectorHeadDrawQeue(WORLDSIZE * WORLDSIZE);
    
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WORLDSIZE, WORLDSIZE,desktopVideoMode.bitsPerPixel ), "SFML window");
    
    int i, j;
    
    int maxMagnitude = 0;
    
    for (i = 0; i < particleVector.size(); i++){   // filling particle draw qeue.
        Particle tempParticle;
        sf::CircleShape tempCircle;
        tempParticle = particleVector.at(i);
        tempCircle.setRadius(0.2*scale);
        tempCircle.setOrigin(0.2*scale,0.2*scale);
        tempCircle.setPosition((tempParticle.getX()*scale-1 + WORLDSIZE/2),(-tempParticle.getY()*scale-1 + WORLDSIZE/2));
        tempCircle.setFillColor(sf::Color::Yellow);
        if (tempParticle.getCharge() > 0){
            tempCircle.setFillColor(sf::Color::Red);
        } else if (tempParticle.getCharge() < 0) {
            tempCircle.setFillColor(sf::Color(132,236,249,255));
        }
        
        
        particleDrawQeue.push_back(tempCircle);
    }
    
    
    
    for(i = 0; i < WORLDSIZE; i++){  //filling grid draw qeue
        for(j = 0; j < WORLDSIZE; j++){
            gridDrawQeue[i * WORLDSIZE + j].setPosition(worldArray[i * WORLDSIZE + j].getX()*scale-2 + WORLDSIZE/2 , worldArray[i * WORLDSIZE + j].getY()*scale-2 +WORLDSIZE/2);
            gridDrawQeue[i * WORLDSIZE + j].setSize(sf::Vector2f(4,4));
            gridDrawQeue[i * WORLDSIZE + j].setFillColor(sf::Color::Red);
            
            
            for(Particle& particle : particleVector){  // calculate influence from all particles in world
                
                fieldArray[i * WORLDSIZE + j].Add(particle.calcualteResultingForceVector(worldArray[i * WORLDSIZE + j].getX(),worldArray[i * WORLDSIZE + j].getY()));
            }
            
        }
        
    }
    
    for(i = 0; i < WORLDSIZE; i++){  // calculating the maximum magnitude for correct vector colouring.
        for(j = 0; j < WORLDSIZE; j++){
            if ( fieldArray[i * WORLDSIZE + j].MagnitudeSqr() > maxMagnitude){
                maxMagnitude = fieldArray[i * WORLDSIZE + j].MagnitudeSqr();
            }
            
        }
        
    }
    
    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            float colourMultiplier = 255.f / maxMagnitude;
            int colourStrenght = fieldArray[i * WORLDSIZE + j].MagnitudeSqr() * colourMultiplier;    // calculating vector colour
            if(colourStrenght < 0){
                colourStrenght = 0;
            } else if (colourStrenght > 255){  // clamping colourstrenght to max rgb value.
                colourStrenght = 255;
                
            }
            
        
            vectorDrawQeue[i * WORLDSIZE + j].setFillColor(sf::Color(0,colourStrenght,255-(colourStrenght/2),225));  // colouring vectors.
            vectorHeadDrawQeue[i * WORLDSIZE + j].setFillColor(sf::Color(0,colourStrenght,255-(colourStrenght/2),225));
            
            if (normalizeFieldDisplay){                    // field normalizaiton.
                fieldArray[i * WORLDSIZE + j].Normalize();
            }
            
            
            
            
            
            
            // filling vector and vectorhead qeues.
            
            vectorDrawQeue[i * WORLDSIZE + j].setPosition(worldArray[i * WORLDSIZE + j].getX() *scale + WORLDSIZE/2 ,worldArray[i * WORLDSIZE + j].getY()*scale+ WORLDSIZE/2 );
            
            vectorDrawQeue[i * WORLDSIZE + j].setSize(sf::Vector2f(fieldArray[i * WORLDSIZE + j].Magnitude()* vectorScale,1));
            
            vectorDrawQeue[i * WORLDSIZE + j].setRotation(-fieldArray[i * WORLDSIZE + j].EuelerAngle());
            
            vectorHeadDrawQeue[i * WORLDSIZE + j].setPointCount(3);
            vectorHeadDrawQeue[i * WORLDSIZE + j].setRadius(0.1*scale);
            vectorHeadDrawQeue[i * WORLDSIZE + j].setOrigin(0.1*scale,0.1*scale);
            
            vectorHeadDrawQeue[i * WORLDSIZE + j].setPosition((worldArray[i * WORLDSIZE + j].getX() *scale + WORLDSIZE/2) + (fieldArray[i * WORLDSIZE + j].getX()*vectorScale),(worldArray[i * WORLDSIZE + j].getY() *scale+ WORLDSIZE/2) - (fieldArray[i * WORLDSIZE + j].getY()*vectorScale) );
            
            
            vectorHeadDrawQeue[i * WORLDSIZE + j].setRotation(-fieldArray[i * WORLDSIZE + j].EuelerAngle() + 90);
            
        }
        
    }
    
    
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.setSize(sf::Vector2u(1, 1));
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.setSize(sf::Vector2u(1, 1));
                window.close();
            }
        }
        
        // Clear screen
        window.clear(sf::Color(255,249,244,255));
        
        // Draw the sprite
        
        window.draw(xAxisLine);
        window.draw(yAxisLine);
        
        
        
        
        
        for(i = 1; i < WORLDSIZE / scale; i++){
            for (j = 1; j < (WORLDSIZE / scale) - 1; j++){          // draw all UI elements.
                
                
                
                window.draw(vectorDrawQeue[i * scale * WORLDSIZE +(j * scale)]);
                
                window.draw(gridDrawQeue[i * scale * WORLDSIZE + (j * scale)]);
                
                window.draw(vectorHeadDrawQeue[i * scale * WORLDSIZE +(j * scale)]);
                
                
            }
        }
        
        
        for(sf::CircleShape& circle : particleDrawQeue){ // draw point particles.
            window.draw(circle);
            
        }
        
        
        
        // Update the window
        window.display();
    }
}

#endif /* HelperFunctions_hpp */
