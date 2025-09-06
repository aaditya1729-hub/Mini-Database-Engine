#include <iostream>
#include <string>
#include "database.h"
#include "queryparser.h"

int main() {
    Database db;
    QueryParser parser(db);

    std::cout << "MiniDB Engine Started (type EXIT to quit)\n";
    std::string line;
    while (true) {
        std::cout << "MiniDB> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "EXIT" || line == "exit") break;
        if (line.empty()) continue;
        parser.parse(line);
    }
    return 0;
}
