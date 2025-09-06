#include "database.h"
#include <iostream>
#include <filesystem>

void Database::createTable(const std::string& name, const std::vector<std::string>& columns) {
    if (tables.find(name) != tables.end()) {
        std::cout << "Table already exists.\n";
        return;
    }
    // If file exists, Table constructor will load columns from file; pass columns anyway
    tables.emplace(std::make_pair(name, Table(name, columns)));
    std::cout << "Created table " << name << "\n";
}

void Database::insert(const std::string& tableName, const std::vector<std::string>& values) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        std::cout << "Table not found: " << tableName << "\n";
        return;
    }
    it->second.insert(values);
    std::cout << "Inserted record into " << tableName << "\n";
}

void Database::select(const std::string& tableName, const std::string& column, const std::string& value) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        std::cout << "Table not found: " << tableName << "\n";
        return;
    }
    it->second.select(column, value);
}

void Database::selectRange(const std::string& tableName, const std::string& column, int low, int high) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        std::cout << "Table not found: " << tableName << "\n";
        return;
    }
    it->second.selectRange(column, low, high);
}

void Database::remove(const std::string& tableName, const std::string& column, const std::string& value) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        std::cout << "Table not found: " << tableName << "\n";
        return;
    }
    it->second.remove(column, value);
    std::cout << "Deleted record(s) from " << tableName << "\n";
}
