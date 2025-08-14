# DataForge ETL Engine 

**DataForge** é um motor de ETL (Extract, Transform, Load) de alto desempenho, desenvolvido em C++17 moderno. Projetado do zero com foco em performance e modularidade, o sistema é capaz de processar arquivos de dados em escala de gigabytes, oferecendo uma fundação robusta para pipelines de engenharia de dados complexos.

O projeto nasceu como um estudo aprofundado sobre arquitetura de software de baixo nível, gerenciamento de memória e os benefícios de C++ para manipulação de grandes volumes de dados, indo além de scripts tradicionais para fornecer uma solução compilada e otimizada.

-----

## Principais Características

  * **Núcleo de Alto Desempenho em C++17:** Utiliza recursos modernos de C++ para garantir máxima eficiência e segurança no gerenciamento de memória, sem a sobrecarga de um garbage collector.
  * **Arquitetura Modular e Extensível:** O design do motor é baseado em uma clara separação de responsabilidades (Extract, Transform, Load), permitindo que novos formatos de dados e transformações sejam adicionados com mínimo impacto no sistema existente.
  * **Extração Polimórfica de Dados:** Suporte nativo para extração de dados de arquivos **CSV** e **JSON** através de uma interface de extração comum, demonstrando o uso eficaz de polimorfismo.
  * **Projetado para Arquivos Gigabytes:** A lógica de processamento é baseada em *streaming*, lendo os dados linha a linha (ou registro a registro) para manter o consumo de memória baixo e constante, independentemente do tamanho do arquivo de entrada.
  * **Roadmap Ambicioso:**
      * **Agregação de Dados (`GROUP BY`):** Módulo em desenvolvimento para realizar operações de agregação complexas e com estado.
      * **Serialização Binária:** Módulo planejado para carregar os dados transformados em um formato binário compacto e de leitura rápida.
      * **Suporte a Multithreading:** Evolução planejada para paralelizar as etapas de ETL, aproveitando ao máximo os processadores multi-core modernos.

-----

## Arquitetura do Projeto

A organização do DataForge segue as melhores práticas de engenharia de software, com uma clara separação entre interface (`include`), implementação (`src`), testes e outros artefatos. Isso garante um projeto limpo, escalável e de fácil manutenção.

```
dataforge-etl/
├── src/                # Código-fonte (.cpp)
│   ├── core/           # Motor principal, pipeline, extratores e fábrica
│   ├── aggregator/     # (Planejado) Lógica de agregação
│   ├── serializer/     # (Planejado) Lógica de serialização
│   └── utils/          # Ferramentas auxiliares
├── include/            # Arquivos de cabeçalho (.h/.hpp)
│   ├── common/         # Estruturas de dados comuns (ex: DataRow.h)
│   ├── core/           # Interfaces e declarações do motor principal
│   └── utils/          # Declarações de ferramentas e bibliotecas de terceiros
├── tests/              # Testes unitários e de integração
├── data/               # Dados de exemplo para teste
│   ├── input/          # Arquivos de entrada (CSV, JSON)
│   └── output/         # Arquivos de saída gerados
├── build/              # Diretório de saída da compilação (ignorado pelo Git)
├── Makefile            # Automatiza o processo de build
└── README.md           # Esta documentação
```

-----

## Primeiros Passos

### Pré-requisitos

Para compilar e executar o projeto, você precisará de:

  * Um compilador C++ com suporte a C++17 (ex: `g++` versão 8 ou superior)
  * `make` para executar a compilação automatizada
  * `git` para clonar o repositório

### Compilando e Executando

1.  **Clone o repositório:**

    ```bash
    git clone https://github.com/caio2203/dataforge-etl.git
    cd dataforge-etl
    ```

2.  **Compile o projeto:**
    O `Makefile` cuidará de todo o processo de compilação.

    ```bash
    make
    ```

    O executável final será gerado em `build/dataforge`.

3.  **Execute o motor de ETL:**
    Passe o caminho de um arquivo de dados (CSV ou JSON) como argumento.

    ```bash
    # Exemplo com um arquivo CSV
    ./build/dataforge data/input/exemplo.csv

    # Exemplo com um arquivo JSON
    ./build/dataforge data/input/exemplo.json
    ```

-----

## Status e Roadmap

Este projeto está em desenvolvimento ativo.

  - [x] Arquitetura modular e extensível definida.
  - [x] Interface de extração de dados (`IDataExtractor`).
  - [x] Implementação de extrator para **CSV**.
  - [x] Implementação de extrator para **JSON** (usando a biblioteca nlohmann/json).
  - [x] Fábrica de extratores para seleção dinâmica do formato.
  - [x] Setup de compilação profissional com `Makefile`.
  - [ ] Implementação do módulo `Aggregator` (GROUP BY, SUM, COUNT).
  - [ ] Implementação do módulo `Serializer` para escrita em formato binário.
  - [ ] Adição de suporte a multithreading no pipeline de ETL.
  - [ ] Criação de uma suíte de testes unitários.

-----

## Como Contribuir

Contribuições são bem-vindas\! Se você tem ideias para novas funcionalidades, melhorias de performance ou correções de bugs, por favor, siga estes passos:

1.  Faça um "Fork" do repositório.
2.  Crie uma nova branch para sua feature (`git checkout -b feature/minha-feature`).
3.  Faça o commit de suas alterações (`git commit -m 'Adiciona minha-feature'`).
4.  Envie para a sua branch (`git push origin feature/minha-feature`).
5.  Abra um "Pull Request".

-----

## Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
