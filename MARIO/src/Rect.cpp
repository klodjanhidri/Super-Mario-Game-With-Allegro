#include "Rect.hpp"

const int   Rect::GetX1 (void) const
        { return x1; }

const int   Rect::GetY1 (void) const
        { return y1; }

const int   Rect::GetX2 (void) const
        { return x2; }

const int   Rect::GetY2 (void) const
        { return y2; }

void        Rect::SetX1 (const int& _x)
        { x1 = _x; }

void        Rect::SetY1 (const int& _y)
        { y1 = _y; }

void        Rect::SetX2 (const int& _x)
        { x2 = _x; }

void        Rect::SetY2 (const int& _y)
        { y2 = _y; }

Rect::Rect  (int _x1, int _y1, int _x2, int _y2)
    : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

Rect::~Rect (void)  {}
