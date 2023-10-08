#ifndef KV_LIST_HPP
#define KV_LIST_HPP

#include <iostream>
#include <vector>
#include "MapNode.hpp"

template <class K, class V>
/**
 * @brief KVList class, a class using a linked list to store key-value pairs
 * 
 * @param size
 * @param *head
 */
class KVList {
    public:
        KVList(); 
        KVList(const KVList &); 
        KVList(KVList &&); 
        ~KVList(); 
        V& get(const K) const;
        bool has(const K) const;
        bool hasValue(const V) const;
        int update(const K, const V);
        V remove(const K); 
        void clear(); 
        int getSize() const; 
        MapNode<K,V>* begin() const;
        bool isEmpty() const;
        std::vector<K> getKeys() const;
        std::vector<V> getValues() const;
        V& operator[](const K) const;
        void show() const;
        template <class T, class U>
        friend std::ostream &operator<<(std::ostream &, KVList<T, U> &);
        KVList<K,V>& operator=(const KVList<K,V>&); 
        KVList<K,V>& operator=(KVList<K,V>&&); 
        KVList<K,V>& operator+=(const KVList<K,V>&); 
        template <class T, class U>
        friend KVList<T,U> operator+(const KVList<T,U>&, const KVList<T,U>&); 
        KVList<K,V>& operator-=(const KVList<K,V>&); 
        template <class T, class U>
        friend KVList<T,U> operator-(const KVList<T,U>&, const KVList<T,U>&); 
        KVList<K,V>& operator*=(const KVList<K,V>&); 
        template <class T, class U>
        friend KVList<T,U> operator*(const KVList<T,U>&, const KVList<T,U>&); 
        template <class T, class U>
        friend bool operator==(const KVList<T,U>&, const KVList<T,U>&); 
        template <class T, class U>
        friend bool operator!=(const KVList<T,U>&, const KVList<T,U>&); 

    private:
        int size;
        MapNode<K, V> *head;
};

template <class K, class V>
/**
 * @brief Default constructor for a KVList object.
 */
KVList<K, V>::KVList() {
    this->size = 0;
    this->head = nullptr;
}

template <class K, class V>
/**
 * @brief Copy constructor for a KVList object.
 * 
 * @param other, a const reference to a KVList object.
 */
KVList<K, V>::KVList(const KVList &other) {
    this->size = other.size;
    if (other.begin()) {
        this->head = new MapNode<K, V>(other.head->key, other.head->value);
        MapNode<K, V> *tmp = this->head;
        MapNode<K, V> *tmp2 = other.begin();
        while (tmp2->next) {
            tmp->next = new MapNode<K, V>(tmp2->next->key, tmp2->next->value);
            tmp = tmp->next;
            tmp2 = tmp2->next;
        }
    } else {
        this->head = nullptr;
    }
}

template <class K, class V>
/**
 * @brief Move constructor for a KVList object.
 * 
 * @param other&&, an rvalue reference to a KVList object.
 */
KVList<K, V>::KVList(KVList &&other) {
    this->head = other.head;
    this->size = other.size;
    other.head = nullptr;
    other.size = 0;
}

template <class K, class V>
/**
 * @brief Destructor for a KVList object.
 */
KVList<K,V>::~KVList() {
    while (this->head) {
        MapNode<K, V> *tmp = this->head->next;
        delete this->head;
        this->head = tmp;
    }
}

template <class K,class V>
/**
 * @brief KVList function to get a value given a key.
 * 
 * @param key 
 * @return V& 
 * @throws std::invalid_argument if the key is not found.
 */
