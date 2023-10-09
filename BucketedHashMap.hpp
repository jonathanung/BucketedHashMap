#ifndef BUCKETED_HASH_MAP_HPP
#define BUCKETED_HASH_MAP_HPP

#include <iostream>
#include <functional>
#include "KVList.hpp"

template <class K, class V>
/**
 * @brief A hash map class which uses buckets, in the form of KVLists to 
 * deal with hashing collision.
 * 
 * @author Jonathan Ung
 */
class BucketedHashMap {
    private: 
        size_t size;
        size_t capacity;
        double loadFactorThreshold;
        std::vector<KVList<K, V>> table;

    public:
        unsigned int getVectorIndex(const K) const;
        BucketedHashMap();
        BucketedHashMap(int);
        BucketedHashMap(double);
        BucketedHashMap(int, double);
        ~BucketedHashMap(){}
        void clear();
        bool containsKey(const K) const;
        bool containsValue(const V) const;
        V& get(const K) const;
        V& operator[](const K) const;
        bool isEmpty() const;
        void insert(const K, const V);
        V remove(const K);
        int getSize() const;
        std::vector<MapNode<K,V>> getEntries() const;
        std::vector<K> getKeys() const;
        std::vector<V> getValues() const;
        void show() const;
        template <class T, class U>
        friend std::ostream &operator<<(std::ostream &, const BucketedHashMap<T,U> &);
        void showStructure() const;
        void reHash();
};

template <class K, class V>
/**
 * @brief Get the unsigned int vector index via hashing
 * 
 * @param key 
 * @param bHM 
 * @return unsigned int 
 */
unsigned int BucketedHashMap<K,V>::getVectorIndex(const K key) const{
    return (std::hash<K>()(key)%this->capacity);
}

template <class K, class V>
/**
 * @brief Construct a new Bucketed Hash Map< K, V>:: Bucketed Hash Map object
 * 
 */
BucketedHashMap<K,V>::BucketedHashMap() {
    this->size = 0;
    this->table = std::vector<KVList<K,V>>(10, KVList<K,V>());
    this->loadFactorThreshold = 1;
    this->capacity = this->table.size();
}

template <class K, class V>
/**
 * @brief Construct a new Bucketed Hash Map< K, V>:: Bucketed Hash Map object
 * 
 * @param cap 
 */
BucketedHashMap<K,V>::BucketedHashMap(int cap) {
    if (cap < 1) {
        throw std::invalid_argument("Capacity must be larger than 0!");
    }
    this->size = 0;
    this->table = std::vector<KVList<K,V>>(cap, KVList<K,V>());
    this->loadFactorThreshold = 1;
    this->capacity = this->table.size();
}

template <class K, class V>
/**
 * @brief Construct a new Bucketed Hash Map< K, V>:: Bucketed Hash Map object
 * 
 * @param cap 
 */
BucketedHashMap<K,V>::BucketedHashMap(double lFT) {
    if (lFT < 0.1 || lFT > 1.0) {
        throw std::invalid_argument("Load factor cannot be greater than 1.0 and cannot be less than 0.1!");
    }
    this->size = 0;
    this->table = std::vector<KVList<K,V>>(10, KVList<K,V>());
    this->loadFactorThreshold = lFT;
    this->capacity = this->table.size();
}

template <class K, class V>
/**
 * @brief Construct a new Bucketed Hash Map< K, V>:: Bucketed Hash Map object
 * 
 * @param cap 
 */
BucketedHashMap<K,V>::BucketedHashMap(int cap, double lFT) {
    if (lFT < 0.1 || lFT > 1.0) {
        throw std::invalid_argument("Load factor cannot be greater than 1.0 and cannot be less than 0.1!");
    }
    if (cap < 1) {
        throw std::invalid_argument("Capacity must be larger than 0!");
    }
    this->size = 0;
    this->table = std::vector<KVList<K,V>>(cap, KVList<K,V>());
    this->loadFactorThreshold = lFT;
    this->capacity = this->table.size();
}

template <class K, class V>
/**
 * @brief clears the hash map vector
 * 
 */
void BucketedHashMap<K,V>::clear() {
    for (int i = 0; i < this->capacity; i++) {
        this->table[i].clear();
    }
}

template <class K, class V>
/**
 * @brief Returns whether or not the hashmap contains the passed in key
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool BucketedHashMap<K,V>::containsKey(const K key) const {
    return this->table[this->getVectorIndex(key)].has(key);
}

template <class K, class V>
/**
 * @brief Returns whether or not the hashmap contains the passed in value
 * 
 * @param value 
 * @return true 
 * @return false 
 */
bool BucketedHashMap<K,V>::containsValue(const V value) const {
    for (int i = 0; i < this->capacity; i++) {
        if (this->table[i].hasValue(value)) {
            return true;
        }
    }
    return false;
}

template <class K, class V>
/**
 * @brief Returns the reference to the value paired to the given key
 * 
 * @param key 
 * @return V& 
 */
V& BucketedHashMap<K,V>::get(const K key) const {
    return this->table[this->getVectorIndex(key)].get(key);
}

