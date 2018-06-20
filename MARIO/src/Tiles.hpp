#ifndef TILES_HPP_INCLUDED
#define TILES_HPP_INCLUDED

#define     SCREEN_WIDTH   800
#define     SCREEN_HEIGHT  600

#define     TILE_WIDTH  16
#define     TILE_HEIGHT 16
#define     MUL_TILE_WIDTH(i)   ((i)<<4)
#define     MUL_TILE_HEIGHT(i)  ((i)<<4)

#define     TERRAIN_MAX_WIDTH   220
#define     TERRAIN_MAX_HEIGHT  15
#define     MAXIMIZATION        40
#define     MOVE_DISTANCE       10

#include    "Rect.hpp"
#include    "Point.hpp"
#include    <allegro5/allegro.h>
#include    <allegro5/allegro_image.h>
#include    <string>
#include    <assert.h>
#include    <iostream>

typedef ALLEGRO_BITMAP* Bitmap;
enum    HorizScroll { LEFT = -MOVE_DISTANCE, HORIZINTACT = 0, RIGHT = +MOVE_DISTANCE };
enum    VertScroll  { UP = -1, VERTINTACT = 0, DOWN = +1 };

class Tiles{
private:
    typedef ALLEGRO_BITMAP* Bitmap;
    typedef Rect    TileMap[TERRAIN_MAX_HEIGHT][TERRAIN_MAX_WIDTH];
    TileMap terrain;        //position of tiles to construcy the map
    Rect    ViewWindow;     //the part of terrain we currently see
                            //(eg the how much of the terrain)
    Rect    displayArea;    //the part of the window we will use to show our game
                            //if it has the same dimensions with allegro display
                            //the we will use the whole window
    Bitmap  tileBitmap;         //the image of all the tiles (tileset)
    bool    solidity[14][19];   //tileBitmap tile size!!
public:
    void    SetTile(const Point& at, const Rect& from);
    Rect    GetTile(const Point& from);
    void    PutTile(Bitmap dest, const Point& at, Bitmap tileset, const Rect& tilesetTile);
    void    DisplayTerrain(ALLEGRO_DISPLAY* disp);
    void    CalculateViewDimensions(int dw, int dh, int* vw, int* vh);
    void    loadBitmap(const std::string& path);
    void    CreateDisplayArea(const int& x1, const int& x2, const int& y1, const int& y2);
    void    CreateViewWindow(const int& x1, const int& x2, const int& y1, const int& y2);
    Bitmap  getTileBitmap(void);
    int     getDisplayAreaWidth(void);
    int     getDisplayAreaHeight(void);
    int     getViewWindowX1(void);
    int     getViewWindowX2(void);
    Rect    getTerrainTileBitmap(int x, int y);
    //scrolling
    void    Scroll (HorizScroll h, VertScroll v);
    bool    CanScroll (HorizScroll h, int mario_x_pos);
    bool    CanScroll (VertScroll v);
    //solidity
    void    initSolidity (void);
    bool    isSolid (unsigned int row, unsigned int col);
    Tiles(void);
    ~Tiles(void);
};
#endif // TILES_HPP_INCLUDED
