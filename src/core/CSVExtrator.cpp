// Arquivo: src/core/CSVExtractor.cpp

#include "core/CSVExtractor.h"
#include <sstream>
#include <iostream>

CSVExtractor::CSVExtractor(char delim) : delimiter(delim) {}

bool CSVExtractor::open(const std::string& source) {
    file.open(source);
    if (!file.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo CSV " << source << std::endl;
        return false;
    }
    return true;
}

bool CSVExtractor::readRow(DataRow& row) {
    std::string line;
    if (std::getline(file, line)) {
        row.fields.clear();
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, delimiter)) {
            row.fields.push_back(field);
        }
        return true;
    }
    return false;
}

void CSVExtractor::close() {
    if (file.is_open()) {
        file.close();
    }
}