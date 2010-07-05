#ifndef RADIX_TREE_NODE_HPP
#define RADIX_TREE_NODE_HPP

#include <map>

namespace dnn {

template <typename K, typename T>
class radix_tree_node {
        friend class radix_tree<K, T>;
        friend class radix_tree_it<K, T>;

        typedef std::pair<const K, T> value_type;
        typedef typename std::map<K, radix_tree_node<K, T>* >::iterator it_child;

private:
        radix_tree_node() : m_parent(NULL), m_value(NULL), m_depth(0),
                            m_is_leaf(false) { }
        radix_tree_node(const value_type &val);

        ~radix_tree_node();

        std::map<K, radix_tree_node<K, T>*> m_children;
        radix_tree_node<K, T> *m_parent;
        value_type *m_value;
        int         m_depth;
        bool        m_is_leaf;
        K           m_key;
};

template <typename K, typename T>
radix_tree_node<K, T>::radix_tree_node(const value_type &val) : m_parent(NULL),
                                                                m_depth(0),
                                                                m_is_leaf(false)
{
        m_value = new value_type(val);
}

template <typename K, typename T>
radix_tree_node<K, T>::~radix_tree_node()
{
        it_child it;

        for (it = m_children.begin(); it != m_children.end(); ++it) {
                delete it->second;
        }

        delete m_value;
}

}

#endif // RADIX_TREE_NODE_HPP
