/**
 * @file 0073_dynamic_casting.cpp
 * @author cg
 * @brief Dynamic Casting in C++
 * @version 0.1
 * @date 2023-09-10
 * 
 * @copyright Copyright (c) 2023
 * **Key Takeaways**
 * 1. What does dynamic_cast does?
 *    用于沿继承层次结构进行转换. Essentially 
 *    what that means is if I have a class that
 *    is a subclass of another class, and I wanna
 *    either cast to the base type or from the base
 *    type to the derived type, that's where I can
 *    actually use a dynamic_cast. Let's just say
 *    we have an Entity class, which is the class for
 *    all of our entities in our game. We also have a
 *    Player class and an Enemy class (both entities,
 *    derived from the Entity class).
 *    1) If I just wanna to cast a player object back to 
 *    an entity object, that can be done implicitly, no casting
 *    is necessary although we could use dynamic_cast to do it.
 *    2) If we have an entity object, and we want to cast it to
 *    a player, but we have no way of knowing whether or not 
 *    it's a player (it could also be an enemy). We could use 
 *    dynamic_cast to **check** if an object is a given type.
 * 
 * 2. How does dynamic_cast know that the entity I have is actually
 *    a player or an enemy?
 *    The way that it does that is it actually stores Run-Time Type Information
 *    about all of our types (RTTI).
 *    我们可以关闭 RTTI, 但是就不能用 dynamic_cast.
 */
#include <iostream>

// //////////////////////////////// //
// dynamic_cast
// //////////////////////////////// //
// dynamic_cast is not cast that is 
// done at like compile time, it's evaluated
// at runtime and because of that it does
// has an associated runtime cost.
// Downcasting: Casting a base class pointer (or reference) 
// to a derived class pointer (or reference) is known as downcasting.

class Entity 
{
public:
    virtual void PrintName() { }
};

class Player : public Entity 
{
};

class Enemy : public Entity 
{
};

int main()
{
    Player* actually_player = new Player();
    Entity* e = actually_player; // implicit cast
    // If I wanna go back to player
    // Player* p = e; // error

    Entity* actually_enemy = new Enemy();
    Player* p = (Player*) actually_enemy; // This will initially work but it's dangerous.
                                          // If we try to do sth that is unique to player
                                          // that enemy does't have, such as acess to 
                                          // certain data members, our program will likely
                                          // crash.
    Player* p1 = dynamic_cast<Player*>(actually_enemy);
    if (p1 == nullptr) std::cout << "null pointer.\n";
    Player* p2 = dynamic_cast<Player*>(e);
    

    std::cin.get();
}