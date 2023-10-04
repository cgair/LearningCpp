// Item 20: Prefer pass-by-reference-to-const to pass-by-value.
// Things to Remember
// ✦ Prefer pass-by-reference-to-const over pass-by-value. 
//   It’s typically more efficient and it avoids the slicing problem.
// ✦ The rule doesn’t apply to built-in types and STL iterator and function object types. 
//   For them, pass-by-value is usually appropriate.
#include <iostream>
#include <string>

// Passing parameters by reference also avoids the slicing problem.
// 
// a graphical window
class Window {
    std::string name_;
public:
    Window() : name_("window") { }
    // return name of window
    std::string name() const {
        return name_;
    }

    // draw window and contents
    virtual void display() const {
        std::cout << "This is a Window.\n";
    } 
};

class WindowWithScrollBars: public Window { 
    std::string name_;
public:
    WindowWithScrollBars() : name_("window with scroll bars") { }

    std::string name() const {
        return name_;
    }
    
    virtual void display() const {
        std::cout << "This is a WindowWithScrollBars.\n";
    } 
};

// print out a window's name and then display the window.
// void print_name_and_display(Window w) // incorrect! parameter may be sliced!
void print_name_and_display(const WindowWithScrollBars &wwsb) // fine, parameter won’t be sliced
{
    std::cout << wwsb.name() << std::endl;
    wwsb.display();   
}

int main()
{
    WindowWithScrollBars wwsb;
    // The parameter w will be constructed — it’s passed by value — as a Window object, 
    // and all the specialized information that made wwsb act like 
    // a WindowWithScrollBars object will be sliced off.
    print_name_and_display(wwsb);

    std::cin.get();
}