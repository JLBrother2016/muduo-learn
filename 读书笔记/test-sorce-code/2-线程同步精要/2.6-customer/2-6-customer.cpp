#include <map>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "Mutex.h"

using std::string;
using namespace std;

typedef std::pair<string, int> Entry;      // 表项
typedef std::vector<Entry> EntryList;      // 目录表
typedef std::map<string, EntryList> Map;   // 一个string对应一个表项
typedef boost::shared_ptr<Map> MapPtr;     // 用shared_ptr来指向Map

class CustomerData : boost::noncopyable
{
 public:
  CustomerData()
    : data_(new Map)   // 用一个map来代替hash表
  { }

  int query(const string& customer, const string& stock) const;

 private:
  void update(const string& customer, const EntryList& entries);
  void update(const string& message);
  // 用lower_bound在entries里面找stock
  static int findEntry(const EntryList& entries, const string& stock);
  static MapPtr parseData(const string& message);

  MapPtr getData() const
  {
    muduo::MutexLockGuard lock(mutex_);
    return data_;
  }

  // MapPtr parseData(const string& message) const
  // {
  //   muduo::MutexLockGuard lock(mutex_);
  //   return data_;
  // }

  mutable muduo::MutexLock mutex_;
  MapPtr data_;
};

int CustomerData::query(const string& customer, const string& stock) const
{
  MapPtr data = getData();  // data 一旦拿到就不需要锁了
  // 取数据的时候只有getData()内部有锁, 多线程读的性能会很好

  Map::const_iterator entries = data->find(customer);
  if (entries != data->end())
    return findEntry(entries->second, stock);
  else
    return -1;
}

void CustomerData::update(const string& customer, const EntryList& entries)
{
  muduo::MutexLockGuard lock(mutex_);
  if (!data_.unique())  // 有多个读线程, 修改的是原来的一份拷贝
  {
    MapPtr newData(new Map(*data_));  
    data_.swap(newData);
  }  // data_.unique()用来判断是不是有人在读 
  assert(data_.unique());   // 如果没有用户在读, 就直接修改, 节约一次拷贝
  (*data_)[customer] = entries;
}

void CustomerData::update(const string& message)
{
  MapPtr newData = parseData(message);
  if (newData)
  {
    muduo::MutexLockGuard lock(mutex_);
    data_.swap(newData);
  }
}
// 大部分情况下更新都是在原来的数据上进行的, 拷贝的比例还不到1%, 很高效;
// 更准确的说, 这不是copy-on-write, 而是copy-on-other-reading
// 与read-copy-update颇有相似之处

MapPtr CustomerData::parseData(const string& message)
{
  MapPtr res_(new Map);
  return res_;
}

int CustomerData::findEntry(const EntryList& entries, const string& stock)
{
  return 0;
}


int main()
{
  CustomerData data;
}
