#include <stdio.h>
#include <stdint.h>


// API COMMANDS address
uint8_t* cmd = (uint8_t*)0xFF00;

// API parameters base address (8 bytes)
uint8_t* API_PARAMS = (uint8_t*)0xFF04 ; 

void wait_cmd() {
  while(cmd[0]) {}                // Wait available
}

// Call API command
void call_cmd(int group, int command) {
    cmd[1] = command;                     // Command 
    cmd[0] = group;                       // Group 
}

// Write character to console - (API Group 2, Function 6)
int write(int /* fildes */ , const unsigned char* buf , unsigned count)
{
  while (count--)
  {
    wait_cmd();
    API_PARAMS[0] = *buf++;
    call_cmd(2, 6);
  }

  return 0 ;
}


/****************************************************** 
    Duplicate or similar to CONIO functions
*******************************************************/
 
void cursor(char onoff) {
    // Turning off flashing cursor
}

// Get character from keyboard
int inkey() {
    wait_cmd();
    call_cmd(2,1);                     // Group 2, Command 1
    wait_cmd();
    return API_PARAMS[0];              // Return parameter
}


int cgetc() {
  char ch=0;
  while(ch==0) {
    ch=inkey();
  }
  return ch;
}

 
// Position cursor (API Group 2, Function 7)
void gotoxy(uint8_t sx, uint8_t sy)
{
  API_PARAMS[0] = sx;
  API_PARAMS[1] = sy;
  call_cmd(2,7);
}


// Put a character
void cputc(char ch) {
    wait_cmd();
    API_PARAMS[0] = ch;
    call_cmd(2, 6);
}

// Put a character at screen coord
void cputcxy(int sx, int sy, char ch) {
    gotoxy(sx,sy);
    cputc(ch);
}

// Clear screen
void clrscr() {
    cputc(12);
    gotoxy(0,0);
}
 