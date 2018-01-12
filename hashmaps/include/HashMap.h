#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include "../dictionary.h"

template<typename K>
using HashFunction = unsigned int (*)(const K&);

template <typename K, typename V>
class HashMap : public Dictionary<K, V>
{
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

    protected:

    private:
        std::vector<Bucket> buckets;
        int size;
        int capacity;
        HashFunction<K> hashFunction;
};

#endif // HASHMAP_H











