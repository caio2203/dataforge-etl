// Arquivo: include/core/JSONExtractor.h

#ifndef JSON_EXTRACTOR_H
#define JSON_EXTRACTOR_H

#include "core/IDataExtractor.h"
#include "utils/nlohmann/json.hpp" // Nossa biblioteca de terceiro

using json = nlohmann::json;

// Implementa o "contrato" IDataExtractor para arquivos JSON.
class JSONExtractor : public IDataExtractor {
private:
    json data;
    json::iterator it; // Iterador para percorrer o array de objetos JSON

public:
    JSONExtractor() = default;
    
    bool open(const std::string& source) override;
    bool readRow(DataRow& row) override;
    void close() override;
};

#endif // JSON_EXTRACTOR_H