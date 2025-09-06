#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>
#include <iostream>

class Record {
public:
    Record() {}
    Record(const std::vector<std::string>& values) : values(values) {}
    bool matches(const std::string& column, const std::string& value, const std::vector<std::string>& columns) const;
    void print() const;

    size_t size() const { return values.size(); }
    const std::string& get(size_t i) const { return values[i]; }

private:
    std::vector<std::string> values;
};

#endif
