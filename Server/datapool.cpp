#include"datapool.hpp"

data_pool::data_pool(int cap)
  :_cap(cap)
   ,_product_post(0)
   ,_consume_post(0)
   ,_datapool(cap)
   ,_size(0)
{
  sem_init(&_blank,0,cap);
  sem_init(&_data,0,0);
}

void data_pool::getdata(string &instring)
{
  sem_wait(&_data);
  instring=_datapool[_consume_post];
  _consume_post++;
  _size--;
  _consume_post%=_cap;
  sem_post(&_blank);
}

void data_pool::putdata(string &outstring)
{
  sem_wait(&_blank);
  _datapool[_product_post]=outstring;
  _consume_post++;
  _size++;
  _consume_post%=_cap;
  sem_post(&_data);
}

data_pool::~data_pool()
{
  _cap=0;
  _size=0;
  sem_destroy(&_blank);
  sem_destroy(&_data);
}
