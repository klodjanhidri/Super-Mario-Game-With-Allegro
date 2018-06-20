#ifndef ANIMATION_FILM_HPP_INCLUDED
#define ANIMATION_FILM_HPP_INCLUDED

#include    <vector>
#include    "Rect.hpp"
#include    "Point.hpp"
#include    <string>
#include    <allegro5/allegro.h>
typedef ALLEGRO_BITMAP* Bitmap;
typedef unsigned short int byte;

class AnimationFilm {
    Bitmap                  bitmap;
    std::vector<Rect>       boxes;
    std::string             id;
public:
    byte                    GetTotalFrames  (void)  const;
    Bitmap                  GetBitmap       (void)  const;
    const std::string       GetId           (void)  const;
    const Rect              GetFrameBox     (byte frameNo)  const;
    void                    DisplayFrame    (Bitmap dest,const Point& at,
                                             byte frameNo) const;

    AnimationFilm (Bitmap _bitmap, const std::vector<Rect> _boxes, const std::string& _id);
};

#endif // ANIMATIONFILM_HPP_INCLUDED
