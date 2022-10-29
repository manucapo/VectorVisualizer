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
#include "Line.hpp"
#include "Integrator.hpp"
#include "Trace.hpp"


#define WORLDSIZE 800       // defines default render window size in pixels.
#define SCALE 40    // defines default amount of pixesl per unit.
#define VECTORMULTIPLIER 1  // defines default vector magnitude scaling.
#define PARTICLESHAPERADIUS 0.2f // defines the radius of the cirlce shapes corresponding to particles

Evaluator *Evaluator::instancePtr = 0; // SINGLETON INSTANCE POINTER INIT.

void CreateParticle(Particle *tempParticle,shared_ptr<World> world, double charge, double forceConstant, double decayExponent, double x, double y);
void CreateCustomParticle(string *inputString,float *userInputFloat, Particle *tempParticle,shared_ptr<World> world);
void CreateCustomLine(string* inputString, float* userInputFloat, Line* tempLine, shared_ptr<World> world);
void SFMLSetUp(Point worldArray[], Vector2 fieldArray[],vector<Particle> particleVector,vector<Line> lineVector, bool normalizeFieldDisplay, int scale , float vectorScale);
float RemapFloatRange(float value, float from1, float to1, float from2, float to2);

void CreateParticle(Particle *tempParticle,shared_ptr<World> world, double charge, double forceConstant, double decayExponent, double x, double y){ //Create particle without user input
    tempParticle->setCharge(charge);
    tempParticle->setForceConstant(forceConstant);
    tempParticle->setDecayExponent(decayExponent);
    tempParticle->setX(x);
    tempParticle->setY(y);
    world->particleVector.push_back(*tempParticle);     // push particle to world
}

void CreateCustomParticle(string *inputString,float *userInputFloat, Particle *tempParticle,shared_ptr<World> world){ //Create particle asking user for input
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
    world->particleVector.push_back(*tempParticle); // push particle to world
}

void CreateCustomLine(string* inputString, float* userInputFloat, Line* tempLine, shared_ptr<World> world) {  //Create line asking user for input
    cout << "Enter Desired amount of line segments: " << endl;
    getline(cin, *inputString);
    stringstream(*inputString) >> *userInputFloat;
    int lineSegmentAmount = *userInputFloat;
    if (lineSegmentAmount > 0)
    {
        Line line;
        for (int i = 0; i < lineSegmentAmount; i++)
        {

            Point start;
            if (i == 0)
            {
                cout << "LINE SEGMENT " << i << " START :" << endl;
                cout << "Enter Desired start point X coordinate : " << endl;
                getline(cin, *inputString);
                stringstream(*inputString) >> *userInputFloat;
                start.setX(*userInputFloat);
                cout << "Enter Desired start point Y coordinate : " << endl;
                getline(cin, *inputString);
                stringstream(*inputString) >> *userInputFloat;
                start.setY(*userInputFloat);
            }
            else
            {
                start.setX(line.getTail().getX());
                start.setY(line.getTail().getY());
            }
            cout << "LINE SEGMENT " << i << " END :" << endl;
            Point end;
            cout << "Enter Desired end point X coordinate : " << endl;
            getline(cin, *inputString);
            stringstream(*inputString) >> *userInputFloat;
            end.setX(*userInputFloat);
            cout << "Enter Desired end point Y coordinate : " << endl;
            getline(cin, *inputString);
            stringstream(*inputString) >> *userInputFloat;
            end.setY(*userInputFloat);

            line.addSegment(start, end);
        }
        world->lineVector.push_back(line);
    }
}

void CreateCustomTrace(string* inputString, float* userInputFloat, Trace* tracePtr, shared_ptr<World> world) {  //Create trace asking user for input

        Trace trace;
        double xCoord;
        double yCoord;
                cout << "CREATING TRACE : " << endl;
                cout << "Enter Desired start point X coordinate : " << endl;
                getline(cin, *inputString);
                stringstream(*inputString) >> *userInputFloat;
                xCoord = *userInputFloat;
                cout << "Enter Desired start point Y coordinate : " << endl;
                getline(cin, *inputString);
                stringstream(*inputString) >> *userInputFloat;
                yCoord = *userInputFloat;

                trace.SetStart(xCoord, yCoord);
                trace.CreateTrace(world->particleVector);

        world->traceVector.push_back(trace);
    
}

