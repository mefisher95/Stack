#include <iostream>
#include "Stack.h"

int main()
{
    Stack< int >::debug_printing(true);
    Stack< int > stack;
    stack.push(5);
    stack.push(6);
    stack.push(8);
    std::cout << stack << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack << std::endl;

    std::cout << stack.top() << std::endl;
    stack.top() = 99;
    std::cout << stack << std::endl;
    std::cout << stack.size() << std::endl;
    std::cout << stack.is_empty() << std::endl;
    stack.clear();
    std::cout << stack.is_empty() << std::endl;
    std::cout << stack << std::endl;
    
}