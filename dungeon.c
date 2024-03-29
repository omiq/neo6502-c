// CC65 C libs
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Character terminal functions
#include "conio.h"

 
// Global key variable
bool run=true;
bool in_play=false;
bool obstruction=false;
unsigned int timer,delay;
unsigned int key,i,c,ex,ey,ax,ay;
unsigned char x=19;
unsigned char y=8;
unsigned char old_x, old_y, direction_x, direction_y, fx, fy;
unsigned char room=0;
unsigned char max_rooms=2;
unsigned char buffer [sizeof(int)*40+1];

// Player 
unsigned char keys,idols,potion=0;
int health=100;
int magic=0;
unsigned int score=0;
bool sword = false;

// Enemy
unsigned int enemy_count=0;
struct enemy {
    unsigned char tile;
    unsigned char room;
    unsigned char x;
    unsigned char y;
    unsigned char old_x;
    unsigned char old_y;
    char health;
    unsigned char strength;
    unsigned char speed;
    unsigned char armour;
};
unsigned int this_enemy = 0;

struct enemy enemies[1000];
unsigned char rooms[] = {

// Room 1
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 75, 32, 38, 32, 38, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 124, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 64, 32, 32, 42, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 38, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 88, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 43, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 35, 35, 35, 35, 45, 35, 35, 35, 35, 35, 35, 35, 35, 35, 32, 32, 32, 32, 32, 43, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 36, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 75, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 43, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 75, 32, 32, 32, 32, 32, 124, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 33, 32, 88, 32, 32, 32, 32, 124, 32, 32, 32, 32, 38, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 94, 32, 32, 32, 32, 35, 32, 32, 94, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 36, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 35, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,

// room 2
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 35, 35, 35, 35, 35, 35, 35, 35, 61, 61, 61, 61, 35, 35, 35, 35, 35, 35, 35, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 61, 32, 32, 32, 32, 32, 32, 32, 61, 61, 61, 61, 32, 32, 32, 32, 32, 32, 32, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 61, 32, 32, 32, 32, 32, 32, 32, 61, 61, 61, 61, 32, 32, 32, 32, 32, 32, 32, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 61, 32, 32, 32, 32, 32, 32, 32, 61, 61, 61, 61, 32, 32, 32, 32, 32, 32, 32, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 35, 61, 61, 61, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 61, 32, 32, 36, 32, 94, 94, 94, 94, 94, 94, 94, 94, 94, 32, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 35, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 88, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 38, 32, 32, 36, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 43, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 43, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 38, 32, 32, 36, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 88, 32, 32, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 32, 32, 32, 32, 32, 32, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 32, 32, 36, 32, 94, 94, 94, 94, 94, 94, 94, 94, 94, 32, 32, 32, 32, 32, 61,
 35, 61, 61, 61, 61, 32, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61,
 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 32, 32, 32, 32, 32, 32, 32, 61, 61, 61, 61, 32, 32, 32, 32, 32, 32, 32, 61,
 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61,
 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61,
 
 
 // room 3 
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 111, 111, 111, 111, 32, 111, 111, 111, 111, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 111, 111, 32, 32, 111, 111, 111, 111, 32, 32, 32, 32, 111, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 111, 111, 32, 32, 32, 32, 32, 32,
 32, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32, 32, 32, 32, 32, 88, 43, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 32, 32, 32, 32, 32,
 32, 111, 32, 32, 32, 88, 32, 32, 32, 32, 32, 32, 32, 32, 32, 124, 32, 32, 32, 32, 32, 32, 32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 111, 32, 111, 32, 32, 32, 32, 32,
 32, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 38, 32, 111, 111, 32, 32, 38, 32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 111, 111, 32, 111, 111, 32, 32, 32, 32,
 32, 111, 32, 43, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 111, 32, 32, 32, 111, 32, 32, 32, 32,
 32, 111, 32, 32, 32, 32, 32, 32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 111, 32, 32, 32, 32, 32, 111, 111, 32, 32, 32,
 32, 111, 111, 32, 32, 32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32, 32, 32, 32, 32, 111, 45, 111, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32, 32,
 32, 32, 111, 32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 32, 32, 32, 32, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32,
 32, 32, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 32, 111, 111, 32, 32, 32, 94, 94, 94, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32,
 32, 32, 32, 111, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 111, 32, 32, 94, 94, 94, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32,
 32, 32, 32, 32, 32, 111, 111, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 124, 32, 32, 32, 94, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 111, 111, 111, 111, 111, 111, 32, 32, 32, 32, 32, 111, 32, 32, 94, 32, 32, 32, 32, 32, 32, 64, 32, 32, 32, 32, 32, 111, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 111, 111, 111, 111, 111, 111, 32, 94, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 111, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 111, 111, 32, 32, 32, 32, 32, 111, 111, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 111, 111, 111, 111, 111, 111, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32

};

