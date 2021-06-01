# cpp_example_component_splitting_with_template

 ```cpp
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
  
template <template <class> class...Args>
struct VariadicManager : public Args<VariadicManager<Args...>>...
{
    VariadicManager() : Args<VariadicManager<Args...>>(*this)...
    {}
};

int main() {
    VariadicManager<Foo,Bar> mgr;
    mgr.foo(10);
    mgr.bar(10);
}
```
