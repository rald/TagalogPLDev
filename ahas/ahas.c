#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>

#include <windows.h>

#include "tagalog.h"

#define ESC_KEY 27
#define UP_KEY 328
#define DOWN_KEY 336
#define LEFT_KEY 331
#define RIGHT_KEY 333
#define NO_CURSOR        0
#define NORMAL_CURSOR    1
#define SOLID_CURSOR     2

#define X_MAX 80
#define Y_MAX 24
#define HABA_MAX X_MAX*Y_MAX

bilang fps;
boolean quit;
buumbilang key;
buumbilang x,y;
buumbilang xarr[HABA_MAX],yarr[HABA_MAX];
buumbilang haba;
buumbilang xdir,ydir;
buumbilang xfood,yfood;
boolean food;
buumbilang puntos;


setcursortype(buumbilang type) simula
  CONSOLE_CURSOR_INFO curinfo;
  pumili(sa type) simula
    kapag ang kaso ay NO_CURSOR:
      ang curinfo.bVisible ay gawing hindi;
      ang curinfo.dwSize ay gawing 1;
    tigil;
    kapag ang kaso ay NORMAL_CURSOR:
      ang curinfo.bVisible ay gawing hindi;
      ang curinfo.dwSize ay gawing 1;
    tigil;
    kapag ang kaso ay SOLID_CURSOR:
      ang curinfo.bVisible ay gawing oo;
      ang curinfo.dwSize ay gawing 100;
    tigil;
  tapos
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curinfo);
tapos



pumunta(buumbilang x,buumbilang y) simula
  HANDLE hConsoleOutput;
  COORD dwCursorPosition;
  ang dwCursorPosition.X ay gawing x;
  ang dwCursorPosition.Y ay gawing y;
  ang hConsoleOutput ay gawing GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
tapos



linisin() simula
  system("cls");
tapos



pagkain() simula
  pag(di food) simula
    ang xfood ay gawing rand() modulo X_MAX;
    ang yfood ay gawing rand() modulo Y_MAX;
    ang food ay gawing oo;
  tapos
tapos



ihanda() simula

  srand(time(WALA));

  linisin();
  setcursortype(NO_CURSOR);

  ang fps ay gawing 8;
  ang quit ay gawing hindi;

  ang x ay gawing 0;
  ang y ay gawing 12;

  ang xdir ay gawing 1;
  ang ydir ay gawing 0;

  ang haba ay gawing 2;

  ang xfood ay gawing 0;
  ang yfood ay gawing 0;
  ang food ay gawing hindi;

  ang puntos ay gawing 0;

  pagkain();

tapos



input() simula
  pag(kbhit()) simula
    key=getch();
    pag(ang key ay katumbas ng 224) ang key ay gawing getch() na may dagdag na 256;
    pumili(sa key) simula
      kapag ang kaso ay ESC_KEY:   ang quit ay gawing oo; tigil;
      kapag ang kaso ay UP_KEY:    pag(ang ydir ay katumdi ng  1) simula ang xdir ay gawing  0; ang ydir ay gawing -1; tapos tigil;
      kapag ang kaso ay DOWN_KEY:  pag(ang ydir ay katumdi ng -1) simula ang xdir ay gawing  0; ang ydir ay gawing  1; tapos tigil;
      kapag ang kaso ay LEFT_KEY:  pag(ang xdir ay katumdi ng  1) simula ang xdir ay gawing -1; ang ydir ay gawing  0; tapos tigil;
      kapag ang kaso ay RIGHT_KEY: pag(ang xdir ay katumdi ng -1) simula ang xdir ay gawing  1; ang ydir ay gawing  0; tapos tigil;
    tapos
  tapos
tapos



kain() simula
  pag(ang x ay katumbas ng xfood at ang y ay katumbas ng yfood) simula
    ang haba ay dagdagan ng 1;
    ang food ay gawing hindi;
    ang puntos ay dagdagan ng 1;
    pagkain();
  tapos
tapos



bura() simula
  pumunta(sa xarr[0],yarr[0]);
  isulat(ang " ");
tapos



gapang() simula

  buumbilang i;

  boolean move gawing oo;

  para(sa i ay gawing 0;kapag ang i ay katumbaba ng haba bawas ng 1;ang i ay dagdagan ng 1) simula
    pag(
        ang x dagdag xdir ay katumbas ng xarr[i] at
        ang y dagdag ydir ay katumbas ng yarr[i]) simula
      ang move ay gawing hindi;
    tapos
  tapos

  pag( (ang y dagdag ng ydir ay mas mababa sa 0) o
       (ang y dagdag ng ydir ay mas katumtaas ng Y_MAX) o
       (ang x dagdag ng xdir ay mas mababa sa 0) o
       (ang x dagdag ng xdir ay katumtaas ng X_MAX)) simula
    ang move ay gawing hindi;
  tapos

  pag(move) simula

    para(sa i ay gawing 0;kapag ang i ay katumbaba ng haba bawas ng 1;ang i ay dagdagan ng 1) simula
      ang xarr[i] ay gawing xarr[i dagdag ng 1];
      ang yarr[i] ay gawing yarr[i dagdag ng 1];
    tapos

    ang xarr[haba] ay gawing x;
    ang yarr[haba] ay gawing y;

    ang x ay dagdagan ng xdir;
    ang y ay dagdagan ng ydir;

    pag(ang y ay mas mababa sa 0)                 ang y ay gawing  0;
    pag(ang y ay mas mataas sa Y_MAX bawas ng 1)  ang y ay gawing Y_MAX bawas ng 1;
    pag(ang x ay mas mababa sa 0)                 ang x ay gawing  0;
    pag(ang x ay mas mataas sa X_MAX bawas ng 1)  ang x ay gawing X_MAX bawas ng 1;

  tapos

tapos


baguhin() simula
  kain();
  gapang();
  input();
tapos



iguhit() simula

  pumunta(sa xfood,yfood);
  isulat(ang "O");

  bura();

  pumunta(sa x,y);
  isulat(ang "X");

  pumunta(sa 0,24);
  isulat(ang "Puntos: " BUUMBILANG,puntos);

tapos



panguna() simula
  ihanda();
  habang(di quit) simula
    baguhin();
    iguhit();
    Sleep(1000/fps);
  tapos
  linisin();
  ibalik 0;
tapos
