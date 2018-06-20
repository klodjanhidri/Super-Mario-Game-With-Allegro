#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

#include    "AnimationFilm.hpp"
#include    "Tiles.hpp"

class Sprite    {
private:
    int             frameNo;
    Rect            frameBox;
    int             x,y;
    int             actual_x; // the x above is the x in viewwindow this x is the x in terrain
    AnimationFilm*  currFilm;
    bool            isVisible;
    bool            gravityAddicted;
    bool            isFalling;
    //TileLayer*    myLayer;
public:
    int             GetXPos             (void) const;
    int             GetYPos             (void) const;
    void            ChangeXPos          (int posx);
    void            ChangeYPos          (int posy);
    void            SetFrame            (byte i);
    int             GetFrame            (void) const;
    AnimationFilm*  GetFilm             (void) const;
    void            SetVisibility       (bool v);
    bool            IsVisible           (void) const;
    void            SetGravity          (bool grv);
    bool            IsGravityAddicted   (void) const;
    void            SetFalling          (bool fall);
    bool            IsFalling           (void) const;
    bool            CollisionCheck      (Sprite* s);
    void            ChangeFilm          (AnimationFilm* anfilm);
    void            Move                (int dx, int dy, Tiles tiles);
    Sprite (byte _x, byte _y, AnimationFilm* film);
};

#endif // SPRITE_HPP_INCLUDED
