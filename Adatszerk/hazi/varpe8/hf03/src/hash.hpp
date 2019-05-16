#ifndef HASH_H_
#define HASH_H_

#include <string>
#include "exp.hpp"

using namespace std;

class HASH
{
private:
    struct stressor
    {
        string str;
        size_t sor;
    };
    stressor htable[256];
    unsigned char _set(string &str);
public:
    HASH();

    void set(string str,size_t sor); // Belerak
    size_t get(string str); // Benne van-e? x=0 nem, x>0 akk x-1=sor
};

HASH::HASH()
{
    for (int i = 0; i < 256; ++i)
    {
        htable[i].str="";
        htable[i].sor=0;
    }
}

unsigned char HASH::_set(string &str)
{
    unsigned int c = 1;
    for (unsigned int i = 0; i < str.size(); ++i)
    {
        c = (c*256+(unsigned char)str.at(i));
    }
    return c%257%256;
}

void HASH::set(string str,size_t sor)
{
    unsigned int it=0;
    unsigned char hid; 
    do {
        string u = str;
        u+=(unsigned char)it;
        hid = _set(u);
        it++;
    } while(htable[hid].str!="" and htable[hid].str!=str and it<256);

    if (it==256) {throw EXP("HASH_betelt"); }

    htable[hid].str=str;
    htable[hid].sor=sor;
}

size_t HASH::get(string str)
{
    unsigned int it=0;
    unsigned char hid; 
    do {
        string u = str;
        u+=(unsigned char)it;
        hid = _set(u);
        it++;
    } while(htable[hid].str!=str and htable[hid].str!="" and it<256);

    if (htable[hid].str!=str) return 0;
    return htable[hid].sor+1;
}

#endif