template<typename K,typename V>
HashMap<K,V>::HashMap(){
    this->size = 0;
    this->len_map = 4;
    this->hash_func = std::hash<K>();
    Node<K,V> **tmp = new Node<K,V>*[len_map];
    hash_map = tmp;
    for (int i = 0; i < len_map; i++) {
        hash_map[i] = nullptr;
    }
}
template<typename K,typename V>
HashMap<K,V>::~HashMap<K, V>() {
    if(hash_map!= nullptr)
        full_del();
}

template<typename K,typename V>
std::vector<K> HashMap<K,V>::getKeys() const {
    std::vector<K> keys;
    for (int i = 0; i < this->len_map; i++) {
        if (hash_map[i] != nullptr) {
            Node<K,V> *cur = hash_map[i];
            while(cur!= nullptr){
                keys.push_back(cur->key);
                cur = cur->next;
            }
        }
    }
    return keys;
}

template<typename K,typename V>
std::vector<V> HashMap<K,V>::getValue() const {
    std::vector<V> value;
    for (int i = 0; i < this->len_map; i++) {
        if (hash_map[i] != nullptr) {
            Node<K,V> *cur = hash_map[i];
            while(cur!= nullptr){
                value.push_back(cur->value);
                cur = cur->next;
            }
        }
    }
    return value;
}
template<typename K,typename V>
std::vector<V> HashMap<K,V>::getValue(std::vector<K> key_vector) const{
    std::vector<V> value_vector;
    for (int i = 0; i < key_vector.size(); i++) {
        try {
            V value = (*this)[key_vector[i]];
            value_vector.push_back(value);
        }
        catch (const std::exception& ex){
            std::cout<<"The key "<<key_vector[i]<<" is missing from the "
                                                  "collection\n";
        }
    }
    return value_vector;
}

template<typename K,typename V>
void HashMap<K,V>::readFile(std::string file_name){
    K key;
    V value;
    std::fstream file;
    file.open(file_name);
    while(!file.eof()){
        file >> key;
        file >> value;
        add(key,value);
    }
    file.close();
}

template<typename K,typename V>
void HashMap<K,V>::writeFile(std::string file_name){
    std::ofstream file;
    file.open(file_name);
    std::vector<K> key = getKeys();
    std::vector<V> value = getValue();
    for (int i = 0; i < this->size; i++) {
        file << key[i] <<std::endl;
        if(i == this->size - 1)
            file << value[i];
        else
            file << value[i] <<std::endl;
    }
    file.close();
}

template<typename K,typename V>
V& HashMap<K,V>::operator[] (const K& key){
    int id = this->hash_func(key) % this->len_map;
    if(hash_map[id] == nullptr) {
        throw std::exception("No such key");
    }
    else{
        Node<K,V> * cur = hash_map[id];
        while(cur->next!= nullptr) {
            if(cur->key == key)
                return cur->value;
            cur = cur->next;
        }
        if(cur->key == key)
            return cur->value;
        else
            throw std::exception("No such key");
    }
}

template<typename K,typename V>
void HashMap<K,V>::add(K key, V value){
    if(hash_map == nullptr){
        Node<K,V> **tmp = new Node<K,V>*[len_map];
        hash_map = tmp;
        for (int i = 0; i < len_map; i++) {
            hash_map[i] = nullptr;
        }
    }
    else if(this->size == this->len_map){
        Node<K,V> **tmp = new Node<K,V>*[this->len_map*2];
        Node<K,V> **new_hash_map = tmp;
        for (int i = 0; i < this->len_map*2; i++) {
            new_hash_map[i] = nullptr;
        }
        Node<K,V> *cur;
        int new_id;
        for (int i = 0; i < this->len_map; i++)
            if(hash_map[i] != nullptr){
                cur = hash_map[i];
                while(cur != nullptr){
                    Node<K,V> * new_node =  new Node<K,V>;
                    new_node->key = cur->key;
                    new_node->value = cur->value;
                    new_node->next = nullptr;
                    new_id = this->hash_func(new_node->key) % (this->len_map*2);
                    if(new_hash_map[new_id] == nullptr)
                        new_hash_map[new_id] = new_node;
                    else{
                        Node<K,V> *cur2 = new_hash_map[new_id];
                        while (cur2->next != nullptr)
                            cur2 = cur2->next;
                        cur2->next = new_node;
                    }
                    cur = cur->next;
                }
            }
        int siz = this->size;
        int len = this->len_map;
        full_del();
        this->hash_map = new_hash_map;
        this->len_map = len*2;
        this->size = siz;
    }
    int id = this->hash_func(key) % this->len_map;
    Node<K,V> * new_key = new Node<K,V>;
    new_key->key = key;
    new_key->value = value;
    new_key->next = nullptr;
    if(hash_map[id] == nullptr){
        this->size ++;
        hash_map[id] = new_key;
    }
    else{
        Node<K,V> * cur = hash_map[id];
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
            this->size ++;
            cur->next = new_key;
        }
    }
}

