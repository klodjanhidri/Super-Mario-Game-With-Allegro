#ifndef BITMAPLOADER_HPP_INCLUDED
#define BITMAPLOADER_HPP_INCLUDED
#include    <map>
#include    <string>
#include    <allegro5/allegro.h>
typedef ALLEGRO_BITMAP* Bitmap;

class BitmapLoader  {
private:
    typedef std::map<std::string, Bitmap>   BitmapMap;
    BitmapMap   bitmaps;
    Bitmap      GetBitmap (const std::string path) const;
public:
    Bitmap      Load (const std::string& path);
    void        CleanUp (void);
    BitmapLoader (void);
    ~BitmapLoader (void);
};


#endif // BITMAPLOADER_HPP_INCLUDED
