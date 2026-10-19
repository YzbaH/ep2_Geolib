
#include <stdio.h>
#include <math.h>
#include "GeoEspacial.h"
#include <stddef.h>

int main(void) {
    geo_status status;
    int testesAprovados = 0;
    int testesFalhou = 0;

    geo_cubo cuboTeste = {8.0};
    double resultado;

    // Testa a área correta do cubo.
    if ((status = areaCubo(&cuboTeste, &resultado)) != GEO_OK ||
        fabs(resultado - 384.0) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a área do cubo identifica um ponteiro nulo.
    if ((status = areaCubo(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    cuboTeste.aresta = -8.0;

    // Testa se uma aresta negativa é rejeitada.
    if ((status = areaCubo(&cuboTeste, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    geo_paralelepipedo pTeste = {2.0, 3.0, 4.0};

    // Testa a área correta do paralelepípedo.
    if ((status = areaParalelepipedo(&pTeste, &resultado)) != GEO_OK ||
        fabs(resultado - 52.0) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica um ponteiro de saída nulo.
    if ((status = areaParalelepipedo(&pTeste, NULL)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    pTeste.comprimento = -2.0;

    // Testa se um comprimento negativo é rejeitado.
    if ((status = areaParalelepipedo(&pTeste, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    geo_esfera esfTest = {2.0};

    // Testa a área correta da esfera.
    if ((status = areaEsfera(&esfTest, &resultado)) != GEO_OK ||
        fabs(resultado - 16.0 * GEO_PI) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica uma esfera nula.
    if ((status = areaEsfera(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    esfTest.raio = -2.0;

    // Testa se um raio negativo é rejeitado.
    if ((status = areaEsfera(&esfTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    geo_cilindro cilTest = {2.0, 3.0};

    // Testa a área correta do cilindro.
    if ((status = areaCilindro(&cilTest, &resultado)) != GEO_OK ||
        fabs(resultado - 20.0 * GEO_PI) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica um cilindro nulo.
    if ((status = areaCilindro(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    cilTest.raio = -2.0;

    // Testa se um raio negativo é rejeitado.
    if ((status = areaCilindro(&cilTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    geo_cone coneTest;
    coneTest.raio = 2.0;
    coneTest.geratriz = 3.0;

    // Testa a área correta do cone.
    if ((status = areaCone(&coneTest, &resultado)) != GEO_OK ||
        fabs(resultado - 10.0 * GEO_PI) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica um cone nulo.
    if ((status = areaCone(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    coneTest.raio = -2.0;

    // Testa se um raio negativo é rejeitado.
    if ((status = areaCone(&coneTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    geo_tetraedro tetraTest = {2.0};

    // Testa a área correta do tetraedro.
    if ((status = areaTetraedro(&tetraTest, &resultado)) != GEO_OK ||
        fabs(resultado - 4.0 * SQRT3) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica um tetraedro nulo.
    if ((status = areaTetraedro(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    tetraTest.aresta = -2.0;

    // Testa se uma aresta negativa é rejeitada.
    if ((status = areaTetraedro(&tetraTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    cuboTeste.aresta = 8.0;

    // Testa o volume correto do cubo.
    if ((status = volumeCubo(&cuboTeste, &resultado)) != GEO_OK ||
        fabs(resultado - 512.0) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica um cubo nulo.
    if ((status = volumeCubo(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    cuboTeste.aresta = -8.0;

    // Testa se uma aresta negativa é rejeitada.
    if ((status = volumeCubo(&cuboTeste, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica um ponteiro de saída nulo.
    if ((status = volumeParalelepipedo(&pTeste, NULL)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se as dimensões inválidas do paralelepípedo são rejeitadas.
    if ((status = volumeParalelepipedo(&pTeste, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica uma esfera nula.
    if ((status = volumeEsfera(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se o raio negativo da esfera é rejeitado.
    if ((status = volumeEsfera(&esfTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica um cilindro nulo.
    if ((status = volumeCilindro(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a função identifica um cone nulo.
    if ((status = volumeCone(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se o raio negativo do cone é rejeitado.
    if ((status = volumeCone(&coneTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    // Testa se a aresta negativa do tetraedro é rejeitada.
    if ((status = volumeTetraedro(&tetraTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    printf("Passou: %d\n", testesAprovados);
    printf("Falhou: %d\n", testesFalhou);

    return (testesFalhou > 0) ? 1 : 0;
}
