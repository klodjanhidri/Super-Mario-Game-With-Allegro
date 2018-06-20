#include    "Tiles.hpp"

void Tiles::SetTile     (const Point& at, const Rect& from){
    terrain[at.GetY()][at.GetX()] = from; // [row] [col]
}
Rect Tiles::GetTile     (const Point& from){
    return  terrain[from.GetY()][from.GetX()]; // [row] [col]
}
void Tiles::PutTile     (Bitmap dest, const Point& at, Bitmap tileset, const Rect& tilesetTile){
    al_set_target_bitmap(dest);//we write at the backbuffer of display
    //prints:
    //at destination "dest" at point "at"
    //the part "tilesetTile"(rectangle) of bitmap "tileset"
    //which is the tileset for the game
    al_draw_scaled_bitmap(tileset, tilesetTile.GetX1(), tilesetTile.GetY1(),
                          (tilesetTile.GetX2()-tilesetTile.GetX1()),
                          (tilesetTile.GetY2()-tilesetTile.GetY1()),
                          at.GetX(), at.GetY(), MAXIMIZATION, MAXIMIZATION,
                            0
    );
}
void Tiles::DisplayTerrain(ALLEGRO_DISPLAY* disp){
    assert(al_get_backbuffer(disp));
    int height = 0;
    int width = 0;
    //                         pixels
    if ( (ViewWindow.GetY2()-ViewWindow.GetY1())/TILE_HEIGHT > TERRAIN_MAX_HEIGHT ){
        height = TERRAIN_MAX_HEIGHT;
    }
    else{
        height = (ViewWindow.GetY2()-ViewWindow.GetY1())/TILE_HEIGHT ;
    }
    if ( (ViewWindow.GetX2()-ViewWindow.GetX1())/TILE_WIDTH > TERRAIN_MAX_WIDTH ){
        width = TERRAIN_MAX_WIDTH;
    }
    else{
        width = (ViewWindow.GetX2()-ViewWindow.GetX1())/TILE_WIDTH ;
    }
    //above is in case of going out of terrain space !!!
    for (int row = 0; row < ( height ); ++row)
    {
        for (int col = 0; col < ( width ); ++col)
        {
            Point* p = new Point(displayArea.GetX1()+(col*MAXIMIZATION),
                                displayArea.GetY1()+(row*MAXIMIZATION));
            PutTile(al_get_backbuffer(disp), *p, tileBitmap,
                    terrain[row+ViewWindow.GetY1()][col+(ViewWindow.GetX1()/MAXIMIZATION)]);
        }
    }
    al_flip_display();
}
void    Tiles::CalculateViewDimensions(int dw, int dh, int* vw, int* vh){
    *vw = dw/TILE_WIDTH; *vh = dh/TILE_HEIGHT;
}
void    Tiles::loadBitmap(const std::string& path){
    tileBitmap = al_load_bitmap(path.c_str());
}
void    Tiles::CreateDisplayArea(const int& x1, const int& x2, const int& y1, const int& y2){
    displayArea.SetX1(x1);
    displayArea.SetX2(x2);
    displayArea.SetY1(y1);
    displayArea.SetY2(y2);

}
void    Tiles::CreateViewWindow(const int& x1, const int& x2, const int& y1, const int& y2){
    ViewWindow.SetX1(x1);
    ViewWindow.SetX2(x2); //until
    ViewWindow.SetY1(y1);
    ViewWindow.SetY2(y2); //until the bottom (whole image)
}
int     Tiles::getDisplayAreaWidth(void){
    return displayArea.GetX2()-displayArea.GetX1();
}
int     Tiles::getDisplayAreaHeight(void){
    return displayArea.GetY2()-displayArea.GetY1();
}
Bitmap  Tiles::getTileBitmap(void){
    return tileBitmap;
}
int     Tiles::getViewWindowX1(void){
    return ViewWindow.GetX1();
}
int     Tiles::getViewWindowX2(void){
    return ViewWindow.GetX2();
}
Rect    Tiles::getTerrainTileBitmap(int x, int y){
    return terrain[y][x];
}
///scrolling
void    Tiles::Scroll (HorizScroll h, VertScroll v){
    ViewWindow.SetX1(ViewWindow.GetX1() + (int)h);
    ViewWindow.SetX2(ViewWindow.GetX2() + (int)h);
    ViewWindow.SetY1(ViewWindow.GetY1() + (int)v);
    ViewWindow.SetY2(ViewWindow.GetY2() + (int)v);
}
bool    Tiles::CanScroll (HorizScroll h, int mario_x_pos){
    int oneThird = ( ViewWindow.GetX2()-ViewWindow.GetX1() ) / 3;
    //the one third of viewwindows width, from which if mario is beyond
    //we are allowed to have scrolling
    return  ViewWindow.GetX1() >= -(int) h &&
            mario_x_pos >= oneThird &&
            (int)h + ViewWindow.GetX2() <= (TERRAIN_MAX_WIDTH-16)*MAXIMIZATION;
            // -16 at the end is because we dont want to see the next level
}
bool    Tiles::CanScroll (VertScroll v){
    return  ViewWindow.GetY1() >= -(int) v &&
            ViewWindow.GetY1() + ((int)v) + (ViewWindow.GetY2()-ViewWindow.GetY1())/MAXIMIZATION<= (TERRAIN_MAX_HEIGHT);
}
///solidity
void    Tiles::initSolidity (void){
    for ( int r = 0; r<14; ++r ){
        for ( int c = 0; c<19; ++c ){
            solidity[c][r
            ] = false;
        }
    }
    solidity[0][0] = true; //which tiles are solid
    solidity[0][1] = true; //from the tileset
    solidity[0][2] = true; //tile based coordinates
    solidity[2][3] = true;
    solidity[2][4] = true;
    solidity[3][3] = true;
    solidity[3][4] = true;
    solidity[4][5] = true;
    solidity[4][6] = true;
    solidity[5][5] = true;
    solidity[5][6] = true;
}
bool    Tiles::isSolid (unsigned int row, unsigned int col){
    //extract from terrain coordinates(pixel based coordinates)
    //the tile based coordinates of tilebitmap
    //unsigned int real_row = row % TILE_HEIGHT;
    //unsigned int real_col = col % TILE_WIDTH;
    return solidity[row][col];
}
Tiles::Tiles(void) {};
Tiles::~Tiles(void) {};
