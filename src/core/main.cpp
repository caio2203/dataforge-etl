// Arquivo: src/main.cpp

/*
 * ========================================================
 * ARQUIVO PRINCIPAL (main) - "O Cliente no Restaurante"
 * ========================================================
 *
 * Este arquivo (main.cpp) é onde a história da nossa aplicação acontece.
 * Ele é o cliente que entra no nosso restaurante e usa seus serviços.
 *
 * FUNÇÃO PRINCIPAL:
 * 1. SER O PONTO DE ENTRADA: A execução do programa sempre começa aqui, na
 * função 'main'. É a "porta da frente" do nosso sistema, onde o cliente
 * chega.
 *
 * 2. ORQUESTRAR A LÓGICA: A 'main' é o maestro. Ela decide quando consultar
 * o "cardápio" (.h) do nosso parser, quando "fazer um pedido"
 * (criar um objeto CSVParser) e em que ordem os "pratos" (funções)
 * serão solicitados (primeiro open(), depois readRow() em um laço, etc).
 *
 * 3. USAR AS FERRAMENTAS: Este arquivo não se preocupa em COMO o parser
 * funciona (a "cozinha"). Ele simplesmente confia no "cardápio"
 * e usa as ferramentas (classes e funções) que outras partes do
 * código oferecem para atingir um objetivo final (neste caso,
 * ler um arquivo CSV e mostrar os dados na tela).
*/

// Arquivo: src/core/main.cpp

#include "core/ExtractorFactory.h" // Apenas conhece a fábrica e a interface
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./dataforge <caminho_do_arquivo>" << std::endl;
        return 1;
    }

    std::string filepath = argv[1];
    std::cout << "Iniciando DataForge ETL Engine para o arquivo: " << filepath << std::endl;

    // A fábrica decide qual extrator criar (CSV ou JSON)
    auto extractor = ExtractorFactory::createExtractor(filepath);
    
    if (!extractor) {
        std::cerr << "Erro: Formato de arquivo não suportado." << std::endl;
        return 1;
    }

    // A partir daqui, o código é genérico. Ele usa a interface IDataExtractor
    // e não se importa com a implementação concreta.
    if (extractor->open(filepath)) {
        DataRow row;
        int lineCount = 0;
        while (extractor->readRow(row)) {
            lineCount++;
            std::cout << "Linha " << lineCount << ": ";
            row.print(); // Usando nosso método de debug

            // AQUI ENTRA A LÓGICA DE TRANSFORMAÇÃO (aggregator)
        }
        extractor->close();
        std::cout << "Extração concluída. Total de " << lineCount << " registros lidos." << std::endl;
    }
    
    return 0;
}