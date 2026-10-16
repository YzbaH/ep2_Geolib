# Biblioteca de Vetores e Geometria em C

Uma biblioteca desenvolvida C que reúne funções para fazer cálculos de geometria, trabalhar com pontos e vetores e resolver problemas envolvendo figuras planas, retas e sólidos geométricos, incluindo o estudo de posições relativas entre retas no plano cartesiano.


## Pré-requisitos

* **Compilador C:** GCC ou outro compilador compatível com o padrão C utilizado pelo projeto.
* **GNU Make:** para automatizar a compilação por meio do `Makefile`.
* **Biblioteca matemática:** funções como `sqrt()` e `fabs()` são utilizadas em cálculos geométricos.
* **Arquivos do projeto:** cabeçalhos (`.h`) e implementações (`.c`) correspondentes aos módulos utilizados.

## Módulos da biblioteca

* **Geometria Analítica 2D:** coeficiente angular, distâncias, ponto médio, interseção e posição relativa de retas.
* **Geometria Plana:** colinearidade, triângulos, círculos, áreas, perímetros e posição de pontos em relação a círculos.
* **Geometria Espacial:** áreas e volumes de sólidos geométricos.
* **Geometria Vetorial 2D e 3D:** operações com vetores, produtos escalares e vetoriais, normas, ângulos, normalização e dependência linear.

### Códigos de status

As funções que utilizam `geo_status` podem retornar os seguintes códigos para indicar o resultado da operação:
* `GEO_OK`: operação realizada com sucesso.
* `GEO_ERR_NULL`: ponteiro nulo.
* `GEO_ERR_INVALID`: parâmetro inválido.
* `GEO_ERR_DEGENERATE`: situação geométrica degenerada.



## Compilação

A compilação é realizada por meio do `Makefile`.


## Testes

O projeto possui testes para os módulos de geometria analítica 2D, geometria plana e geometria espacial. Eles verificam se as operações geométricas estão sendo feitas corretamente ou se foram inseridos parâmetros inválidos ou ponteiros nulos.



