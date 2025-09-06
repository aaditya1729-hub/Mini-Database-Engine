#include "bplustree.h"

void BPlusTree::insert(int key, int recordId) {
    index[key].push_back(recordId);
}

std::vector<int> BPlusTree::search(int key) {
    if (index.find(key) != index.end()) return index[key];
    return {};
}

std::vector<int> BPlusTree::rangeQuery(int low, int high) {
    std::vector<int> result;
    for (auto& [k, ids] : index) {
        if (k >= low && k <= high) {
            result.insert(result.end(), ids.begin(), ids.end());
        }
    }
    return result;
}
