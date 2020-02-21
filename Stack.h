#ifndef STACK_H
#define STACK_H

#include "SLList.h"

class UnderflowError {};

template < typename t >
class Stack
{
    public:

    //=========================================================================
    // Reference Methods
    //=========================================================================

    SLList< t > &__list__() { return list_; }

    t &top() { return list_.front(); }
    t top() const { return list_.front(); }

    //=========================================================================
    // Information Methods
    //=========================================================================

    int size() const { return list_.size(); }
    bool is_empty() { return list_.is_empty(); }
    
    //=========================================================================
    // Mutator Methods
    //=========================================================================
    void push(t key) { list_.insert_head(key); }
    t pop()
    { 
        if (!list_.size()) throw UnderflowError();
        return list_.remove_head(); 
    }
    void clear() { list_.clear(); }

    static bool debug_printing() { return SLList< t >::debug_printing(); }
    static bool debug_printing(bool toggle) 
    { 
        SLList< t >::debug_printing(toggle);
        SLNode< t >::debug_printing(toggle);
        return SLList< t >::debug_printing(); 
    }

    private:
    SLList< t > list_;

};

template < typename t >
std::ostream &operator<<(std::ostream &cout, Stack< t > &stack)
{
    cout << stack.__list__();
    return cout;
}


#endif