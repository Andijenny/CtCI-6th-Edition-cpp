#include <iostream>
#include <string>

using namespace std;

int charAt(char c)
{
    if(c >= 'A' && c <= 'z') return c - 'A';
    else return -1;
}
/*Memory O(1)*/
bool palindromePermutation(const string& str)
{
    int dict[52]= {0};
    int count = 0;
    for(auto it = str.begin(); it != str.end(); ++it) {
       int i = charAt(*it);
       if(i < 0) continue;
       dict[i]++;
       if(dict[i] & 0x01) count++;
       else count--;
    }
    return count <= 1;
}

void toggle(int64_t& count, int idx)
{
    int64_t mask = 1 << idx;
    count ^= mask;
}
/*Memory O(1)*/
bool palindromePermutationBitwise(const string& str)
{
    int64_t count = 0;
    for(auto it = str.begin(); it != str.end(); ++it) {
       int i = charAt(*it);
       if(i < 0) continue;
       toggle(count, i);
    }
    return (count & (count-1) == 0);
}

int main()
{
   string str;
   cout << "input str:";
   getline(cin, str);
   cout << "is palindrome permutation ? " << boolalpha << palindromePermutationBitwise(str) << endl;
}