V& KVList<K,V>::get(const K key) const{
    MapNode<K, V> *tmp = this->head;
    while (tmp)
    {
        if (key == tmp->key) {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    
    throw std::invalid_argument("Key not found");
}

template <class K, class V>
/**
 * @brief KVList function to check if a key exists in the map.
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool KVList<K,V>::has(const K key) const{
    MapNode<K, V> *tmp = this->head;
    while (tmp)
    {
        if (key == tmp->key) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

template <class K, class V>
/**
 * @brief KVList function to check if a value exists in the map.
 * 
 * @param value
 * @return true 
 * @return false 
 */
bool KVList<K,V>::hasValue(const V value) const{
    MapNode<K, V> *tmp = this->head;
    while (tmp)
    {
        if (value == tmp->value) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

template <class K, class V>
/**
 * @brief KVList function to update a MapNode given a key.
 * 
 * @param key 
 * @param value 
 * @return MapNode<K,V>* 
 */
int KVList<K,V>::update(const K key, const  V value){
    if (this->head) {
        MapNode<K, V> *tmp = head;
        while (tmp) {
            if (key == tmp->key) {
                tmp->value = value;
                return 0;
            } else if (tmp->next) {
                tmp = tmp->next;
            } else
            {
                MapNode<K,V> *n = new MapNode<K, V>(key, value);
                tmp->next = n;
                this->size++;
                return 1;
            }
        }
    }
    MapNode<K, V> *n = new MapNode<K, V>(key, value);
    this->head = n;
    this->size++;
    return 1;
}

template <class K, class V>
/**
 * @brief KVList function to remove a MapNode given a key.
 * 
 * @param key 
 * @return MapNode<K,V>* 
 */
V KVList<K,V>::remove(const K key) {
    MapNode<K,V> *tmp = this->head;
    if (tmp && tmp->next) {
        if (tmp->key == key) {
            this->head = tmp->next;
            this->size--;
            V res = tmp->value;
            delete tmp;
            return res;
        }
    }
    while (tmp->next){
        if (tmp->next->key == key) {
            MapNode<K, V> *n = tmp->next;
            tmp->next = tmp->next->next;
            this->size--;
            V res = tmp->value;
            delete n;
            return res;
        }
    }
    throw std::invalid_argument("No key found.");
}

template <class K, class V>
/**
 * @brief KVList function to clear the map.
 */
void KVList<K,V>::clear() {
    while (this->head) {
        MapNode<K, V> *tmp = this->head->next;
        delete this->head;
        this->head = tmp;
    }
    this->size = 0;
}

template <class K, class V>
/**
 * @brief KVList function to get the size of the map.
 * 
 * @return int 
 */
int KVList<K,V>::getSize() const {
    return this->size;
}

template <class K, class V>
/**
 * @brief KVList function to get the head of the map.
 * 
 * @return MapNode<K,V>* 
 */
MapNode<K,V>* KVList<K,V>::begin() const {
    return this->head;
}

template <class K, class V>
/**
 * @brief Returns true if the List is empty.
 * 
 * @return true 
 * @return false 
 */
bool KVList<K,V>::isEmpty() const{
    return this->head == nullptr;
}

template <class K, class V>
/**
 * @brief Returns all keys in the list.
 * 
 * @return std::vector<K> all keys
 */
std::vector<K> KVList<K,V>::getKeys() const{
    std::vector<K> res = std::vector<K>();
    MapNode<K, V> *tmp = this->head;
    while (tmp)
    {
        res.push_back(tmp->key);
        tmp = tmp->next;
    }
    return res;
}

template <class K, class V>
/**
 * @brief Returns all values in the list.
 * 
 * @return std::vector<V> all values
 */
std::vector<V> KVList<K,V>::getValues() const{
    std::vector<V> res = std::vector<V>();
    MapNode<K, V> *tmp = this->head;
    while (tmp)
    {
        res.push_back(tmp->value);
        tmp = tmp->next;
    }
    return res;
}

template <class K,class V>
/**
 * @brief KVList function to get a value given a key via [] operator.
 * 
 * @param key 
 * @return V& 
 * @throws std::invalid_argument if the key is not found.
 */
V& KVList<K,V>::operator[](const K key) const{
    return this->get(key);
}

template <class K, class V>
/**
 * @brief KVList function to return an ostream object representing the map.
 * 
 * @param o 
 * @param map 
 * @return std::ostream& 
 */
void KVList<K,V>::show() const{
    MapNode<K, V> *tmp = this->head;
    while (tmp) {
        std::cout << "{K: " << tmp->key << ", V: " << tmp->value << "}";
        if (tmp->next) {
            std::cout << ", ";
        }
        tmp = tmp->next;
    }
}

template <class K, class V>
/**
 * @brief KVList function to return an ostream object representing the map.
 * 
 * @param o 
 * @param map 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& o, KVList<K,V>& map){
    MapNode<K, V> *tmp = map.head;
    while (tmp) {
        o << "{K: " << tmp->key << ", V: " << tmp->value << "}";
        if (tmp->next) {
            o << ", ";
        }
        tmp = tmp->next;
    }
    return o;
}

template <class K, class V>
/**
 * @brief KVList function to copy a map using an overloaded assignment operator.
 * 
 * @param other 
 * @return KVList<K,V>& 
 */
KVList<K,V>& KVList<K,V>::operator=(const KVList<K,V>& other) {
    if (this != &other) {
        this->clear();
        this->size = other.size;
        if (other.begin()) {
            this->head = new MapNode<K, V>(other.head->key, other.head->value);
            MapNode<K, V> *tmp = this->head;
            MapNode<K, V> *tmp2 = other.begin();
            while (tmp2->next) {
                tmp->next = new MapNode<K, V>(tmp2->next->key, tmp2->next->value);
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }
        } else {
            this->head = nullptr;
        }
    }
    return *this;
}

template <class K, class V>
/**
 * @brief KVList function to move a map using an overloaded assignment operator.
 * 
 * @param other 
 * @return KVList<K,V>& 
 */
KVList<K,V>& KVList<K,V>::operator=(KVList<K,V>&& other) {
    if (this != &other) {
        this->clear();
        this->head = other.head;
        this->size = other.size;
        other.head = nullptr;
        other.size = 0;
    }
    return *this;
}

template <class K, class V>
/**
 * @brief KVList function to add two maps in place using an overloaded += operator.
 * Note: this function will only compare the keys of the maps, and return the values of the first.
 * 
 * @param other 
 * @return KVList<K,V>& 
 */
KVList<K,V>& KVList<K,V>::operator+=(const KVList<K,V>& other) {
    MapNode<K, V> *tmp = other.begin();
    while (tmp) {
        if (!this->has(tmp->key)){
            this->update(tmp->key, tmp->value);
        }
        tmp = tmp->next;
    }
    return *this;
}

template <class K, class V>
/**
 * @brief KVList function to add two maps using an overloaded + operator.
 * Note: this function will only compare the keys of the maps, and return the values of the first.
 * 
 * @param m1 
 * @param m2 
 * @return KVList<K,V>& 
 */
KVList<K,V> operator+(const KVList<K,V>& m1, const KVList<K,V>& m2) {
    KVList<K, V> tmp = m1;
    tmp += m2;
    return tmp;
}

template <class K, class V>
/**
 * @brief KVList function to subtract two maps in place using an overloaded -= operator.
 * Note: this function will only compare the keys of the maps, and return the values of the first.
 * 
 * @param other 
 * @return KVList<K,V>& 
 */
KVList<K,V>& KVList<K,V>::operator-=(const KVList<K,V>& other) {
    MapNode<K, V> *tmp = other.begin();
    while (tmp) {
        this->remove(tmp->key);
        tmp = tmp->next;
    }
    return *this;
}

template <class K, class V>
/**
 * @brief KVList function to subtract two maps using an overloaded - operator.
 * Note: this function will only compare the keys of the maps, and return the values of the first.
 * 
 * @param m1 
 * @param m2 
 * @return KVList<K,V>& 
 */
KVList<K,V> operator-(const KVList<K,V>& m1, const KVList<K,V>& m2) {
    KVList<K, V> tmp = m1;
    tmp -= m2;
    return tmp;
}

template <class K, class V>
/**
 * @brief KVList function to get the intersection of two maps in place using an overloaded *= operator.
 * Note: this function will only compare the keys of the maps, and return the values of the first.
 * 
 * @param other 
 * @return KVList<K,V>& 
 */
KVList<K,V>& KVList<K,V>::operator*=(const KVList<K,V>& other){
    MapNode<K, V> *tmp = this->begin();
    while (tmp) {
        if (!other.has(tmp->key)) {
            this->remove(tmp->key);
        }
        tmp = tmp->next;
    }
    return *this;
}

template <class K, class V>
/**
 * @brief KVList function to get the intersection of two maps using an overloaded * operator.
 * Note: this function will only compare the keys of the maps, and return the values of the first.
 * 
 * @param m1 
 * @param m2 
 * @return KVList<K,V>& 
 */
KVList<K,V> operator*(const KVList<K,V>& m1, const KVList<K,V>& m2) {
    KVList<K, V> tmp = m1;
    tmp *= m2;
    return tmp;
}

template <class K, class V>
/**
 * @brief KVList function to check if two maps are equal using an overloaded == operator.
 * 
 * @param other 
 * @return KVList<K,V>& 
 */
bool operator==(const KVList<K,V>& m1, const KVList<K,V>& m2) {
    if (m1.size != m2.size) {
        return false;
    }
    MapNode<K, V> *tmp = m1.begin();
    while (tmp) {
        if (!m2.has(tmp->key)) {
            return false;
        } else if (m2.get(tmp->key) != tmp->value) {
            return false;
        }
        tmp = tmp->next;
    }
    return true;
}


template <class K, class V>
/**
 * @brief KVList function to check if two maps are not equal using an overloaded != operator.
 * 
 * @param other 
 * @return KVList<K,V>& 
 */
bool operator!=(const KVList<K,V>& m1, const KVList<K,V>& m2) {
    return !(m1 == m2);
}

#endif