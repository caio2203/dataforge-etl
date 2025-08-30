// Arquivo: include/aggregator/Aggregator.h

#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include "common/DataRow.h"
#include <string>
#include <vector>
#include <unordered_map>

// Estrutura para armazenar o resultado de uma agregação para uma chave específica
struct AggregationResult {
    std::string key;      // A chave pela qual agrupamos (ex: "Paris")
    long long   count = 0;    // Contagem de registros para esta chave
    double      sum = 0.0;    // Soma de um valor numérico para esta chave
    double      avg = 0.0;    // Média (será calculada no final)
};

// A classe Aggregator é o coração da etapa "Transform"
class Aggregator {
private:
    // A nossa tabela de hash. A chave é uma string (ex: nome da cidade) e o valor
    // é a struct com os resultados da agregação para aquela cidade.
    std::unordered_map<std::string, AggregationResult> m_results;

    // Índices das colunas que vamos usar
    size_t m_key_column_index;
    size_t m_value_column_index;

public:
    // Construtor: define qual coluna usar como chave e qual coluna agregar
    Aggregator(size_t key_column_index, size_t value_column_index);

    // Processa uma única linha de dados, atualizando a tabela de hash
    void process_row(const DataRow& row);

    // Finaliza os cálculos (como a média) e retorna todos os resultados
    std::vector<AggregationResult> get_results();
};

#endif // AGGREGATOR_H