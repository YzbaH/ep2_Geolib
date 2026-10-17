
# GeoLib — Bibliotecas de Geometria e Vetores em C

Projeto em C que reúne bibliotecas para facilitar cálculos de geometria analítica no plano e geometria espacial. Também conta com operações auxiliares envolvendo pontos, retas, figuras geométricas e vetores, incluindo cálculos e operações vetoriais. A ideia é organizar essas funcionalidades em módulos, deixando o código mais simples de reutilizar e facilitando a criação de outros programas que precisem desses recursos.


## Pré-requisitos

- Sistema compatível com ferramentas GNU/Linux.
- GCC para compilar o código C.
- GNU Make para executar os alvos do projeto.
- Biblioteca matemática padrão do C (`libm`), vinculada com `-lm` nos testes.

## Estrutura do projeto

```text
.
├── include/                 # Cabeçalhos públicos e tipos compartilhados
│   ├── GeoAnalitica2D.h      # Geometria analítica no plano
│   ├── GeoEspacial.h         # Áreas e volumes de sólidos
│   ├── geo_common.h          # Tipos e utilitários comuns
│   ├── geo_plane.h           # Operações com figuras planas
│   └── vecoperations.h       # Operações com vetores 2D e 3D
├── src/                     # Implementações das bibliotecas
│   ├── GeoAnalitica2D.c
│   ├── GeoEspacial.c
│   ├── geo_common.c
│   ├── geo_plane.c
│   └── vecoperations.c
├── tests/                   # Programas de teste
│   ├── test_geoAnalitica2D.c
│   ├── test_geoEspacial.c
│   ├── test_plane.c
│   └── test_vecoperation.c
├── Makefile                 # Regras de compilação, testes e instalação
└── README.md
```

## Compilação

Na raiz do projeto, execute:

```bash
make all
```

O alvo `all` gera as bibliotecas estática e dinâmica:

- `libgeolib.a` — biblioteca estática.
- `libgeolib.so` — biblioteca dinâmica compartilhada.

Os arquivos objeto intermediários (`.o`) são gerados dentro de `src/`. A compilação usa `gcc` com as opções `-Wall -Wextra -Iinclude -fPIC -g`.

## Alvos do Makefile

| Comando | Descrição |
|---|---|
| `make` ou `make all` | Compila as bibliotecas estática e dinâmica. |
| `make clean` | Remove arquivos objeto, as bibliotecas geradas e o executável `test_runner`. |
| `make run` | Executa a dependência `all` e imprime uma mensagem de sucesso. No estado atual, não inicia uma aplicação separada. |
| `make test` | Tenta compilar os testes em `test_runner` e executá-lo. Consulte a observação na seção [Testes](#testes). |
| `make install` | Instala as bibliotecas e os cabeçalhos em `$(PREFIX)`. Por padrão, `PREFIX=/usr/local`. |

É possível escolher outro diretório de instalação passando `PREFIX`. Por exemplo:

```bash
make install PREFIX="$HOME/.local"
```

## Execução

O projeto disponibiliza bibliotecas. Para gerar as bibliotecas, use:

```bash
make all
```

O alvo `make run` existe no `Makefile`, mas atualmente apenas compila as bibliotecas (se necessário) e exibe a mensagem `Aplicação executada com sucesso.`; não executa um programa de demonstração.

## Testes

Para tentar compilar e executar os testes:

```bash
make test
```

O `Makefile` reúne automaticamente todos os arquivos `.c` de `tests/` em um único executável chamado `test_runner`. Entretanto, os arquivos de teste atuais contêm funções `main` próprias; vinculá-los todos juntos pode gerar erro de múltiplas definições de `main`. Se isso ocorrer, cada programa de teste deverá ser compilado e executado separadamente ou as regras do `Makefile` deverão ser ajustadas.

## Instalação

Por padrão, a instalação copia:

- `libgeolib.a` para `$(PREFIX)/lib/`;
- `libgeolib.so` para `$(PREFIX)/lib/`;
- todos os arquivos `.h` de `include/` para `$(PREFIX)/include/`.

O prefixo padrão é `/usr/local`, que normalmente exige permissões administrativas. Para instalar nesse local:

```bash
sudo make install
```

Ou instale em um diretório do usuário, sem `sudo`:

```bash
make install PREFIX="$HOME/.local"
```

Para remover os artefatos gerados na pasta do projeto:

```bash
make clean
```

> `make clean` remove os arquivos gerados dentro do projeto; ele não desinstala arquivos que já tenham sido copiados para o diretório de instalação.
