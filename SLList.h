#ifndef SLLIST_H
#define SLLIST_H
#include "SLNode.h"

class IndexError
{};

class ValueError
{};

template < typename t >
class SLList
{
    public:
    SLList()
    : phead_(NULL)
    {}

    SLNode< t > *phead() const { return phead_; }

    //=========================================================================
    // reference methods
    //=========================================================================
    t &front()      { return phead_->key(); }
    t front() const { return phead_->key(); }

    t &back()
    {
        SLNode< t > *temp = phead_;
        while(temp->get_next() != NULL)
        {
            temp = temp->get_next();
        }
        return temp->key();
    }

    t back() const 
    {

        SLNode< t > *temp = phead_;
        while(temp->get_next() != NULL)
        {
            temp = temp->get_next();
        }
        return temp->key();
    }

    //=========================================================================
    // Information Methods
    //=========================================================================
    int size() const
    {
        SLNode< t > *node = phead_;
        int count = 0;

        while(node != 0)
        {
            ++count;
            node = node->get_next();
        }

        return count;
    }

    SLNode< t > *find(t key) const
    {
        SLNode< t > *temp = phead_;

        while (temp != NULL)
        {
            if (temp->get_key() == key)
            return temp;
            temp = temp->get_next();
        }
        return temp;
    }

    bool is_empty()
    {
        if (phead_ == NULL) return true;
        else return false;
    }

    //=========================================================================
    // List mutators
    //=========================================================================
    
    // adders
    void insert_head(t key)
    {
        phead_ = new SLNode< t >(key, phead_);
    }

    void insert_tail(t key)
    {
        SLNode< t > *temp = phead_;

        if (phead_ == NULL)
        {
            insert_head(key);
            return;
        }

        while (temp->get_next() != NULL)
        {
            temp = temp->get_next();
        }
        
        SLNode< t > *newnode = new SLNode< t >(key);
        temp->set_next(newnode);
    }

    void insert_before(SLNode< t > *node, t key)
    {
        SLNode< t > *prev = NULL;
        SLNode< t > *temp = phead_;

        while (temp != NULL)
        {
            if (temp == node)
            {
                prev->set_next(new SLNode< t >(key));
                prev->get_next()->set_next(temp);
                return;
            }
            else
            {
                prev = temp;
                temp = temp->get_next();
            }
        }
    }

    void insert_after(SLNode< t > *node, t key)
    {
        SLNode< t > *temp = phead_;

        while (temp != NULL)
        {
            if (temp == node)
            {
                SLNode< t > *n = new SLNode< t >(key);
                n->set_next(temp->get_next());
                temp->set_next(n);
                return;
            }
            else
            {
                temp = temp->get_next();
            }
        }
    }

    // removers
    t remove_head()
    {
        SLNode< t > *temp = phead_;

        t ret = phead_->get_key();
        phead_ = phead_->get_next();

        delete temp;

        return ret;
    }

    t remove_tail()
    {
        SLNode< t > *prev = NULL;
        SLNode< t > *temp = phead_;

        while (temp->get_next() != NULL)
        {
            prev = temp;
            temp = temp->get_next();
        }

        prev->set_next(NULL);
        t ret = temp->get_key();

        delete temp;

        return ret;
    }    

    t remove(SLNode< t > *node)
    {
        SLNode< t > *prev = NULL;
        SLNode< t > *temp = phead_;

        if (node == NULL) throw ValueError();

        while (temp != NULL)
        {
            if (phead_ == node)
            {
                t ret = temp->get_key();
                phead_ = phead_->get_next();
                delete temp;
                
                return ret;
            }
            else if (temp == node)
            {
                prev->set_next(temp->get_next());
                t ret = temp->get_key();
                delete temp;
                return ret;
            }
            else
            {
                prev = temp;
                temp = temp->get_next();
            }
        }
        
        throw ValueError();
        
    }

    t remove(t key)
    {
        SLNode< t > *prev = NULL;
        SLNode< t > *temp = phead_;

        while (temp != NULL)
        {
            if (phead_->get_key() == key)
            {
                t ret = temp->get_key();
                phead_ = phead_->get_next();
                delete temp;
                
                return ret;
            }
            else if (temp->get_key() == key)
            {
                prev->set_next(temp->get_next());
                t ret = temp->get_key();
                delete temp;
                return ret;
            }
            else
            {
                prev = temp;
                temp = temp->get_next();
            }
        }
        throw ValueError();
    }

    void clear()
    {
        SLNode< t > *temp = phead_;
        while (temp != NULL)
        {
            temp = phead_->get_next();
            delete phead_;
            phead_ = temp;
        }
    }

    //=========================================================================
    // Operator Overloads
    //=========================================================================

    t &operator[](int pos)
    {
        if (pos < 0) throw IndexError();
        
        SLNode< t > *node = phead_;
        int count = 0;

        while(node != NULL)
        {
            if (count == pos)
            {
                return node->key();
            }

            ++count;
            node = node->get_next();
        }

        throw IndexError();
    }

    bool operator==(const SLList< t > &list)
    {
        SLNode< t > *local_temp = phead_;
        SLNode< t > *forgn_temp = list.phead();
        
        while(local_temp != NULL && forgn_temp != NULL)
        {
            if ((local_temp->get_next() != NULL &&
                 forgn_temp->get_next() == NULL) ||
                (local_temp->get_next() == NULL &&
                 forgn_temp->get_next() != NULL) ||
                 local_temp->get_key() != forgn_temp->get_key())
            return false;

            local_temp = local_temp->get_next();
            forgn_temp = forgn_temp->get_next();
        }
        return true;
    }

    bool operator!=(SLList< t > &list)
    {
        if (list == *this) return false;
        return true;
    }
    
    //=========================================================================
    // Debug printing control
    //=========================================================================
    static bool debug_printing() { return debug_print; }
    static bool debug_printing(bool toggle) 
    { 
        debug_print = toggle; 
        return debug_print; 
    }

    private:
    SLNode < t > *phead_;
    static bool debug_print;
};

//=============================================================================
// Initialize Static members
//=============================================================================
template <typename t >
bool SLList< t >::debug_print(false);

//=============================================================================
// Non-member operator overloads
//=============================================================================
template < typename t >
std::ostream &operator<<(std::ostream &cout, SLList< t > &list)
{
    if (SLList< t >::debug_printing())
    {
        cout << "<SLList " << &list << " phead:" << list.phead() << std::endl;
        SLNode< t > *temp = list.phead();
        while(temp != NULL)
        {
            cout << "    " << *temp << std::endl;
            temp = temp->get_next();
        }
        cout << '>' << std::endl;
    }
    else
    {
        cout << '[';
        SLNode< t > *temp = list.phead();
        while(temp != NULL)
        {
            cout << temp->get_key();
            if (temp->get_next() != NULL)
            cout << ", ";
            temp = temp->get_next();
        }
        cout << ']';
    }
    
    return cout;
}


#endif