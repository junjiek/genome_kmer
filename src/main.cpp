#include <iostream>
#include "KmerSearcher.h"

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s k query\n", argv[0]);
        return 1;
    }
    int k = atoi(argv[1]);
    KmerSearcher searcher;
    clock_t start, end;
    start = clock();
    searcher.createIndex("../data/solexa_100_170_1.fa", "../data/solexa_100_170_2.fa", k);
    end = clock();
    printf("dict built (%.2lfs passed, list size: %lu)\n",
                        (end-start)/1000.0, searcher.invertedList.size());
    FILE * fp = fopen(argv[2], "r");
    char *line = NULL;
    size_t len = 0;
    vector<pair<int, int>> result;
    while (getline(&line, &len, fp) != -1) {
        line[strlen(line)-1] = '\0';
        start = clock();
        searcher.searchKmer(line, result);
        end = clock();
        printf("+ %s (%.2lfs passed, %lu results found)\n",
                  line, (end-start)/1000.0, result.size());
        // for (auto& i: result) {
        //     string s = string(searcher.dataStr[i.first]);
        //     printf(" %d (%d, %d) : %s\n", i.first, i.second, i.second+k-1, s.substr(i.second, k).c_str());
        // }
    }
    fclose(fp);
    return 0;
}