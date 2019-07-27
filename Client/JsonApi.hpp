#include<iostream>
#include<json/json.h>

class JsonApi
{
  public:
    JsonApi();
    static void serialize(Json::Value &val,std::string &str);
    static void deserialize(std::string &str,Json::Value &val);
    ~JsonApi();
};
