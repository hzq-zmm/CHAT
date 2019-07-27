#include<iostream>
#include<vector>
#include<semaphore.h>
using namespace std;
class data_pool
{
  public:
    data_pool(int cap);
    void getdata(string &instring);
    void putdata(string &outstring);
    ~data_pool();
  private:
    int _cap;
    int _product_post;
    int _consume_post;
    vector<string> _datapool;
    sem_t _blank;
    sem_t _data;
    int _size;
};
