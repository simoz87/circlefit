#pragma once


class Point2D
{
  float x_,y_;
public:
  Point2D(float x,float y);

  ~Point2D(void);

  float getx() const;
  float gety() const;

  friend const Point2D operator+(const Point2D &p1, const Point2D &p2);
  friend const bool compx(const Point2D &p1, const Point2D &p2);
  friend const bool compy(const Point2D &p1, const Point2D &p2);
};
