#include "stdafx.h"
#include "NRVO.h"

#include <iostream>
#include <cassert>

class A
{
    int state_;
public:
    enum { destructed = -2, moved_from, default_constructed };

    A() : state_(default_constructed) { std::cout << "constructed default" << std::endl; }
    A(const A& a) : state_(a.state_) { std::cout << "constructed from object" << std::endl; }
    A& operator=(const A& a) { state_ = a.state_; std::cout << "assigned from object" << std::endl;  return *this; }
    A(A&& a) : state_(a.state_) { std::cout << "moved from" << std::endl; a.state_ = moved_from; }
    A& operator=(A&& a)
    {
        std::cout << "assigned - moved" << std::endl;
        state_ = a.state_; a.state_ = moved_from; return *this;
    }
    ~A() { std::cout << "destructued" << std::endl;  state_ = destructed; }

    explicit A(int s) : state_(s) { assert(state_ > default_constructed); }

    friend
        std::ostream&
        operator<<(std::ostream& os, const A& a)
    {
        switch (a.state_)
        {
        case A::destructed:
            os << "A is destructed\n";
            break;
        case A::moved_from:
            os << "A is moved from\n";
            break;
        case A::default_constructed:
            os << "A is default constructed\n";
            break;
        default:
            os << "A = " << a.state_ << '\n';
            break;
        }
        return os;
    }

    friend bool operator==(const A& x, const A& y)
    {
        return x.state_ == y.state_;
    }
    friend bool operator<(const A& x, const A& y)
    {
        return x.state_ < y.state_;
    }
};

//A&& f()
A f()
{
    A y;
    //return std::move(y);
    std::cout << &y << std::endl;
    return y;
}

void nrvo()
{
    std::cout << std::endl << "Named Return Value Optimization (NRVO)" << std::endl;

    A a = f();
    std::cout << &a << std::endl;
    std::cout << a << std::endl;
}