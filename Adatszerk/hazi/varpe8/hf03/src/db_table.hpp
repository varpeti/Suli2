#ifndef DB_TABLE_H_
#define DB_TABLE_H_

#include <map>
#include <vector>
#include <sstream>

#include "hash.hpp"
#include "exp.hpp"

using namespace std;

class DB_TABLE
{
private:
    std::map<string, vector<string> > table;
    size_t row_size;

    bool alfanumeric(const string &str) const;
    bool contain_p0(const string &str) const;
    bool contain_col(const string &col) const;
public:
    DB_TABLE();
    
    void add_column(string name);
    std::vector<string> column_names() const;
    void add_row();
    size_t row_count();
    void set(string col, size_t row, string value);
    string get(string col, size_t row) const;
    DB_TABLE join(const DB_TABLE &other, string cond) const;
};

DB_TABLE::DB_TABLE()
{
    row_size = 0;
}

bool DB_TABLE::alfanumeric(const string &str) const // Trua ha csak szám vagy betű van benne
{
    for (unsigned int i = 0; i < str.size(); ++i)
    {   //                 numbers                                 UPCASE                               letters         
        if ( not( (str.at(i)>=48 and str.at(i)<=57) or (str.at(i)>=65 and str.at(i)<=90) or (str.at(i)>=97 and str.at(i)<=122) ) ) return false;
    }
    return true;
}

bool DB_TABLE::contain_p0(const string &str) const // False ha tartalmaz \0-at
{
    for (unsigned int i = 0; i < str.size(); ++i)
    {      
        if ( str.at(i)=='\0' ) return false;
    }
    return true;
}

bool DB_TABLE::contain_col(const string &col) const // True ha benne van.
{
    for (std::map<string, std::vector<string> >::const_iterator i = table.cbegin(); i != table.cend(); ++i)
    {
        if (col==i->first) return true;
    }
    return false;
}

void DB_TABLE::add_column(string name)
{
    if ( name=="" or  table.find(name)!=table.end() or !alfanumeric(name) ) 
    {
        throw invalid_column_name();
    }
    std::vector<string> v(row_size,"");
    table[name]=v;
}

std::vector<string> DB_TABLE::column_names() const
{
    std::vector<string> names;
    for (std::map<string, std::vector<string> >::const_iterator i = table.cbegin(); i != table.cend(); ++i)
    {
        names.push_back(i->first);
    }
    return names;
}

void DB_TABLE::add_row()
{
    for (std::map<string, std::vector<string> >::iterator i = table.begin(); i != table.end(); ++i)
    {
        i->second.push_back("");
    }
    row_size++;
}

size_t DB_TABLE::row_count()
{
    return row_size;
}

void DB_TABLE::set(string col, size_t row, string value)
{
    if ( table.find(col)==table.end() or row>row_size ) throw invalid_index();
    if ( !contain_p0(value) ) throw invalid_value();
    table[col][row]=value;
}

string DB_TABLE::get(string col, size_t row) const
{
    if ( table.find(col)==table.end() or row>row_size ) throw invalid_index();
    return table.at(col)[row];
}

DB_TABLE DB_TABLE::join(const DB_TABLE &other, string cond) const
{   
	//cond feldolgozása, hibák kiszűrése 
    struct sCo
    {
        string ca;
        string cb;
    };
    std::vector<sCo> sco;
    string line1;
    stringstream str1(cond);
    if (cond.at(cond.size()-1)==',') throw invalid_condition(); // , a végén
    while(getline(str1,line1,','))
    {
        string line2;
        stringstream str2(line1);
        char o = 0;
        sCo p;
        while(getline(str2,line2,'='))
        {   
            if      (o==0) if (      contain_col(line2)) p.ca = line2; else throw invalid_condition(); // Nincs ilyen oszlop az A ban
            else if (o==1) if (other.contain_col(line2)) p.cb = line2; else throw invalid_condition(); // Nincs ilyen oszlop a  B ben
            else throw invalid_condition(); // több egyenlőség jel
            o++;
        }
        if (o!=2) throw invalid_condition(); // nincs egyenlőség jel
        sco.push_back(p);
    }

    DB_TABLE uj;

    // Kiszűri az azonos nevű oszlopokat, és feltölti a neveket
    for (std::map<string, std::vector<string> >::const_iterator it = table.cbegin(); it != table.cend(); ++it)
    {   
        uj.add_column(it->first);
    }
    for (std::map<string, std::vector<string> >::const_iterator it = other.table.cbegin(); it != other.table.cend(); ++it)
    {   
       try {uj.add_column(it->first);} catch(...) {throw invalid_condition();} //Azonos oszlop
    }

    HASH hash;

    // Az A tábláből feltöltöm a hashtáblát
    for (unsigned int i = 0; i < row_size; ++i)
    {   
        string ca="";
        for (unsigned int j = 0; j < sco.size(); ++j)
        {
            //if (table.find(sco[j].ca)==table.end()) throw invalid_condition(); // Ha nincs ilyen oszlop // Ha nincsenek sorok (row.size==0), nem szűri ki hogy nincs ilyen oszlop, (nem jut el ide a program) ezért átkerült feljebb a vizsgálat
            ca += table.at(sco[j].ca)[i] + '\0'; //Így is működik (nálam) ha mégse: ca += table.at(sco[j].ca)[i]; ca.push_back('\0');
        }
        hash.set(ca,i);
    }

    //A B tábláblól pedig megnézem hogy benne van-e
    for (unsigned int i = 0; i < other.row_size; ++i)
    {   
        string cb="";
        for (unsigned int j = 0; j < sco.size(); ++j)
        {
            //if (other.table.find(sco[j].cb)==other.table.end()) throw invalid_condition(); // Ha nincs ilyen oszlop // Ha nincsenek sorok (other.row.size==0), nem szűri ki hogy nincs ilyen oszlop
            cb += other.table.at(sco[j].cb)[i] + '\0'; //Így is működik (nálam) ha mégse: ca += table.at(sco[j].ca)[i]; ca.push_back('\0');
        }

        size_t sor = hash.get(cb);
        if (sor!=0) // Ha stimmel, hozzáadja a sort
        {
            uj.add_row();
            for (std::map<string, std::vector<string> >::const_iterator it = table.cbegin(); it != table.cend(); ++it)
            {
                uj.set(it->first,uj.row_size-1,it->second[sor-1]);
            }
            for (std::map<string, std::vector<string> >::const_iterator it = other.table.cbegin(); it != other.table.cend(); ++it)
            {   
                uj.set(it->first,uj.row_size-1,it->second[i]);
            }
        }
    }
    return uj;
}

#endif