template<typename K, typename V>
struct Node {
    K key;
    V value;
    Node * next;
};

template<typename K,typename V>
class HashTable{
private:
    Node<K,V> **hash_tab;
    std::hash<K> hashFunction;
    int count;
    int len;
public:
    HashTable();
    HashTable(const HashTable<K,V> &a);
    ~HashTable();
    std::vector<K> getKeys() const;
    std::vector<K> getKeys(V value) const;
    std::vector<V> getValue() const;
    void read(std::string name);
    void write(std::string name);
    V& operator[] (const K& key);
    void push_back(K key, V value);
    void delet(K key);
    bool check(K key);
    int getCount() const;
    int getLen() const;
    void full_delete();
};

template<typename K, typename V>
bool operator==(HashTable<K, V> &hash1, HashTable<K, V> &hash2);