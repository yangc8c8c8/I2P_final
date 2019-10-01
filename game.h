#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "image.h"
#include "font.h"
#include "audio.h"
#include "framework.h"
#include "menu.h"

#define weidth 62
#define hight 47
#define NUM_KEYS1 6
#define NUM_KEYS2 11
#define NUM_TANK 2
#define LIFE 3
#define pwitdth 20
#define phight 16
#define p2off 50
#define stage 5

typedef struct
{
    int x;
    int y;
    int direction;
    int flag;
    int shape[6][6];
    int death;
}tank;

typedef struct
{
    int x;
    int y;
    int direction;
    int party;
    int flag;
}bullet;

struct t_node
{
    int x;
    int y;
    struct t_node* next;
};
typedef struct t_node Node;
Node* ptr;
Node* front=NULL;
Node* rear=NULL;

typedef struct
{
    int x;
    int y;
}vertex;
vertex v;
Audio efx[4];

void walls(void);
void map(char);
void getank(tank *,int,int);
void getank2(tank *,int);
void turn(tank *);
int const check(tank,int);
void sohwtank(tank *,int);
void getboss(tank *);
void turnboss(tank *);
int const checkboss(tank,int);
void sohwboss(tank *);
void boss(tank *,bullet*,int*);
void shoot(bullet *,tank,int,int);
void shootboss(bullet *,tank,int,int);
void flying(bullet *,tank*,int,int);
void enemies(tank *,bullet*,int*,int);
int find_next_step (tank*,int);
void enqueue(int,int);
void dequeue(void);
int isQueueEmpty(void);
void reset(void);
int change_color(tank *,int);
int game1(void);
int game2(void);
void walls1(int,int,int,int);
void walls2(int,int,int,int);
void sohwtank1(tank *,int,int,int,int);
void sohwtank2(tank *,int,int,int,int);
void flying2(bullet *,tank*,int,int,int,int,int,int,int,int,int);
void lifebar1(tank*);
void lifebar2(tank*);
void lifebarb(tank*);


#endif // GAME_H_INCLUDED
