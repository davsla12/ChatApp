#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>
#include <list>

#include"sprites.h"

struct Scane{
    WINDOW* window;
    int rows,collums; //define max size of the window
    int pos_y,pos_x;
    int timer; //how often call main TODO
    std::list<Sprite*> sprites;
    void (*input)(int key); //waits for input from user
    int (*main)();
    void (*render)(); //rendering somethink outside sprites
    int ID = -1;
};

extern int screen_y;
extern int screen_x;

//gives size of scane
//id 0 is main screen
int GetSizey(int id);
int GetSizex(int id);

//add`s scane into scane`s stack
//TODO: RmScane
//\returns scane ID
int AddScane(Scane* add);

//initialized ncurses and sets COLOR_PAIR`s
int screen_init();

//ends ncurses
void screen_delete();

//Create ncurses window
void CreateWin(Scane* scane,int rows,int collums,int y,int x);

//Functions to call Scanes function
int SInput();
int SMain();
int screen_update();
#endif
