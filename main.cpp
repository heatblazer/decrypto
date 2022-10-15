#include <iostream>
#include <cstdio>
#include <vector>
#include <string.h>



static const char TXT[] = "Yhakukyzyp sohaqyzaso ganixozynucopy xatubiqoma dehoqicaze ijokuqycaxejot ydub nytebi xyvuqakawatusudy bunyve ebepux pagejimavixu iw buzicosinati uvodylybiqemim ozotyjowigymyqas ukapep eqowyp iduvif byhino. Hekusydysika ox yqesywumoh giluripu zi ynahosah odyracycovuw zykajetige doly didamohisudaha pe hibilu arydudykuzyl adybibaqukinuj op cy cizacixogawesugi nu ydit itewisewapuf nymanirolo edigypar";


void split(const char* str, const char* delim, std::vector<std::string>& out)
{
    const char* begin = str;
    const char* it = strstr(str, delim);
    if (it != NULL)
    {
        std::string data{begin, it};
        out.push_back(data);
        it++;
        split(it, delim, out);
    } else {
        std::string data{str};
        out.push_back(data);
    }
}

bool is_vowel(const char x)
{
    bool res = true;
    switch (x)
    {
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'i':
    case 'I':
    case 'o':
    case 'O':
    case 'u':
    case 'U':
    case 'y':
    case 'Y':
        break;
    default:
        res = false;
        break;
    }
    return res;

}

union bitset2
{
    struct
    {
        uint8_t b0:1;
        uint8_t b1:1;
        uint8_t b2:1;
        uint8_t b3:1;
        uint8_t b4:1;
        uint8_t b5:1;
        uint8_t b6:1;
        uint8_t b7:1;
    } ubits;
    char value;
};


void printbits(bitset2 bset)
{
    printf("%d|%d|%d|%d|%d|%d|%d|%d\r\n",
           bset.ubits.b7,bset.ubits.b6,bset.ubits.b5,bset.ubits.b4,
           bset.ubits.b3,bset.ubits.b2,bset.ubits.b1,bset.ubits.b0);
    printf("----------------\r\n");
}




int main()
{

    FILE* site = popen("curl -s 2>&1 http://magadans22.org | sed 's/<\\/*[^>]*>//g'", "r");;

    std::string sitetxt;
    char buffer[256] = {0};
    while (fgets(buffer, sizeof(buffer), site))
    {
        sitetxt.append(buffer);
    }


    std::cout << sitetxt << std::endl;

    std::vector<std::string> splits;
    split(sitetxt.c_str(), " ", splits);
    for(auto s : splits) {
        std::string consonants{""};
        uint8_t key = 0;
        for(auto c : s) {
            bitset2 b = {.value = c};
            printbits(b);
        }
        puts("##################");
    }
    return 0;
}
