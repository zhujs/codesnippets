// C++11

#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>

// simplify the template with auto
template <typename Creator>  
auto processProduct(const Creator& creator) -> decltype(creator.maeOject()) {  
    auto val = creator.makeObject();  
    // do somthing with val  
    return val;
} 

int main () {
    // shared_ptr in stl
    std::shared_ptr<int> ptr;
    if (ptr == 0)
      std::cout<< "(shared_ptr_object == 0) is valid." << std::endl;

    std::map<std::string, int> allPeople;

    allPeople.insert(std::make_pair("WestBrook", 26));

    // new type of for loop
    for (auto person : allPeople) {
      std::cout << person.first << " : " << person.second << std::endl;
    }

    // new way of initialization
    std::vector<int> vec{5, 4, 3, 2, 1};  
    int num1 = 1, num2 = 1;  

    // lambda function
    // [context_variables] (function parameters) -> return type { codes }
    std::for_each(vec.begin(), vec.end(), [=](int &element)->int {
            std::cout << " * " << element << " * " << std::endl;
            return element * (num1 + num2 );
            });
    return 0;
}
