#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <thread>

#define LOOPCNT 1

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
    for(int i=sizeof(T)-1; i >= 0; i--) {
        printf("%d|%d|%d|%d|%d|%d|%d|%d|",
            bset.ubits[i].b7, bset.ubits[i].b6, bset.ubits[i].b5, bset.ubits[i].b4,
            bset.ubits[i].b3, bset.ubits[i].b2, bset.ubits[i].b1, bset.ubits[i].b0);
    }
    printf("\r\n----------------\r\n");
}

template<typename T>
T reversebits(T val)
{
    T result = 0;
    for(int i = (sizeof(T) * 8) -1; val; i--, val >>= 1) {
        result |= ((val & 1) << i) ;
    }
    return result;
}


typedef int (*binop)(unsigned char a, unsigned char b);

bool is_vowel(const char x);

int pairbytes(unsigned char a, unsigned char b);

void split(const char* str, const char* delim, std::vector<std::string>& out);

void removenl(std::string& str);

void removesym(std::string& str, const char* syms);

void tablocation(const std::string& str, std::vector<int>& out);

size_t tabcounter(const std::string str);

void pairtext(const std::vector<std::string>& strvec, std::vector<std::string>& out, binop bop);

void removetags(std::string& ref);



#ifdef __unix__
#define  DOWNLOAD popen("curl -s http://magadans22.org ", "r")
#else 
#define DOWNLOAD _popen("curl -s http://magadans22.org ", "r")
#endif


struct DoWork 
{
    FILE* site;
    std::string sitetxt, originaltxt;
    size_t tabulations, counter, vowels, consonants, words, symcount;
    uint16_t checksum ;
    std::vector<int> tablocations; 
    std::vector<std::string> splits, paired;
    char buffer[512] ;

    DoWork() : site{NULL}, tabulations{0}, counter{0}, 
    vowels{0}, consonants{0}, words{0}, symcount{0}, checksum{0}, buffer{0}
    {
    }

    void operator()()
    {
        site = DOWNLOAD; 
        while (fgets(buffer, sizeof(buffer), site))
        {        
            sitetxt.append(buffer);
            originaltxt.append(buffer);
        }
        removetags(sitetxt);
        removenl(sitetxt);
        split(sitetxt.c_str(), " ", splits);
        
        removesym(sitetxt, ".\t\n ");
        symcount = sitetxt.size();
        for (int i=0; i < sitetxt.size(); i++) {
            if (is_vowel(sitetxt[i])) 
                vowels += 1;
            else
                consonants+=1;
        }
        tabulations = tabcounter(sitetxt);
        tablocation(sitetxt, tablocations);
        pairtext(splits, paired, nullptr);
    }

    void test1()
    {
        std::cout << "Words: " << splits.size() << std::endl;
        for (auto s : paired) 
        {
            unsigned char a = s[0], b = s[1];
            for(int i=0; i < 8; i++) 
            {
                int shift = 7-i;
                printf("[%c]", (a & b) | (vowels) >> shift);
                printf("[%c]", (a & b) ^ (vowels) >> shift);
                printf("[%c]", (a ^ b) & (vowels) >> shift);
                printf("[%c]", (a ^ b) ^ (vowels) >> shift);

                printf("[%c]", (a & b) | (consonants) >> shift);
                printf("[%c]", (a & b) ^ (consonants) >> shift);
                printf("[%c]", (a ^ b) & (consonants) >> shift);
                printf("[%c]", (a ^ b) ^ (consonants) >> shift);

                printf("[%c]", (a & b) | (vowels &  consonants));
                printf("[%c]", (a & b) ^ (vowels &  consonants));
                printf("[%c]", (a ^ b) & (vowels &  consonants));
                printf("[%c]", (a ^ b) ^ (vowels &  consonants));

                puts("..");
            }
        }
    }


    void test2()
    {
        std::cout << "Words: " << splits.size() << std::endl;
        
        unsigned short h = (vowels ^ consonants);
        for (auto s : paired) 
        {
            unsigned char a = s[0], b = s[1];
            unsigned short paired = (a << 8) | (b);
            unsigned char t = (paired ) & splits.size();
            printf("[%c]\r\n", t);            
        }
    }

    void test3()
    {
        const char key[]  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        for(auto p : paired) {
            auto b = p.cbegin();
            auto e = p.end()-1;
            unsigned char t ;
            if (is_vowel(*b))
                t = *b  | *e;
            else 
                t = *b & *e;

            printf("[%c]", t);
        }
    }

    void test4()
    {
        const char key[]  = "mgdns22";
        int cnt = 0;

        std::cout << sitetxt << std::endl;
    }

    void test5()
    {
        std::cout << "WORDS: " << splits.size() << std::endl;
        std::cout << "SYMBOLS: " << symcount << std::endl;
    }
};


int main(void)
{        
    DoWork w[LOOPCNT];
    std::vector<std::thread> workers;
    for(int i=0; i < LOOPCNT; i++) {
        workers.push_back(std::thread(&DoWork::operator(), &w[i]));
    }
    for(int i=0; i < LOOPCNT; i++)
        workers[i].join();

    for (int i = 0; i < LOOPCNT; i++) {
        w[i].test3();
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
    else 
    {
        std::string data{ str };
        out.push_back(data);
    }
}


void removenl(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.cend());    
}

void removesym(std::string& str, const char* syms)
{
    if (!syms) 
        return ; 
    for(const char* it = syms ; *it != '\0' ; it++) {
        str.erase(std::remove(str.begin(), str.end(), *it), str.cend());
    }
}


void tablocation(const std::string& str, std::vector<int>& out)
{
    for(int i=0; i < str.size(); i++)
        if (str[i] == '\t') out.push_back(i);    
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
#ifdef __unix__
            sprintf(pair, "%c%c", *c, *n);
#else
            sprintf_s(pair, "%c%c", *c, *n);
#endif
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
        if (endpos != std::string::npos) 
        {
            ref.erase(startpos, endpos - startpos);
        }
    }
}