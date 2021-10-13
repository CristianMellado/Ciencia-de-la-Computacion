#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <curses.h> // type conio.h for getch
#include <sys/ioctl.h>
#include <iostream>

int my_kbhit();
char my_getch();