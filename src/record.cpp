#include "record.h"

bool Record::matches(const std::string& column, const std::string& value, const std::vector<std::string>& columns) const {
    for (size_t i = 0; i < columns.size(); i++) {
        if (columns[i] == column && values[i] == value) return true;
    }
    return false;
}

void Record::print() const {
    for (size_t i = 0; i < values.size(); ++i) {
        if (i) std::cout << " ";
        std::cout << values[i];
    }
    std::cout << "\n";
}
