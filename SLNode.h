#ifndef SLNODE_H
#define SLNODE_H

#include <iostream>

template < typename t >
class SLNode
{
public:
    SLNode(const t &key, SLNode *next=NULL)
    : key_(key), next_(next)
    {}

    //debug print control
    static bool debug_printing() { return debug_print; }
    static bool debug_printing(bool toggle) 
    { 
        debug_print = toggle; 
        return debug_print; 
    }
    
    //get methods
    t get_key() const { return key_; }
    SLNode *get_next() { return next_;}

    //refrence methods for Key
    t key() const { return key_; }
    t &key() { return key_; }

    //set methods
    void set_key(t new_key) { key_ = new_key; }
    void set_next(SLNode *node) { next_ = node; }

    private:
    t key_;
    SLNode *next_;
    static bool debug_print;
};

template < typename t >
bool SLNode< t >::debug_print(false);

template < typename t >
std::ostream &operator<<(std::ostream &cout, SLNode< t > &node)
{
    if (SLNode< t >::debug_printing())
    {
        cout << "<SLNode " << &node << " key:" << node.get_key() 
             << ", next:" << node.get_next() 
             //<< " size_of: " << sizeof(node)
             <<'>';
    }
    else 
    {
        cout << node.get_key();
    }
    return cout;
}


#endif