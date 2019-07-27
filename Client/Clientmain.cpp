#include<iostream>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<set>
#include"tcp.hpp"
#include"Window.hpp"
#include"dataType.hpp"
using namespace std;

typedef  struct node
{
  char flag;
  char name[20];
  char id[20];
}Node,*Pstr;

typedef  struct WIN
{
 UDPclient *cli;
 MyWindow *win;
}NWIN;


void Jiemian()
{
    cout<<"*******网络聊天室********"<<endl;
    cout<<"*******1.注册************"<<endl;
    cout<<"*******2.登陆************"<<endl;
    cout<<"*******3.退出************"<<endl;
    cout<<"*************************"<<endl;
}

dataType senddata; //发数据的类对象
dataType recvdata; //收数据的类对象
set<string> circle_friend;

void* HeaderID(void *arg)    //头匡函数
{
   NWIN *temp=(NWIN *)arg;
   int x,y;
   string msg="welecom to chat sys!";
   int step=0;
   while(1)
   {
     temp->win->createHeader();
     temp->win->myWinRefresh(temp->win->header);
     getmaxyx(temp->win->header,y,x);
     int startY=y*4/10;
     int startX=x;
     
     temp->win->putStrToWin(temp->win->header,startY,step++,msg);
     temp->win->myWinRefresh(temp->win->header);
     usleep(20000000);

     step%=(startX-1);
     temp->win->clearWinLine(temp->win->header,startY,1);
     temp->win->myWinRefresh(temp->win->header);
   }


   pthread_exit(NULL);


}

void* OutputID(void *arg)    //输出函数
{
   NWIN *temp=(NWIN *)arg;
  int x,y;
  x=y=0;
  int step=1;
  temp->win->createOutput();
  temp->win->myWinRefresh(temp->win->output);

  while(1)
  {
    string msg;
    cout<<"hhhh"<<endl;
    temp->cli->Recvfrom(msg);
    cout<<"ajjjj"<<endl;
    recvdata .str_to_val(msg);
    msg.clear();
    string name_school=recvdata.nick_name+"-"+recvdata.school;
    msg=name_school+":"+recvdata.msg;
    if(recvdata.cmd=="QUIT")
    {
       circle_friend.erase (name_school);
    }
    else{
      temp->win->putStrToWin(temp->win->output,step++,1,msg);
      temp->win->myWinRefresh(temp->win->output);
      getmaxyx(temp->win->output,y,x);
      int startY=y;
      step%=startY;
      if(step==0)
      {
        temp->win->createOutput();
        temp->win->myWinRefresh(temp->win->output);
        step=1;
        temp->win->putStrToWin(temp->win->output,step++,1,msg);
        temp->win->myWinRefresh(temp->win->output);
      }
    }
  }

   pthread_exit(NULL);
}
void* FirendID(void *arg)   //好友列表
{
   NWIN *temp=(NWIN *)arg;
  temp->win->createFriendList();
  temp->win->myWinRefresh(temp->win->friendlist);
  int x,y;
  int step=1;
  while(1)
  {
    string msg;
    set<string>::iterator iter=circle_friend.begin();

    temp->win->createFriendList();
    temp->win->myWinRefresh(temp->win->friendlist);
    step=1;
    for(;iter!=circle_friend.end();iter++)
    {
      msg=*iter;
      temp->win->putStrToWin(temp->win->friendlist,step++,1,msg);
      temp->win->myWinRefresh(temp->win->friendlist);
      getmaxyx(temp->win->friendlist,y,x);
      int startY=y;
      step%=startY;
      if(step==0)
      {
        sleep(3);
        temp->win->createFriendList();
        temp->win->myWinRefresh(temp->win->friendlist);
        step=1;
        temp->win->putStrToWin(temp->win->friendlist,step++,1,msg);
        temp->win->myWinRefresh(temp->win->friendlist);
      }
    }
    sleep(1);
  }
   pthread_exit(NULL);
}
void* InputID(void *arg)  //输入窗口
{
   NWIN *temp=(NWIN *)arg;
  string point="Please Enter:";
  while(1)
  {
    temp->win->createInput();
    temp->win->myWinRefresh(temp->win->input);

    temp->win->putStrToWin(temp->win->input,1,1,point);
    temp->win->myWinRefresh(temp->win->input);

    string msg=temp->win->getWinStr(temp->win->input);
    senddata.msg=msg;
    cout<<"dhsjhdjsa"<<endl;
    senddata.val_to_str(msg);
    cout<<"djskjdas"<<endl;
    temp->cli->Sendto(msg);
  }
   pthread_exit(NULL);
}
void mywindow()     //登录成功后进入的界面
{
  senddata.nick_name="dafu";
  senddata.school="xatu";
  senddata.cmd="None";

  MyWindow win;
  NWIN temp;
  temp.win=&win;

  UDPclient _udp("127.0.0.1",8080);
  _udp.InitUDPclient();
  temp.cli=&_udp;

  pthread_t headerID;
  pthread_t outputID;
  pthread_t friendID;
  pthread_t inputID;

 pthread_create(&headerID,NULL,HeaderID,(void *)&temp);
 pthread_create(&outputID,NULL,OutputID,(void *)&temp);
 pthread_create(&friendID,NULL,FirendID,(void *)&temp);
 pthread_create(&inputID,NULL,InputID,(void *)&temp);

  pthread_join(headerID,NULL);
  pthread_join(outputID,NULL);
  pthread_join(friendID,NULL);
  pthread_join(inputID,NULL);

}
void Registration(Client &cli)//注册函数
{
  Node log;
  log.flag=0;
  cout<<"please put name"<<endl;
  cin>>log.name;
  cout<<"please put id"<<endl;
  cin>>log.id;
  send(cli.sockfd,&log,sizeof(log),0);
  char buf[5]={0};
  recv(cli.sockfd,buf,5,0);
  if((strncmp(buf,"ok",2))==0)
    cout<<"注册 成功"<<endl;
} 


bool Login(Client &cli)   //登录函数
{
 Node log;
 log.flag=1;
  cout<<"please put name"<<endl;
  cin>>log.name;
  cout<<"please put id"<<endl;
  cin>>log.id;
  send(cli.sockfd,&log,sizeof(log),0);
  char buf[5]={0};
  recv(cli.sockfd,buf,5,0);

  if((strncmp(buf,"ok",2))==0)
  {
    cout<<"登录 成功"<<endl;
    return true;
  } 
  return false;
}
void Run()
{
    Client cli;
 if(!(cli.Connect("127.0.0.1",8080)))
 {
   perror("cli connect error\n");
   exit(-1);
 }
  while(1)
  {
  cout<<"please change"<<endl;
  int tmp;
  cin>>tmp;
  switch(tmp)
  {
    case 1:   //选择注册
    //注册函数
    Registration(cli);
    break;
    case 2:
    //登录函数
    if(Login(cli))
    {
//      close(cli.sockfd);
      //进入界面聊天函数
      mywindow();
    }
   // cli.Close();
    break;
    case 3:
    //退出函数
    break;
  }
  } 
}
int main()
{

  Jiemian();
  Run();
  return 0;
}
