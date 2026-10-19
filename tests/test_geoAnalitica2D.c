
#include <stdio.h>
#include "GeoAnalitica2D.h"
#include <stddef.h>
#include <math.h>

int main(void) {
    int testesAprovados = 0;
    int testesFalhou = 0;
    geo_ponto2d p1, p2;
    geo_status status;
    double coeficiente, dist;

    p1.x = 2.0;
    p1.y = 2.0;
    p2.x = 4.0;
    p2.y = 4.0;

    // Testa o cálculo correto do coeficiente angular.
    if ((status = calculaCoefAngular(p1, p2, &coeficiente)) == GEO_OK &&
        fabs(coeficiente - 1.0) < GEO_EPS) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    // Testa se a função identifica um ponteiro de saída nulo.
    if ((status = calculaCoefAngular(p1, p2, NULL)) == GEO_ERR_NULL) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    p2.x = 2.0;

    // Testa se uma reta vertical gera erro no coeficiente angular.
    if ((status = calculaCoefAngular(p1, p2, &coeficiente)) == GEO_ERR_INVALID) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    // Testa o cálculo correto da distância entre dois pontos.
    if ((status = distPontoPonto(p1, p2, &dist)) == GEO_OK &&
        fabs(dist - 2.0) < GEO_EPS) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    // Testa se a função identifica um ponteiro de saída nulo.
    if ((status = distPontoPonto(p1, p2, NULL)) == GEO_ERR_NULL) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    geo_eqGeralReta reta;
    geo_ponto2d ponto;

    reta.coefX = 1.0;
    reta.coefY = 0.0;
    reta.c = -2.0;

    ponto.x = 5.0;
    ponto.y = 2.0;

    // Testa a distância de um ponto até uma reta válida.
    if ((status = distPontoReta(&reta, ponto, &dist)) == GEO_OK &&
        fabs(dist - 3.0) < GEO_EPS) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    // Testa se a função identifica uma reta nula.
    if ((status = distPontoReta(NULL, ponto, &dist)) == GEO_ERR_NULL) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    reta.coefX = 0.0;
    reta.coefY = 0.0;
    reta.c = 1.0;

    // Testa se uma equação que não define uma reta válida gera erro.
    if ((status = distPontoReta(&reta, ponto, &dist)) == GEO_ERR_INVALID) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    geo_eqGeralReta r1, r2;
    posicao_retas posicao;
    geo_ponto2d interseccao;

    r1.coefX = 1.0;
    r1.coefY = 1.0;
    r1.c = -4.0;

    r2.coefX = 1.0;
    r2.coefY = -1.0;
    r2.c = 0.0;

    // Testa se identifica retas concorrentes e calcula a interseção.
    if ((status = posicaoRelativaRetas(&r1, &r2, &posicao, &interseccao)) == GEO_OK &&
        posicao == RETAS_CONCORRENTES &&
        fabs(interseccao.x - 2.0) < GEO_EPS &&
        fabs(interseccao.y - 2.0) < GEO_EPS) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    r2.coefX = 1.0;
    r2.coefY = 1.0;
    r2.c = -6.0;

    // Testa se identifica corretamente duas retas paralelas.
    if ((status = posicaoRelativaRetas(&r1, &r2, &posicao, &interseccao)) == GEO_OK &&
        posicao == RETAS_PARALELAS) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    r2.coefX = 2.0;
    r2.coefY = 2.0;
    r2.c = -8.0;

    // Testa se identifica duas equações que representam a mesma reta.
    if ((status = posicaoRelativaRetas(&r1, &r2, &posicao, &interseccao)) == GEO_OK &&
        posicao == RETAS_COINCIDENTES) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    // Testa se a função identifica um ponteiro de reta nulo.
    if ((status = posicaoRelativaRetas(NULL, &r2, &posicao, &interseccao)) == GEO_ERR_NULL) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    r2.coefX = 0.0;
    r2.coefY = 0.0;
    r2.c = 1.0;

    // Testa se uma reta inválida gera erro na classificação.
    if ((status = posicaoRelativaRetas(&r1, &r2, &posicao, &interseccao)) == GEO_ERR_INVALID) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    r1.coefX = 1.0;
    r1.coefY = 1.0;
    r1.c = -4.0;

    r2.coefX = 1.0;
    r2.coefY = -1.0;
    r2.c = 0.0;

    // Testa o cálculo correto do ponto de encontro das retas.
    if ((status = pontoEncontro(&r1, &r2, &interseccao)) == GEO_OK &&
        fabs(interseccao.x - 2.0) < GEO_EPS &&
        fabs(interseccao.y - 2.0) < GEO_EPS) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    // Testa se a função identifica a primeira reta nula.
    if ((status = pontoEncontro(NULL, &r2, &interseccao)) == GEO_ERR_NULL) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    r2.coefX = 1.0;
    r2.coefY = 1.0;
    r2.c = -6.0;

    // Testa se retas paralelas retornam erro por não terem interseção única.
    if ((status = pontoEncontro(&r1, &r2, &interseccao)) == GEO_ERR_INVALID) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    r2.coefX = 0.0;
    r2.coefY = 0.0;
    r2.c = 1.0;

    // Testa se uma reta inválida gera erro ao calcular a interseção.
    if ((status = pontoEncontro(&r1, &r2, &interseccao)) == GEO_ERR_INVALID) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }



    geo_ponto2d pMedio;

    // Testa o cálculo correto do ponto médio.
    if ((status = pontoMedio(p1, p2, &pMedio)) == GEO_OK &&
        fabs(pMedio.x - 2.0) < GEO_EPS &&
        fabs(pMedio.y - 3.0) < GEO_EPS) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    // Testa se a função identifica um ponteiro de saída nulo.
    if ((status = pontoMedio(p1, p2, NULL)) == GEO_ERR_NULL) {
        testesAprovados++;
    } else {
        testesFalhou++;
    }

    printf("Aprovados: %d\n", testesAprovados);
    printf("Falharam: %d\n", testesFalhou);

    return (testesFalhou > 0) ? 1 : 0;
}

