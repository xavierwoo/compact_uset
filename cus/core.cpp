//
// Created by 吴 歆韵 on 2025/3/20.
//

#include "core.h"
#include <iostream>

void compact_uset::it_works() {
    Set<> set(10);

    set.insert(3);
    set.insert(1);
    assert(set.get_data_list()[0] == 3);
    assert(set.get_data_list()[1] == 1);
    assert(set.get_hash_list()[3] == 0);
    assert(set.get_hash_list()[1] == 1);

    set.insert(1);
    assert(set.size() == 2);

    set.remove(3);
    assert(set.get_data_list()[0] == 1);
    assert(set.get_hash_list()[1] == 0);

    set.re_set(15);
    set.insert(12);
    set.check();

    set.clear();
    set.insert(3);
    set.insert(1);
    set.insert(1);
    set.check();

    std::cout<<"cus works!"<<std::endl;
}