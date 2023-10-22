#include "my_string.h"
#include <string>
#include <iterator>
#include <string.h>
#include <iostream>
#include <typeinfo> // typeid()

// test
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <ctime>

ms::MyString::MyString(const char* p) : len_(strlen(p)) {
    ++Ctor;
    init_data_(p);
}

ms::MyString::~MyString() {
    ++DCtor;
    if (data_) delete[] data_;
}

ms::MyString::MyString(const MyString& str) : len_(str.len_) {
    ++CCtor;
    init_data_(str.data_);
}

ms::MyString& ms::MyString::operator=(const MyString& str) {
    ++CAsgn;
    if (this != &str) {
        if (data_ != nullptr) delete[] data_;
        len_ = str.len_;
        init_data_(str.data_);
    }

    return *this;
}

ms::MyString::MyString(MyString&& str) noexcept
: data_(str.data_), len_(str.len_)
{
    ++MCtor;
    str.len_ = 0;
    str.data_ = nullptr;
}

ms::MyString& ms::MyString::operator=(MyString&& str) noexcept {
    ++MAsgn;
    if (this != &str) {
        if (data_) delete[] data_;
        len_ = str.len_;
        init_data_(str.data_);
        str.data_ = nullptr;
    }

    return *this;
}

bool ms::MyString::operator<(const MyString& rhs) const {
    // 简单起见, 借用 std 现成的 string 的比较
    return std::string(this->data_) < std::string(rhs.data_);
}

bool ms::MyString::operator==(const MyString& rhs) const {
    return std::string(this->data_) == std::string(rhs.data_);
}

template<typename T>
void output_static_data(const T& my_str) {
    std::cout << typeid(my_str).name() << "--\n";
    std::cout << "CCtor=" << T::CCtor
              << " MCtor=" << T::MCtor
              << " CAsgn=" << T::CAsgn
              << " MAsgn=" << T::MAsgn
              << " Dtor=" << T::Dtor
              << " Ctor=" << T::Ctor
              << " DCtor=" << T::DCtor
              << std::endl;
}

// move aware 测试
template<typename M, typename NM>
void test_moveable(M c1, NM c2, long& value) {
    char buf[10];

    // 测试 moveable
    std::cout << "TEST: with moveable elements\n";
    typedef typename std::iterator_traits<typename M::iterator>::value_type V1type;

    clock_t start;
    start = clock();
    for (long i = 0; i < value; ++i) {
        snprintf(buf, 10, "%d", rand());
        auto ite = c1.end(); // 定位尾端
        // <https://en.cppreference.com/w/cpp/container/vector/insert>
        c1.insert(ite, V1type(buf)); // 安插于尾端
    }

    std::cout << "construction, milli-seconds: "
              << clock() - start
              << std::endl;
    std::cout << "size: "
              << c1.size()
              << std::endl;
    output_static_data(*(c1.begin()));

    start = clock();
    M c11(c1);
    std::cout << "copy, milli-seconds: "
              << clock() - start
              << std::endl;

    start = clock();
    M c12(std::move(c1));
    std::cout << "move copy, milli-seconds: "
              << clock() - start
              << std::endl;

    start = clock();
    c11.swap(c12);
    std::cout << "swap, milli-seconds: "
              << clock() - start
              << std::endl;


    // 测试 non-moveable
    std::cout << "\nTEST: with non-moveable elements\n";
    typedef typename std::iterator_traits<typename NM::iterator>::value_type V2type;
    start = clock();
    for (long i = 0; i < value; ++i) {
        snprintf(buf, 10, "%d", rand());
        auto ite = c2.end(); // 定位尾端
        c2.insert(ite, V2type(buf)); // 安插于尾端
    }

    std::cout << "construction, milli-seconds: "
              << clock() - start
              << std::endl;
    std::cout << "size: "
              << c2.size()
              << std::endl;
    output_static_data(*(c2.begin()));
    
    start = clock();
    NM c21(c2);
    std::cout << "copy, milli-seconds: "
              << clock() - start
              << std::endl;

    start = clock();
    NM c22(c21);
    std::cout << "move copy, milli-seconds: "
              << clock() - start
              << std::endl;

    start = clock();
    c21.swap(c22);
    std::cout << "swap, milli-seconds: "
              << clock() - start
              << std::endl;
}

int main(int argc, char* argv[])
{

    if (argc == 1) {
        std::cout << "input times\n";
        exit(EXIT_FAILURE);
    }
    std::vector<ms::MyString> c1;
    std::vector<ms::MyStringNonMove> c2;
    long times = std::stol(argv[1]);

    test_moveable<std::vector<ms::MyString>, std::vector<ms::MyStringNonMove>>(c1, c2, times);

    return 0;
}