#ifndef ITEM_TWO_H_
#define ITEM_TWO_H_

namespace two 
{
    // 1. const is allocated with a storage 
    // so can be accessed by the deugger.
    #define ASPECT_RATIO 1.653

    // As a language constant, AspectRatio is definitely seen by  
    // compilers and is certainly entered into their symbol tables
    const double aspect_ratio_const = 1.653;   // uppercase names are usually for 
                                               // macros, hence the name change
    /*
    **gdb 调试 info variables 查看程序中定义的所有变量的符号**
    (gdb) info variables 
    All defined variables:

    File ./item_02.h:
    10:     static const double two::aspect_ratio_const;
    */


    // 2. class-specific constants.
    // 我想在类中定义一个常量大小的数组
    class GamePlayer {
        static const int NumTurns = 5;  // constant declaration
        // const int NumTurns = 5;      // 不是static, 该类还未构造时， NumTurns 不存在
        int scores[NumTurns];           // use of constant

        enum { NumTurns = 5 }; // "the enum hack" — makes
                               // NumTurns a symbolic name for 5
        int sscores[NumTurns]; // fine

    };

    // enum 声明的常量是一个右值.
    // 如果不想别人用一个 pointer 或者 reference 
    // 指向一个整型常量, 使用 enum 即可.
    enum { FIRST = 1 };


    // 3. A common (mis)use of the #define directive is 
    // using it to implement macros that look like functions 
    // but that don't incur the overhead of a function call.
    // call f with the maximum of a and b
    #define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))    // You have to remember to parenthesize all the arguments in the macro body. 
                                                            // Otherwise you can run into trouble when somebody calls the macro with an expression.
}

#endif