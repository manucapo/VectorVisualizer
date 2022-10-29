#pragma once

#ifndef Integrator_hpp
#define Integrator_hpp

#include "Line.hpp"
#include "Particle.hpp"
#include "Evaluator.hpp"

 

class Integrator
{
#define DELTA 0.0001;  

public:
	double IntegrateLine(Line line, vector<Particle> particleVector) {

        double summer = 0;


        for (int i = 0; i < line.getSegments().size(); i++)
        {
            Vector2 diffVector;
            double delta = DELTA;
            diffVector = line.getSegments().at(i).vector;
            double magnitude = diffVector.Magnitude();

            diffVector.Normalize();
            diffVector.Multiply(delta);

            int n = magnitude / diffVector.Magnitude();  // calculate amount of steps to integrate

            for (int  j = 0; j < n; j++)
            {
                Evaluator::instance()->setXValue(line.getSegments().at(i).start.getX() + (diffVector.getX() * j));
                Evaluator::instance()->setYValue(line.getSegments().at(i).start.getY() + (diffVector.getY() * j));
                Evaluator::instance()->setXResult(0);                                                        // Set Dummy evaluator results in case evaluator is in test mode.
                Evaluator::instance()->setYResult(0);
#ifdef EXPRESSIONMODE1
                if (Evaluator::instance()->getParserState())
                {
                    Evaluator::instance()->setXResult(Evaluator::instance()->getExpressionX().value());          // Set Actual evaluator results in full mode.
                    Evaluator::instance()->setYResult(Evaluator::instance()->getExpressionY().value());
                }
#endif

                Vector2 sampledVector;
               sampledVector.setX(Evaluator::instance()->getXResult());
               sampledVector.setY(Evaluator::instance()->getYResult());

               for (Particle& particle : particleVector) {  // calculate influence from all particles in world
                   sampledVector.Add(particle.calcualteResultingForceVector(Evaluator::instance()->getXValue(), Evaluator::instance()->getYValue()));
               }
              
               summer += sampledVector.dot(diffVector);
           
            }

        }
        return summer;
	}
 
	Integrator();
	~Integrator();
};

#endif
