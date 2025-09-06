#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include <string>
#include "database.h"

class QueryParser {
public:
    QueryParser(Database& db) : db(db) {}
    void parse(const std::string& query);

private:
    Database& db;
};

#endif
