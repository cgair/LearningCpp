# C++11 新特性

## auto 和 decltype

## nullptr

## final 和 override

## default/delete

## explicit

## constexpr


## static_assert

## 右值引用

## 列表初始化


## 智能指针




## 关于模板 (C++11)
### 完美转发
*完美转发*指可以写一个接受任意实参的函数模板, 并转发到其它函数, 目标函数会收到与转发函数完全相同的实参, 转发函数实参是左值那目标函数实参也是左值, 转发函数实参是右值那目标函数实参也是右值.
* [std::forward](https://en.cppreference.com/w/cpp/utility/forward)
  * Forwards lvalues as either lvalues or as rvalues, depending on T.
  * Forwards rvalues as rvalues and prohibits forwarding of rvalues as lvalues.


## 并发


## 随机数功能

## 正则表达式


## chrono



