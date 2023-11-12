# Iterator

## Intent
Lets you traverse elements of a collection without exposing its underlying representation (list, stack, tree, etc.).
* 使用面向对象将这种遍历机制抽象为 "迭代器对象".

![](https://img-blog.csdnimg.cn/0841265806b84f689746522ebfdbb83a.png)

## NOTE
1. 这种面向对象的方式已经过时, 因为有性能问题 (虚函数调用需要从 vtable 中找到函数地址)
2. STL中的迭代器是泛型编程思想, 基于模版, 编译时多态.
3. 运行时绑定是没有编译时绑定效率高的.

```c++
MyCollection<int> mc;
mc.CreateIterator();
for (iter.First(); !iter.IsDone(); iter.Next()) { // 全是虚函数调用
    
}
```