unsigned char game_map[1000];

unsigned int map(char x, char y) {
    
    unsigned char c;

    c = game_map[40*y+x];

    return c;
}

void load_room() {
    int pos;

    clrscr();
    gotoxy(0,0);
    sprintf(buffer,"loading room %d",room+1); puts(buffer);
    cputc(141);
    for (pos = 0; pos < 1000; pos++) {   

        c=rooms[pos+(1000*room)];

        // Player x and y
        if(c==64) {
            y=pos/40;
            x=pos % 40;
        }

        // Goblin
        if(c==38) {

            // Increment for next enemy (Enemy 0 is counted as no enemy)
            enemy_count+=1;

            // Create the enemy in the list
            enemies[enemy_count].tile = c;
            enemies[enemy_count].room = room;
            enemies[enemy_count].x = pos % 40;
            enemies[enemy_count].y = pos/40;
            enemies[enemy_count].old_x = enemies[enemy_count].x;
            enemies[enemy_count].old_y = enemies[enemy_count].y;
            enemies[enemy_count].health = 25;
            enemies[enemy_count].strength = 5;
            enemies[enemy_count].speed = 1;
            enemies[enemy_count].armour = 10;

        }  

        // Rat
        else if (c==94) {

            // Increment for next enemy (Enemy 0 is counted as no enemy)
            enemy_count+=1;

            // Create the enemy in the list
            enemies[enemy_count].tile = c;
            enemies[enemy_count].room = room;
            enemies[enemy_count].x = pos % 40;
            enemies[enemy_count].y = pos/40;
            enemies[enemy_count].old_x = enemies[enemy_count].x;
            enemies[enemy_count].old_y = enemies[enemy_count].y;
            enemies[enemy_count].health = 10;
            enemies[enemy_count].strength = 5;
            enemies[enemy_count].speed = 2;
            enemies[enemy_count].armour = 0;

        }  

        game_map[pos] = c;     
    }
    
 
}

void set_map(char x, char y, int tile) {
    
    // Set the part of the array to the given tile
    game_map[40*y+x]=tile;
    
}



unsigned int nop_delay(unsigned int delay) {
    for(timer=0; timer<delay*7; timer++) {
        __asm__ ("NOP");
    }
    return timer;
}

// Returns the enemy for a given x,y coord
unsigned int which_enemy(unsigned char ex, unsigned char ey) {

    if(map(ex,ey)==32) return 0;

    // Enemies starts at 1, 0 = no enemy
    for(i=1;i<enemy_count+1;i++)
    {
        if(enemies[i].x == ex && enemies[i].y == ey && enemies[i].health >= 1) return i;
       
    }

    // No enemies
    return 0;

}


