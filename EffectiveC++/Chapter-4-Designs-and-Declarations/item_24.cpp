// Item 24: Declare non-member functions when type conversions should apply to all parameters.
// Things to Remember
// ✦ If you need type conversions on all parameters to a function 
//   (including the one that would otherwise be pointed to by the this pointer), 
//   the function must be a non-member.
#include <iostream>

class Rational {
    int numerator_, denominator_;
public:
    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator) { }

    int numerator() const {
        return numerator_;
    }

    int denominator() const {
        return denominator_;
    }

    // const Rational operator*(const Rational& rhs) const {
    //     int new_numerator = numerator_ * rhs.numerator_;
    //     int new_denominator = denominator_ * rhs.denominator_;
    //     return Rational(new_numerator, new_denominator);
    // }
    // 
    // 只有上面会导致 result = 3 * one_half; 报错,
    // because the compiler doesn't automatically perform implicit conversions 
    // in both directions when overloading binary operators.
    // We have an operator* overload in the Rational class that 
    // handles the case when a Rational object is on the left side of the * operator. 
};

std::ostream& operator<<(std::ostream& out, const Rational& r) {
    return out  << r.numerator() << "/" << r.denominator();
}

const Rational operator*(const Rational& lhs, const Rational& rhs) { // now a non-member function
    return Rational(lhs.numerator() * rhs.numerator(),
                    lhs.denominator() * rhs.denominator());    
}

// TODO
// const Rational operator*(Rational lhs, const Rational& rhs) { // passing lhs by value helps optimize chained a+b+c
// }

int main()
{
    Rational one_eighth(1, 8);
    Rational one_half(1, 2);

    Rational result = one_eighth * one_half;
    std::cout << result << std::endl;

    // You’d also like to support mixed-mode operations, 
    // where Rationals can be multiplied with, for example, ints.
    // Through **implicit type conversion**
    result = one_half * 3; // fine with non-explicit ctor.
    std::cout << result << std::endl;
    
    result = 3 * one_half; // error! even with non-explicit ctor.
    std::cout << result << std::endl;


    std::cin.get();
}