void SFMLSetUp(Point worldArray[], Vector2 fieldArray[],vector<Particle> particleVector,vector<Line> lineVector, vector<Trace> traceVector, bool normalizeFieldDisplay, int scale, float vectorScale){
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
    std::vector<sf::RectangleShape> lineDrawQeue;
    std::vector<sf::CircleShape> vectorHeadDrawQeue(WORLDSIZE * WORLDSIZE);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WORLDSIZE, WORLDSIZE,desktopVideoMode.bitsPerPixel ), "SFML window");
    
    int i, j; // iterator counters
    // filling particle draw qeue.
    for (i = 0; i < particleVector.size(); i++){   
        Particle particle = particleVector.at(i);
        sf::CircleShape circle;
        double xCoord = particle.getX();   // Get particle position  Coordinates
        double yCoord = -particle.getY();  // The y coordinate is inverted so that the y axis is rendered in the correct orientation                   
        xCoord *= scale;                   // Scale particle position to the appropiate world scale ( pixels per unit )
        yCoord *= scale;
        xCoord += (WORLDSIZE / 2);         // Offset particle position so the world origin is at the centre of the render window
        yCoord += (WORLDSIZE / 2);
        circle.setPosition(xCoord, yCoord);
        float radius = PARTICLESHAPERADIUS;
        radius *= scale;                   // Scale particle shape radius to the appropiate world scale ( pixels per unit )
        circle.setRadius(radius);
        circle.setOrigin(radius, radius);
        circle.setFillColor(sf::Color::Yellow);              // Neutral particle => YELLOW, Positive charge => BLUE, Negative charge => RED
        if (particle.getCharge() > 0){
            circle.setFillColor(sf::Color::Red);
        } else if (particle.getCharge() < 0) {
            circle.setFillColor(sf::Color(132,236,249,255));
        }
        particleDrawQeue.push_back(circle);            // push circle shape to draw qeue
    }
    // filling line draw qeue.
    for (i = 0; i < lineVector.size(); i++) {   
        Line line = lineVector.at(i);
        sf::RectangleShape rectangle;

        for (j = 0; j < line.getSegments().size(); j++)
        {
            Point start = line.getSegments().at(j).start;
            Vector2 vector = line.getSegments().at(j).vector;
            double xCoord = start.getX();   // Get line start Coordinates
            double yCoord = -start.getY();  // The y coordinate is inverted so that the y axis is rendered in the correct orientation         
            xCoord *= scale;                   // Scale start position to the appropiate world scale ( pixels per unit )
            yCoord *= scale;
            xCoord += (WORLDSIZE / 2);         // Offset start position so the world origin is at the centre of the render window
            yCoord += (WORLDSIZE / 2);
            rectangle.setPosition(xCoord, yCoord);
            double magnitude = vector.Magnitude();
            magnitude *= scale;          // Scale the visualization of lines with the fixed world scale ( pixels per unit )     
            rectangle.setSize(sf::Vector2f(magnitude, 1));
            rectangle.setFillColor(sf::Color::Yellow);
            rectangle.setRotation(-vector.EuelerAngle());       // Invert angle to be rendered in the proper orientaton
            lineDrawQeue.push_back(rectangle);                    // push rectangle shape to draw qeue
        }
        Integrator integrator;
        cout << "Line " << i << " integral = " << integrator.IntegrateLine(line, particleVector) << endl;
    }

    // filling trace draw qeue.
    for (i = 0; i < traceVector.size(); i++) {
        Trace trace = traceVector.at(i);
        Line line = trace.GetLine();
        sf::RectangleShape rectangle;

        for (j = 0; j < line.getSegments().size(); j++)
        {
            Point start = line.getSegments().at(j).start;
            Vector2 vector = line.getSegments().at(j).vector;
            double xCoord = start.getX();   // Get line start Coordinates
            double yCoord = -start.getY();  // The y coordinate is inverted so that the y axis is rendered in the correct orientation         
            xCoord *= scale;                   // Scale start position to the appropiate world scale ( pixels per unit )
            yCoord *= scale;
            xCoord += (WORLDSIZE / 2);         // Offset start position so the world origin is at the centre of the render window
            yCoord += (WORLDSIZE / 2);
            rectangle.setPosition(xCoord, yCoord);
            double magnitude = vector.Magnitude();
            magnitude *= scale;          // Scale the visualization of lines with the fixed world scale ( pixels per unit )     
            rectangle.setSize(sf::Vector2f(magnitude, 1));
            rectangle.setFillColor(sf::Color::Yellow);
            rectangle.setRotation(-vector.EuelerAngle());       // Invert angle to be rendered in the proper orientaton
            lineDrawQeue.push_back(rectangle);                    // push rectangle shape to draw qeue
        }
    }
    
    //filling grid draw qeue
    for(i = 0; i < WORLDSIZE; i++){  
        for(j = 0; j < WORLDSIZE; j++){
            sf::RectangleShape* rectangle = &gridDrawQeue[i * WORLDSIZE + j];
            double xCoord = worldArray[i * WORLDSIZE + j].getX();
            double yCoord = -worldArray[i * WORLDSIZE + j].getY(); // The y coordinate is inverted so that the y axis is rendered in the correct orientation     
            xCoord *= scale;                                       // Scale grid position to the appropiate world scale ( pixels per unit )
            yCoord *= scale;
            xCoord +=  WORLDSIZE / 2;        // Offset shape position so the world origin is at the centre of the render window
            yCoord += WORLDSIZE / 2;
            rectangle->setSize(sf::Vector2f(2, 2));
            rectangle->setOrigin(1.0f,1.0f);
            rectangle->setPosition(xCoord, yCoord);
            rectangle->setFillColor(sf::Color::Red);
            
            for(Particle& particle : particleVector){  // calculate influence from all particles in world
                xCoord = worldArray[i * WORLDSIZE + j].getX();                // Get mathematical coordinates
                yCoord = worldArray[i * WORLDSIZE + j].getY();
                Vector2 force = particle.calcualteResultingForceVector(xCoord, yCoord); // Calculate force vector
                 fieldArray[i * WORLDSIZE + j].Add(force);
            }        
        }       
    }
    // calculating the maximum magnitude for correct vector colouring.
    float maxMagnitude = 0;                             
    float minMagnitude = FLT_MAX;

    for(i = 0; i < WORLDSIZE; i++){  
        for(j = 0; j < WORLDSIZE; j++){
            Vector2 vector = fieldArray[i * WORLDSIZE + j];
            if (vector.Magnitude() < minMagnitude) {       // Check magnitude against lower bound
                minMagnitude = vector.Magnitude();         
            }

            if (vector.Magnitude() > maxMagnitude) {       // Check magnitude against upper bound
                maxMagnitude = vector.Magnitude();
            }   
        }
    }
    // calculating vector colour
    for(i = 0; i < WORLDSIZE; i++){                          
        for(j = 0; j < WORLDSIZE; j++){
            Vector2 vector = fieldArray[i * WORLDSIZE + j];
            sf::RectangleShape* vectorShapePtr = &vectorDrawQeue[i * WORLDSIZE + j];
            sf::CircleShape* vectorHeadShapePtr = &vectorHeadDrawQeue[i * WORLDSIZE + j];

            int colourStrenght = RemapFloatRange(vector.Magnitude(), minMagnitude, maxMagnitude, 1, 100);   // Remap vector magnitudes between 1-100
            colourStrenght = RemapFloatRange(log(colourStrenght), log(1), log(100), 0, 255);    // Remap magnitudes between 0-255 logarithmicaly
            vectorShapePtr->setFillColor(sf::Color(0,colourStrenght, 255 - colourStrenght,225));  // Colouring vectors.
            vectorHeadShapePtr->setFillColor(sf::Color(0,colourStrenght, 255 -  colourStrenght,225));  
            
            if (normalizeFieldDisplay){                    // field normalizaiton.
                vector.Normalize();
            }

            // filling vector and vectorhead qeues.
            double xCoord = worldArray[i * WORLDSIZE + j].getX();  // Get mathematical coordinates
            double yCoord = -worldArray[i * WORLDSIZE + j].getY(); // The y coordinate is inverted so that the y axis is rendered in the correct orientation   
            xCoord *= scale;                                       // Scale vector position to the appropiate world scale ( pixels per unit )
            yCoord *= scale;
            xCoord += WORLDSIZE / 2;                               // Offset vector position so the world origin is at the centre of the render window
            yCoord += WORLDSIZE / 2; 

            vectorShapePtr->setPosition(xCoord,yCoord);
            vectorShapePtr->setSize(sf::Vector2f(vector.Magnitude() * vectorScale,1));   // Scale magnitude with user set scaling
            vectorShapePtr->setOrigin(0, 0.5f);
            vectorShapePtr->setRotation(-vector.EuelerAngle());                 // Invert angle to be rendered in the proper orientaton

            if (vector.Magnitude() > 0)
            {
                vectorHeadShapePtr->setPointCount(3);
                vectorHeadShapePtr->setRadius(0.1 * scale);
                vectorHeadShapePtr->setOrigin(0.1 * scale, 0);
                xCoord += vector.getX() * vectorScale;                    // Offset arrow head position to be at end of vector
                yCoord -= vector.getY() * vectorScale;
                vectorHeadShapePtr->setPosition(xCoord, yCoord);
                vectorHeadShapePtr->setRotation(-vector.EuelerAngle() + 90);   // Invert angle  and add a 90 degree offset so shape is rendered properly
            }    
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
        window.clear(sf::Color(0,0,0,255));
        
        // Draw the sprite
        
        window.draw(xAxisLine);
        window.draw(yAxisLine);
        
        for(i = 1; i < WORLDSIZE / scale; i++){
            for (j = 1; j < (WORLDSIZE / scale) - 1; j++){          // draw all UI elements.
                int index = i * scale * WORLDSIZE + (j * scale);
                window.draw(vectorDrawQeue[index]); 
                window.draw(gridDrawQeue[index]);
                window.draw(vectorHeadDrawQeue[index]);
                
            }
        }
        
        for(sf::CircleShape& circle : particleDrawQeue){ // draw point particles.
            window.draw(circle);    
        }

        for (sf::RectangleShape& rectangle : lineDrawQeue) { // draw lines.
            window.draw(rectangle);
        }
        
        // Update the window
        window.display();
    }
}

inline float RemapFloatRange(float value, float from1, float to1, float from2, float to2)
{
    return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
}

#endif /* HelperFunctions_hpp */
