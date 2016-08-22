#include "mylibc.h"
#include "nolibc-syscall-linux.h"


char mygetchar(int fd){
  char buf[4];
  read_buffer(fd, buf, 1);
  return buf[0];
}

int myputchar(int fd, char c){
  char buf[] = {c, 0};
  return write(fd, buf, 1);
}

void myprintf(int fd, char* format, ...){
  char* s; int i;
  va_list arg;
  va_start(arg, format);
  for(i=0; i< mystrlen(format); i++){
    if( format[i] == '%' ) 
    switch( format[i+1] ){
      case 'd': 
        write_ulong( fd, va_arg(arg, int) ); i++; break;
      case 's':
        s = va_arg(arg, char*);  
		write_string(fd, s); i++; break;
      case 'c':
        myputchar( fd, va_arg(arg, int) ); i++; break;
    } else myputchar( fd, format[i] );
  }
  va_end(arg);
}

int myclearscreen(int fd){
  return write_cstring(fd, "\033[0m;\033[2J\033[1;1H\033c");
}

int mymovecursor(int fd, int row, int col){
  myprintf(fd, "\033[%d;%dH", row, col); 
  return row+col;
}

int mystrlen(const char *str){
  return nolibc_strlen(str);
}

int mywritebuf(int fd, const char *buf, int count){
  return write_all(fd, buf, count);
}

int mytcgetattr(int fd, struct termios *t){
  return (int)syscall3(__NR_ioctl, fd, TCGETS, t);
}

int mytcsetattr(int fd, int opt, const struct termios *t){
  (void)opt;
  return (int)syscall3(__NR_ioctl, fd, TCSETS, t);
}

int mygetsizeterm(int fd, const struct winsize *ws){
  return (int)syscall3(__NR_ioctl, fd, TIOCGWINSZ, ws);
}

int myfillterm(int fd, int param, int fg, int bg){
  char buf[255*255];
  int i;
  struct winsize sz;
  mygetsizeterm(fd, &sz);
  mymovecursor(fd, 1, 1);
  myprintf(fd, "\033[%d;%d;%dm", param, fg, bg);
  for(i=0; i< sz.ws_row*sz.ws_col; i++) buf[i] = ' ';
  return write_all(fd, buf, sz.ws_row*sz.ws_col);
}

void mysetcolor(int fd, int param, int fg, int bg){
  myprintf(fd, "\033[%d;%d;%dm", param, fg, bg);
}

int myhidecursor(int fd){
  return write_cstring(fd, "\033[?25l");
}

int myshowcursor(int fd){
  return write_cstring(fd, "\033[?25h");
}

long mytime(){
  long t;
  syscall1(__NR_time, &t);
  return t;
}

void myexit(int status){
  nolibc_exit(status);
}

/* Functions, do not used in presentation engine. 
 * Needed to remove compiler warnings */
int myclose(int fd){
  return close(fd);
}

int myopen2(const char *pathname, int flags){
  return open2(pathname, flags);
}

int myexecve(const char *filename, char *const argv[], char *const envp[]){
  return execve(filename, argv, envp);
}

