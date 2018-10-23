## muduo网络库简介
* 高级语言(Java, Python等)的Sockects库并没有对Sockects API提供更高层的封装, 直接用它编写程序很容易掉到陷阱中；
* 网络库的价值还在于能方便地处理并发链接;

#### 网络核心库
* muduo是基于Reactor模式的网络库, 其核心是个事件循环EventLoop,用于响应计时器和IO事件;
    - muduo采用基于对象(object-based)而非面向对象(object-oriented)的设计风格;

#### 网络附属库
* 网络库有一些附属模块, 它们不是核心内容, 在使用的时候需要链接相应的库;
* 使用muduo库而言, 只需要掌握5个关键类:Buffer，EventLoop, TcpConnection, TcpClient, TcpServer;

#### 线程模型
* muduo的线程模型符合one loop per thread + thread pool模型;
    - 每个线程最多有一个EventLoop, 每个TcpConnection必须归某个EventLoop管理, 所有的IO会转移到这个线程;
* ThreadPool, 新到的链接会按round-robin方式分配到线程池中;
* muduo库的核心是每个IO线程一个事件循环, 把IO事件分发到回调函数上;
* 希望muduo库能减少网络编程中的偶发复杂性(accidental complexity);
* 基于事件的非阻塞网络编程是编写高性能并发网络服务程序的主流模式;
    - 大量用到了回调函数的思想;
* TCP网络编程最本质是处理三个半事件:
    - 连接的建立, 包括服务器端接受(accept)新链接和客户端成功发起(connect)链接; TCP连接一旦建立, 客户端和服务端是平等的, 可以各自收发数据;
    - 连接的断开, 包括主动断开(close, shutdown)和被动断开(read返回0);
    - 消息到达, 文件描述符可读; 这是最重要的一个事件, 对它的处理方式决定了网络编程的风格(阻塞还是非阻塞, 如何处理分包, 应用层的缓冲如何设计, 等等);
    - 消息发送完毕, 这个算半个; 对于低流量的服务, 可以不必关心这个事件; 另外, 这里的发送完毕是指数据写入操作系统的缓冲区, 将由TCP协议栈负责数据的发送与重传, 不代表对方已经收到了数据;
* echo 服务器的实现:
    - muduo的使用非常简单, 不需要从指定的类派生, 也不用覆写虚函数, 只需要注册几个回调函数去处理三个半事件就行了;
    - echo服务器的业务逻辑就是把收到的数据原封不动地发回客户端;
    - 程序主体是被动等待事件发生, 事件发生之后网络库会调用(回调)事先注册的事件处理函数(event handler);
* 七步实现finger服务
    - Python Twisted是一款非常好的网络库, 它也是采用的Reactor作为网络编程的基本模型, 所以从使用上与muduo颇有相似之处(muduo没有deferreds);
    - finger是Twisted文档中一个经典的例子, muduo来实现最简单的finger服务端;
        + [大佬的muduo学习笔记](https://blog.csdn.net/zhangxiao93/article/details/52745316);
        + finger(端口79)是互连网上最古老的协议之一, 用于提供站点及用户的基本信息, 一般通过finger服务,你可以查询到站点上的在线用户清单及其他一些有用的信息;
        + finger服务是基于客户/服务器模式的，目标机上通常有一个fingerd的服务器程序（在unix中，被称为finger守护进程）;
        + 而finger返回的结果是由这个进程决定的，使用或自己编些不同的进程，可以提供各种各样的finger服务;
* 性能评测
    - 在muduo库擅长的领域(TCP长连接), 其性能不比任何开源网络库差;
    - muduo最开始并没有以高并发、高吞吐为主要目标;
        + ping pong 测试表明:
            * muduo的吞吐量比Boost.Asio高15%;
            * muduo的吞吐量比libevnet2高18%;
        + muduo与Nginx的吞吐量对比
            * 对比内置的简陋的HTTP服务器的长连接性能;
            * 直接返回内存中的数据, 比较程序的网络性能;
            * qps(每秒请求数)都能超过10万;
        + muduo与ZeroMQ的延迟对比;
            * muduo的延迟稳定的低于ZeroMQ;
* 详解muduo库多线程模型
    - 以一个sudoku solver为例， 一个求解数独的服务器程序;
    - 从网络连接读入一个sudoku题目, 算出答案, 再发回给客户端;
    - 怎么做才能发挥多核硬件的能力;
    - 一个简单的以'\r\n'分隔的文本行协议, 使用TCP长连接, 客户端在不需要服务时主动断开连接;
* 正确使用non-blocking IO需要考虑的问题很多, 不适宜直接调用Sockect API, 而需要一个功能完善的网络库支撑;
* 目前高性能httpd普遍采用的是单线程Reactor方式;
    - reactors+thread pool是最灵活的IO与CPU配置;
* 通常由网络库负责读写socket, 用户代码负责解码、计算和编码;
* C++多线程服务器编程模式为: one loop per thread + thread pool
    - event loop 用作non-blocking IO 和定时器;
    - thread pool用来做计算, 具体可以是任务队列或生产者消费者队列;CC