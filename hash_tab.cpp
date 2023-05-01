template<typename K,typename V>
HashTable<K,V>::HashTable(){
    this->count = 0;
    this->len = 4;
    this->hashFunction = std::hash<K>();
    Node<K,V> **T = new Node<K,V>*[len];
    hash_tab = T;
    for (int i = 0; i < len; i++) {
        hash_tab[i] = nullptr;
    }
}
template<typename K,typename V>
HashTable<K,V>::~HashTable<K, V>() {
    if(hash_tab!= nullptr)
        full_delete();
}

template<typename K,typename V>
std::vector<K> HashTable<K,V>::getKeys() const {
    std::vector<K> keys;
    for (int i = 0; i < this->len; i++) {
        if (hash_tab[i] != nullptr) {
            Node<K,V> *cur = hash_tab[i];
            while(cur!= nullptr){
                keys.push_back(cur->key);
                cur = cur->next;
            }
        }
    }
    return keys;
}

template<typename K,typename V>
std::vector<K> HashTable<K,V>::getKeys(V value) const {
    std::vector<K> keys;
    Node<K,V>* cur;
    for (int i = 0; i < this->len; i++) {
        if(hash_tab[i] != nullptr){
            cur = hash_tab[i];
            while(cur != nullptr){
                if(cur->value == value){
                    keys.push_back(cur->key);
                }
                cur = cur->next;
            }
        }
    }
    return keys;
}
template<typename K,typename V>
std::vector<V> HashTable<K,V>::getValue() const {
    std::vector<V> value;
    for (int i = 0; i < this->len; i++) {
        if (hash_tab[i] != nullptr) {
            Node<K,V> *cur = hash_tab[i];
            while(cur!= nullptr){
                value.push_back(cur->value);
                cur = cur->next;
            }
        }
    }
    return value;
}

template<typename K,typename V>
void HashTable<K,V>::read(std::string name){
    K key;
    V value;
    std::fstream file;
    file.open(name);
    while(!file.eof()){
        file >> key;
        file >> value;
        push_back(key,value);
    }
    file.close();
}

template<typename K,typename V>
void HashTable<K,V>::write(std::string name){
    std::ofstream file;
    file.open(name);
    std::vector<K> key = getKeys();
    std::vector<V> value = getValue();
    for (int i = 0; i < this->count; i++) {
        file << key[i] <<std::endl;
        if(i == this->count - 1)
            file << value[i];
        else
            file << value[i] <<std::endl;
    }
    file.close();
}

template<typename K,typename V>
V& HashTable<K,V>::operator[] (const K& key){
    int id = this->hashFunction(key) % this->len;
    std::string a = "No key";
    if(hash_tab[id] == nullptr) {
        throw a;
    }
    else{
        Node<K,V> * cur = hash_tab[id];
        while(cur->next!= nullptr) {
            if(cur->key == key)
                return cur->value;
            cur = cur->next;
        }
        if(cur->key == key)
            return cur->value;
        else
            throw a;
    }
}

template<typename K,typename V>
void HashTable<K,V>::push_back(K key, V value){
    if(hash_tab == nullptr){
        Node<K,V> **T = new Node<K,V>*[len];
        hash_tab = T;
        for (int i = 0; i < len; i++) {
            hash_tab[i] = nullptr;
        }
    }
    else if(this->count == this->len){
        Node<K,V> **T = new Node<K,V>*[this->len*2];
        Node<K,V> **new_hash_tab = T;
        for (int i = 0; i < this->len*2; i++) {
            new_hash_tab[i] = nullptr;
        }
        Node<K,V> *cur;
        int id;
        for (int i = 0; i < this->len; i++)
            if(hash_tab[i] != nullptr){
                cur = hash_tab[i];
                while(cur != nullptr){
                    Node<K,V> * new_node =  new Node<K,V>;
                    new_node->key = cur->key;
                    new_node->value = cur->value;
                    new_node->next = nullptr;
                    id = this->hashFunction(new_node->key) % (this->len*2);
                    if(new_hash_tab[id] == nullptr)
                        new_hash_tab[id] = new_node;
                    else{
                        Node<K,V> *cur2 = new_hash_tab[id];
                        while (cur2->next != nullptr)
                            cur2 = cur2->next;
                        cur2->next = new_node;
                    }
                    cur = cur->next;
                }
            }
        int count = this->count;
        int len = this->len;
        full_delete();
        this->hash_tab = new_hash_tab;
        this->len = len*2;
        this->count = count;
    }
    int id = this->hashFunction(key) % this->len;
    Node<K,V> * new_key = new Node<K,V>;
    new_key->key = key;
    new_key->value = value;
    new_key->next = nullptr;
    if(hash_tab[id] == nullptr){
        this->count ++;
        hash_tab[id] = new_key;
    }
    else{
        Node<K,V> * cur = hash_tab[id];
        while(cur->next!= nullptr) {
            if(cur->key == key){
                cur->value = value;
                return;
            }
            cur = cur->next;
        }
        if(cur->key == key)
            cur->value = value;
        else{
            this->count ++;
            cur->next = new_key;
        }
    }
}