template<typename K,typename V>
void HashMap<K,V>:: del(K key){
    int id = this->hash_func(key) % this->len_map;
    if(hash_map[id] != nullptr){
        Node<K,V> * cur = hash_map[id];
        if(cur->key == key){
            this->size --;
            hash_map[id] = cur->next;
            delete cur;
        }
        else {
            Node<K, V> *pred = cur;
            cur = cur->next;
            while (cur != nullptr) {
                if (cur->key == key) {
                    pred->next = cur->next;
                    delete cur;
                    this->size --;
                    break;
                }
                cur = cur->next;
            }
        }
    }
}

template<typename K,typename V>
bool HashMap<K,V>:: check_key(K key){
    try {
        V check = HashMap<K, V>::operator[](key);
        return true;
    }
    catch (const std::exception& ex){
        return false;
    }
}

template<typename K,typename V>
int HashMap<K,V>:: getSize() const{
    return this->size;
}

template<typename K,typename V>
int HashMap<K,V>:: getLen() const{
    return this->len_map;
}

template<typename K,typename V>
void HashMap<K,V>:: full_del(){
    Node<K,V> *cur,*d;
    for (int i = 0; i < this->len_map; i++) {
        if(hash_map[i] != nullptr){
            cur = hash_map[i];
            while(cur != nullptr){
                d = cur;
                cur = cur->next;
                delete d;
            }
        }
    }
    delete[] hash_map;
    this->size = 0;
    this->len_map = 4;
    hash_map = nullptr;
}

template<typename K,typename V>
HashMap<K,V>::HashMap(const HashMap<K,V> &other){
    this->size = other.size;
    this->len_map = other.len_map;
    Node<K,V> **tmp = new Node<K,V>*[len_map];
    hash_map = tmp;
    for (int i = 0; i < len_map; i++)
        hash_map[i] = nullptr;

    Node<K,V> *cur;
    int new_id;
    for (int i = 0; i < this->len_map; i++)
        if(other.hash_map[i] != nullptr){
            cur = other.hash_map[i];
            while(cur != nullptr){
                Node<K,V> * new_node =  new Node<K,V>;
                new_node->key = cur->key;
                new_node->value = cur->value;
                new_node->next = nullptr;
                new_id = this->hash_func(new_node->key) % (this->len_map);
                if(hash_map[new_id] == nullptr)
                    hash_map[new_id] = new_node;
                else{
                    Node<K,V> *cur2 = hash_map[new_id];
                    while (cur2->next != nullptr)
                        cur2 = cur2->next;
                    cur2->next = new_node;
                }
                cur = cur->next;
            }
        }
}

template<typename K, typename V>
bool operator==(HashMap<K, V> &map1, HashMap<K, V> &map2) {
    if(map1.getSize() != map2.getSize())
        return false;
    std::vector<K> key_v = map1.getKeys();
    for (int i = 0; i < key_v.size(); i++) {
        try{
            if(map1[key_v[i]] != map2[key_v[i]]){
                return false;
            }
        }
        catch(std::exception& ex) {
            return false;
        }
    }
    return true;
}