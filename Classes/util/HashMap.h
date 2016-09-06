/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#define USE_STD_UNORDERED_HASHMAP 1

#include "ccMacros.h"
#include <vector>

#if USE_STD_UNORDERED_HASHMAP
#include <unordered_map>
#else
#include <map>
#endif

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{ddddddddddddddddddd
 */

template <class K, class V>
class CC_DLL HashMap
{
public:
    // ------------------------------------------
    // Iterators
    // ------------------------------------------
#if USE_STD_UNORDERED_HASHMAP
    typedef std::unordered_map<K, V> RefMap;
#else
    typedef std::map<K, V> RefMap;
#endif
    
    typedef typename RefMap::iterator iterator;
    typedef typename RefMap::const_iterator const_iterator;
    
    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    
    const_iterator cbegin() const { return _data.cbegin(); }
    const_iterator cend() const { return _data.cend(); }
    
    /** Default constructor */
    HashMap<K, V>()
    : _data()
    {

    }
    
    /** Contructor with capacity */
    explicit HashMap<K, V>(ssize_t capacity)
    : _data()
    {
        _data.reserve(capacity);
    }
    
    /** Copy constructor */
    HashMap<K, V>(const HashMap<K, V>& other)
    {
        _data = other._data;
        addRefForAllObjects();
    }
    
    /** Move constructor */
    HashMap<K, V>(HashMap<K, V>&& other)
    {
        _data = std::move(other._data);
    }
    
    /** Destructor
     *  It will release all objects in map.
     */
    ~HashMap<K, V>()
    {
        clear();
    }
    
    /** Sets capacity of the map */
    void reserve(ssize_t capacity)
    {
#if USE_STD_UNORDERED_HASHMAP
        _data.reserve(capacity);
#endif
    }
    
    /** Returns the number of buckets in the HashMap container. */
    ssize_t bucketCount() const
    {
#if USE_STD_UNORDERED_HASHMAP
        return _data.bucket_count();
#else
        return 0;
#endif
    }
    
    /** Returns the number of elements in bucket n. */
    ssize_t bucketSize(ssize_t n) const
    {
#if USE_STD_UNORDERED_HASHMAP
        return _data.bucket_size(n);
#else
        return 0;
#endif
    }
    
    /** Returns the bucket number where the element with key k is located. */
    ssize_t bucket(const K& k) const
    {
#if USE_STD_UNORDERED_HASHMAP
        return _data.bucket(k);
#else
        return 0;
#endif
    }
    
    /** The number of elements in the HashMap. */
    ssize_t size() const
    {
        return _data.size();
    }
    
    /** Returns a bool value indicating whether the HashMap container is empty, i.e. whether its size is 0.
     *  @note This function does not modify the content of the container in any way.
     *        To clear the content of an array object, member function unordered_HashMap::clear exists.
     */
    bool empty() const
    {
        return _data.empty();
    }
    
    /** Returns all keys in the HashMap */
    std::vector<K> keys() const
    {
        std::vector<K> keys;

        if (!_data.empty())
        {
            keys.reserve(_data.size());
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                keys.push_back(iter->first);
            }
        }
        return keys;
    }
    
    /** Returns all keys that matches the object */
    std::vector<K> keys(V object) const
    {
        std::vector<K> keys;
        
        if (!_data.empty())
        {
            keys.reserve(_data.size() / 10);
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                if (iter->second == object)
                {
                    keys.push_back(iter->first);
                }
            }
        }
        
        keys.shrink_to_fit();
        
        return keys;
    }
    
    /** @brief Returns a reference to the HashMapped value of the element with key k in the HashMap.
     *  @note If key does not match the key of any element in the container, the function return nullptr.
     *  @param key Key value of the element whose HashMapped value is accessed.
     *       Member type K is the keys for the elements in the container. defined in HashMap<K, V> as an alias of its first template parameter (Key).
     */
	    const V at(const K& key) const
	{
	auto iter = _data.find(key);
	if (iter != _data.end())
	return iter->second;
	V v;
	return v;
	}
    
    V at(const K& key)
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
		V v;
        return v;
    }
    
    /** @brief Searches the container for an element with 'key' as key and returns an iterator to it if found,
     *         otherwise it returns an iterator to HashMap<K, V>::end (the element past the end of the container).
     *  @param key Key to be searched for.
     *         Member type 'K' is the type of the keys for the elements in the container,
     *         defined in HashMap<K, V> as an alias of its first template parameter (Key).
     *
     */
    const_iterator find(const K& key) const
    {
        return _data.find(key);
    }

	bool containKey(const K& key){
		auto iter=_data.find(key);
		if (iter!=_data.end())
		{
			return true;
		}
		return false;
	}
    
    iterator find(const K& key)
    {
        return _data.find(key);
    }
    
    /** @brief Inserts new elements in the HashMap.
     *  @note If the container has already contained the key, this function will erase the old pair(key, object)  and insert the new pair.
     *  @param key The key to be inserted.
     *  @param object The object to be inserted.
     */
    void insert(const K& key, V object)
    {
        erase(key);
        _data.insert(std::make_pair(key, object));
    }
    
    /** @brief Removes an element with an iterator from the HashMap<K, V> container.
     *  @param position Iterator pointing to a single element to be removed from the HashMap<K, V>.
     *         Member type const_iterator is a forward iterator type.
     */
    iterator erase(const_iterator position)
    {
        return _data.erase(position);
    }
    
    /** @brief Removes an element with an iterator from the HashMap<K, V> container.
     *  @param k Key of the element to be erased.
     *         Member type 'K' is the type of the keys for the elements in the container,
     *         defined in HashMap<K, V> as an alias of its first template parameter (Key).
     */
    size_t erase(const K& k)
    {
        auto iter = _data.find(k);
        if (iter != _data.end())
        {
            _data.erase(iter);
            return 1;
        }
        
        return 0;
    }
    
    /** @brief Removes some elements with a vector which contains keys in the HashMap.
     *  @param keys Keys of elements to be erased.
     */
    void erase(const std::vector<K>& keys)
    {
        for(const auto &key : keys) {
            this->erase(key);
        }
    }
    
    /** All the elements in the HashMap<K,V> container are dropped:
     *  their reference count will be decreased, and they are removed from the container,
     *  leaving it with a size of 0.
     */
    void clear()
    {
        for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
        {

        }
        
        _data.clear();
    }
    
    /** @brief Gets a random object in the HashMap
     *  @return Returns the random object if the HashMap isn't empty, otherwise it returns nullptr.
     */
    V getRandomObject() const
    {
        if (!_data.empty())
        {
            ssize_t randIdx = rand() % _data.size();
            const_iterator randIter = _data.begin();
            std::advance(randIter , randIdx);
            return randIter->second;
        }
        return nullptr;
    }
    
    // Don't uses operator since we could not decide whether it needs 'retain'/'release'.
    //    V& operator[] ( const K& key )
    //    {
    //        CCLOG("copy: [] ref");
    //        return _data[key];
    //    }
    //
    //    V& operator[] ( K&& key )
    //    {
    //        CCLOG("move [] ref");
    //        return _data[key];
    //    }
    
    //    const V& operator[] ( const K& key ) const
    //    {
    //        CCLOG("const copy []");
    //        return _data.at(key);
    //    }
    //
    //    const V& operator[] ( K&& key ) const
    //    {
    //        CCLOG("const move []");
    //        return _data.at(key);
    //    }
    
    /** Copy assignment operator */
    HashMap<K, V>& operator= ( const HashMap<K, V>& other )
    {
        if (this != &other) {
            CCLOGINFO("In the copy assignment operator of HashMap!");
            clear();
            _data = other._data;
            addRefForAllObjects();
        }
        return *this;
    }
    
    /** Move assignment operator */
    HashMap<K, V>& operator= ( HashMap<K, V>&& other )
    {
        if (this != &other) {
            CCLOGINFO("In the move assignment operator of HashMap!");
            clear();
            _data = std::move(other._data);
        }
        return *this;
    }
    
protected:
    
    /** Retains all the objects in the map */
    void addRefForAllObjects()
    {
        for (auto iter = _data.begin(); iter != _data.end(); ++iter)
        {

        }
    }
    
    RefMap _data;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCMAP_H__ */
