// Arquivo: include/core/Loader.h

#ifndef LOADER_H
#define LOADER_H

#include "common/DataRow.h"
#include "fast_serializer/Serializer.h"
#include <memory>
#include <string>
#include <vector>

// A classe Loader é responsável pela etapa "Load" do ETL.
// Ela usa a biblioteca fast-serializer para fazer o trabalho pesado.
class Loader {
private:
    // Usamos um ponteiro inteligente para gerenciar o objeto Serializer
    std::unique_ptr<Serializer> m_serializer;
    bool m_header_written = false; // Controle para escrever o cabeçalho apenas uma vez

public:
    // O construtor abre o arquivo de saída
    Loader(const std::string& output_filename);

    // Escreve o cabeçalho e os metadados no arquivo binário
    void write_header_and_metadata(uint64_t record_count);

    // Processa uma única linha de dados agregados e a serializa
    void load_record(const DataRow& row);

    // Fecha o arquivo e finaliza a escrita
    void close();
};

#endif // LOADER_H