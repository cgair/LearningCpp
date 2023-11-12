#include "singleton.h"

int main()
{   
    // 只有一次类的构造函数被调用
    Singleton0::getInstance()->doSth();
    Singleton0* s0 = Singleton0::getInstance();
    s0->doSth();

    // 推荐的懒汉式单例
    Singleton& s = Singleton::getInstance();
    s.doSth();
    Singleton::getInstance().doSth();

    return 0;
}