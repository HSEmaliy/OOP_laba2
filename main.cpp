#include <iostream>
#include "fstream"
#include "vector"
#include "assert.h"
#include "hash_set.h"
#include "hash_set.cpp"
int main() {
    HashMap<std::string,std::string> map1;
    assert(map1.getSize() == 0);

    int previous_size = map1.getSize();
    map1.add("key1","value1");
    assert(map1.getSize() == previous_size + 1);

    previous_size = map1.getSize();
    map1.add("key1","value2");
    assert(map1.getSize() == previous_size);

    assert(map1.check_key("key1"));

    assert(map1["key1"] == "value2");

    previous_size = map1.getSize();
    map1.del("key2");
    assert(map1.getSize() == previous_size);
    map1.del("key1");
    assert(map1.getSize() == previous_size - 1);

    assert(!map1.check_key("key1"));

    map1.add("key1","value1");
    map1.add("key2","value2");
    map1.add("key3","value3");
    HashMap<std::string,std::string> map2(map1);
    assert(map1 == map2);
    map2.del("key2");
    assert(!(map1 == map2));

    map2.full_del();
    HashMap<std::string,std::string> map3;
    assert(map3 == map2);

    map1.writeFile("file1.txt");
    map2.readFile("file1.txt");
    assert(map1 == map2);
}
