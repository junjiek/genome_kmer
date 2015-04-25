#include "KmerSearcher.h"
#include <fstream>
#include <queue>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <climits>

inline int mypow(int x, int y) {
    int result = 1;
    for (int i = 0; i < y; i ++)
        result *= x;
    return result;
}

int index(char a) {
    switch(a) {
        case 'A': return A;
        case 'T': return T;
        case 'C': return C;
        case 'G': return G;
        default: return -1;
    }
}

void KmerSearcher::prepareHash() {
    int hash = mypow(HASH, k);
    for (int n = 0; n < 4; n++) {
        Hashk[n] = n * hash;
    }
}

void KmerSearcher::hashKmer(const char* str, int lineNum) {
    int hashCode = 0;
    for (int i = 0; i < k; i++) {
        hashCode = hashCode * HASH + index(str[i]);
    }
    invertedList[hashCode].push_back(make_pair(lineNum, 0));
    for (int i = 1; i <= (int)strlen(str)-k; i++) {
        hashCode = hashCode * HASH - Hashk[index(str[i-1])] + index(str[i+k-1]);
        vector<pair<int, int>> &list = invertedList[hashCode];
        list.push_back(make_pair(lineNum, i));
    }
}

int KmerSearcher::createIndex(const char *filename, const char* filename2, int k) {
    this->k = k;
    prepareHash();
    ifstream fin(filename);
    string line;
    char * buf;
    dataStr.clear();
    invertedList.clear();
    dataStr.push_back("null");
    while (getline(fin, line)) {
        if (line[0] == '>')
            continue;
        int lineNum = dataStr.size();
        buf = (char*)malloc(105);
        strcpy(buf, line.c_str()); 
        dataStr.push_back(buf);
        hashKmer(buf, lineNum);
    };
    fin.close();
    ifstream fin2(filename2);
    while (getline(fin2, line)) {
        if (line[0] == '>')
            continue;
        int lineNum = dataStr.size();
        buf = (char*)malloc(105);
        strcpy(buf, line.c_str()); 
        dataStr.push_back(buf);
        hashKmer(buf, lineNum);
    };
    fin2.close();
    return SUCCESS;
}

int KmerSearcher::searchKmer(const char *query, vector<pair<int, int> > &result) {
    result.clear();
    int hashCode = 0;
    for (int i = 0; i < k; i++) {
        hashCode = hashCode * HASH + index(query[i]);
    }
    unordered_map<int, vector<pair<int, int>>>::iterator iter;
    iter = invertedList.find(hashCode);
    if (iter != invertedList.end()) {
        result = iter->second;
    }
    return SUCCESS;
}
