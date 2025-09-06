#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <vector>
#include <unordered_map>

class BPlusTree {
public:
    BPlusTree() {}
    void insert(int key, int recordId);
    std::vector<int> search(int key);
    std::vector<int> rangeQuery(int low, int high);

private:
    std::unordered_map<int, std::vector<int>> index;
};

#endif
