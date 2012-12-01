#pragma once


class Point2D
{
  float _x,_y;
public:
  Point2D(float x,float y):
    _x(x),
    _y(y)
  {
  }

  ~Point2D(void)
  {
  }

  float getx(){
	  return _x;
  }
  float gety(){
	  return _y;
  }
};
