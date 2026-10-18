# Biblioteca de Geometria e Vetores em C

Projeto em C que reúne módulos para cálculos de geometria analítica no plano e no espaço, geometria espacial, figuras planas e operações com vetores 2D e 3D. A organização em bibliotecas facilita a reutilização das funcionalidades em outros programas.

## Pré-requisitos

- Sistema compatível com ferramentas GNU/Linux.
- GCC para compilar o código C.
- GNU Make para executar os alvos do projeto.
- Biblioteca matemática padrão (libm), utilizada na ligação dos programas que dependem de funções matemáticas, por meio da opção `-lm` do GCC.

## Estrutura do projeto

```text
.
├── app/
│   └── main.c                 # Aplicação de demonstração
├── include/                   # Cabeçalhos públicos
│   ├── GeoAnalitica2D.h       # Geometria analítica 2D
│   ├── GeoEspacial.h          # Áreas e volumes de sólidos
│   ├── geo_analytic3d.h       # Geometria analítica 3D
│   ├── geo_common.h           # Tipos e utilitários comuns
│   ├── geo_plane.h            # Operações com figuras planas
│   └── vecoperations.h        # Operações com vetores 2D e 3D
├── src/                       # Implementações dos módulos
│   ├── GeoAnalitica2D.c
│   ├── GeoEspacial.c
│   ├── geo_analytic3d.c
│   ├── geo_common.c
│   ├── geo_plane.c
│   └── vecoperations.c
├── tests/                     # Programas de teste independentes
│   ├── test_analytic3d.c
|   ├── test_geoAnalitica2D.c
│   ├── test_geoEspacial.c
│   ├── test_plane.c
│   └── test_vecoperation.c
├── Makefile                   # Compilação, execução, testes e instalação
└── README.md
```

## Compilação

Na raiz do projeto, execute:

```bash
make
```

ou:

```bash
make all
```

O alvo `all` compila os arquivos `.c` de `src/` em arquivos objeto (`.o`) e cria duas bibliotecas:

- `libgeolib.a`: biblioteca estática;
- `libgeolib.so`: biblioteca dinâmica compartilhada.

A compilação usa `gcc` com as opções `-Wall -Wextra -Iinclude -fPIC -g`. A opção `-lm` é usada na ligação dos executáveis que utilizam funções matemáticas. Os arquivos objeto são gerados em `src/`.

## Alvos do Makefile

| Comando | Função |
|---|---|
| `make` ou `make all` | Compila as bibliotecas estática e dinâmica. |
| `make run` | Compila a aplicação `app/main.c` quando necessário e a executa. |
| `make test` | Compila e executa cada arquivo de teste de `tests/` como um programa independente. Interrompe a execução se houver falha. |
| `make clean` | Remove os arquivos objeto, as bibliotecas geradas, os executáveis de teste e `app/main`. |
| `make install` | Instala as bibliotecas e os cabeçalhos no prefixo definido por `PREFIX`. O padrão é `$(HOME)/.local`. |

O Makefile detecta automaticamente os arquivos `.c` em `src/` e `tests/`. Cada teste é compilado separadamente porque os arquivos de teste possuem suas próprias funções `main()`.

## Execução da aplicação

Para compilar e iniciar a aplicação de demonstração, execute na raiz do projeto:

```bash
make run
```

O alvo compila `app/main.c`, liga o programa à biblioteca estática `libgeolib.a` e à biblioteca matemática, e inicia `app/main`. Se os arquivos necessários já estiverem atualizados, o Make evita recompilar o que não mudou.

## Testes

Para executar os testes automatizados:

```bash
make test
```

O Makefile compila cada arquivo `.c` encontrado em `tests/` junto com os objetos da biblioteca e executa o programa de teste correspondente. Se uma compilação falhar ou um teste retornar erro, o processo é interrompido. As mensagens são exibidas no terminal.

Para remover os arquivos gerados e fazer uma compilação:

```bash
make clean
make
```

## Instalação

O alvo `install` instala:

- `libgeolib.a` em `$(PREFIX)/lib/`;
- `libgeolib.so` em `$(PREFIX)/lib/`;
- os arquivos `.h` de `include/` em `$(PREFIX)/include/`.

Por padrão, PREFIX=$(HOME)/.local.

O comando `make clean` remove os artefatos de compilação do projeto, mas não desinstala arquivos já copiados para o diretório de instalação.

## Utilização em outros programas

Para usar a biblioteca em outro programa C, inclua os cabeçalhos necessários e compile o programa ligando-o à biblioteca. Por exemplo, com `meu_programa.c` na raiz do projeto:

```bash
gcc -Wall -Wextra -Iinclude meu_programa.c -L. -lgeolib -lm -o meu_programa
```
