#include "stdafx.h"
#include "Containers.h"

#include <string>
#include <iostream>
#include <unordered_map>

void containers()
{
    std::cout << std::endl << "Containers" << std::endl;
    std::unordered_map<int, std::string> map;

    std::cout << "Inserting into a map\n";
    int i = 1;
    auto iter = map.insert(std::pair<int, std::string>(i, "empty"));
    std::cout << map.at(i) << "\n";
    (*iter.first).second = "gds";
    std::cout << map.at(i) << "\n";
    auto iter2 = map.insert(std::pair<int, std::string>(i, ""));
    std::cout << map.at(i) << "\n";
    (*iter2.first).second = "bbb";
    std::cout << map.at(i) << "\n";

    auto it = map.find(2);
    std::string message = (it == map.end()) ? "not found" : (*iter.first).second;
    std::cout << message << "\n";
}
