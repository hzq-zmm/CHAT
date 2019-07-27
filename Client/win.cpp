#include<iostream>
#include<unistd.h>
#include"Window.hpp"
  int main()
  {
    MyWindow win;

  /*  win.createHeader();
    win.myWinRefresh(win.header);

    int y,x;
    std::string msg="welecom to chat sys!";
    getmaxyx(win.header,y,x);
    int startY=y/2;
    int startX=x*2/5;
    win.putStrToWin(win.header,startY,startX,msg);
    win.myWinRefresh(win.header);
*/
   win.createOutput();
    win.createFriendList();
    win.createInput();

  //  sleep(5);
    win.myWinRefresh(win.output);
   // sleep(5); 
    win.myWinRefresh(win.friendlist);
   // sleep(5); 
//  std::string getWinStr(WINDOW* win);
   win.myWinRefresh(win.input);
  //  sleep(5);
  //std::string getWinStr(WINDOW* win);

   std::string str=win.getWinStr(win.output);
   //std::string str1=win.getWinStr(win.friendlist);
   //std::string str2=win.getWinStr(win.input);

   //std::string str=win.getWinStr(win.header);
  // win.myWinRefresh(win.header);
//    sleep(5); 

  // win.clearWinLine(win.header,startY,1);
   // win.myWinRefresh(win.header);


  //  win.putStrToWin(win.header,0,0,str);
   // win.myWinRefresh(win.header);
   // sleep(5);
   getch();
    return 0;

  }


