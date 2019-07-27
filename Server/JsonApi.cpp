#include"JsonApi.hpp"

JsonApi::JsonApi()
{}

void JsonApi::serialize(Json::Value &val,std::string &str)
{
  Json::FastWriter w;
  str= w.write(val);
}

void JsonApi::deserialize(std::string &str,Json::Value &val)
{
  Json::Reader r;
  r.parse(str,val,false);
}
  JsonApi::~JsonApi()
  {}


