#include "curve.h"


Curve::Curve(void) {
	m_refreshNeeded = false;
	m_curveDegree = -1;
}

Curve& Curve::operator=(const Curve &src) {
	m_controlPoints.clear();
	m_controlPoints = src.m_controlPoints;
	m_curveDegree = src.m_curveDegree;
	m_refreshNeeded = src.m_refreshNeeded;

	return *this;
}

Curve::~Curve(void) {

}

void Curve::draw() {

}

void Curve::refresh() {
	m_refreshNeeded = false;
}

void Curve::setCurveDegree(int curveDegree) {
	m_curveDegree = curveDegree;
}

int Curve::getCurveDegree() {
	return m_curveDegree;
}

void Curve::addControlPoint(Point point) {
	m_controlPoints.push_back(point);
}

void Curve::addControlPoint(float x, float y) {
	m_controlPoints.push_back(Point(x, y));
}

vector<Point> Curve::getControlPoints() {
	return m_controlPoints;
}
