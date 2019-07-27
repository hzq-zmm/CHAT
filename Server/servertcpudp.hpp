#pragma  once

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<error.h>
#include<map>
#include<string.h>
#include"datapool.hpp"
#include"dataType.hpp"
using namespace std;
//创建套接字
class TCPServer
{
  public :
    TCPServer(const string &ip,const short port)
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

class UDPServer
{
  public:
    string ip;
    int sock;
    int port;
    map<in_addr_t,struct sockaddr_in> usrlist;
    data_pool pool;
    


  public:
    UDPServer(const string &ip,const short port)
      :ip(ip)
       ,port(port)
       ,pool(1024)
  {}
    void InitServer()
    {
      sock=socket(AF_INET,SOCK_DGRAM,0);
      if(sock==-1)
      {
        cout<<"sock error"<<endl;
        exit(1);
      }

        struct sockaddr_in saddr;
        memset(&saddr,0,sizeof(saddr));
        saddr.sin_family=AF_INET;
        saddr.sin_port=htons(port);
        saddr.sin_addr.s_addr=inet_addr(ip.c_str());
      int tmp=bind(sock,(struct sockaddr*)&saddr,sizeof(saddr));
      
      if(tmp==-1)
      {
        cout<<" bind error"<<endl;
        exit(-1);
      }
    }

  //增加用户 
    void addUser(struct sockaddr_in &saddr) 
    {
      usrlist.insert(pair<in_addr_t,struct sockaddr_in>(saddr.sin_addr.s_addr,saddr));
    }


//删除用户
    void delUser(struct sockaddr_in &saddr)
    {
      map<in_addr_t,struct sockaddr_in> ::iterator it=usrlist.find(saddr.sin_addr.s_addr);
      if(it!=usrlist.end())
        usrlist.erase(it);
    }
//接受消息
    void recvdata(string &outstring)
    {
      struct sockaddr_in saddr;
      memset(&saddr,0,sizeof(saddr));
      socklen_t len=sizeof(saddr);
      
      char buf[1024];
      ssize_t s=recvfrom (sock,buf,sizeof(buf),0,(struct sockaddr*)&saddr,&len);
      if(s<0)
      {
        cout<<"recvfrom error"<<endl;
        exit(1);
      }
      cout<<"ok"<<endl;
      outstring=buf;
      pool.putdata(outstring);
      
      dataType data;
      data.str_to_val(outstring);
      if(data.cmd=="QUIT")
      {
        delUser(saddr);
      }
      else
      {
        addUser(saddr);
      }
 }  

  void Send(string &instring ,struct sockaddr_in &saddr)
  {
   ssize_t len= sendto(sock,instring.c_str(),instring.size(),0,(struct sockaddr*)&saddr,sizeof(saddr));
     if(len<0)
     {
       cout<<"sendto error"<<endl;
       exit(0);
     }
  }

  void boardcast()
  {
    string str;
    pool.getdata(str);
    map<in_addr_t,struct sockaddr_in>::iterator it=usrlist.begin();
    for(;it!=usrlist.end();it++)
    {
      Send(str,it->second);
    }
  }
 
 ~UDPServer()
 {
   close(sock);
 }

};