void attack(int weapon, unsigned char ax, unsigned char ay)
{
    int rnum = 20;
    this_enemy = 0;
    this_enemy = which_enemy(ax,ay);

    if(this_enemy == 0) {
        return;
    } 

    rnum = rand() % 20; 
    // gotoxy(2,2);
    // sprintf(buffer,"dice roll %d",rnum);
    // puts(buffer);

    if(rnum > enemies[this_enemy].armour+enemies[this_enemy].speed) {

        // Damage!
        enemies[this_enemy].health-=weapon;
        if(enemies[this_enemy].health>0) 
        {
            gotoxy(0,0);
            sprintf(buffer,"hit!! enemy health: %3d    ", enemies[this_enemy].health); 
            puts(buffer);
            timer=nop_delay(1000);
        }


        
    } else {
        gotoxy(0,0);
        sprintf(buffer,"miss! enemy health: %3d    ", enemies[this_enemy].health); 
        puts(buffer);
        if((x == ax && y == ay)||(x == ax && (y == ay + 1 || y == ay - 1)) || (y == ay && (x == ax + 1 || x == ax - 1))) 
        {
            health -= enemies[this_enemy].strength;
        }
        timer=nop_delay(1000);
    }

    if(enemies[this_enemy].health < 1 ) {

        // Success!
        gotoxy(0,0);
        puts("enemy defeated!                      ");
        
        // Draw tile in new location
        cputcxy(ax,ay,32); 
        set_map(ax,ay,32);
        enemies[this_enemy].tile = 32;

        // Up the score
        score+=10;
        timer=nop_delay(1000);
    }

}

void enemy_attack(unsigned int this_enemy)
{
    int rnum = 0;
    //rnum = (rand() % 20); 

    if(rnum > 15) {

        // Damage!
        if(health < 1 || (health-enemies[this_enemy].strength) < 1) 
        {
            health = 0;

        } else {
            health-=enemies[this_enemy].strength;
        }    
        gotoxy(0,0);
        sprintf(buffer,"ouch! health: %3d        ", health); puts(buffer);
        timer=nop_delay(1000);

        
    } else {
            enemies[this_enemy].health -= 5;
            if(enemies[this_enemy].health<1) {
               enemies[this_enemy].health=0;
                // Draw tile in new location
                cputcxy(enemies[this_enemy].x,enemies[this_enemy].y,32); 
                set_map(enemies[this_enemy].x,enemies[this_enemy].y,32);
                enemies[this_enemy].tile = 32;
                gotoxy(0,0);
                puts("enemy defeated!            ");
                
            }else {
                gotoxy(0,0);
                sprintf(buffer,"block! health: %3d      ", health); puts(buffer);}
        }
        
        timer=nop_delay(1000);
    

    if(health < 1) {

        // Fail!
        gotoxy(0,0);
        puts("enemy defeated you!                  ");
        health = 0;
        timer=nop_delay(1000);
    }

}


// Move the enemies for a given room
void move_enemies() {

    unsigned char rnd;
    cputc(143);
    // Enemies starts at 1, 0 = no enemy
    for(i=1;i<enemy_count+1;i++)
    {
        if(enemies[i].room == room && enemies[i].health>0){
            
            enemies[i].old_x = enemies[i].x;
            enemies[i].old_y = enemies[i].y; 
            
            // Rat is random
            if(enemies[i].tile == 94) {
                rnd = (rand() % (4)) + 1; 
                if(rnd == 4) enemies[i].x-=1;
                if(rnd == 2) enemies[i].x+=1;
                if(rnd == 1) enemies[i].y-=1;
                if(rnd == 3) enemies[i].y+=1;
            }

            // Gobbo goes for player
            if(enemies[i].tile == 38) {
                if(enemies[i].x > x) enemies[i].x-=1;
                if(enemies[i].x < x) enemies[i].x+=1;
                if(enemies[i].y > y) enemies[i].y-=1;
                if(enemies[i].y < y) enemies[i].y+=1;
            }

            // Redraw
            c=map(enemies[i].x,enemies[i].y);
            if(c!=32) {
                enemies[i].x = enemies[i].old_x;
                enemies[i].y = enemies[i].old_y;
                if(c==64) enemy_attack(i);
            }else{
                set_map(enemies[i].old_x, enemies[i].old_y, 32);
                cputcxy(enemies[i].old_x, enemies[i].old_y, 32);
            }
            set_map(enemies[i].x, enemies[i].y, enemies[i].tile);
            cputcxy(enemies[i].x, enemies[i].y,enemies[i].tile);
            
        }
    }

}

