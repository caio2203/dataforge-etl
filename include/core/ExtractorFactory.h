// Arquivo: include/core/ExtractorFactory.h

#ifndef EXTRACTOR_FACTORY_H
#define EXTRACTOR_FACTORY_H

#include "core/IDataExtractor.h"
#include <string>
#include <memory> // Para std::unique_ptr

// Classe Fábrica que cria o extrator apropriado em tempo de execução.
class ExtractorFactory {
public:
    static std::unique_ptr<IDataExtractor> createExtractor(const std::string& filepath);
};

#endif // EXTRACTOR_FACTORY_H