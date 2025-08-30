# DataForge ETL Engine 🚀

**DataForge** é um motor de ETL (Extract, Transform, Load) de alto desempenho, desenvolvido em C++17 moderno. Projetado do zero com foco em performance e modularidade, o sistema é capaz de processar arquivos de dados de múltiplos formatos (CSV, JSON) em escala de gigabytes, oferecendo uma fundação robusta para pipelines de engenharia de dados complexos e carregando os resultados em um formato binário de alta performance.

O projeto nasceu como um estudo aprofundado sobre arquitetura de software de baixo nível, gerenciamento de dependências (`Git Submodules`) e os benefícios de C++ para manipulação de grandes volumes de dados.

-----

## 📋 Principais Características

  * **Núcleo de Alto Desempenho em C++17:** Utiliza recursos modernos de C++ para garantir máxima eficiência e segurança no gerenciamento de memória, sem a sobrecarga de um garbage collector.
  * **Arquitetura Modular e Extensível:** O design do motor é baseado em uma clara separação de responsabilidades (Extract, Transform, Load), permitindo que novos formatos e transformações sejam adicionados com mínimo impacto.
  * **Extração Polimórfica de Dados:** Suporte nativo para extração de dados de arquivos **CSV** e **JSON** através de uma interface de extração comum, demonstrando o uso eficaz dos padrões de projeto *Strategy* e *Factory*.
  * **Carregamento (Load) em Formato Binário:** Integração com a biblioteca externa **[fast-serializer](https://github.com/caio2203/fast-serializer)** para salvar os dados processados em um formato binário customizado, resultando em arquivos de saída compactos e de leitura extremamente rápida.
  * **Projetado para Arquivos Gigabytes:** A lógica de processamento é baseada em *streaming*, lendo os dados registro a registro para manter o consumo de memória baixo e constante.
  * **Gerenciamento de Dependências com Git Submodules:** Demonstra uma abordagem profissional para integrar bibliotecas externas, mantendo os projetos desacoplados e versionados.

-----

## 🏛️ Arquitetura do Projeto

A organização do DataForge segue as melhores práticas de engenharia de software, com uma clara separação entre interface (`include`), implementação (`src`), dependências (`vendor`), testes e outros artefatos.

```
dataforge-etl/
├── vendor/             # Dependências externas (via Git Submodules)
│   └── fast-serializer/
├── src/                # Código-fonte (.cpp)
│   ├── core/           # Motor principal, pipeline, extratores, loader e fábrica
│   ├── aggregator/     # (Planejado) Lógica de agregação
│   └── ...
├── include/            # Arquivos de cabeçalho (.h/.hpp)
│   ├── common/         # Estruturas de dados comuns (ex: DataRow.h)
│   ├── core/           # Interfaces e declarações do motor principal
│   └── ...
├── tests/              # Testes unitários e de integração
├── data/               # Dados de exemplo para teste
│   ├── input/          # Arquivos de entrada (CSV, JSON)
│   └── output/         # Arquivos de saída gerados (.dfb)
├── build/              # Diretório de saída da compilação (ignorado pelo Git)
├── .gitmodules         # Arquivo de configuração do submódulo
├── Makefile            # Automatiza o processo de build
└── README.md           # Esta documentação
```

-----

## 🛠️ Primeiros Passos

### Pré-requisitos

Para compilar e executar o projeto, você precisará de:

  * Um compilador C++ com suporte a C++17 (ex: `g++` versão 8 ou superior)
  * `make` para executar a compilação automatizada
  * `git` para clonar o repositório

### Compilando e Executando

1.  **Clone o repositório (incluindo o submódulo):**
    Use a flag `--recurse-submodules` para clonar o projeto principal e todas as suas dependências de uma só vez.

    ```bash
    git clone --recurse-submodules https://github.com/caio2203/dataforge-etl.git
    cd dataforge-etl
    ```

    *(Se você já clonou sem a flag, pode inicializar o submódulo com `git submodule update --init --recursive`)*

2.  **Compile o projeto:**
    A `Makefile` cuidará de todo o processo, incluindo a compilação da biblioteca `fast-serializer`.

    ```bash
    make
    ```

    O executável final será gerado em `build/dataforge`.

3.  **Execute o motor de ETL:**
    O programa agora espera **dois argumentos**: o arquivo de entrada e o nome do arquivo de saída.

    ```bash
    # Exemplo com um arquivo CSV
    ./build/dataforge data/input/vendas.csv data/output/resultado.dfb

    # Exemplo com um arquivo JSON
    ./build/dataforge data/input/dados.json data/output/resultado.dfb
    ```

    Após a execução, um novo arquivo binário (`resultado.dfb`) será criado na pasta `data/output/`.

-----

## 🗺️ Status e Roadmap

Este projeto está em desenvolvimento ativo.

  - [x] Arquitetura modular e extensível definida.
  - [x] Interface de extração de dados (`IDataExtractor`).
  - [x] Implementação de extrator para **CSV** e **JSON**.
  - [x] Desenvolvimento da biblioteca **`fast-serializer`** em repositório separado.
  - [x] **Integração** da biblioteca via `Git Submodules` para a etapa de **Load**.
  - [x] Pipeline E-\>L (Extract-\>Load) funcional.
  - [ ] Implementação do módulo `Aggregator` (a etapa **Transform**).
  - [ ] Adição de suporte a multithreading no pipeline de ETL.
  - [ ] Criação de uma suíte de testes unitários com GTest.

-----

## 🤝 Como Contribuir

Contribuições são bem-vindas\! Se você tem ideias para novas funcionalidades, melhorias de performance ou correções de bugs, por favor, siga estes passos:

1.  Faça um "Fork" do repositório.
2.  Crie uma nova branch para sua feature (`git checkout -b feature/minha-feature`).
3.  Faça o commit de suas alterações (`git commit -m 'Adiciona minha-feature'`).
4.  Envie para a sua branch (`git push origin feature/minha-feature`).
5.  Abra um "Pull Request".

-----

## 📄 Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo `LICENSE` para mais detalhes.