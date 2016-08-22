#ifndef MYLIBC_H
#define MYLIBC_H

#include <stdarg.h>

#define MY_STD_IN  0
#define MY_STD_OUT 1


#define MY_BLACK 0
#define MY_RED   1
#define MY_GREEN 2
#define MY_BROWN 3
#define MY_BLUE  4
#define MY_PURPLE 5
#define MY_CYAN  6
#define MY_GRAY  7

#define cBLACK "\033[30m"
#define cRED   "\033[31m"
#define cGREEN "\033[32m"
#define cBROWN "\033[33m"
#define cBLUE  "\033[34m"
#define cPURPLE "\033[35m"
#define cCYAN  "\033[36m"
#define cGRAY  "\033[37m"

#define MY_FG 30
#define MY_BG 40

#define MY_DEF 0
#define MY_INTENSE_FG 1
#define MY_INTENSE_BG 5

/* Code highlight colors */
#if defined(MY_CODE_HIGHLIGHT)
	#define CT cBROWN
	#define CI cGRAY
	#define CS cCYAN
	#define CSs CS"\""
	#define CSe "\""CT
	#define CR cRED
	#define CP cGREEN
	#define CC cBLACK
#endif


#define MY_KEY_UP 65
#define MY_KEY_LEFT 68
#define MY_KEY_RIGHT 67
#define MY_KEY_DOWN 66
#define MY_KEY_BACKSPACE 127
#define MY_KEY_PGUP 53
#define MY_KEY_PGDOWN 54
#define MY_KEY_PGADD 126

#include <termios.h>
#include <sys/ioctl.h>

char mygetchar(int fd);
int myputchar(int fd, char c);
int mystrlen(const char *str);
void myprintf(int fd, char* format, ...);
int myclearscreen(int fd);
void myexit(int status);
int mygetsizeterm(int fd, const struct winsize *ws);
int mytcgetattr(int fd, struct termios *t);
int mytcsetattr(int fd, int opt, const struct termios *t);
int mywritebuf(int fd, const char *buf, int count);
int myfillterm(int fd, int param, int fg, int bg);
int mymovecursor(int fd, int row, int col);
void mysetcolor(int fd, int param, int fg, int bg);
int myhidecursor(int fd);
int myshowcursor(int fd);
long mytime();
int myclose(int fd);
int myopen2(const char *pathname, int flags);
int myexecve(const char *filename, char *const argv[], char *const envp[]);


#endif /* MYLIBC_H */
