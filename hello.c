/**

 To compile and run:
   $ export CC65_HOME=/usr/share/cc65
   $ ca65 crt0.s
   $ ar65 a neo6502.lib crt0.o
   $ cl65 --static-locals -C neo6502.cfg -O --cpu 65c02 -m hello.map \
          -o hello.neo hello.c neo6502.lib
   $ ../../bin/neo hello.neo@800 cold

**/

// CC65 C libs
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


// Character terminal functions
#include "conio.h"

int main()
{
  char c;
  char buffer[256];
  int y=0;
  clrscr();
  cputcxy(52,29,64);
  gotoxy(0 , 22) ;
  puts("                   Hello world!") ;


  for(c=128; c<=143; c++) {
  gotoxy(0,y);
  cputc(c);
  sprintf(buffer,"%d\r",c);
  puts(buffer);
  y++;
  }

  // Wait for keypress
  c = cgetc();

  // End message
  gotoxy(0, 0) ;
  puts("The end");

  return 0 ;
}
