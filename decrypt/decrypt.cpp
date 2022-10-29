#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdalign>
#include <map>
#include <cstring>
#include <cmath>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <thread>
#include <fstream>

#define LOOPCNT 1

#ifdef __unix__
#define SPRINTF sprintf
#else
#define SPRINTF sprintf_s
#endif


template<typename T>
union bitset2
{
    T value;
    alignas(sizeof(T)) struct
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
    alignas(sizeof(T)) uint8_t data[sizeof(T)];
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

bool isprime(long long int);

void lowerall(std::string& ref);

#ifdef __unix__
#define  DOWNLOAD popen("curl -s http://magadans22.org ", "r")
#else 
#define DOWNLOAD _popen("curl -s http://magadans22.org ", "r")
#endif


static const char ALPHA[] = "abcdefghijklmnopqrstuvwxyz";
static const char VOWELS[] = "aeiouy";
static const char CONSONANTS[] = "bcdfghjklmnpqrstvwxz";


struct CharLookup
{
    std::map<std::string, std::vector<char> > m_lookup;

    CharLookup()
    {
        for(int i=0;i < sizeof(VOWELS); i++) {
            for (int j=0; j < sizeof(CONSONANTS); j++) {
                std::string s;
                s += VOWELS[i];
                s += CONSONANTS[j];
                for(int k=0; k < sizeof(ALPHA); k++) {
                    m_lookup[s].push_back(ALPHA[k]);
                }
            }
        }

        for(int i=0;i < sizeof(CONSONANTS); i++) {
            for (int j=0; j < sizeof(VOWELS); j++) {
                std::string s, v;
                s += CONSONANTS[i];
                s += VOWELS[j];
                for(int k=0; k < sizeof(ALPHA); k++) {
                    m_lookup[s].push_back(ALPHA[k]);
                }
            }
        }   
    }

