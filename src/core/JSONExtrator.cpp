// Arquivo: src/core/JSONExtractor.cpp

#include "core/JSONExtractor.h"
#include <fstream>
#include <iostream>

bool JSONExtractor::open(const std::string& source) {
    std::ifstream file(source);
    if (!file.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo JSON " << source << std::endl;
        return false;
    }
    
    try {
        data = json::parse(file);
    } catch (json::parse_error& e) {
        std::cerr << "Erro de parse no JSON: " << e.what() << std::endl;
        return false;
    }
    
    if (!data.is_array()) {
        std::cerr << "Erro: O JSON raiz deve ser um array de objetos." << std::endl;
        return false;
    }

    it = data.begin();
    return true;
}

bool JSONExtractor::readRow(DataRow& row) {
    if (it == data.end()) {
        return false; // Fim dos dados
    }

    row.fields.clear();
    const auto& jsonObj = *it;

    // Converte todos os valores do objeto JSON para string
    if(jsonObj.is_object()) {
        for (auto& el : jsonObj.items()) {
            row.fields.push_back(el.value().dump());
        }
    }

    ++it;
    return true;
}

void JSONExtractor::close() {
    data.clear();
}