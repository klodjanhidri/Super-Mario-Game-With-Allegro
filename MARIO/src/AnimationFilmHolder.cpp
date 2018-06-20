#include "AnimationFilmHolder.hpp"
#include <iostream>
/*static const AnimationFilmHolder&   AnimationFilmHolder::Get (void) const{
    return holder;
}*/
AnimationFilmHolder&         AnimationFilmHolder::Get (void){
    static AnimationFilmHolder  holder;
    return holder;
}
void                         AnimationFilmHolder::Load (const std::string catalogue){
    //read the config with films attributes
    std::ifstream       fileReader;
    std::string         fileContent;
    std::string         bitmapId;
    std::string         bitmapPath;
    int                 boxesCounter;
    int                 x;
    int                 y;
    int                 x2;
    int                 y2;
    int                 first;
    int                 last;
    std::vector<Rect>   boxes;
    Bitmap              tmpBitmap;

    fileReader.open(catalogue.c_str());
    assert( !fileReader.fail() );
    while ( fileReader.good() ){
        std::getline(fileReader, fileContent);
        first = fileContent.find('\"',0);
        last  = fileContent.find('\"', (++first));
        bitmapId.assign( fileContent.substr(first, --last) );
        first = fileContent.find('\"', (last+2));
        last  = fileContent.find('\"', (++first));
        bitmapPath.assign( fileContent.substr(first, fileContent.size()-2) );
        bitmapPath.erase(bitmapPath.size()-1);
        std::getline(fileReader, fileContent);
        sscanf(fileContent.c_str(), "%d", &boxesCounter);
        for (int i=0; i<boxesCounter; ++i){
            std::getline(fileReader, fileContent);
            sscanf(fileContent.c_str(), "%d %d %d %d", &x, &y, &x2, &y2);
            Rect* tmpRect = new Rect(x, y, x2, y2 );
            boxes.push_back(*tmpRect);
        }
        tmpBitmap = bitmaps.Load(bitmapPath);
        assert( tmpBitmap );
        AnimationFilm* anFilm = new AnimationFilm(tmpBitmap, boxes, bitmapId);
        assert( anFilm );
        films.insert ( std::make_pair(bitmapId, anFilm) );
        //std::pair<Films::iterator,bool> result = films.insert ( std::make_pair(bitmapId, anFilm) );
        //std::cout<<result.second<<"\n";
        std::getline(fileReader, fileContent); //this is the blank line
    }
}
void                    AnimationFilmHolder::CleanUp (void){
    for ( Films::iterator i = films.begin(); i!=films.end(); i++ )
        delete(i->second);
    films.clear();
}
AnimationFilm*    AnimationFilmHolder::GetFilm (const std::string id) const{
    Films::const_iterator i = films.find(id);
    return i != films.end() ?   i->second : (AnimationFilm*) 0;
}
AnimationFilmHolder::~AnimationFilmHolder (void){
    CleanUp();
}
