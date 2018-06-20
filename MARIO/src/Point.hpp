#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED

class Point {
    int x;
    int y;
public:
    const int   GetX (void) const;
    const int   GetY (void) const;
    void        SetX (const int& _x);
    void        SetY (const int& _y);
    Point  (int _x=0, int _y=0);
    ~Point (void);
};


#endif // POINT_HPP_INCLUDED
