#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
int cache_size;
int block_size;
int blocks;
int words;
int cache_index;
int associativity;
int algorithm;
int turn = 1;
list <string> tag_index;
vector <string> index;
vector <list<string> > index_of_4;
vector <int> hit;
vector <int> miss;

string hexadecimal_to_binarystring(char);
int string_to_int(string input){
    stringstream ss;
    ss << input;
    int output;
    ss >> output;
    return output;
}
string hexadecimal_to_binary(string input){
    //cout << input << "\n";
    string output;
    for(int i = 0; i < 8; ++i){
        output += hexadecimal_to_binarystring(input[i]);
    }

	//cout << output << "\n";
    return output;
}
int binary_to_decimal(string input){
    int output = 0;
    int mux = 1;
    for(int i = input.length()-1 ; i >= 0; --i){
        output += mux*(input[i] == '0'? 0:1);
        mux *= 2;
    }
    return output;
}
string hexadecimal_to_binarystring(char input){
    switch(input){
        case '0' :
            return "0000";
            break;
        case '1':
            return "0001";
            break;
        case '2' :
            return "0010";
            break;
        case '3':
            return "0011";
            break;
        case '4' :
            return "0100";
            break;
        case '5':
            return "0101";
            break;
        case '6' :
            return "0110";
            break;
        case '7':
            return "0111";
            break;
        case '8' :
            return "1000";
            break;
        case '9':
            return "1001";
            break;
        case 'a':
        case 'A':
            return "1010";
            break;
        case 'b' :
        case 'B':
            return "1011";
            break;
        case 'c':
        case 'C':
            return "1100";
            break;
        case 'd' :
        case 'D':
            return "1101";
            break;
        case 'e':
        case 'E':
            return "1110";
            break;
        case 'f':
        case 'F':
            return "1111";
            break;
    }
}

int log2(int input){
    int output = log(input) / log(2);
    return output;
}
void fully_associative (string input){
    if(algorithm == 0){
        if(find(tag_index.begin(), tag_index.end(), input) != tag_index.end()){
            hit.push_back(turn);
        }
        else{
            if(tag_index.size() == cache_index){
                tag_index.erase(tag_index.begin());
            }
            miss.push_back(turn);
            tag_index.push_back(input);
        }
    }
    else {
        if(find(tag_index.begin(), tag_index.end(), input) != tag_index.end()){
            hit.push_back(turn);
            tag_index.remove(input);
            tag_index.push_back(input);
        }
        else{
            if(tag_index.size() == cache_index){
                tag_index.erase(tag_index.begin());
            }
            miss.push_back(turn);
            tag_index.push_back(input);
        }
    }

}
void four_way_set_associative(string inputaddress,string inputindex){
    if(find(index_of_4[binary_to_decimal(inputindex)].begin(), index_of_4[binary_to_decimal(inputindex)].end(), inputaddress) != index_of_4[binary_to_decimal(inputindex)].end()){
        hit.push_back(turn);
    }
    else{
        if(index_of_4[binary_to_decimal(inputindex)].size() == blocks/4){
                index_of_4[binary_to_decimal(inputindex)].erase(index_of_4[binary_to_decimal(inputindex)].begin());
            }
            miss.push_back(turn);
            index_of_4[binary_to_decimal(inputindex)].push_back(inputaddress);
    }
}
void direct_mapped(string inputaddress,string inputindex){
    if(index[binary_to_decimal(inputindex)] == inputaddress){
        hit.push_back(turn);
    }
    else{
        miss.push_back(turn);
        index[binary_to_decimal(inputindex)] = inputaddress;
    }

}
int main(){
    fstream file;
    file.open("trace1.txt",ios::in);

    string cache_size_string;
    getline(file, cache_size_string);
    cache_size = string_to_int(cache_size_string);

    string block_size_string;
    getline(file, block_size_string);
    block_size = string_to_int(block_size_string);

    blocks = cache_size/block_size;
    cache_index = log2(blocks);
    words = log2(block_size);

    //cout << cache_size << "\n" << block_size << "\n" << blocks << "\n" << cache_index << "\n" << words << "\n";

    string associativitystring;
    getline(file, associativitystring);
    associativity = string_to_int(associativitystring);
    //cout << associativity << "\n";

    string algorithmstring;
    getline(file, algorithmstring);
    algorithm = string_to_int(algorithmstring);
    //cout << algorithm << "\n";

    if(associativity == 2){
        while(file.peek() != EOF){
            string inputstring;
            getline(file, inputstring);
            string intputaddress = hexadecimal_to_binary(inputstring.substr(2,10));
            //cout << intputaddress.substr(0,32-words+1) << "\n";
            fully_associative(intputaddress.substr(0,32-words+1));
            turn++;
        }
        cout << "Hits instructions: ";
        for(int i = 0; i < hit.size();++i){
            if(i == hit.size()-1){
                cout << hit[i];
                break;
            }
            cout << hit[i] << ",";
        }
        cout << "\nMisses instructions: ";
        for(int i = 0; i < miss.size();++i){
            if(i == miss.size()-1){
                cout << miss[i];
                break;
            }
            cout << miss[i] << ",";
        }
        cout << "\nMiss rate: " << (float)miss.size()/(float)(hit.size()+ miss.size());
    }
    else if(associativity == 1){
        for(int i = 0; i < blocks/4;++i){
            list<string> a;
            index_of_4.push_back(a);
        }
        while(file.peek() != EOF){
            string inputstring;
            getline(file, inputstring);
            string intputaddress = hexadecimal_to_binary(inputstring.substr(2,10));
            //cout << intputaddress.substr(0,32-words+1) << "\n";
            four_way_set_associative(intputaddress.substr(0,32-words+1), intputaddress.substr(32-words+1-cache_index, cache_index-2));
            turn++;
        }
        cout << "Hits instructions: ";
        for(int i = 0; i < hit.size();++i){
            if(i == hit.size()-1){
                cout << hit[i];
                break;
            }
            cout << hit[i] << ",";
        }
        cout << "\nMisses instructions: ";
        for(int i = 0; i < miss.size();++i){
            if(i == miss.size()-1){
                cout << miss[i];
                break;
            }
            cout << miss[i] << ",";
        }
        cout << "\nMiss rate: " << (float)miss.size()/(float)(hit.size()+ miss.size());
    }
    else if(associativity == 0){
        for(int i = 0; i < blocks;++i){
            index.push_back("null");
        }
        while(file.peek() != EOF){
            string inputstring;
            getline(file, inputstring);
            string intputaddress = hexadecimal_to_binary(inputstring.substr(2,10));
            //cout << intputaddress.substr(0,32-words+1) << "\n";
            direct_mapped(intputaddress.substr(0,32-words+1), intputaddress.substr(32-words+1-cache_index, cache_index));
            turn++;
        }
        cout << "Hits instructions: ";
        for(int i = 0; i < hit.size();++i){
            if(i == hit.size()-1){
                cout << hit[i];
                break;
            }
            cout << hit[i] << ",";
        }
        cout << "\nMisses instructions: ";
        for(int i = 0; i < miss.size();++i){
            if(i == miss.size()-1){
                cout << miss[i];
                break;
            }
            cout << miss[i] << ",";
        }
        cout << "\nMiss rate: " << (float)miss.size()/(float)(hit.size()+ miss.size());
    }

    return 0;
}