    void print()
    {
        for(auto kv : m_lookup) 
        {
            for (auto v : kv.second) {
                std::cout << "#[" << kv.first << "]$[" << v << "]";
            }
            std::cout << std::endl;
        }
    }


};


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
                vowels{0}, consonants{0}, words{0}, 
                symcount{0}, checksum{0}, buffer{0}
    {
        sitetxt.resize(20000);
        originaltxt.resize(20000);
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
        removesym(sitetxt, ".\t\n");
        split(sitetxt.c_str(), " ", splits);
        
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
            unsigned short paired = (b << 8) | (a);
            if (isprime(paired))
                printf("PRIME\r\n");
            else
                printf("NOT PRIME\r\n");
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
#if 0
    void test5()
    {
        for (auto s : splits) {
            std::string vow, con, fin;
            std::vector<std::string> paired2;
            bool startswithvow = is_vowel(s.at(0)) ? true : false;
            for (auto c : s) {               
                if (is_vowel(c))
                    vow += c;
                else 
                    con += c;
            }
            if (startswithvow) {
                for(auto v : vow)
                    fin += v;
                for (auto c : con)
                    fin += c;
            } else 
            {
                for (auto c : con)
                    fin += c;
                for(auto v : vow)
                    fin += v;
            }
            const char* begin = fin.c_str();
            for(const char*c = begin, *n = begin+1; *c != '\0'; )
            {
                char pair[3]= {0};
    #ifdef __unix__
                sprintf(pair, "%c%c", *c, *n);
    #else
                sprintf_s(pair, "%c%c", *c, *n);
    #endif
                paired2.push_back(pair);
                c += 2;
                n += 2;

            }
            std::string utfs ;
            for(auto p : paired2)            
            {
                utfs += char(3 << 6);
                utfs += char(1 << 7);
            }
            printf("----------\r\n");
        }
    }
#endif 

    void test6()
    {
        std::string utfenc;
        int cnt = 0;
        for (auto p : paired) 
        {
            if (cnt > 1024)
                break;
        /**
         * @brief 
         * out += char(7 << 5);
            out += char(1 << 7);
            out += char(1 << 7);
         */
            for(int i=0; i < utfenc.size(); i++) {
                printf("\\x%02x", utfenc[i] & 0xff);
            }
        }
        return;
    }

    void test7()
    {
        for (auto p : paired)
        {
            unsigned short pb = (p[1] ) & (p[0]);
            float period = sin(pb);
            float period2 = cos(pb);
            bitset2<float> bs,ps;
            bs.value = period;
            ps.value = period2;
            unsigned int ip = (bs.data[3] << 24) | (bs.data[2] << 16) | (bs.data[1] <<8 ) | (bs.data[0]) ;
            unsigned int ip2 = (ps.data[3] << 24) | (ps.data[2] << 16) | (ps.data[1] <<8 ) | (ps.data[0]) ;
            
            for(int j=0, offset = 0 ;j < sizeof(ip); j++, offset += 8)
            {
                char c = (ip >> offset) & 0xff;
                char b = (ip2 >> offset) & 0xff;
                printf("[%c]-[%c]->[%c]", c, b, c + b);
            }
            puts("\r\n----------------------------");
        }
    }

    void test8()
    {
        std::map<int, int> vow ;
        int cnt = 0;
        for(auto c : originaltxt)
        {
            if (is_vowel(c))
                vow[(int)c]++;
        }

        for(auto kv : vow)
        {
            std::cout << "sym: " << (char)kv.first << "\t|" << kv.first << "\t|" << kv.second << std::endl;
        }
        std::cout << std::endl;
    }

    void test9()
    {
        size_t hwm = 0;
        for(auto t : splits) 
            if (t.size() > hwm)
                hwm = t.size();
        if (hwm  >= 16)
            std::cout << "Longest is: " << hwm << std::endl;
    }

    void test10()
    {
        static int cnt = 1;
        char fname[32] = {0};
        SPRINTF(fname, "%d.json", cnt++);
        std::string xtostr;
        std::string ytostr;
        std::string json;
        json += "{\r\n";
        xtostr += "\"x\": [";
        ytostr += "\"y\": [";
        int vcnt = 0, ccnt = 0;
        for(auto p : paired) {
            char xs[16] = {0};
            char ys[16] = {0};
            #if 0
            if (is_vowel(p.at(0))) {
                SPRINTF(xs, "%d,", p.at(0) + p.at(1));
                SPRINTF(ys, "%d,", p.at(1) - p.at(0));
            } else {
                SPRINTF(xs, "%d,", p.at(0) - p.at(1));
                SPRINTF(ys, "%d,", p.at(1) + p.at(0));
            }
            #else
                SPRINTF(xs, "%d,", p.at(0));
                SPRINTF(ys, "%d,", p.at(1));
            #endif
            xtostr += xs;
            ytostr += ys;
            
        }

        xtostr.erase(xtostr.end()-1);
        xtostr += "]";
        json += xtostr;
        json += ",\r\n";
        ytostr.erase(ytostr.end()-1);
        ytostr += "]";
        json += ytostr;
        json += "\r\n}\r\n";

        std::ofstream myfile;
        myfile.open (fname);
        myfile << json;
        myfile.close();      
    }


    void test_from_file()
    {
        CharLookup cl;
        std::string txt;
        std::ifstream ifs {"data.txt"};
        std::string content( (std::istreambuf_iterator<char>(ifs) ),
                           (std::istreambuf_iterator<char>()    ) );
        removesym(content, ".\t\n");
        lowerall(content);
        split(content.c_str(), " ", splits);
        tablocation(content, tablocations);
        pairtext(splits, paired, nullptr);
#if 0 // hint me
            char fname[256] = {0};
            SPRINTF(fname, "/home/ilian/gitprojects/decrypto/decrypt/Text/%d.txt", cnt++);
            std::string text;
            writeout(text, fname);            
#endif         

    }

    void writeout(const std::string& txt, const char* fname)
    {
        std::ofstream myfile;
        myfile.open (fname);
        myfile << txt; 
        myfile.close();
    }

};


int main(void)
{        

#if 0
    DoWork w[LOOPCNT];
    std::vector<std::thread> workers;
    for(int i=0; i < LOOPCNT; i++) {
        workers.push_back(std::thread(&DoWork::operator(), &w[i]));
    }
    for(int i=0; i < LOOPCNT; i++)
        workers[i].join();

    for (int i = 0; i < LOOPCNT; i++) {
        w[i].test10();
    }
#else
    DoWork w;
    w.test_from_file();
//    CharLookup cl;
//    cl.print();
#endif
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

bool isprime(long long int a)
{
    if (a == 1) return false;
    for(long long int i = 2; i <= a / 2; i++) 
    {
        if (a % i == 0) 
            return false;
    }
    return true;
}

void lowerall(std::string& ref)
{
    for (int i=0; i < ref.size(); i++) 
    {
        ref[i] = tolower(ref[i]);
    }
}

