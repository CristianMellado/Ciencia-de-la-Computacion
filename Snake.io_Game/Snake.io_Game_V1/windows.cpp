#include "windows.hpp"
static struct termios old, neew; /////para terminos estaticos

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  neew = old; //make new settings same as old settings
  neew.c_lflag &= ~ICANON; //disable buffered i/o
  neew.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &neew); //apply terminal io settings
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char my_getch()
{
  initTermios(0);
  char ch = getchar();
  resetTermios();
  return ch;
}

int my_kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}



