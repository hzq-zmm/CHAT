#include<iostream>
#include<pthread.h>
#include<map>
#include<string>
#include"servertcpudp.hpp"
using namespace std;

map<string,string> _map;

typedef  struct NODE
{
  char flag;
  char name[20];
  char passwd[20];
}node;

void * product(void *arg)
{
  UDPServer *tmp=(UDPServer *)arg;
  while(1)
  {
    cout<<"pro"<<endl;
    string str;
    tmp->recvdata(str);
    cout<<"pro1"<<endl;
    cout<<str<<endl;
  }
}

void *consum(void *arg)
{
  UDPServer *tmp=(UDPServer *)arg;
  while(1)
  {
    cout<<"con"<<endl;
    tmp->boardcast();
    cout<<"con1"<<endl;
  }
}

void * login(void *arg)
{
  int * tmp=(int *)arg;
  
  char re[5]="ok";
  char er[5]="erro";
  while(1)
  {
    node _no;
    memset(&_no,0,sizeof(_no));
    int res=recv(*tmp,&_no,sizeof(_no),0);
    if(res<0)
    {
      cout<<"recv error"<<endl;
    }
    if(_no.flag==0)
    {
      _map.insert(pair<string,string>(_no.name,_no.passwd));
    send(*tmp,re,5,0);
    }
    else
    {
    map<string,string>::iterator it=  _map.find(_no.name);
    if(it!=_map.end())
    {
      send(*tmp,re,5,0);
//      close(*tmp);
      break;
    }
    else
    {
      send(*tmp,er,5,0);
    }
    }
  }
}

void Start()
{
  TCPServer _tcp("127.0.0.1",8080);
 // while(1)
 // {
    _tcp.Accept();
    int _sock=_tcp.sockfd;
  pthread_t ig;

  pthread_create(&ig,NULL,login,(void *)&_sock);

  pthread_join(ig,NULL);
  
 //}
}

int main()
{
  UDPServer _udp("127.0.0.1",8080);
  _udp.InitServer();

  pthread_t id;
  pthread_t ie;
  pthread_create(&id ,NULL,product,(void *)&_udp);
  pthread_create(&ie,NULL,consum,(void *)&_udp);
  

  Start();

  pthread_join(id,NULL);
  pthread_join(ie,NULL);
  return 0;
}
