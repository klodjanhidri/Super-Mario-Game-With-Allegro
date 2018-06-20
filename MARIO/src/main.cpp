#include    "Tiles.hpp"
#include    "AnimationFilmHolder.hpp"
#include    "Sprite.hpp"
#include    <allegro5/allegro_native_dialog.h>

enum    KEYS {Z=2, S=3};

int main (void)
{
    /////////////////////////////
    ///global vars
    /////////////////////////////
    Tiles                   tiles;
    ALLEGRO_DISPLAY*        display = NULL;
    ALLEGRO_EVENT_QUEUE*    event_queue = NULL;
    ALLEGRO_EVENT           event;
    ALLEGRO_TIMER*          timer = NULL;
    std::string             fileContent = "";
    std::ifstream           fileReader;
    int                     x_coordinate;   //the position of terrain array where to put tile
    int                     y_coordinate;
    int                     x2_coordinate;
    int                     y2_coordinate;
    Point*                  coordinates = new Point();
    Rect*                   tilesetCoordinates = new Rect();
    int*                    viewWidth  = (int*) 0;
    int*                    viewHeight = (int*) 0; //parameters of view window
    bool                    exitGame = false;
    HorizScroll             scroll_h = HORIZINTACT;
    VertScroll              scroll_w = VERTINTACT;
    bool                    keys[6] = {false, false, false, false, false, false};
    bool                    render = false;
    int                     tlspxls = 2; // to scrolling distance se pixels tis eionas tou tile
                                        //dioti to tile emfanizetai 40x40 alla i eikona einai 16x16

    /////////////////////////////
    ///allegro inits
    /////////////////////////////
    if ( !al_init() ){
        std::cout << "Allegro could not be initialized :(" << std::endl;
        return -1;
    }
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if ( !display ){
        std::cout << "Allegro display could not be created :(" << std::endl;
        return -1;
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    if ( !al_init_native_dialog_addon() ){
        std::cout << "Allegro dijnative dialog could not be initialized :(" << std::endl;
        al_destroy_display(display);
        return -1;
    }
    if ( !al_init_image_addon() ){
        al_show_native_message_box(display, "WARNING", "CAUTION",
                                   "Image addon could not be initialized :(",
                                   NULL, 0);
        al_destroy_display(display);
        return -1;
    }
    event_queue = al_create_event_queue();
    if ( !event_queue ){
        al_show_native_message_box(display, "WARNING", "CAUTION",
                                   "Event Queue could not be initialized :(",
                                   NULL, 0);
        al_destroy_display(display);
        return -1;
    }
    if( !al_install_keyboard() ) ///setup the keyboard
    {
        al_show_native_message_box(display, "WARNING", "CAUTION",
                                   "Could'nt install keyboard :(",
                                   NULL, 0);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return -1;
    }
    timer = al_create_timer(1.0 / 60);
    if( !timer )
    {
        al_show_native_message_box(display, "WARNING", "CAUTION",
                                   "Could'nt install timer :(",
                                   NULL, 0);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return -1;
    }

    ///////////////////////////
    ///terrain construction
    ///////////////////////////
    fileReader.open("data/map");
    if ( fileReader.fail() ){
        al_show_native_message_box(display, "WARNING", "CAUTION",
                                   "File of the map is not readable :(",
                                   NULL, 0);
        al_destroy_display(display);
        return -1;
    }
    for ( int i=0; i < TERRAIN_MAX_HEIGHT; ++i  )
    {
       for ( int j=0; j < TERRAIN_MAX_WIDTH; ++j)
       {
            getline(fileReader, fileContent);
            sscanf (fileContent.c_str(), "%u  %u", &y_coordinate, &x_coordinate);
            coordinates->SetY(i);
            coordinates->SetX(j);

            tilesetCoordinates->SetX1(x_coordinate*TILE_WIDTH);
            x2_coordinate = tilesetCoordinates->GetX1() + TILE_WIDTH;
            tilesetCoordinates->SetX2(x2_coordinate);

            tilesetCoordinates->SetY1(y_coordinate*TILE_HEIGHT);
            y2_coordinate = tilesetCoordinates->GetY1() + TILE_HEIGHT;
            tilesetCoordinates->SetY2(y2_coordinate);
            tiles.SetTile(*coordinates, *tilesetCoordinates);
       }
    }

    /////////////////////////////////////////////////////////
    ///image loading and constructing the display attributes
    /////////////////////////////////////////////////////////
    tiles.initSolidity();
    tiles.loadBitmap("data/tileset.png");
    if ( !(tiles.getTileBitmap()) ){
        al_show_native_message_box(display, "WARNING", "CAUTION",
                                   "Bitmap of tileset could not be loaded :(",
                                   NULL, 0);
        return -1;
    }
    tiles.CreateDisplayArea(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT); //we use the whole window
    viewHeight = new int[1];
    viewWidth  = new int[1];
    if ( !viewHeight || !viewWidth ){
        al_show_native_message_box(display, "WARNING", "CAUTION",
                                   "Couldn't allocate memory for viewHeight nad viewWidth :(",
                                   NULL, 0);
        return -1;
    }
    //normally (tiles.displayArea.GetX2()-tiles.displayArea.GetX1(),
    //tiles.displayArea.GetY2()-tiles.displayArea.GetY1(), ..., ...);
    tiles.CalculateViewDimensions(SCREEN_WIDTH, SCREEN_HEIGHT, viewWidth, viewHeight);
    tiles.CreateViewWindow(0, ((*viewWidth)*TILE_WIDTH), 0, ((*viewHeight)*TILE_HEIGHT));

    ///////////////////////////////
    ///printing the origin terrain
    ///////////////////////////////
    tiles.DisplayTerrain(display);

    ///////////////////////////////
    ///Animation films and Sprites
    //////////////////////////////
    AnimationFilmHolder     filmHolder = AnimationFilmHolder::Get();
    filmHolder.Load("data/films_config");
                            /// MARIO
    Sprite*     mario = new Sprite( 0, 480, filmHolder.GetFilm("mario_walking_small") );
    al_convert_mask_to_alpha( mario->GetFilm()->GetBitmap(), al_map_rgb(0, 0, 0) );
    mario->SetFrame(4);
    Point* at = new Point( mario->GetXPos(),mario->GetYPos() );
    mario->GetFilm()->DisplayFrame( al_get_backbuffer(display),*at, mario->GetFrame() );
    int marioFrameChange = 0;

    ///////////////////////////////////////
    /// game loop (scrolling, eventqueue)
    ///////////////////////////////////////
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_start_timer(timer);
    while ( !exitGame ){
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER)
		{
            render = true;
		}
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			exitGame = true;
		}
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
			{
                case ALLEGRO_KEY_ESCAPE:
                    exitGame = true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_S:
                    keys[S] = true;
                    break;
                case ALLEGRO_KEY_Z:
                    keys[Z] = true;
                    break;
			}
        }
        if(event.type == ALLEGRO_EVENT_KEY_UP)
        {
             switch(event.keyboard.keycode)
			{
                case ALLEGRO_KEY_ESCAPE:
                    exitGame = true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    mario->SetFrame(3);
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    mario->SetFrame(4);
                    break;
                case ALLEGRO_KEY_S:
                    keys[S] = false;
                    break;
                case ALLEGRO_KEY_Z:
                    keys[Z] = false;
                    break;
			}
        }

        if ( al_is_event_queue_empty(event_queue) && render){
            render = false;
            if ( keys[RIGHT] ){
                if ( mario->GetFrame()==4 || mario->GetFrame()==3)
                    mario->SetFrame(5);
                else if ( mario->GetFrame()==0){
                    mario->SetFrame(5);
                    marioFrameChange = 0;
                }
                else if ( mario->GetFrame()==1 || mario->GetFrame()==2)
                    mario->SetFrame(0);
                else if ( mario->GetFrame() == 5 ){
                    if ( marioFrameChange<2 )
                        ++marioFrameChange;
                    else{
                        mario->SetFrame(6);
                        marioFrameChange = 0;
                    }
                }
                else if ( mario->GetFrame() == 6 ){
                    if ( marioFrameChange<2 )
                        ++marioFrameChange;
                    else{
                        mario->SetFrame(5);
                        marioFrameChange = 0;
                    }
                }
                scroll_h = RIGHT;
                int dx = MOVE_DISTANCE;
                int dy = 0;
                mario->Move( dx, dy, tiles );
                if ( tiles.CanScroll(scroll_h, mario->GetXPos()+40) ){
                    tiles.Scroll(scroll_h, scroll_w);
                    tiles.DisplayTerrain(display);
                    tlspxls += 2;
                    mario->ChangeXPos(-dx);
                    at->SetX( mario->GetXPos() );
                    at->SetY( mario->GetYPos() );
                    mario->GetFilm()->DisplayFrame( al_get_backbuffer(display),
                                                  *at, mario->GetFrame() );
                    scroll_h = HORIZINTACT;
                }
                else{
                    tiles.DisplayTerrain(display);
                    at->SetX( mario->GetXPos() );
                    at->SetY( mario->GetYPos() );
                    mario->GetFilm()->DisplayFrame( al_get_backbuffer(display),
                                                  *at, mario->GetFrame() );
                }
            }//end of RIGHT
            if ( keys[LEFT] ){
                if ( mario->GetFrame()==3 || mario->GetFrame()==4)
                    mario->SetFrame(2);
                else if ( mario->GetFrame()==7){
                    mario->SetFrame(2);
                    marioFrameChange = 0;
                }
                else if ( mario->GetFrame()==5 || mario->GetFrame()==6)
                    mario->SetFrame(7);
                else if ( mario->GetFrame() == 2 ){
                    if ( marioFrameChange<2 )
                        ++marioFrameChange;
                    else{
                        mario->SetFrame(1);
                        marioFrameChange = 0;
                    }
                }
                else if ( mario->GetFrame() == 1 ){
                    if ( marioFrameChange<2 )
                        ++marioFrameChange;
                    else{
                        mario->SetFrame(2);
                        marioFrameChange = 0;
                    }
                }
                int dx = -MOVE_DISTANCE;
                int dy = 0;
                mario->Move( dx, dy, tiles );
                tiles.DisplayTerrain(display);
                at->SetX( mario->GetXPos() );
                at->SetY( mario->GetYPos() );
                mario->GetFilm()->DisplayFrame( al_get_backbuffer(display),
                                                  *at, mario->GetFrame() );
            } //end of LEFT
            else{
                at->SetX( mario->GetXPos() );
                at->SetY( mario->GetYPos() );
                mario->GetFilm()->DisplayFrame( al_get_backbuffer(display),
                                                  *at, mario->GetFrame() );
            }
        }// end of if
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    return 0;
}
