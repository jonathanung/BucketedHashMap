#ifndef MAP_NODE_HPP
#define MAP_NODE_HPP

template <class K, class V>
/**
 * @brief A node class that stores key-value pairs and implements an std::cout function.
 * 
 * @author Jonathan Ung
 */
class MapNode{
    public:
        K key;
        V value;
        MapNode *next;
        MapNode(K, V);
        MapNode(K, V, MapNode *);
        ~MapNode() {}
        template <class T, class U>
        friend std::ostream &operator<<(std::ostream &, const MapNode<T,U> &);
};

template <class K, class V>
/**
 * @brief Construct a new Map Node< K, V>:: Map Node object
 * 
 * @param k 
 * @param v 
 */
MapNode<K,V>::MapNode(K k, V v) {
    this->key = k;
    this->value = v;
    this->next = nullptr;
}

template <class K, class V>
/**
 * @brief Construct a new Map Node< K, V>:: Map Node object
 * 
 * @param k 
 * @param v 
 * @param mN 
 */
MapNode<K,V>::MapNode(K k, V v, MapNode* mN) {
    this->key = k;
    this->value = v;
    this->next = mN;
}

template <class K, class V>
/**
 * @brief ostream function for MapNode Object
 * 
 * @param o 
 * @param mN 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& o, MapNode<K,V> mN) {
    o << "{K: " << mN->key << ", V: " << mN->value << "}";
    return o;
}

#endif