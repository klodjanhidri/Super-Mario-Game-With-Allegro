#include "Point.hpp"

const int   Point::GetX (void) const{
    return x;
}
const int   Point::GetY (void) const{
    return y;
}
void        Point::SetX (const int& _x){
    x = _x;
}
void        Point::SetY (const int& _y){
    y = _y;
}
Point::Point  (int _x, int _y) : x(_x), y(_y) {}
Point::~Point (void) {}
