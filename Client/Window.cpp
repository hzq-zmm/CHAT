#include"Window.hpp"
#include<unistd.h>
using namespace std;
MyWindow::MyWindow()
{
  initscr();
  curs_set(0);
}

MyWindow::~MyWindow()
{
  delwin(header);
  delwin(output);
  delwin(friendlist);
  delwin(input);
  endwin();
}

void MyWindow::createHeader()
{
  int y=0;
  int x=0;
  int h=LINES/5;
  int w=COLS;
  header=createNewWin(h,w,y,x);
}

void MyWindow::createOutput()
{
  int y=LINES/5;
  int x=0;
  int h=LINES*3/5;
  int w=COLS*2/3;
  output=createNewWin(h,w,y,x);
}

void MyWindow::createFriendList()
{
  int y=LINES/5;
  int x=COLS*2/3;
  int h=LINES*3/5;
  int w=COLS*1/5;
  friendlist=createNewWin(h,w,y,x);
}

void MyWindow::createInput()
{
 int y=LINES*4/5;
 int x=0;
 int h=LINES/5;
 int w=COLS;
 input=createNewWin(h,w,y,x);
}

void MyWindow::myWinRefresh(WINDOW *win) //刷新窗口
{
  wrefresh(win);
}

WINDOW *MyWindow::createNewWin(int h,int w,int startY,int startX)
{
  WINDOW *local=newwin(h,w,startY,startX);
  box(local,0,0);
  return local;
}

void MyWindow::putStrToWin(WINDOW *win,int startY,int startX,const std::string &msg) //向窗口中写数据
{
  mvwaddstr(win,startY,startX,msg.c_str());
}

void MyWindow::clearWinLine(WINDOW *win,int begin,int line)//清除窗口从bengin开始的line行
{
  while(line-->0)
  {
    wmove(win,begin++,0);
    wclrtoeol(win);
  }
}
std::string MyWindow::getWinStr(WINDOW* win)
{
  char buf[1024]={0};
  wgetnstr(win,buf,sizeof(buf));
  return buf;
}


