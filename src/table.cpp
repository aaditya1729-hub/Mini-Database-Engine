#include "table.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

static int ensure_int(const std::string& s){ try{ return std::stoi(s);}catch(...){ return 0;} }

Table::Table(const std::string& name, const std::vector<std::string>& cols) {
    this->name = name;
    // If file exists, load columns from file header; else use provided cols
    std::string f = this->filename();
    if (std::filesystem::exists(f)) {
        // load will set columns and records
        loadFromFile();
        // ensure bplus indexes on numeric columns
        for (auto &c : columns) if (c=="age"||c=="id") bplusIndexes[c]=BPlusTree();
        // rebuild indexes from records
        for (auto &kv : records) {
            int id = kv.first;
            const Record &r = kv.second;
            for (size_t i=0;i<columns.size();++i){
                if (bplusIndexes.find(columns[i])!=bplusIndexes.end()){
                    int key = ensure_int(r.get(i));
                    bplusIndexes[columns[i]].insert(key, id);
                }
            }
            nextId = std::max(nextId, id+1);
        }
    } else {
        this->columns = cols;
        // create indexes for id/age by default
        for (auto &c : columns) if (c=="age"||c=="id") bplusIndexes[c]=BPlusTree();
        // ensure data dir exists
        std::filesystem::create_directories("data");
        saveToFile(); // write header
    }
}

std::string Table::filename() const {
    return "data/" + name + ".tbl";
}

void Table::insert(const std::vector<std::string>& values) {
    if (values.size() != columns.size()) {
        std::cout << "Column count mismatch\n";
        return;
    }
    Record rec(values);
    int id = nextId++;
    records[id] = rec;
    // update indexes
    for (size_t i=0;i<columns.size();++i){
        auto it = bplusIndexes.find(columns[i]);
        if (it!=bplusIndexes.end()) {
            int key = ensure_int(values[i]);
            it->second.insert(key, id);
        }
    }
    saveToFile();
}

void Table::select(const std::string& column, const std::string& value) {
    auto it = bplusIndexes.find(column);
    if (it != bplusIndexes.end()) {
        int key = ensure_int(value);
        auto res = it->second.search(key);
        for (int id : res) records[id].print();
        return;
    }
    // fallback linear search
    for (auto &kv : records) {
        const Record &r = kv.second;
        if (r.matches(column, value, columns)) r.print();
    }
}

void Table::selectRange(const std::string& column, int low, int high) {
    auto it = bplusIndexes.find(column);
    if (it == bplusIndexes.end()) {
        std::cout << "No B+Tree index on column: " << column << "\n";
        return;
    }
    auto res = it->second.rangeQuery(low, high);
    for (int id : res) records[id].print();
}

void Table::remove(const std::string& column, const std::string& value) {
    std::vector<int> toDelete;
    for (auto &kv : records) {
        if (kv.second.matches(column, value, columns)) toDelete.push_back(kv.first);
    }
    for (int id : toDelete) records.erase(id);
    saveToFile();
}

void Table::saveToFile() const {
    std::ofstream out(filename(), std::ios::trunc);
    // header: columns separated by |
    for (size_t i=0;i<columns.size();++i){ out << columns[i]; if (i+1<columns.size()) out << "|"; }
    out << "\n";
    // each record: id|v1|v2|...
    for (auto &kv : records) {
        out << kv.first;
        for (size_t i=0;i<kv.second.size();++i) out << "|" << kv.second.get(i);
        out << "\n";
    }
}

void Table::loadFromFile() {
    std::ifstream in(filename());
    if (!in.good()) return;
    std::string line;
    if (!std::getline(in, line)) return;
    // header line
    {
        columns.clear();
        std::stringstream ss(line);
        std::string tok;
        while (std::getline(ss, tok, '|')) columns.push_back(tok);
    }
    records.clear();
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string idtok;
        if (!std::getline(ss, idtok, '|')) continue;
        int id = std::stoi(idtok);
        std::vector<std::string> vals;
        std::string tok;
        while (std::getline(ss, tok, '|')) vals.push_back(tok);
        Record r(vals);
        records[id] = r;
    }
}
