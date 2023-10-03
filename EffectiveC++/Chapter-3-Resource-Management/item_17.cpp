// Item 17: Store newed objects in smart pointers in standalone statements.
// Things to Remember
// ✦ Store newed objects in smart pointers in standalone statements. 
//   Failure to do this can lead to subtle resource leaks when exceptions are thrown.
#include <iostream>

struct Widget
{
    float x, y;
    Widget() : x(0), y(0) { }
};

int priority() {

    return 0;
}

int process_widget(std::shared_ptr<Widget> pw, int(*func)())
{   
    return 0;
}

int main()
{
    // 尽管使用 object-managing resources, 此调用可能会 leak resources.
    process_widget(std::shared_ptr<Widget> (new Widget), priority);

    // 1
    // Use a separate statement to create the Widget and store it in a smart pointer, 
    // then pass the smart pointer to process_widget:
    std::shared_ptr<Widget> pw(new Widget); // store newed object
                                            // in a smart pointer in a 
                                            // standalone statement
    process_widget(pw, priority); // this call won’t leak

    // 2
    // It's also a good practice to use
    // `std::make_shared` or `std::make_unique` (in C++14 and later) 
    // to allocate objects and manage their ownership with smart pointers:
    process_widget(std::make_shared<Widget>(), priority);

    return 0;
}