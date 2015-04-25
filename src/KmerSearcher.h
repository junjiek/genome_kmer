#ifndef KMERSEARCHER_H_
#define KMERSEARCHER_H_

#include <vector>
#include <utility>
#include <cstring>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <climits>

const int SUCCESS = 0;
const int FAILURE = 1;
const int HASH = 95891;
const int A = 0;
const int T = 1;
const int C = 2;
const int G = 3;

using namespace std;

class KmerSearcher {
private:
    int k;
    int Hashk[4];
public:
    unordered_map<int, vector<pair<int, int>>> invertedList;
    vector<const char*> dataStr;
    KmerSearcher() {}
    ~KmerSearcher() {}
    void prepareHash();
    void hashKmer(const char* str, int lineNum);
    int createIndex(const char *filename, const char* filename2, int k);
    int searchKmer(const char *query, vector<pair<int, int> > &result);
};

#endif
