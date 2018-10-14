tid=28300, constructing 0x774c20            //构造
tid=28300, obj1 0x774c20 name=main one      //设置名字
tid=28300, constructing 0x775060            //构造对象2
tid=28300, obj2 0x775060 name=              //print

tid=28301, constructing 0x7fcdb40008c0      //创建新线程的每个线程独占数据
tid=28301, obj1 0x7fcdb40008c0 name=
tid=28301, constructing 0x7fcdb40008f0
tid=28301, obj2 0x7fcdb40008f0 name=

tid=28301, obj1 0x7fcdb40008c0 name=changed 1
tid=28301, obj2 0x7fcdb40008f0 name=changed 42  //改变值
tid=28301, destructing 0x7fcdb40008c0 changed 1     //销毁对象
tid=28301, destructing 0x7fcdb40008f0 changed 42

tid=28300, obj1 0x774c20 name=main one
tid=28300, obj2 0x775060 name=main two
tid=28300, destructing 0x774c20 main one        //主线程销毁对象
tid=28300, destructing 0x775060 main two

#define STL muduo::Singleton<muduo::ThreadLocal<Test> >::instance().value() //定义一个单例对象
tid=28335, constructing 0x1426c40               构造一个线程特定数据main one

tid=28336, constructing 0x7f726c0008c0          连续创建两个独立的线程
tid=28336, 0x7f726c0008c0 name=                 同时打印特定数据，thread1 和 thread2

tid=28337, constructing 0x7f72640008c0
tid=28337, 0x7f72640008c0 name=

tid=28336, 0x7f726c0008c0 name=thread1          setName后的打印数据
tid=28336, destructing 0x7f726c0008c0 thread1   线程1结束会销毁特定数据

tid=28337, 0x7f72640008c0 name=thread2
tid=28337, destructing 0x7f72640008c0 thread2

tid=28335, 0x1426c40 name=main one
tid=28335, destructing 0x1426c40 main one       主线程退出

单例对象single是指线程只被运行一次
tid=28296, constructing 0x1c31c20               构造一个Test对象，对象名字为only one

tid=28297, 0x1c31c20 name=only one              在另外新建的线程中仍然可以访问主线程的对象         
tid=28296, 0x1c31c20 name=only one, changed
tid=28296, destructing 0x1c31c20 only one, changed

### 19分析单例对象的线程独有数据ThreadLocalSigleton_test
tid=29094, constructing 0x2103c40               //主函数创建一个单例对象Test, 名字设为main one

tid=29095, constructing 0x7f589c0008c0          //创建线程一
tid=29095, 0x7f589c0008c0 name=

tid=29096, constructing 0x7f58940008c0          //创建线程二
tid=29096, 0x7f58940008c0 name=

tid=29095, 0x7f589c0008c0 name=thread1          //在线程1中设置线程独有数据的名字为thread1, 并输出
tid=29095, destructing 0x7f589c0008c0 thread1

tid=29096, 0x7f58940008c0 name=thread2
tid=29096, destructing 0x7f58940008c0 thread2

tid=29094, 0x2103c40 name=main one
tid=29094, destructing 0x2103c40 main one
