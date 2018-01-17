#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include "../dictionary.h"
#include <iostream>
template<typename K>
using HashFunction = unsigned int (*)(const K&);

template<typename K, typename V>
class HashMapIterator;

template <typename K, typename V>
class HashMap : public Dictionary<K, V>
{
    friend class HashMapIterator<K,V>;
    public:
  using Bucket = std::vector<KeyValuePair<K,V>>;

        HashMap(HashFunction<K> hash, int capacity = 10)
        :size(0), capacity(capacity), hashFunction(hash) {
            buckets.resize(capacity, Bucket());
        }
        virtual ~HashMap() { }

  // търсене на стойност по ключ
  virtual V* lookup(K const& key) {
    unsigned int keyHash = hashFunction(key) % capacity;
    for (auto& entry : buckets[keyHash]) {
        if (entry.key() == key) {
            return &(entry.value());
        }
    }
    return nullptr;
  }

  // добавяне на връзка (ключ, стойност)
  virtual bool add(K const& key, V const& value) {
      ensureCapacity(size+1);
      unsigned int keyHash = hashFunction(key) % capacity;
      for (auto const& entry : buckets[keyHash]) {
        // entry KeyValuePair
        if (entry.key() == key) {
            return false;
        }
      }
      buckets[keyHash].push_back(KeyValuePair<K,V>(key, value));
      size++;
      return true;
  }

  // изтриване на ключ и стойността, свързана с него
  virtual bool remove(K const& key) {
    unsigned int keyHash = hashFunction(key) % capacity;
    for (auto it = buckets[keyHash].begin(); it != buckets[keyHash].end(); ++it) {
        if (it->key() == key) {
            buckets[keyHash].erase(it);
            size--;
            return true;
        }
    }
    return false;
  }

  // списък от ключове
  virtual std::vector<K> keys() {
      std::vector<K> result;
      for (auto const& bucket : buckets) {
        for (auto const& entry : bucket) {
            result.push_back(entry.key());
        }
      }
      return result;
  }

  // списък от стойности
  virtual std::vector<V> values() {
      std::vector<K> result;
      for (auto const& bucket : buckets) {
        for (auto const& entry : bucket) {
            result.push_back(entry.value());
        }
      }
      return result;
  }

  float efficiency() const {
      int collisions = 0;
      for (auto const& bucket: buckets) {
          if (bucket.size() > 1) {
            collisions += bucket.size() - 1;
          }
      }
      return (size - collisions)/(float)size;
  }

  HashMapIterator<K,V> begin() {
      return HashMapIterator<K,V>(*this);
  }
  HashMapIterator<K, V> end() {
      return HashMapIterator<K,V>(*this, true);

  }
    protected:

    private:
        std::vector<Bucket> buckets;
        int size;
        int capacity;
        HashFunction<K> hashFunction;

    public:
        void ensureCapacity(int newSize) {
            if (newSize < capacity) {
                return;
            }
            int newCapacity = capacity;
            do {
                newCapacity *= 2;
            }
            while (newCapacity < newSize);

            std::cout<<"Resizing hashmap to " << newCapacity << std::endl;
            std::vector<Bucket> updated(newCapacity, Bucket());
            for (auto const& bucket: buckets) {
                for (auto const& entry: bucket) {
                    int newHash = hashFunction(entry.key()) % newCapacity;
                    updated[newHash].push_back(entry);
                }
            }
            buckets = std::move(updated);
            this->capacity = newCapacity;
        }
};

template <typename K, typename V>
class HashMapIterator {
    friend class HashMap<K,V>;
private:
    const HashMap<K,V>& map;
    int bucketIndex;
    int entryIndex;
    HashMapIterator(const HashMap<K, V>& map, bool isEnd=false)
        :map(map) {
        if (isEnd) {
            bucketIndex = map.buckets.size();
            entryIndex = 0;
        } else {
            bucketIndex = -1;
            entryIndex = 0;
            nextBucket();
        }
    }
    void nextBucket() {
        do {
            bucketIndex++;
        } while(bucketIndex < map.buckets.size() &&
                map.buckets[bucketIndex].empty());
    }

public:
    bool end() {
        return bucketIndex >= map.buckets.size();
    }
    bool operator!=(const HashMapIterator<K, V>& other) {
        return bucketIndex != other.bucketIndex ||
                entryIndex != other.entryIndex;
    }
    bool operator==(const HashMapIterator<K, V> & other) {
        return !(*this != other);
    }

    const KeyValuePair<K,V>& operator*() {
        return map.buckets[bucketIndex][entryIndex];
    }
    HashMapIterator<K, V>& operator++() {
        if (end()) {
            return *this;
        }
        if (entryIndex + 1 < map.buckets[bucketIndex].size()) {
            entryIndex++;
        } else {
            nextBucket();
            entryIndex = 0;
        }
        return *this;
    }

};

#endif // HASHMAP_H











