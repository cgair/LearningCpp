#ifndef MY_STRING_H
#define MY_STRING_H
#include <stddef.h>
#include <string.h>

namespace ms {
class MyString {
public: 
    static size_t DCtor; // The number of times the default constructor was called
    static size_t Ctor; // The number of times the constructor was called
    static size_t CCtor; // The number of times the copy constructor was called
    static size_t CAsgn; // The number of times the copy assignment was called
    static size_t MCtor; // The number of times the move constructor was called
    static size_t MAsgn; // The number of times the move assignment was called
    static size_t Dtor; // The number of times the destructor was called
private:
    char* data_;
    size_t len_;

    void init_data_(const char* s) {
        data_ = new char[len_ + 1];
        memcpy(data_, s, len_);
        data_[len_] = '\0';
    }

public:
    // default constructor
    MyString() : data_(nullptr), len_(0) { ++DCtor; }

    // constructor
    MyString(const char* p);
    // destructor
    virtual ~MyString();

    // copy constructor
    MyString(const MyString& str);
    // copy assignment
    MyString& operator=(const MyString& str);

    // move constructor
    MyString(MyString&& str) noexcept;
    // move assignment
    MyString& operator=(MyString&& str) noexcept;

    bool operator<(const MyString& rhs) const;

    bool operator==(const MyString& rhs) const;

    char* get() const;
};
    size_t MyString::DCtor = 0;
    size_t MyString::Ctor = 0;
    size_t MyString::CCtor = 0;
    size_t MyString::CAsgn = 0;
    size_t MyString::MCtor = 0;
    size_t MyString::MAsgn = 0;
    size_t MyString::Dtor = 0;

class MyStringNonMove {
public: 
    static size_t DCtor; // The number of times the default constructor was called
    static size_t Ctor; // The number of times the constructor was called
    static size_t CCtor; // The number of times the copy constructor was called
    static size_t CAsgn; // The number of times the copy assignment was called
    static size_t MCtor; // The number of times the move constructor was called
    static size_t MAsgn; // The number of times the move assignment was called
    static size_t Dtor; // The number of times the destructor was called
private:
    char* data_;
    size_t len_;

    void init_data_(const char* s) {
        data_ = new char[len_ + 1];
        memcpy(data_, s, len_);
        data_[len_] = '\0';
    }

public:
    // default constructor
    MyStringNonMove() : data_(nullptr), len_(0) { ++DCtor; }

    // constructor
    MyStringNonMove(const char* p) : len_(strlen(p)) {
        ++Ctor;
        init_data_(p);
    }

    // destructor
    virtual ~MyStringNonMove() {
        ++DCtor;
        if (data_) delete[] data_;
    }

    // copy constructor
    MyStringNonMove(const MyStringNonMove& str) : len_(str.len_) {
        ++CCtor;
        init_data_(str.data_);
    }
    // copy assignment
    MyStringNonMove& operator=(const MyStringNonMove& str) {
        ++CAsgn;
        if (this != &str) {
            if (data_ != nullptr) delete[] data_;
            len_ = str.len_;
            init_data_(str.data_);
        }

        return *this;
    }


    // bool operator<(const MyStringNonMove& rhs) const;

    // bool operator==(const MyStringNonMove& rhs) const;

    char* get() const;
};
    size_t MyStringNonMove::DCtor = 0;
    size_t MyStringNonMove::Ctor = 0;
    size_t MyStringNonMove::CCtor = 0;
    size_t MyStringNonMove::CAsgn = 0;
    size_t MyStringNonMove::MCtor = 0;
    size_t MyStringNonMove::MAsgn = 0;
    size_t MyStringNonMove::Dtor = 0;
}

#endif