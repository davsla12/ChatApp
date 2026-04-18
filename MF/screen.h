#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>
#include <list>

#include"sprites.h"

struct Scane{
    WINDOW* window;
    int rows,collums; //define max size of the window
    int pos_y,pos_x;
    int timer; //how often call main
    std::list<Sprite*> sprites;
    void (*input)(int key); //waits for input from user
    int (*main)();
    void (*render)(); //rendering somethink outside sprites
    int ID = 0;
};

extern int screen_y;
extern int screen_x;

int GetSizey(int id);
int GetSizex(int id);
int AddScane(Scane* add);
int screen_init();
void screen_delete();
void CreateWin(Scane* scane,int rows,int collums,int y,int x);
int SInput();
int SMain();
int screen_update();
#endif
