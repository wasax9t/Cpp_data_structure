#pragma once
//词条模板类，未封装
template<typename K, typename V> struct Entry {
	K key; V value;//关键码作为特征是词条间比较的依据，value是数据
	Entry(K k = K(), V v = V()) : key(k), value(v) {}
	Entry(Entry<K, V> const&e) :key(e.key), value(e.value) {}
	bool operator<(Entry<K, V> const&e) { return key < e.key; }
	bool operator>(Entry<K, V> const&e) { return key > e.key; }
	bool operator==(Entry<K, V> const&e) { return key == e.key; }
	bool operator!=(Entry<K, V> const&e) { return key != e.key; }
};