void draw_screen() {

    int row,col;
    for(row=0; row<25; row++)
    {
        for(col=0; col < 40; col++){
            cputcxy(col,row,map(col,row));
        }
    };

}



void draw_momentary_object(unsigned char obj_old_x, unsigned char obj_old_y, unsigned char obj_x, unsigned char obj_y, unsigned char obj_tile, unsigned int delay) {

    cputc(143);

    // Replace tile
    cputcxy(obj_old_x,obj_old_y,map(obj_old_x,obj_old_y));

    // Draw tile in new location
    cputcxy(obj_x,obj_y,obj_tile); 

    // Delay
    timer=nop_delay(delay);

    // Replace tile again
    cputcxy(obj_x,obj_y,map(obj_x,obj_y));
    
}


void draw_move(bool replace) {

    // Delete the player character
    if(!replace) {
        set_map(old_x, old_y, 32);
    }

    // Draw new location
    cputc(143);
    cputcxy(old_x,old_y,map(old_x,old_y));
    cputcxy(x, y, 64); 
    set_map(x, y, 64);
}


void title_screen() {

    clrscr();
    cputcxy(10,10,32);
    gotoxy(18,9);
    cputc(134);
    puts("Neo6502 DUNGEON\n");
    timer=nop_delay(5000);
    gotoxy(15,10);
    cputc(143);
    puts("by RetroGameCoders.com");
    gotoxy(20,14);
    cputc(140);
    puts("Press a key");
    gotoxy(21,15);
    key=cgetc();
    puts("Get ready!");
    timer=nop_delay(5000);
    in_play=true;
    clrscr();
}


bool game_over() {
    clrscr();
    gotoxy(20,2);
    puts("GAME OVER");
    timer=nop_delay(500);
    gotoxy(0,5);
    puts("ah, such a shame,");
    gotoxy(0,7);
    puts("you were doing so well!");
    timer=nop_delay(1000);
    gotoxy(0,9);
    sprintf(buffer,"score:%03d",score);
    puts(buffer);
    gotoxy(0,15);
    puts("play again (y/n)?");
    key=cgetc();
    in_play=false;
    if(key=='n') {
        return false;
    } else {
        return true;
    }
}