template <class K, class V>
/**
 * @brief Returns the reference to the value paired to the given key
 * 
 * @param key 
 * @return V& 
 */
V& BucketedHashMap<K,V>::operator[](const K key) const {
    return this->get(key);
}

template <class K, class V>
/**
 * @brief Returns whether or not the map is empty.
 * 
 * @return true 
 * @return false 
 */
bool BucketedHashMap<K,V>::isEmpty() const {
    return this->size == 0;
}

template <class K, class V>
/**
 * @brief inserts a key-value pair into the map
 * 
 * @param key 
 * @param value 
 */
void BucketedHashMap<K,V>::insert(const K key, const V value) {
    if (((double)this->size/(double)this->capacity) >= this->loadFactorThreshold) {
        this->reHash();
    }
    this->size += this->table[this->getVectorIndex(key)].update(key, value);
}

template <class K, class V>
/**
 * @brief removes the given key and value node from the map
 * 
 * @param key 
 * @return V 
 */
V BucketedHashMap<K,V>::remove(const K key) {
    this->size--;
    return this->table[this->getVectorIndex(key)].remove(key);
}

template <class K, class V>
/**
 * @brief returns the size of the map
 * 
 * @return int 
 */
int BucketedHashMap<K,V>::getSize() const {
    return this->size;
}

template <class K, class V>
/**
 * @brief returns all entries in the map in a vector
 * 
 * @return std::vector<MapNode<K,V>> 
 */
std::vector<MapNode<K,V>> BucketedHashMap<K,V>::getEntries() const {
    std::vector<K> keys = this->getKeys();
    std::vector<V> values = this->getValues();
    std::vector<MapNode<K,V>> res = std::vector<MapNode<K,V>>();
    for (int i = 0; i < this->size; i++) {
        res.push_back(MapNode<K,V>(keys[i], values[i]));
    }
    return res;
}

template <class K, class V>
/**
 * @brief returns all keys in the map in a vector
 * 
 * @return std::vector<K> 
 */
std::vector<K> BucketedHashMap<K,V>::getKeys() const{
    std::vector<K> res = std::vector<K>();
    for (int i = 0; i < this->capacity; i++) {
        std::vector<K> tmpV = this->table[i].getKeys();
        for (int j = 0; j < tmpV.size(); j++)
        {
            res.push_back(tmpV[j]);
        }
    }
    return res;
}

template <class K, class V>
/**
 * @brief returns all values in the map in a vector
 * 
 * @return std::vector<V> 
 */
std::vector<V> BucketedHashMap<K,V>::getValues() const{
    std::vector<V> res = std::vector<V>();
    for (int i = 0; i < this->capacity; i++) {
        std::vector<V> tmpV = this->table[i].getValues();
        for (int j = 0; j < tmpV.size(); j++)
        {
            res.push_back(tmpV[j]);
        }
    }
    return res;
}

template <class K, class V>
/**
 * @brief prints the map
 * 
 */
void BucketedHashMap<K,V>::show() const{
    std::vector<MapNode<K,V>> entries = this->getEntries();
    std::cout << "Bucketed Hash Map Entries: [ " << std::endl;
    for (int i = 0; i < this->size; i++)
    {
        std::cout << "    " << "{K: " << entries[i].key << ", V: " << entries[i].value << "}";
        if (i < this->size-1) {
            std::cout << ",";
        }
        std::cout << std::endl;
    }
    std::cout << "]" << std::endl;
}

template <class K, class V>
/**
 * @brief returns an ostream representation of the map
 * 
 * @param o 
 * @param bHM 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& o, BucketedHashMap<K,V> & bHM) {
    std::vector<MapNode<K,V>> entries = bHM.getEntries();
    o << "Bucketed Hash Map Entries: [ " << std::endl;
    for (int i = 0; i < bHM.getSize(); i++)
    {
        o << "    " << "{K: " << entries[i].key << ", V: " << entries[i].value << "}";
        if (i < bHM.getSize()-1) {
            o << ",";
        }
        o << std::endl;
    }
    o << "]" << std::endl;
    return o;
}

template <class K, class V>
/**
 * @brief prints the list + structure
 * 
 */
void BucketedHashMap<K,V>::showStructure() const{
    std::cout << "Bucketed Hash Map Structure: < " << std::endl;
    for (int i = 0; i < this->capacity; i++) {
        std::cout << "    Bucket at index " << i << ": ";
        this->table[i].show();
        std::cout << std::endl;
    }
    std::cout << ">" << std::endl;
}

template <class K, class V>
/**
 * @brief rehashes ahd resizes the hashmap
 * 
 */
void BucketedHashMap<K,V>::reHash() {
    std::vector<MapNode<K,V>> entries = this->getEntries();
    this->capacity = this->capacity * 2;
    this->table = std::vector<KVList<K, V>>(this->capacity, KVList<K,V>());
    this->size = 0;
    for (int i = 0; i < entries.size(); i++)
    {
        this->insert(entries[i].key, entries[i].value);
    }
}

#endif