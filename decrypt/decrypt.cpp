#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

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

typedef int (*binop)(unsigned char a, unsigned char b);

bool is_vowel(const char x);

int pairbytes(unsigned char a, unsigned char b);

void split(const char* str, const char* delim, std::vector<std::string>& out);

void printbits(bitset2 bset);

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
            bitset2 b;
            b.value = c;
            printbits(b);
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


void printbits(bitset2 bset)
{
    printf("%d|%d|%d|%d|%d|%d|%d|%d\r\n",
        bset.ubits.b7, bset.ubits.b6, bset.ubits.b5, bset.ubits.b4,
        bset.ubits.b3, bset.ubits.b2, bset.ubits.b1, bset.ubits.b0);
    printf("----------------\r\n");
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