void game_loop() {

    gotoxy(0,24);
    cputc(139);
    sprintf(buffer," K: %02d H: %03d *: %03d score: %04d", keys, health, magic, score); 
    puts(buffer);

    // Change direction
    if(x != old_x || y != old_y) {
        direction_x = x-old_x;
        direction_y = y-old_y;
    }


    move_enemies();

    // Backup the location
    old_x = x;
    old_y = y;

        
        // Check keys;
        switch (key=cgetc()) 
        { 

            case 'w':
                if(y>0) y--; 
                break; 
            case 'a': 
                if(x>0) x--; 
                break; 
            case 'A': 
            case 'o':
                if(sword==true) {
                    draw_momentary_object(x-1,y,x-1,y,45,2000); 
                    attack(10,x-1,y);
                }
                break;     
            case 's': 
                if(y<24) y++; 
                break; 
            case 'd': 
                if(x<39) x++; 
                break; 
            case 'D': 
            case 'p':
                if(sword==true) {
                    draw_momentary_object(x+1,y,x+1,y,45,2000); 
                    attack(10,x+1,y);
                }
                break; 
            case 'f': 

                if(magic > 5) {

                    magic-=5;
                    fx = x+direction_x;
                    fy = y+direction_y;  

                    c=map(fx,fy);
                    while(c==32 && magic > 0) {             
                        draw_momentary_object(fx,fy,fx,fy,42,200); 
                        magic-=1;
                        fx = fx+direction_x;
                        fy = fy+direction_y;  
                        c=map(fx,fy);
                    }

                    attack(10,fx,fy);

                }

                break;            
            case 'Q':
            case 3:
                in_play = false;
                break;
            default:
                // Figure out scan codes 
                //gotoxy(0,0);
                //puts(printf("%d",key); puts(buffer);
                break; 
        }
    //} Remove comment to make more action than turn-based

    gotoxy(0,0);
    puts("                              ");


    // Anything in our path?
    obstruction=false;
    c=map(x,y);
    
    // Collision
    switch (c)
    {
        case 35:
            // Wall               
            obstruction=true;
            break;
        
        case 75: // Key +1
            keys+=1;
            break;

        case 124:
        case 45:
            if(keys>0)
            {
                keys-=1;
                score+=5;
                obstruction=false;

            }else{

                // Not enough keys to unlock!
                set_map(x, y, 47); // turn into partially open
                health-=10; // lose 10 health
                obstruction=true;
            }
            break;

        case 47: // Partially open door

            if(keys>0)
            {
                keys-=1;
                score+=5;
                obstruction=false;

            }else{
                // Not enough keys to unlock!
                set_map(x, y, 32);  // turn into fully open
                health-=10;         // lose 10 health
                obstruction=true;
            }
            break;

        case 33: // Sword!
            sword=true;
            break;

        case 36: // Cash money
            score+=5;
            break;

        case 42:
            score+=15;
            magic+=100;
            break;

        case 43: // Health
            health=100;
            break;


/* Enemies >> */

        case 38: // Gobbo
            attack(5,x,y);
            obstruction=true;
            break;

        case 94: // Rats
            attack(5,x,y);
            obstruction=true;
            break;

/* ^^ Enemies */

        case 88: // Idol
            score+=10;
            idols+=1;
            if(idols==2) {
                room+=1;
                if(room > max_rooms) room=0;
                load_room();
                draw_screen();
                idols=0;
            }
            break;

        case 64: // Player
            break;
        
        default:
            
            // convert integer to ascii: itoa(c,buffer,10);
            
            if(c!=32) {
                
                // Figure out what the code is for tile
                gotoxy(0,0);
                sprintf(buffer,"bumped into ...... %03d",c); puts(buffer);
                obstruction=true;
            }
            
            break;
    }

    // If obstructed then bounce
    if(obstruction) {
        x=old_x;
        y=old_y;
    } else {
        draw_move(false);
    }

    if(health<1) {
        in_play = false;
    }

    
    
}


int main() {

    // Use current time as 
    // seed for random generator 
    srand(1); 

    /* Clear Screen */
    clrscr();

    /* Hide cursor */
    cursor(0);

    // Titles
    title_screen();

    // Start running     
    run=true;
        
    // Should the program end?
    while(run){

        // Initialize if not already running a game
        if (in_play != true) {
            keys=0;
            health=100;
            score=0;
            keys=0;
            room=0;
            potion=0;
            magic=0;
            enemy_count=0;
            sword=false;
        }

        // Set up the screen
        load_room();
        draw_screen();
        cputc(129);
        cputcxy(x,y,64);
        nop_delay(500);
        cputc(136);
        cputcxy(x,y,64);
        nop_delay(500);
        cputc(129);
        cputcxy(x,y,64);
        nop_delay(500);
        cputc(136);
        cputcxy(x,y,64);
        nop_delay(500);
        cputc(135);
        cputcxy(x,y,64);

        // Game on!
        in_play = true;

        /* Loop until game ends */
        while (in_play)
        {
            game_loop();
        }

        // Try again or quit?
        run=game_over();

    }
    clrscr();
    puts("goodbye!\n\n");
    cursor(1);
    return(0);
}