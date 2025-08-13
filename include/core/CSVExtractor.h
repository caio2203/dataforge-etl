// Arquivo: include/core/CSVExtractor.h

#ifndef CSV_EXTRACTOR_H
#define CSV_EXTRACTOR_H

#include "core/IDataExtractor.h"
#include <fstream>

// Implementa o "contrato" IDataExtractor para arquivos CSV.
class CSVExtractor : public IDataExtractor {
private:
    std::ifstream file;
    char delimiter;

public:
    CSVExtractor(char delim = ',');
    
    bool open(const std::string& source) override;
    bool readRow(DataRow& row) override;
    void close() override;
};

#endif // CSV_EXTRACTOR_H