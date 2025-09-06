#include "queryparser.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip> 

static std::string toLowerCopy(std::string s){ std::transform(s.begin(), s.end(), s.begin(), ::tolower); return s; }

void QueryParser::parse(const std::string& query) {
    std::istringstream iss(query);
    std::string command;
    iss >> command;
    if (command.empty()) return;
    std::string cmdLower = toLowerCopy(command);

    if (cmdLower == "create") {
        std::string tableName;
        iss >> tableName;
        std::vector<std::string> columns;
        std::string col;
        while (iss >> col) columns.push_back(col);
        db.createTable(tableName, columns);
    }
    else if (cmdLower == "insert") {
        std::string tableName;
        iss >> tableName;
        std::vector<std::string> values;
        std::string val;
        // read remaining tokens as values (handles quoted strings without splitting inside quotes poorly)
        while (iss >> std::quoted(val)) values.push_back(val);
        if (values.empty()) {
            // fallback: simple split by whitespace
            iss.clear();
            iss.str(query);
            std::string token; iss >> token; // command
            iss >> token; // tableName
            while (iss >> token) values.push_back(token);
        }
        db.insert(tableName, values);
    }
    else if (cmdLower == "select") {
        std::string tableName, column, value;
        iss >> tableName >> column >> value;
        if (value.empty()) { std::cout << "Usage: select <table> <column> <value_or_range>\n"; return; }
        size_t dashPos = value.find('-');
        if (dashPos != std::string::npos) {
            try {
                int low = std::stoi(value.substr(0, dashPos));
                int high = std::stoi(value.substr(dashPos + 1));
                db.selectRange(tableName, column, low, high);
            } catch (...) {
                std::cout << "Invalid range format. Use e.g. 20-30\n";
            }
        } else {
            db.select(tableName, column, value);
        }
    }
    else if (cmdLower == "delete") {
        std::string tableName, column, value;
        iss >> tableName >> column >> value;
        db.remove(tableName, column, value);
    }
    else {
        std::cout << "Unknown command.\n";
    }
}
