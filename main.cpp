#include <iostream>
#include "fstream"
#include "vector"
#include "assert.h"
#include "hash_tab.h"
#include "hash_tab.cpp"
int main() {
    HashTable<std::string,std::string> *tab22 = new HashTable<std::string,std::string>;
    HashTable<std::string,std::string> tab1;
    assert(tab1.getCount() == 0);

    int size = tab1.getCount();
    tab1.push_back("key1","val1");
    assert(tab1.getCount() == size + 1);

    size = tab1.getCount();
    tab1.push_back("key1","vallll");
    assert(tab1.getCount() == size);

    assert(tab1.check("key1"));

    assert(tab1["key1"] == "vallll");

    size = tab1.getCount();
    tab1.delet("key2");
    assert(tab1.getCount() == size);
    tab1.delet("key1");
    assert(tab1.getCount() == size - 1);

    assert(!tab1.check("key1"));

    tab1.push_back("key1","val1");
    tab1.push_back("key2","val2");
    tab1.push_back("key3","val3");
    HashTable<std::string,std::string> tab2(tab1);
    assert(tab1 == tab2);
    tab2.delet("key2");
    assert(!(tab1 == tab2));

    tab2.full_delete();
    HashTable<std::string,std::string> tab3;
    assert(tab3 == tab2);

    tab1.write("file1.txt");
    tab2.read("file1.txt");
    assert(tab1 == tab2);
    std::cout<<"correct!\n";


    HashTable<std::string,std::string> tab0;
    tab0.push_back("key1","val1");
    tab0.push_back("key2","val2");
    tab0.push_back("key3","val2");
    tab0.push_back("key4","val1");
    tab0.push_back("key5","val3");
    tab0.push_back("key6","val1");
    tab0.push_back("key7","val5");

    std::vector<std::string> vec = tab0.getKeys("val1");
    for (int i = 0; i <vec.size(); i++) {
        std::cout<<vec[i]<<std::endl;
    }
}
