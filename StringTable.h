#include<string>
#include<iostream>

using namespace std;


const int MAX = 1000 ;


struct stringTableEntry{
 string data;
 stringTableEntry* next = nullptr;
 };
typedef stringTableEntry* StringTableRef;

class StringTable {

 public:
    StringTable();
    ~StringTable();
    stringTableEntry* insert(string item);
    stringTableEntry* search(string item);
    string search(stringTableEntry* ref);
    void print();
    void destruct();
private:
    stringTableEntry* bucket[MAX];
    int hash( string item);
    int num_col=0;
    int num_entries=0;
};

