#include    "Sprite.hpp"

int             Sprite::GetXPos             (void) const{
    return x;
}
int             Sprite::GetYPos             (void) const{
    return y;
}
void            Sprite::ChangeXPos          (int posx){
    x += posx;
}
void            Sprite::ChangeYPos          (int posy){
    y += posy;
}
void            Sprite::SetFrame            (byte i){
     if ( i!=frameNo ){
        assert( i < currFilm->GetTotalFrames() );
        frameBox = currFilm->GetFrameBox(frameNo = i);
     }
}
int             Sprite::GetFrame            (void) const{
    return frameNo;
}
AnimationFilm*  Sprite::GetFilm             (void) const{
    return currFilm;
}
void            Sprite::SetVisibility       (bool v){
    isVisible = v;
}
bool            Sprite::IsVisible           (void) const{
    return isVisible;
}
void            Sprite::SetGravity          (bool grv){
    gravityAddicted = grv;
}
bool            Sprite::IsGravityAddicted   (void) const{
    return gravityAddicted;
}
void            Sprite::SetFalling          (bool fall){
    isFalling = fall;
}
bool            Sprite::IsFalling           (void) const{
    return isFalling;
}
bool            Sprite::CollisionCheck      (Sprite* s){

}
void            Sprite::ChangeFilm          (AnimationFilm* anfilm){
    currFilm = anfilm;
}
void            Sprite::Move                (int dx, int dy, Tiles tiles){
    int x1 = tiles.getViewWindowX1();
    int x2 = ( (TERRAIN_MAX_WIDTH-16)*MAXIMIZATION - 40 );
    //-40 is for the player whos width is 40
    if ( (actual_x+dx) < x1 )
        return;
    else if ( (actual_x+dx) > x2)
        return;
   /* else if ( dx > 0){
        Rect tmp = tiles.getTerrainTileBitmap(y/MAXIMIZATION, (actual_x+40+dx)/MAXIMIZATION);
        std::cout << tmp.GetX1() << "\t"<<tmp.GetY1() <<"\n";
        if ( tiles.isSolid(tmp.GetY1(), tmp.GetX1()) )
            return;
    }
    else if ( dx < 0 ){
        Rect tmp = tiles.getTerrainTileBitmap(y/MAXIMIZATION, (actual_x+dx)/MAXIMIZATION);
        if ( tiles.isSolid(tmp.GetY1(), tmp.GetX1()) )
            return;
    }*/

    x += dx;
    y += dy;
    actual_x += dx;
    if ( this->IsGravityAddicted() ){
        int tileBelow_x = x / MAXIMIZATION;
        int tileBelow_y = (y+MAXIMIZATION) / MAXIMIZATION;
        if ( tiles.isSolid(tileBelow_y, tileBelow_x) ){
            if ( IsFalling() ){
                SetFalling(false);
                //NotifyStopFalling();
            }
        }
        //gravityaddicted and not over solid terrain
        //and hasnt started falling yet
        else if( !IsFalling() ) {
            SetFalling(true);
            //NotifyStartFalling();
        }
    }
}
Sprite::Sprite (byte _x, byte _y, AnimationFilm* film):
        x(_x), y(_y), actual_x(0),currFilm(film),
        isVisible(true),gravityAddicted(true),isFalling(false)
        { assert( film ); frameNo = currFilm->GetTotalFrames();
            Sprite::SetFrame(0); }
