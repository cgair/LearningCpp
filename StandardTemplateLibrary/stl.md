# Standard Template Library (STL)
![6 大 Components](https://pic1.zhimg.com/80/v2-7d2cf9c544fd78329215c15dd85aed20_1440w.webp)


## See also
* [The C++ Standard Template Library (STL)](https://www.geeksforgeeks.org/the-c-standard-template-library-stl/)


# list
`/usr/include/c++/11/list`

# 迭代器的设计原则和 Iterator Traits 的作用与设计
## [Iterator Traits.Q1 - Iterator 需要遵循的原则?]

Traits: 丢给它什么东西希望给我们萃取出我们想要的特征. 
`/usr/include/c++/11/bits/stl_iterator_base_types.h`

Iterator 必须提供的 5 种 associated types 来回答算法 (algorithm) 对它的提问.
1. iterator_category (迭代器类型: 指的是移动性质, 有的 iterator 只能往前走 ++, 有的可以后退 --, 还有的可以跳着走)    
2. value_type
3. difference_type (两个元素之间的距离)
4. pointer
5. reference

P.S. 主要是前三种

![algorithm 提问, iterator 回答](https://pic2.zhimg.com/80/v2-8559da84c2409a02d0d0e9f67d4a0d05_1440w.webp)

由图片可知: algorithm 提问, iterator 回答(直接 access struct 内 members), 看起来好像也不需要 traits?
* 如果一个迭代器不是一个类呢?
  * 收到的 iterator 可能是退化的 iterator (如 native pointer)
![traits 在哪里](https://pic4.zhimg.com/80/v2-ba9ea0fb88f7165192fe9fccc53e8c43_1440w.webp)

Iterator Traits 用以分离 class iterators 和 non-class iterators: 引入Traits机作为中间层, 接收类迭代器和指针迭代器, 做相应的工作 (模板偏特化), 得到 5 种迭代器关联类型.
![](https://pic4.zhimg.com/80/v2-12b24c71def453d691cc2b2cc3565787_1440w.webp)

各式各样的 traits
![](https://pic1.zhimg.com/80/v2-de8c17fe10557960eee645d32b2a6e7c_1440w.webp)

# vector
![](https://pic4.zhimg.com/80/v2-46f37b0fd4502dc0264e4a0cd14bf71b_1440w.webp)

## [vector.Q1 - vector 扩容?]
1. 初始时 vector 的 capacity 为 0, 插入第一个元素后capacity 增加为 1.
2. 不同的编译器实现的扩容方式不一样, VS2015中 以 1.5 倍扩容, GCC 以 2 倍扩容.
3. 一旦空间重新配置, 指向原 vector 的所有迭代器都失效了.

### Iterator Invalidation
When elements are moved from one position to another, and the initial iterator still points to the old invalid location, then it is called Iterator invalidation. 
* [iterator invalidation example](https://godbolt.org/z/Pe4xfs9q6)
* See also [Iterator Invalidation in C++](https://www.geeksforgeeks.org/iterator-invalidation-cpp/)

## [vector.Q2 - How to supercharge C++11 vector performance?]
* [6 Tips to supercharge C++11 vector performance](https://godbolt.org/z/axKTx89dh)
* See also [6 Tips to supercharge C++11 vector performance](https://www.acodersjourney.com/6-tips-supercharge-cpp-11-vector-performance/)


# deque, queue, stack
## deque
![](https://img-blog.csdnimg.cn/69bc9de2ecf646a4af315bb9d7b52992.png)
![G4.9](https://pic4.zhimg.com/80/v2-c75b5a371e80a93813382df56f3cf5d7_1440w.webp)
### deque 如何模拟连续空间
其实重点就是看迭代器 (iterator) 的 `iterator++`, `iterator--`. (全都是 deque iterator 的功劳)
![deque 如何模拟连续空间](https://pic3.zhimg.com/80/v2-eea98f04cbd78bcfbcee1bee884a63fe_1440w.webp)

### emplace_back
[EXAMPLE](https://godbolt.org/z/j5bzoWbW3) demonstrating how using [emplace_back](https://en.cppreference.com/w/cpp/container/deque/emplace_back) avoids the extra copy or move operation required when using push_back.

## queue


## stack

