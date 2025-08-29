// Arquivo: src/core/ExtractorFactory.cpp

#include "core/ExtractorFactory.h"
#include "core/CSVExtractor.h"
#include "core/JSONExtractor.h"

std::unique_ptr<IDataExtractor> ExtractorFactory::createExtractor(const std::string& filepath) {
    if (filepath.size() > 4 && filepath.substr(filepath.size() - 4) == ".csv") {
        return std::make_unique<CSVExtractor>();
    }
    if (filepath.size() > 5 && filepath.substr(filepath.size() - 5) == ".json") {
        return std::make_unique<JSONExtractor>();
    }
    
    return nullptr; // Formato não suportado
}