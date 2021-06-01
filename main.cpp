#include <iostream>

template<class Manager_t>
struct Foo
{
    Manager_t& mgr;
    Foo(Manager_t& mgr):mgr(mgr){}
    
    void foo(int i)
    {
        std::cout << "foo(" << i << ")\n";
        if (i > 0) mgr.bar(i-1);
    }
};

template<class Manager_t>
struct Bar
{
    Manager_t& mgr;
    Bar(Manager_t& mgr):mgr(mgr){}

    void bar(int i)
    {
        std::cout << "bar(" << i << ")\n";
        if (i > 0) mgr.foo(i-1);
    }
};

template<
    template <class> class Foo_t,
    template <class> class Bar_t
>
struct Manager : public Foo_t<Manager<Foo_t, Bar_t>>, public Bar_t<Manager<Foo_t, Bar_t>>
{
    Manager()
        : Foo_t<Manager<Foo_t, Bar_t>>(*this)
        , Bar_t<Manager<Foo_t, Bar_t>>(*this)
    {}
};


template <template <class> class...Args>
struct VariadicManager : public Args<VariadicManager<Args...>>...
{
    VariadicManager() : Args<VariadicManager<Args...>>(*this)...
    {}
};

int main() {

    Manager<Foo,Bar> mgr;
    mgr.foo(10);

    VariadicManager<Foo,Bar> vmgr;
    vmgr.foo(10);
}

/*
Output:
foo(10)
bar(9)
foo(8)
bar(7)
foo(6)
bar(5)
foo(4)
bar(3)
foo(2)
bar(1)
foo(0)
foo(10)
bar(9)
foo(8)
bar(7)
foo(6)
bar(5)
foo(4)
bar(3)
foo(2)
bar(1)
foo(0)
//*/
