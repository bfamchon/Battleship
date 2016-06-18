#ifndef POSITION_HPP
#define POSITION_HPP

struct Position {
  int _x;
  int _y;
  Position operator+(const Position& p) const 
  { return Position{p._x+_x, p._y+_y}; }
};

#endif
