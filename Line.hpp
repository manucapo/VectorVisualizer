#pragma once

#include <vector>
#include "Point.hpp"
#include "Vector2.hpp"

class Line
{

	struct LineSegment {
		Point start;
		Point end;
		Vector2 vector;
	};

	std::vector<LineSegment> segments;

public:

	void addSegment(Point start, Point end) {
		LineSegment segment;
		segment.start = start;
		segment.end = end;
		Vector2 vector;
		vector.setX(end.getX() - start.getX());
		vector.setY(end.getY() - start.getY());
		segment.vector = vector;
		segments.push_back(segment);
	}

	Point getTail() {
		return segments.back().end;
	}

	std::vector<LineSegment> getSegments() {
		return segments;
	}

	Line();
	~Line();
};