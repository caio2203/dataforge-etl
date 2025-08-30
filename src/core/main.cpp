// Arquivo: src/core/main.cpp
// O maestro do pipeline de ETL, agora em modo multithreaded.

#include "core/ExtractorFactory.h"
#include "core/Loader.h"
#include "aggregator/Aggregator.h"
#include "common/BlockingQueue.h" // A fila para comunicação entre threads
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <thread> // A biblioteca para threads do C++17

// ===================================================================
// THREAD PRODUTORA (Equivalente à fase "Extract")
// Responsabilidade: Ler o arquivo o mais rápido possível e colocar os
// dados em uma fila para a outra thread consumir.
// ===================================================================
void extractor_thread(const std::string& input_path, BlockingQueue<DataRow>& queue) {
    try {
        auto extractor = ExtractorFactory::createExtractor(input_path);
        if (!extractor || !extractor->open(input_path)) {
            std::cerr << "Erro fatal na thread de extração ao abrir o arquivo." << std::endl;
            queue.done(); // Libera a outra thread caso ela esteja esperando
            return;
        }

        DataRow row;
        int lineCount = 0;
        while (extractor->readRow(row)) {
            queue.push(row); // Coloca a linha na "esteira"
            lineCount++;
        }

        extractor->close();
        std::cout << "   [Thread Extractor] Extração concluída. " << lineCount << " registros lidos." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exceção na thread de extração: " << e.what() << std::endl;
    }
    // Sinaliza para a outra thread que não haverá mais dados
    queue.done();
}

// ===================================================================
// THREAD CONSUMIDORA (Equivalente às fases "Transform" e "Load")
// Responsabilidade: Pegar os dados da fila, processá-los (agregar) e
// depois salvá-los no destino final.
// ===================================================================
void worker_thread(BlockingQueue<DataRow>& queue, const std::string& output_path) {
    try {
        Aggregator aggregator(0, 1);
        DataRow row;
        int transformed_count = 0;

        // --- Parte Transform ---
        // Pega itens da "esteira" até ela ser esvaziada e o produtor sinalizar 'done'
        while (queue.pop(row)) {
            aggregator.process_row(row);
            transformed_count++;
        }
        
        auto aggregated_data = aggregator.get_results();
        std::cout << "   [Thread Worker] Transformação concluída. " << transformed_count << " registros processados, "
                  << aggregated_data.size() << " grupos únicos encontrados." << std::endl;

        // --- Parte Load ---
        Loader loader(output_path);
        for (const auto& result : aggregated_data) {
            DataRow aggregated_row;
            aggregated_row.fields.push_back(result.key);
            aggregated_row.fields.push_back(std::to_string(result.sum));
            aggregated_row.fields.push_back(std::to_string(result.count));
            aggregated_row.fields.push_back(std::to_string(result.avg));
            loader.load_record(aggregated_row);
        }

        loader.close();
        std::cout << "   [Thread Worker] Carregamento concluído." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exceção na thread de trabalho: " << e.what() << std::endl;
    }
}


// ===================================================================
// FUNÇÃO MAIN (A Gerente da Linha de Montagem)
// Responsabilidade: Criar a "esteira" (fila), contratar os "chefs"
// (iniciar as threads) e esperar que eles terminem.
// ===================================================================
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: ./dataforge <arquivo_de_entrada> <arquivo_de_saida.dfb>" << std::endl;
        return 1;
    }

    std::string input_path = argv[1];
    std::string output_path = argv[2];
    std::cout << "Iniciando pipeline ETL multithreaded do DataForge..." << std::endl;

    // A "esteira" que conecta as threads
    BlockingQueue<DataRow> queue;

    // Contrata os dois "chefs" e os coloca para trabalhar em paralelo
    std::thread producer(extractor_thread, input_path, std::ref(queue));
    std::thread consumer(worker_thread, std::ref(queue), output_path);

    // Espera os dois terminarem seus trabalhos antes de encerrar o programa
    producer.join();
    consumer.join();

    std::cout << "\nPipeline ETL completo executado com sucesso!" << std::endl;
    
    return 0;
}