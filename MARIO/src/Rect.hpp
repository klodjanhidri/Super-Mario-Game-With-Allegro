#ifndef RECT_HPP_INCLUDED
#define RECT_HPP_INCLUDED

class Rect {
    int x1;
    int y1;
    int x2;
    int y2;
public:
    const int   GetX1 (void) const;
    const int   GetY1 (void) const;
    const int   GetX2 (void) const;
    const int   GetY2 (void) const;
    void        SetX1 (const int& _x);
    void        SetY1 (const int& _y);
    void        SetX2 (const int& _x);
    void        SetY2 (const int& _y);
    Rect  (int _x1=0, int _y1=0, int _x2=0, int _y2=0);
    ~Rect (void);
};

#endif // RECT_HPP_INCLUDED
