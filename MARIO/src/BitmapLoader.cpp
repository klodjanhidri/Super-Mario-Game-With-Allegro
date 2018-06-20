#include    "BitmapLoader.hpp"

Bitmap      BitmapLoader::GetBitmap (const std::string path) const{
    BitmapMap::const_iterator i = bitmaps.find(path);
    return i != bitmaps.end()   ?   i->second : (Bitmap) 0;
}
Bitmap      BitmapLoader::Load (const std::string& path){
    //first we look at hash table
    Bitmap b = GetBitmap(path);
    //if there isnt in hash table then load from hard drive
    if ( !b ) {
        bitmaps[path] = (b = al_load_bitmap(path.c_str()));
        assert(b);
    }
    return b;
    //prefer to massively clear bitmaps at the end tha
    //to destroy individual bitmaps during gameplay
}
void        BitmapLoader::CleanUp (void){
    for ( BitmapMap::iterator i = bitmaps.begin(); i!=bitmaps.end(); ++i) {
        al_destroy_bitmap(i->second);
    }
    bitmaps.clear();
}
BitmapLoader::BitmapLoader (void){}
BitmapLoader::~BitmapLoader (void){ CleanUp(); }
