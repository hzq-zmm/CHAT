#include<iostream>
#include<stdlib.h>
#include"JsonApi.hpp"

class dataType
{
  public:
    void val_to_str(std::string &str);
    void str_to_val(std::string &str);

  public:
    std::string nick_name;
    std::string school;
    std::string msg;
    std::string cmd;
};
