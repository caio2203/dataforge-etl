// Arquivo: src/aggregator/Aggregator.cpp

#include "aggregator/Aggregator.h"
#include <stdexcept>

Aggregator::Aggregator(size_t key_column_index, size_t value_column_index)
    : m_key_column_index(key_column_index), m_value_column_index(value_column_index) {}

void Aggregator::process_row(const DataRow& row) {
    // 1. Valida se a linha tem colunas suficientes
    if (row.fields.size() <= m_key_column_index || row.fields.size() <= m_value_column_index) {
        // Ignora linhas malformadas
        return;
    }

    // 2. Extrai a chave e o valor da linha
    const std::string& key = row.fields[m_key_column_index];
    
    double value;
    try {
        value = std::stod(row.fields[m_value_column_index]);
    } catch (const std::invalid_argument& e) {
        // Ignora a linha se o valor não for um número válido
        return;
    }

    // 3. Atualiza a tabela de hash
    // A mágica do unordered_map: se a chave 'key' não existe, ele a cria!
    // Se já existe, ele apenas nos dá acesso ao AggregationResult existente.
    AggregationResult& result = m_results[key];

    // 4. Faz os cálculos de agregação
    result.key = key; // Garante que a chave seja armazenada na primeira vez
    result.count++;
    result.sum += value;
}

std::vector<AggregationResult> Aggregator::get_results() {
    std::vector<AggregationResult> final_results;
    
    // Itera sobre todos os pares [chave, valor] da nossa tabela de hash
    for (auto& pair : m_results) {
        // Acessa o AggregationResult (o 'valor' do par)
        AggregationResult& result = pair.second;

        // Calcula a média, evitando divisão por zero
        if (result.count > 0) {
            result.avg = result.sum / result.count;
        }

        // Adiciona o resultado final ao nosso vetor de resultados
        final_results.push_back(result);
    }
    
    return final_results;
}