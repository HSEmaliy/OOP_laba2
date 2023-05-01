template<typename K, typename V>
struct Node {
    K key;
    V value;
    Node * next;
};

template<typename K,typename V>
class HashMap{
private:
    Node<K,V> **hash_map;
    std::hash<K> hash_func;
    int size;
    int len_map;
public:
    HashMap();
    HashMap(const HashMap<K,V> &other);
    ~HashMap();
    std::vector<K> getKeys() const;
    std::vector<V> getValue() const;
    std::vector<V> getValue(std::vector<K> key_vector) const;
    void readFile(std::string file_name);
    void writeFile(std::string file_name);
    V& operator[] (const K& key);
    void add(K key, V value);
    void del(K key);
    bool check_key(K key);
    int getSize() const;
    int getLen() const;
    void full_del();
};

template<typename K, typename V>
bool operator==(HashMap<K, V> &map1, HashMap<K, V> &map2);