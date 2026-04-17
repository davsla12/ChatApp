#include <ncurses.h>
#include "screen.h"
#include <fstream>
#include <locale>
#include <vector>

int screen_y;
int screen_x;
int iy,ix;
extern int x,y;
int IDs = 1;
std::vector<Scane*> Scanes;
//long long update = 0;

int init_screen(){
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr,true);

    getmaxyx(stdscr,iy,ix);

    setlocale(LC_ALL, "");

    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    init_pair(4,COLOR_BLACK,COLOR_RED);
    init_pair(5,COLOR_BLACK,COLOR_GREEN);

    return 0;
}

void CreateWin(Scane* scane,int rows,int collums,int y,int x){
    scane->window = newwin(rows,collums,y,x);
    scane->rows = rows;
    scane->collums = collums;
    scane->pos_y = y;
    scane->pos_x = x;
}

int GetSizey(int id){
    if(id == 0)return getmaxy(stdscr);
    for (auto &p : Scanes) {
        if(p->ID == id)return getmaxy(p->window);
    }
    return 0;
}

int GetSizex(int id){
    if(id == 0)return getmaxx(stdscr);
    for (auto &p : Scanes) {
        if(p->ID == id)return getmaxx(p->window);
    }
    return 0;
}

int AddScane(Scane* add){
    add->ID = IDs;
    Scanes.push_back(add);
    return IDs++;
}

int RmScane(int ID){
    for (int i = 0;i < Scanes.size();i++){
        if (Scanes[i]->ID == ID){
            Scanes.erase(Scanes.begin()+ID);
            return 0;
        }
    }
    return -1;
}

int SInput(){
    int key = getch();
    for (auto &p : Scanes) {
        if(p->input != NULL)p->input(key);
    }
    return 0;
}

int SMain(){
    for (auto &p : Scanes) {
        if(p->main != NULL)p->main();
    }
    return 0;
}

int update_scr(){
    for (auto &p : Scanes) {
        werase(p->window);
        box(p->window,0,0);
        for (auto* d : p->sprites) {
            wattron(p->window,COLOR_PAIR(d->color_pair));
            mvwprintw(p->window,d->y,d->x*2-1,d->mask.c_str());
            wattroff(p->window,COLOR_PAIR(d->color_pair));
        }
        if(p->render != NULL)p->render();
        wnoutrefresh(p->window);
    }
    doupdate();
    return 0;
}
