#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>



static const char TXT[] = "Yhakukyzyp sohaqyzaso ganixozynucopy xatubiqoma dehoqicaze ijokuqycaxejot ydub nytebi xyvuqakawatusudy bunyve ebepux pagejimavixu iw buzicosinati uvodylybiqemim ozotyjowigymyqas ukapep eqowyp iduvif byhino. Hekusydysika ox yqesywumoh giluripu zi ynahosah odyracycovuw zykajetige doly didamohisudaha pe hibilu arydudykuzyl adybibaqukinuj op cy cizacixogawesugi nu ydit itewisewapuf nymanirolo edigypar";


void split(const char* str, const char* delim, std::vector<std::string>& out)
{
    const char* begin = str;
    const char* it = strstr(str, delim);
    if (it != NULL)
    {
        std::string data{ begin, it };
        out.push_back(data);
        it++;
        split(it, delim, out);
    }
    else {
        std::string data{ str };
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
        uint8_t b0 : 1;
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;
    } ubits;
    char value;
};


void printbits(bitset2 bset)
{
    printf("%d|%d|%d|%d|%d|%d|%d|%d\r\n",
        bset.ubits.b7, bset.ubits.b6, bset.ubits.b5, bset.ubits.b4,
        bset.ubits.b3, bset.ubits.b2, bset.ubits.b1, bset.ubits.b0);
    printf("----------------\r\n");
}


#ifdef __unix__
#define  DOWNLOAD popen("curl -s 2>&1 http://magadans22.org | sed 's/<\\/*[^>]*>//g'", "r")
void removetags(std::string& ref)
{
    (void)ref;
}

#else 
#define DOWNLOAD _popen("curl -s http://magadans22.org ", "r")
void removetags(std::string& ref)
{
    while (ref.find("<") != std::string::npos)
    {
        auto startpos = ref.find("<");
        auto endpos = ref.find(">") + 1;
        if (endpos != std::string::npos) {
            ref.erase(startpos, endpos - startpos);
        }
    }
}
#endif

void removenl(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
}

int main()
{

    
    FILE* site = DOWNLOAD;

    std::string sitetxt;
    char buffer[512] = { 0 };
    while (fgets(buffer, sizeof(buffer), site))
    {        
        sitetxt.append(buffer);
    }

    removetags(sitetxt);
    removenl(sitetxt);

    std::cout << sitetxt << std::endl;

    std::vector<std::string> splits;
    split(sitetxt.c_str(), " ", splits);
    for (auto s : splits) {
        for (auto c : s) {
            bitset2 b;
            b.value = c;
            printbits(b);
        }
        puts("##################");
    }
    return 0;
}
