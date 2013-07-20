#pragma once

#include "point.h"
#include <vector>

using namespace std;

class Curve
{

public:
	Curve(void);
	~Curve(void);

	Curve& operator=(const Curve&);

	virtual void draw();
	virtual void refresh();

	void setCurveDegree(int);
	void addControlPoint(Point);
	void addControlPoint(float, float);

	int getCurveDegree();
	vector<Point> getControlPoints();

protected:
	vector<Point> m_controlPoints;
	int m_curveDegree;
	bool m_refreshNeeded;

private:

};