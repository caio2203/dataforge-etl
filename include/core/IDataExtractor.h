// Arquivo: include/core/IDataExtractor.h

#ifndef IDATA_EXTRACTOR_H
#define IDATA_EXTRACTOR_H

#include "common/DataRow.h" // Usa nossa estrutura de dados comum
#include <string>
#include <vector>

// Interface (contrato) que todos os extratores devem seguir.
// Garante que o motor possa tratar qualquer fonte de dados da mesma maneira.
class IDataExtractor {
public:
    virtual ~IDataExtractor() = default; // Destrutor virtual é obrigatório!

    virtual bool open(const std::string& source) = 0;
    virtual bool readRow(DataRow& row) = 0; 
    virtual void close() = 0;
};

#endif // IDATA_EXTRACTOR_H