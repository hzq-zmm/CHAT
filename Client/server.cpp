#include<iostream>
#include"tcp.hpp"
using namespace std;
typedef  struct node
{
  char name[20];
  char id[20];
}Node;
int main()
{
  Server ser("127.0.0.1",8080);
  ser.Accept();
  Node no;
  recv(ser.sockfd,&no,sizeof(no),0);
  cout<<no.name<<endl;
  cout<<no.id<<endl;
  char buf[5]="ok";
  send(ser.sockfd,buf,sizeof(buf),0);
  recv(ser.sockfd,&no,sizeof(no),0);
  cout<<no.name<<endl;
  cout<<no.id<<endl;
  char buf1[5]="ok";
  send(ser.sockfd,buf1,sizeof(buf1),0);
  while(1)
  {
    char buff[80]={0};
    recv(ser.sockfd,buff,sizeof(buff),0);
    cout<<buff<<endl;
  }
  return 0;

}
