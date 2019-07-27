#include"dataType.hpp"

void dataType::val_to_str(std::string &str)
{
  Json::Value val;
  val["nick_name"]=nick_name;
  val["school"]=school;
  val["msg"]=msg;
  val["cmd"]=cmd;
  JsonApi::serialize(val,str);
}

void dataType::str_to_val(std::string &str)
{
  Json::Value val;
  JsonApi::deserialize(str,val);
  nick_name=val["nick_name"].asString();
  school=val["school"].asString();
  msg=val["msg"].asString();
  cmd=val["cmd"].asString();
}
