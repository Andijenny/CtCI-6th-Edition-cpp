#include <iostream>
#include <vector>

bool checkPermuatation(const std::string& str1, const std::string& str2)
{
    if(str1.size() != str2.size()) return false;
    std::vector<int> chars(128, 0);
    for(auto it = str1.begin(); it != str1.end(); ++it) {
        const uint8_t i = static_cast<uint8_t>(*it);
        chars[i]++;
    }

    for(auto it = str2.begin(); it != str2.end(); ++it) {
        const uint8_t i = static_cast<uint8_t>(*it);
        chars[i]--;
        if(chars[i] < 0) return false;
    }
    return true;
}

int main()
{
    std::string str1;
    std::string str2;
    std::cout << "input str1:";
    std::cin >> str1;
    std::cout << "input str2:";
    std::cin >> str2;
    std::cout << str1 << " is a permutation of " << str2 << "? " << std::boolalpha << checkPermuatation(str1, str2) << std::endl;
}
