//
//  Dictionary.cpp
//  EWeek4
//
//  Created by CLAYTON WONG on 5/23/18.
//  Copyright © 2018 Clayton Wong. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Dictionary.hpp"

using namespace std;

Dictionary::Dictionary(const char* filename) {
    ifstream fin;
    fin.open(filename);
    if (!fin.is_open())
        return;
    try{
        string str;
        while (getline(fin,str)){
            istringstream ss(str);
            string word;
            while (ss >> word){
                transform(word.begin(),word.end(),word.begin(),::tolower);
                myWords.insert(word);
            }
        }
        fin.close();
    } catch(...) {
        fin.close();
    }
}

bool Dictionary::Contains(const std::string & word) const {
    string w(word);
    transform(w.begin(),w.end(),w.begin(),::tolower);
    return myWords.find(w)!=myWords.end();
}