template<typename K,typename V>
void HashTable<K,V>:: delet(K key){
    int id = this->hashFunction(key) % this->len;
    if(hash_tab[id] != nullptr){
        Node<K,V> * cur = hash_tab[id];
        if(cur->key == key){
            this->count --;
            hash_tab[id] = cur->next;
            delete cur;
        }
        else {
            Node<K, V> *pred = cur;
            cur = cur->next;
            while (cur != nullptr) {
                if (cur->key == key) {
                    pred->next = cur->next;
                    delete cur;
                    this->count --;
                    break;
                }
                cur = cur->next;
            }
        }
    }
}

template<typename K,typename V>
bool HashTable<K,V>:: check(K key){
    try {
        V check = HashTable<K, V>::operator[](key);
        return true;
    }
    catch (std::string a){
        return false;
    }
}

template<typename K,typename V>
int HashTable<K,V>:: getCount() const{
    return this->count;
}

template<typename K,typename V>
int HashTable<K,V>:: getLen() const{
    return this->len;
}

template<typename K,typename V>
void HashTable<K,V>:: full_delete(){
    Node<K,V> *cur,*d;
    for (int i = 0; i < this->len; i++) {
        if(hash_tab[i] != nullptr){
            cur = hash_tab[i];
            while(cur != nullptr){
                d = cur;
                cur = cur->next;
                delete d;
            }
        }
    }
    delete[] hash_tab;
    this->count = 0;
    this->len = 4;
    hash_tab = nullptr;
}

template<typename K,typename V>
HashTable<K,V>::HashTable(const HashTable<K,V> &other){
    this->count = other.count;
    this->len = other.len;
    Node<K,V> **T = new Node<K,V>*[len];
    hash_tab = T;
    for (int i = 0; i < len; i++)
        hash_tab[i] = nullptr;

    Node<K,V> *cur;
    int new_id;
    for (int i = 0; i < this->len; i++)
        if(other.hash_tab[i] != nullptr){
            cur = other.hash_tab[i];
            while(cur != nullptr){
                Node<K,V> * new_node =  new Node<K,V>;
                new_node->key = cur->key;
                new_node->value = cur->value;
                new_node->next = nullptr;
                new_id = this->hashFunction(new_node->key) % (this->len);
                if(hash_tab[new_id] == nullptr)
                    hash_tab[new_id] = new_node;
                else{
                    Node<K,V> *cur2 = hash_tab[new_id];
                    while (cur2->next != nullptr)
                        cur2 = cur2->next;
                    cur2->next = new_node;
                }
                cur = cur->next;
            }
        }
}

template<typename K, typename V>
bool operator==(HashTable<K, V> &map1, HashTable<K, V> &map2) {
    if(map1.getCount() != map2.getCount())
        return false;
    std::vector<K> key_v = map1.getKeys();
    for (int i = 0; i < key_v.size(); i++) {
        try{
            if(map1[key_v[i]] != map2[key_v[i]]){
                return false;
            }
        }
        catch(std::string a) {
            return false;
        }
    }
    return true;
}