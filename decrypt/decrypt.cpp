#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

template<typename T>
union bitset2
{
    T value;
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
    } ubits[sizeof(T)];
    uint8_t data[sizeof(T)];
};

template<typename T>
void printbits(T val)
{
    bitset2<T> bset;
    bset.value = val;
    for(int i=0; i < sizeof(T); i++) {
        printf("%d|%d|%d|%d|%d|%d|%d|%d|",
            bset.ubits[i].b7, bset.ubits[i].b6, bset.ubits[i].b5, bset.ubits[i].b4,
            bset.ubits[i].b3, bset.ubits[i].b2, bset.ubits[i].b1, bset.ubits[i].b0);
    }
    printf("\r\n----------------\r\n");
}

typedef int (*binop)(unsigned char a, unsigned char b);

bool is_vowel(const char x);

int pairbytes(unsigned char a, unsigned char b);

void split(const char* str, const char* delim, std::vector<std::string>& out);

void removenl(std::string& str);

void tablocation(const std::string& str, std::vector<int>& out);

size_t tabcounter(const std::string str);

void pairtext(const std::vector<std::string>& strvec, std::vector<std::string>& out, binop bop);

void removetags(std::string& ref);


#ifdef __unix__
#define  DOWNLOAD popen("curl -s http://magadans22.org ", "r")
#else 
#define DOWNLOAD _popen("curl -s http://magadans22.org ", "r")
#endif

int main(void)
{        


#if 0 //test section
printbits<int>(0xff00ffaa);
#endif


    FILE* site = DOWNLOAD;
    std::string sitetxt;
    size_t tabulations = 0;
    std::vector<int> tablocations; 
    std::vector<std::string> splits, paired;
    char buffer[512] = { 0 };

    while (fgets(buffer, sizeof(buffer), site))
    {        
        sitetxt.append(buffer);
    }

    removetags(sitetxt);
    removenl(sitetxt);
    
    tabulations = tabcounter(sitetxt);
    std::cout << "TABS: " << tabulations << std::endl;
    tablocation(sitetxt, tablocations);

    puts("####################################");

    std::cout << sitetxt << std::endl;

    split(sitetxt.c_str(), " ", splits);

    pairtext(splits, paired, &pairbytes);

    for (auto s : splits) {
        for (auto c : s) {
            printbits<char>(c);
        }
        puts("####################################");
    }
    return 0;
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


int pairbytes(unsigned char a, unsigned char b)
{
    unsigned short res = (a & b);
    return (int)res;
}


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


void removenl(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.cend());    
}


void tablocation(const std::string& str, std::vector<int>& out)
{
    for(int i=0; i < str.size(); i++)
        if (str[i] == '\t') out.push_back(i);
    
    for(auto l : out) 
        std::cout << l << "|";
    std::cout << "\r\n";
}

size_t tabcounter(const std::string str)
{
    size_t cnt = 0;
    for(auto c : str) 
        if (c == '\t') cnt++;
    return cnt;
}

void pairtext(const std::vector<std::string>& strvec, std::vector<std::string>& out, binop bop)
{
    for(auto str : strvec)
    {
        const char * begin = str.c_str();
        while (*begin == '\t') begin++;
        size_t cnt = 0 ;
        for(const char*c = begin, *n = begin+1; *c != '\0'; )
        {
            char pair[3]= {0};
            sprintf(pair, "%c%c", *c, *n);
            if (bop) 
            {
                int result = bop(*c, *n);
            }
            c += 2;
            n += 2;
            out.push_back(pair);
        }
    }
}

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