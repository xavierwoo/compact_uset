# Compact Unsigned int Set lib

This is a simple set implementation for unsigned int type.

It is an auxiliary lib for my other projects

This set implementation support very quick insertion, deletion, inquiry and traversal.
Each element is unique in the structure.
The order is not guaranteed.

## Usage

```c++
#include <cus/core.h> // header file for this lib
#include <cassert>
#include <iostream>

int main(){
        //When declaring, the maximum possible value should be specified.
    //The maximum possible value cannot be changed due to performance concern.
    compact_uset::Set<> set(10);

    //Use insert() to insert elements
    //Inserting same values is OK, but it will be ignored automatically
    set.insert(3);
    set.insert(1);
    set.insert(2);
    set.insert(2);// Will be ignored.
    assert(set.size() == 3);

    //You cannot insert a value bigger than the declared maximum
    //set.insert(11) produces an error in debug mode

    //Use remove() to delete elements
    set.remove(3);
    assert(set.size() == 2);

    //Removing a non-existing element is OK. It is simply ignored
    set.remove(3); //Will ignore
    assert(set.size() == 2);

    //Use contains() to check if a value exists
    assert(set.contains(2));
    assert(! set.contains(3));

    //Use iterators to traverse all element, order not guaranteed.
    for (auto e : set) {
        std::cout << e << "\n";
    }
    
    return 0;
}
```

## Add CUS to your project using CMake

Consult the following CMakeLists.txt to see how to include the lib to your project using CMake.

```cmake
cmake_minimum_required(VERSION 3.29)
project(your_project)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        compact_uset
        GIT_REPOSITORY https://github.com/xavierwoo/compact_uset.git
        GIT_TAG v0.1.0  # Specify the Git tag here
)

FetchContent_MakeAvailable(compact_uset)

add_executable(your_project main.cpp)

target_link_libraries(your_project compact_uset)
```

## More Compact memory layout

You can make the structure more compact in the memory layout by specifying the template parameter.
For example


```c++
//If maximum is smaller than 255
compact_uset::Set<uint8_t> set(10);
```


