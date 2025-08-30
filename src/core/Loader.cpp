// Arquivo: src/core/Loader.cpp

#include "core/Loader.h"
#include <iostream>
#include <stdexcept>

Loader::Loader(const std::string& output_filename) {
    try {
        m_serializer = std::make_unique<Serializer>(output_filename);
        // Não imprimimos mais a mensagem aqui, pois a main já o faz.
    } catch (const std::exception& e) {
        std::cerr << "Erro fatal no Loader: " << e.what() << std::endl;
        throw;
    }
}

void Loader::write_header_and_metadata(uint64_t record_count) {
    if (!m_serializer || m_header_written) return;

    dfb::Header header = {
        {'D', 'F', 'B', '1'}, // Magic number
        record_count,         // Número de registros que vamos escrever
        0                     // Tamanho dos metadados (ainda não implementado)
    };
    m_serializer->write_struct(header);
    m_header_written = true;
}

void Loader::load_record(const DataRow& row) {
    if (!m_serializer) return;

    try {
        if (row.fields.size() >= 2) {
            // Campo 1: Chave (string)
            m_serializer->write_string(row.fields[0]);
            
            // Campo 2: Soma (double)
            m_serializer->write_double(std::stod(row.fields[1]));
            
            // Campo 3: Contagem (uint64_t)
            if (row.fields.size() >= 3) {
                 m_serializer->write_uint64(std::stoull(row.fields[2]));
            }

            // Campo 4: Média (double)
             if (row.fields.size() >= 4) {
                 m_serializer->write_double(std::stod(row.fields[3]));
            }
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Aviso: Registro ignorado no Loader por erro de conversão de dados." << std::endl;
    }
}

void Loader::close() {
    m_serializer.reset();
}