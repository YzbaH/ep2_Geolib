#include <stdio.h>
#include <math.h>
#include "GeoEspacial.h"
#include <stddef.h>

int main(void){
    geo_status status;
    int testesAprovados = 0;
    int testesFalhou = 0;

    geo_cubo cuboTeste = {8.0};
    double resultado;
    
    if ((status = areaCubo(&cuboTeste, &resultado)) != GEO_OK || fabs(resultado - 384.0) >= GEO_EPS ){
        testesFalhou ++;
    } else {
        testesAprovados ++;
    }

    if ((status = areaCubo(NULL, &resultado)) != GEO_ERR_NULL){
        testesFalhou ++;
    } else {
        testesAprovados ++;
    }
  
    cuboTeste.aresta = -8.0;
    if ((status = areaCubo(&cuboTeste, &resultado)) != GEO_ERR_INVALID){
        testesFalhou ++;
    } else {
        testesAprovados ++;
    }
    
    geo_paralelepipedo pTeste = {2.0, 3.0, 4.0};
    if ((status = areaParalelepipedo(&pTeste, &resultado)) != GEO_OK || fabs(resultado - 52.0) >= GEO_EPS){
        testesFalhou ++;
    } else {
        testesAprovados ++;
    }

    if ((status = areaParalelepipedo(&pTeste, NULL)) != GEO_ERR_NULL){
        testesFalhou ++;
    } else {
        testesAprovados ++;
    }
    
    pTeste.comprimento = -2.0;
    if ((status = areaParalelepipedo(&pTeste, &resultado)) != GEO_ERR_INVALID){
        testesFalhou ++;
    } else {
        testesAprovados ++;
    }

    geo_esfera esfTest = {2.0};
    if ((status = areaEsfera(&esfTest, &resultado)) != GEO_OK || fabs(resultado - 50.24) >= GEO_EPS){
        testesFalhou ++;
    } else {
        testesAprovados ++;
    }

    if ((status = areaEsfera(NULL, &resultado)) != GEO_ERR_NULL){
        testesFalhou ++;
    } else {
        testesAprovados ++;
    }

    esfTest.raio = -2.0;
    if ((status = areaEsfera(&esfTest, &resultado)) != GEO_ERR_INVALID){
        testesFalhou ++;
    } else {
        testesAprovados ++;
    }

    geo_cilindro cilTest = {2.0, 3.0};

    if ((status = areaCilindro(&cilTest, &resultado)) != GEO_OK || fabs(resultado - 62.8) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = areaCilindro(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    cilTest.raio = -2.0;
    if ((status = areaCilindro(&cilTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }
    
    geo_cone coneTest;
    coneTest.raio = 2.0;
    coneTest.geratriz = 3.0;
    if ((status = areaCone(&coneTest, &resultado)) != GEO_OK || fabs(resultado - 31.4) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = areaCone(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    coneTest.raio = -2.0;
    if ((status = areaCone(&coneTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }


    geo_tetraedro tetraTest = {2.0};

    if ((status = areaTetraedro(&tetraTest, &resultado)) != GEO_OK || fabs(resultado - 6.92) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = areaTetraedro(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    tetraTest.aresta = -2.0;

    if ((status = areaTetraedro(&tetraTest, &resultado)) != GEO_ERR_INVALID) {
      testesFalhou++;
    } else {
      testesAprovados++;
    }


    cuboTeste.aresta = 8.0;
    if ((status = volumeCubo(&cuboTeste, &resultado)) != GEO_OK ||
        fabs(resultado - 512.0) >= GEO_EPS) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }


    if ((status = volumeCubo(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    cuboTeste.aresta = -8.0;

    if ((status = volumeCubo(&cuboTeste, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = volumeParalelepipedo(&pTeste, NULL)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = volumeParalelepipedo(&pTeste, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = volumeEsfera(NULL, &resultado)) != GEO_ERR_NULL) {
       testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = volumeEsfera(&esfTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = volumeCilindro(NULL, &resultado)) != GEO_ERR_NULL) {
    testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = volumeCone(NULL, &resultado)) != GEO_ERR_NULL) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = volumeCone(&coneTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }

    if ((status = volumeTetraedro(&tetraTest, &resultado)) != GEO_ERR_INVALID) {
        testesFalhou++;
    } else {
        testesAprovados++;
    }
    
    printf("Passou: %d \n", testesAprovados);
    printf("Falhou: %d \n", testesFalhou);
    return 0;
}