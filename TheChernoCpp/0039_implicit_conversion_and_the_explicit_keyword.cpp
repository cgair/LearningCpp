/**
 * @file 0039_implicit_conversion_and_the_explicit_keyword.cpp
 * @author cg
 * @brief Implicit Conversion and the Explicit Keyword in C++
 * @version 0.1
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 * **Key Takeaways**
 * 
 */
#include <iostream>
#include <string>

class Entity
{
    int age_;
    std::string name_;
public:
    Entity(const std::string& name)
        : name_(name), age_(-1) { }
    Entity(int age)
        : name_("Unknown"), age_(age) { }

    // explicit Entity(int age)
    //     : name_("Unknown"), age_(age) { }
};

void PrintEntity(const Entity& entity) {
    // Printing
}

int main() {
    // Implicit Conversion
    // 
    // implicit means kind of without you explicitly telling it what to do
    // so it kind of work automatically.
    // what the compiler is allowed to do is perform one implicit conversion on your code.
    Entity a("Easton");
    Entity b(22);
    // what you can do which 
    // a lot people don't know is
    std::string myName = "Easton";
    Entity c = myName;
    Entity d = 22;  // I can assign 22, what is going on here?
                    // This is called implicit conversion
                    // or implicit construction

    PrintEntity(22);
    // PrintEntity("Easton"); // In order for this to work
                           // C++ would actually have to do two conversions:
                           // 1. const char array -> std::string
                           // 2. std::string -> Entity ❌
    PrintEntity(std::string("Cherno"));
    PrintEntity(Entity("Cherno"));

    // Explicit Keyword
    // 
    // explicit disables the implicit functionality
    // If you write a explicit constructor it means
    // that no no no implicit conversions.
    // comment line 23, 24
    // and uncomment line 26, 27

    std::cin.get();
}