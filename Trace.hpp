#pragma once
#ifndef Trace_hpp
#define Trace_hpp

#include "Point.hpp"
#include "Vector2.hpp"
#include "Line.hpp"
#include "Evaluator.hpp"
#include "Particle.hpp"
#include <vector>


#define DELTA 0.01
#define RANGE 20 

class Trace
{
	Line line;
	Point start;

public:

	Line GetLine() {
		return line;
	}

	void SetStart(double xCoord, double yCoord) {
		start.setX(xCoord);
		start.setY(yCoord);
	}

	void CreateTrace(vector<Particle> particleVector) {

		Vector2 sampledVector;
		Point segmentStart = start;
		Point segmentEnd;
		double delta = DELTA;

		Evaluator::instance()->setXValue(segmentStart.getX());
		Evaluator::instance()->setYValue(segmentStart.getY());
		Evaluator::instance()->setXResult(0);                                                        // Set Dummy evaluator results in case evaluator is in test mode.
		Evaluator::instance()->setYResult(0);
#ifdef EXPRESSIONMODE1
		if (Evaluator::instance()->getParserState())
		{
			Evaluator::instance()->setXResult(Evaluator::instance()->getExpressionX().value());          // Set Actual evaluator results in full mode.
			Evaluator::instance()->setYResult(Evaluator::instance()->getExpressionY().value());
		}
#endif
		sampledVector.setX(Evaluator::instance()->getXResult());
		sampledVector.setY(Evaluator::instance()->getYResult());

		segmentEnd.setX(segmentStart.getX());
		segmentEnd.setY(segmentStart.getY());
		line.addSegment(segmentStart, segmentEnd);

		int n = RANGE / DELTA;  // calculate amount of steps to integrate

		for (double i = 0; i < n; i++)
		{
			segmentStart = segmentEnd;

			Evaluator::instance()->setXValue(segmentStart.getX());
			Evaluator::instance()->setYValue(segmentStart.getY());
			Evaluator::instance()->setXResult(0);                                                        // Set Dummy evaluator results in case evaluator is in test mode.
			Evaluator::instance()->setYResult(0);
#ifdef EXPRESSIONMODE1
			if (Evaluator::instance()->getParserState())
			{
				Evaluator::instance()->setXResult(Evaluator::instance()->getExpressionX().value());          // Set Actual evaluator results in full mode.
				Evaluator::instance()->setYResult(Evaluator::instance()->getExpressionY().value());
			}
#endif
			sampledVector.setX(Evaluator::instance()->getXResult());
			sampledVector.setY(Evaluator::instance()->getYResult());

			for (Particle& particle : particleVector) {  // calculate influence from all particles in world
				sampledVector.Add(particle.calcualteResultingForceVector(Evaluator::instance()->getXValue(), Evaluator::instance()->getYValue()));
			}
			sampledVector.Normalize();
			sampledVector.Multiply(delta);

			double xCoord = segmentStart.getX() + sampledVector.getX();
			double yCoord = segmentStart.getY() + sampledVector.getY();
			segmentEnd.setX(xCoord);
			segmentEnd.setY(yCoord);
			line.addSegment(segmentStart, segmentEnd);
		}
	}

	Trace();
	~Trace();
};

#endif
