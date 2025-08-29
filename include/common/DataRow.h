// Arquivo: include/common/DataRow.h

#ifndef DATA_ROW_H
#define DATA_ROW_H

#include <string>
#include <vector>
#include <iostream>

// Esta é a nossa estrutura de dados genérica para uma linha de registro.
// Ela não se importa se os dados vieram de um CSV, JSON ou banco de dados.
struct DataRow {
    std::vector<std::string> fields;

    void print() const {
        for (size_t i = 0; i < fields.size(); ++i) {
            std::cout << "[" << fields[i] << "]";
        }
        std::cout << std::endl;
    }
};

#endif // DATA_ROW_H