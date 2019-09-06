#include <iostream>
#include <string>
#include <bitset>

bool isUnique(const std::string& str)
{
    if(str.size() > 128) return false;
    //std::vector<uint8_t> cache(128, 0);
    // uint8_t cache[128] = {0};
    std::bitset<128> cache(0);
    for(auto it = str.begin(); it != str.end(); ++it) {
       const uint8_t idx = static_cast<uint8_t>(*it);
      // if(cache[idx] == 1) return false;
       if(cache.test(idx)) return false;
      // cache[idx] = 1;
       cache.set(idx);
    }
    return true;
}

int main()
{
    std::string str;
    std::cout << "input a string:";
    std::cin >> str;
    std::cout << "Is unique? " << std::boolalpha << isUnique(str) << std::endl;
}
