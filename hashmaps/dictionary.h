#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <vector>
#include <utility>

template <typename K, typename V>
class Dictionary {
public:

  // d[k] = v;
  // std::cout << d[k];
  // ���� ������ ��� �������, �� k �� ��� � d
  V& operator[](K const& key) {
    V* pv = lookup(key);
    if (pv)
      // ��� ���� ��� ��������, ������� ���� ���������
      return *pv;
    // �����, ������ �� ���� ��������� ��� �������� �� ������������
    add(key, V());
    // � � �������
    return *lookup(key);
  }

  // ������� �� �������� �� ����
  virtual V* lookup(K const&) = 0;

  // �������� �� ������ (����, ��������)
  virtual bool add(K const&, V const&) = 0;

  // ��������� �� ���� � ����������, �������� � ����
  virtual bool remove(K const&) = 0;

  // ������ �� �������
  virtual std::vector<K> keys() = 0;

  // ������ �� ���������
  virtual std::vector<V> values() = 0;

  virtual ~Dictionary() {}
};

template <typename K, typename V>
class KeyValuePair : public std::pair<K, V> {
public:

  KeyValuePair(K const& k = K(), V const& v = V()) : std::pair<K, V>(k, v) {}

  K& key()   { return std::pair<K,V>::first; }
  V& value() { return std::pair<K,V>::second; }

  K const& key()   const { return std::pair<K,V>::first; }
  V const& value() const { return std::pair<K,V>::second; }

  bool operator<(KeyValuePair const& kvp) const {
    return key() < kvp.key();
  }

  bool operator>(KeyValuePair const& kvp) const {
    return key() > kvp.key();
  }

  bool operator>=(KeyValuePair const& kvp) const {
    return key() >= kvp.key();
  }
  bool operator<=(KeyValuePair const& kvp) const {
    return key() <= kvp.key();
  }

  bool operator==(KeyValuePair const& kvp) const {
    return key() == kvp.key();
  }

  bool operator!=(KeyValuePair const& kvp) const {
    return !(*this == kvp);
  }
};

#endif
