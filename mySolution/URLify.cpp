#include <iostream>
#include <string>
#include <cstring>

/*return a copy of original string*/
void URLify(std::string& str, uint32_t flag)
{
    uint32_t st = 0, ed = str.find(" ");
    if(ed == st) return;
    std::string res=str.substr(st, ed - st);
    if(ed == flag) {
        str = res;
        return;
    }
    while(ed < flag) {
        res.append("%20");
        st = ed+1;
        ed = str.find(" ", st);
        if(st == ed || ed == std::string::npos) break;
        res.append(str.substr(st, ed-st));
    }
    str = res;
}

/*replace ' '  with "%20" inplace*/
void URLify(char str[], uint32_t trueLen)
{
    uint32_t count = 0;
    for(uint32_t i = 0; i < trueLen; ++i) {
        if(str[i] == ' ') count++;
    }

    int i = trueLen + 2*count - 1;
    for(int j = trueLen-1; j >= 0; --j) {
        if(str[j] == ' '){
            str[i] = '0';
            str[i-1] = '2';
            str[i-2] = '%';
            i = i - 3;
        }
        else {
            str[i--] = str[j];
        }
    }
}

int main()
{
    //std::string str{"Mr John Smith   "};
    std::string str;
    std::cout << "input string:";
    std::getline(std::cin, str);

    uint32_t len;
    std::cout << "input length:";
    std::cin >> len;

    char* p = new char(str.size());
    strcpy(p, str.c_str());
    URLify(p, len);
    std::cout << "URL: *" << p << "*" << std::endl;
}
