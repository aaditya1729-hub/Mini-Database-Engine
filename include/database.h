#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <unordered_map>
#include "table.h"

class Database {
public:
    void createTable(const std::string& name, const std::vector<std::string>& columns);
    void insert(const std::string& tableName, const std::vector<std::string>& values);
    void select(const std::string& tableName, const std::string& column, const std::string& value);
    void selectRange(const std::string& tableName, const std::string& column, int low, int high);
    void remove(const std::string& tableName, const std::string& column, const std::string& value);

private:
    std::unordered_map<std::string, Table> tables;
};

#endif
