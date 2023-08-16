#include <iostream>
#include "../include/embedded_json.hpp"


int main() {
    embeddedjson::Json<2000> json;
    json.add("key1", 12);
    json.add("key2", 23);

    auto [array, size] = json.get_as_c_array();
    for (std::size_t i = 0; i < size; i++) {
        std::cout << array[i];
    }

    json.clear();

    json.add("dddd", 23);
    json.add("daswe", 23);

    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    json.add("array", arr);

    auto [array2, size2] = json.get_as_c_array();
    for (std::size_t i = 0; i < size2; i++) {
        std::cout << array2[i];
    }
}
