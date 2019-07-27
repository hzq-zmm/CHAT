#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<error.h>
#include<string.h>
using namespace std;
//创建套接字
class Server
{
  public :
    Server(const string &ip,const short port)
    {
      sockfd=socket(AF_INET,SOCK_STREAM,0);
      struct sockaddr_in saddr;
      memset(&saddr,0,sizeof(saddr));
      saddr.sin_family=AF_INET;
      saddr.sin_port=htons(port);
      saddr.sin_addr.s_addr=inet_addr(ip.c_str());
      int tmp=bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
      
      if(tmp==-1)
      {
        cout<<" bind error"<<endl;
        exit(-1);
      }
      tmp=listen(sockfd,5);
      if(tmp==-1)
      {
        cout<<"lieten error"<<endl;
        exit(-1);
      }
    }
    bool Accept()
    {
      struct sockaddr_in saddr1;
      socklen_t saddr1_len;
      sockfd=accept(sockfd,(struct sockaddr*)&saddr1,&saddr1_len);
      if(sockfd==-1)
      {
        cout<<"accept error"<<endl;
        return false;
      }
      return true;
    }
    bool Send(std::string &instring)
    {
      ssize_t s=send(sockfd,instring.c_str(),instring.size(),0);
      if(s<0)
      {
        perror("send error\n");
        return false;
      }
      else{
        return true;
      }
    }
    bool Recv(std::string &outstring)
    {
      char buf[1024]={0};
      ssize_t s=recv(sockfd,buf,sizeof(buf),0);
      if(s<0)
      {
        perror("recv error\n");
        return false;
      }
      else{
        int i=0;
        while(buf[i]!='\0')
        {
          outstring+=buf[i];
          i++;
        }
        return true;
      }
    }
    void Close()
    {
      close(sockfd);
    }
  public :
    int sockfd;
};



//客户端封装
class Client
{
  public:
    Client()
    {
      sockfd=socket(AF_INET,SOCK_STREAM,0);
      if(sockfd<0)
      {
        cout<<"sockfd error"<<endl;
        exit(-1);
      }
    }
    bool Connect(const string ip,const short port)
    { 
      struct sockaddr_in saddr;
      memset(&saddr,0,sizeof(saddr));
      saddr.sin_family=AF_INET;
      saddr.sin_port=htons(port);
      saddr.sin_addr.s_addr=inet_addr(ip.c_str());
      int ret=connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
      if(ret<0)
      {
        cout<<"connect error"<<endl;
        return false;
      }
      return true;
    }
    bool Send(std::string &instring)
    {
      ssize_t s=send(sockfd,instring.c_str(),instring.size(),0);
      if(s<0)
      {
        perror("send error\n");
        return false;
      }
      else{
        return true;
      }
    }
    bool Recv(std::string &outstring)
    {
      char buf[1024]={0};
      ssize_t s=recv(sockfd,buf,sizeof(buf),0);
      if(s<0)
      {
        perror("recv error\n");
        return false;
      }
      else{
        int i=0;
        while(buf[i]!='\0')
        {
          outstring+=buf[i];
          i++;
        }
        return true;
      }
    }
    void Close()
    {
      close(sockfd);
    }
  public:
    int sockfd;
};



class UDPclient
{
  public:
    int sockfd;
    struct sockaddr_in saddr;
  public:
  UDPclient (string const &ip,const short port)
  {
    saddr.sin_family=AF_INET;
    saddr.sin_port=htonl(port);
    saddr.sin_addr.s_addr=inet_addr(ip.c_str());
    
  }
  void InitUDPclient()
  {
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)
    {
      cout<<"socket error"<<endl;
    }
  }

  void Recvfrom(string &instring)
  {
    struct sockaddr_in _saddr;
    char buf[1024]={0};
    socklen_t len=sizeof(_saddr);
    recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&_saddr,&len);

    instring=buf;

  }
  void Sendto(string &outstring)
  {
    sendto(sockfd,outstring.c_str(),outstring.size(),0,(struct sockaddr*)&saddr,sizeof(saddr));
  }
  
  ~UDPclient()
  {}

};
