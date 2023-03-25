#include <iostream>
#include <cstring>
#include <algorithm>
#include <crypt.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

void findPass(string pass, const string& hash)
{
    crypt_data *pCryptData = new crypt_data;
    size_t pos = hash.find_last_of('$');
    string hashHead = hash.substr(0,pos);
    do {
        string newHash(crypt_r(pass.data(),hashHead.data(),pCryptData));
        if (newHash == hash) {
            cout<<"Hash: "<<hash<<endl<<"Pass: "<<pass<<endl;
            break;
        }
    } while ( next_permutation( pass.begin(), pass.end() ) );
    delete pCryptData;
}

int main()
{
    string hashpsw;
    string chs = "123456789";
    ifstream MyFile;
    MyFile.open("/media/Общедоступные/Для 7 лабы/hashes");
    while (!MyFile.eof()) {
        MyFile>>hashpsw;
        findPass(chs, hashpsw);
    }
    return 0;
}