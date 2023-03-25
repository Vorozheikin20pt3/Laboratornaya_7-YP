#include <iostream>
#include <cstring>
#include <algorithm>
#include <crypt.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <thread>
using namespace std;
class findPass
{
public:
    void operator()(string pass, const string& hash)
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
};
int main()
{
    string hash;
    string hashes[8];
    thread thread_array[8];
    ifstream MyFile;
    int x =0;
    MyFile.open("/media/Общедоступные/Для 7 лабы/8.txt");
    while(!MyFile.eof()) {
        MyFile >> hashes[x];
        x++;
    }
    for (int i=0; i<8; i++) {
        hash = hashes[i];
        thread_array[i] = thread(findPass(),"123456789", hash);
    }
    for (int k=0; k<8; k++) {
        if (thread_array[k].joinable()) {
            thread_array[k].join();
        }
    }
    return 0;
}