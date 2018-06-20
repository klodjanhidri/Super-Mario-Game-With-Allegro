#ifndef ANIMATION_FILM_HOLDER_HPP_INCLUDED
#define ANIMATION_FILM_HOLDER_HPP_INCLUDED
#include    "AnimationFilm.hpp"
#include    "BitmapLoader.hpp"
#include    <stdio.h>
#include    <iostream>
#include    <fstream>
#include    <assert.h>

class AnimationFilmHolder   {
    typedef std::map<std::string, AnimationFilm*> Films;
    Films                       films;
    BitmapLoader                bitmaps; //only for loading bitmaps
    static AnimationFilmHolder  holder;  //singleton
    AnimationFilmHolder  (void) {}
public:
   //static const AnimationFilmHolder&    Get (void) const;
   static AnimationFilmHolder&    Get (void);
   void                           Load (const std::string catalogue);
   void                           CleanUp (void);
   AnimationFilm*                 GetFilm (const std::string id) const;
   ~AnimationFilmHolder (void);
};


#endif // ANIMATION_FILM_HOLDER_HPP_INCLUDED
