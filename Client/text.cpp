#include <ncurses.h>                    /* ncurses.h 已经包含了stdio.h */
#include <string.h>
int main()
{
  char mesg[]="Enter a string: ";     /* 将要被打印的字符串信息*/
  char str[80];
  int row,col;                        /* 存储行号和列号的变量，用于指定光标位置*/
  initscr();/* 进入curses 模式*/
 // box();
 // getmaxyx(stdscr,row,col);           /* 取得stdscr 的行数和列数*/
 // mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
  /* 在屏幕的正中打印字符串mesg */
  getstr(str);                        /* 将指针str 指向读取的字符串*/
 // mvprintw(LINES-2, 0, "You Entered: %s", str);
  getch();
  endwin();
  return 0;

}
