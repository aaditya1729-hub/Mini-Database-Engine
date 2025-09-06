#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <unordered_map>
#include "record.h"
#include "bplustree.h"

class Table {
public:
    Table() {}
    Table(const std::string& name, const std::vector<std::string>& cols);

    void insert(const std::vector<std::string>& values);
    void select(const std::string& column, const std::string& value);
    void selectRange(const std::string& column, int low, int high);
    void remove(const std::string& column, const std::string& value);

private:
    std::string name;
    std::vector<std::string> columns;
    std::unordered_map<int, Record> records;
    std::unordered_map<std::string, BPlusTree> bplusIndexes;
    int nextId = 1;

    void loadFromFile();
    void saveToFile() const;
    std::string filename() const;
};

#endif

// #ifndef TABLE_H
// #define TABLE_H

// #include <string>
// #include <vector>
// #include <unordered_map>
// #include "record.h"
// #include "bplustree.h"

// class Table {
// public:
//     Table() {}
//     Table(const std::string& name, const std::vector<std::string>& cols);

//     void insert(const std::vector<std::string>& values);
//     void select(const std::string& column, const std::string& value);
//     void selectRange(const std::string& column, int low, int high);
//     void remove(const std::string& column, const std::string& value);

//     //  For benchmarking: get all records
//     std::vector<Record> getAllRecords() const {
//         std::vector<Record> all;
//         for (const auto &kv : records) {
//             all.push_back(kv.second);
//         }
//         return all;
//     }

//     // For benchmarking: range query using B+Tree
//     std::vector<Record> rangeQuery(const std::string& column, int low, int high) {
//         std::vector<Record> result;
//         auto it = bplusIndexes.find(column);
//         if (it == bplusIndexes.end()) return result;

//         auto &index = it->second;
//         auto values = index.rangeSearch(low, high);

//         for (int key : values) {
//             if (records.find(key) != records.end()) {
//                 result.push_back(records[key]);
//             }
//         }
//         return result;
//     }

// private:
//     std::string name;
//     std::vector<std::string> columns;
//     std::unordered_map<int, Record> records;
//     std::unordered_map<std::string, BPlusTree> bplusIndexes;
//     int nextId = 1;

//     void loadFromFile();
//     void saveToFile() const;
//     std::string filename() const;
// };

// #endif

