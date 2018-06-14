#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
using namespace std;

int turn = 1;
map<unsigned int, list<unsigned int> > fourcache;
map<unsigned int, unsigned int> directcache;
list<unsigned int> fullycache;
vector<int> hit;
vector<int> miss;

int string_to_int(string);
unsigned int hexadecimal_to_decimal(string);
int log2(int);
void direct_mapped(unsigned int,unsigned int);
void four_way_set_associative(unsigned int, unsigned int, int);
void fully_associative (unsigned int, int, int);

int main(int argc, char* argv[]){
    fstream file;
    ofstream out(argv[4]);
    file.open(argv[2] ,ios::in);
    //out.open(argv[4] ,ios::out);


    int cache_size;
    int block_size;
    int associativity;
    int algorithm;

    string cache_size_string;
    string block_size_string;
    string associativitystring;
    string algorithmstring;
    getline(file, cache_size_string);
    getline(file, block_size_string);
    getline(file, associativitystring);
    getline(file, algorithmstring);
    cache_size = string_to_int(cache_size_string) * 1024;
    block_size = string_to_int(block_size_string);
    associativity = string_to_int(associativitystring);
    algorithm = string_to_int(algorithmstring);

    int block_number = cache_size / block_size;
    int words = log2(block_size);
    /*
    cout << "cache_size: " << cache_size << endl;
    cout << "block_size: " << block_size << endl;
    cout << "associativity: " << associativity << endl;
    cout << "algorithm: " << algorithm << endl;
    cout << "block_number: " << block_number << endl;
    cout << "words: " << words << endl;
    */
    string inputstring;
    if(associativity == 0){
        while(getline(file, inputstring)){
            //cout << inputstring << endl << inputstring.substr(2,8) << endl;
            unsigned int address = (hexadecimal_to_decimal(inputstring.substr(2,8)) >> words);
            direct_mapped(address, address%(block_number));
            //cout << address << endl;
        }
    }
    else if(associativity == 1){
        while(getline(file, inputstring)){
            //cout << inputstring << endl << inputstring.substr(2,8) << endl;
            unsigned int address = (hexadecimal_to_decimal(inputstring.substr(2,8)) >> words);
            four_way_set_associative(address, address%((unsigned int)block_number/4), algorithm);
            //cout << address << endl;
        }
    }
    else {
        while(getline(file, inputstring)){
            //cout << inputstring << endl << inputstring.substr(2,8) << endl;
            unsigned int address = (hexadecimal_to_decimal(inputstring.substr(2,8)) >> words);
            fully_associative(address, block_number, algorithm);
            //cout << address << endl;
        }
    }

    out << "Hits instructions: ";
    for(int i = 0; i < hit.size();++i){
        if(i == hit.size()-1){
            out << hit[i];
            break;
        }
        out << hit[i] << ",";
    }
    out << endl << "Misses instructions: ";
    for(int i = 0; i < miss.size();++i){
        if(i == miss.size()-1){
            out << miss[i];
            break;
        }
        out << miss[i] << ",";
    }

    out << endl << "Miss rate: " << (float)miss.size()/(float)(hit.size()+ miss.size()) << endl;
    //cout << "Miss rate: " << (float)miss.size()/(float)(hit.size()+ miss.size()) << endl;
    return 0;
}

void fully_associative (unsigned int address, int block_number, int algorithm){
    if(algorithm == 0){
        if(find(fullycache.begin(), fullycache.end(), address) != fullycache.end()){
            hit.push_back(turn);
        }
        else{
            miss.push_back(turn);
            if(fullycache.size() >= block_number){
                fullycache.pop_front();
            }
            fullycache.push_back(address);
        }
    }
    else {
        if(find(fullycache.begin(), fullycache.end(), address) != fullycache.end()){
            hit.push_back(turn);
            fullycache.remove(address);
            fullycache.push_back(address);
        }
        else{
            miss.push_back(turn);
            if(fullycache.size() >= block_number){
                fullycache.pop_front();
            }
            fullycache.push_back(address);
        }
    }
    turn ++;
}

void direct_mapped(unsigned int address,unsigned int index){
    if(directcache.find(index) == directcache.end()){
        directcache[index] = address;
        miss.push_back(turn);
    }
    else {
        if(directcache[index] == address){
            hit.push_back(turn);
        }
        else {
            miss.push_back(turn);
            directcache[index] = address;
        }
        turn++;
    }
}

void four_way_set_associative(unsigned int address, unsigned int index, int algorithm){
    //cout << "address: " << address << endl;
    //cout << "index: " << index << endl;
    if(fourcache.find(index) == fourcache.end()){
        list<unsigned int> a;
        fourcache[index] = a;
        fourcache[index].push_back(address);
        miss.push_back(turn);
    }
    else {
        if(algorithm == 0){
            if(find(fourcache[index].begin(), fourcache[index].end(), address) != fourcache[index].end()){
                hit.push_back(turn);
            }
            else {
                miss.push_back(turn);
                if(fourcache[index].size() >= 4){
                    fourcache[index].pop_front();
                }
                fourcache[index].push_back(address);
            }
        }
        else{
            if(find(fourcache[index].begin(), fourcache[index].end(), address) != fourcache[index].end()){
                hit.push_back(turn);
                fourcache[index].remove(address);
                fourcache[index].push_back(address);
            }
            else {
                miss.push_back(turn);
                if(fourcache[index].size() >= 4){
                    fourcache[index].pop_front();
                }
                fourcache[index].push_back(address);
            }
        }
    }
    turn++;
}

int string_to_int(string input){
    stringstream ss;
    ss << input;
    int output;
    ss >> output;
    return output;
}

unsigned int hexadecimal_to_decimal(string input){
    unsigned int output;
    stringstream ss;
    ss << std::hex << input;
    ss >> output;
    return output;
}

int log2(int input){
    int output = log(input) / log(2);
    return output;
}
