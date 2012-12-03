#include "Point2D.h"

Point2D::Point2D (float x,float y):
    x_(x),
    y_(y)
  {
  }

Point2D::~Point2D(void)
  {}

float Point2D::getx() const{
	  return x_;
  }

float Point2D::gety() const{
	  return y_;
  }


const Point2D operator+(const Point2D &p1, const Point2D &p2){
	float allx=p1.getx()+p2.getx();
	float ally=p1.gety()+p2.gety();
	return Point2D(allx, ally);
}

const bool compx(const Point2D &p1, const Point2D &p2){return p1.getx()<p2.getx();}
const bool compy(const Point2D &p1, const Point2D &p2){return p1.gety()<p2.gety();}
