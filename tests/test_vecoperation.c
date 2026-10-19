#include <stdio.h>
#include <math.h>
#include "geo_common.h"
#include "vecoperations.h"

int main(void) {
    // Declaração dos vetores e variáveis de teste
    vec2 v1 = {1.0, 2.0}, v2 = {3.0, 4.0}, zero2 = {0.0, 0.0};
    vec2 res2;
    
    vec3 v3_a = {1.0, 2.0, 3.0}, v3_b = {2.0, 4.0, 6.0}, zero3 = {0.0, 0.0, 0.0};
    vec3 res3;

    double d_val = 0.0;
    int int_val = 0;

    // soma e subtracao vec2 
    if (somavec2(v1, v2, &res2) != GEO_OK || !geo_approx_equal(res2.x, 4.0) || !geo_approx_equal(res2.y, 6.0)) return 1;
    if (somavec2(v1, v2, NULL) != GEO_ERR_NULL) return 1;
    if (subtraivec2(v2, v1, &res2) != GEO_OK || !geo_approx_equal(res2.x, 2.0) || !geo_approx_equal(res2.y, 2.0)) return 1;
    if (subtraivec2(v2, v1, NULL) != GEO_ERR_NULL) return 1;

    // multiplicacao escalar e produto escalar vec2 
    if (multescalarv2(v1, 2.0, &res2) != GEO_OK || !geo_approx_equal(res2.x, 2.0) || !geo_approx_equal(res2.y, 4.0)) return 1;
    if (multescalarv2(v1, 2.0, NULL) != GEO_ERR_NULL) return 1;
    if (produtoescalarv2(v1, v2, &d_val) != GEO_OK || !geo_approx_equal(d_val, 11.0)) return 1;
    if (produtoescalarv2(v1, v2, NULL) != GEO_ERR_NULL) return 1;

    // norma e normalizacao vec2 
    if (normav2(v2, &d_val) != GEO_OK || !geo_approx_equal(d_val, 5.0)) return 1;
    if (normav2(v2, NULL) != GEO_ERR_NULL) return 1;
    if (normalizav2(v2, &res2) != GEO_OK || !geo_approx_equal(res2.x, 0.6) || !geo_approx_equal(res2.y, 0.8)) return 1;
    if (normalizav2(zero2, &res2) != GEO_ERR_DEGENERATE) return 1;
    if (normalizav2(v2, NULL) != GEO_ERR_NULL) return 1;

    // angulo e dependencia linear vec2 
    vec2 ort1 = {1.0, 0.0}, ort2 = {0.0, 1.0};
    if (angulovec2(ort1, ort2, &d_val) != GEO_OK || !geo_approx_equal(d_val, GEO_PI / 2.0)) return 1;
    if (angulovec2(zero2, ort2, &d_val) != GEO_ERR_DEGENERATE) return 1;
    if (angulovec2(ort1, ort2, NULL) != GEO_ERR_NULL) return 1;
    if (dependencialinearv2(v1, v2, &int_val) != GEO_OK || int_val != 0) return 1; 
    if (dependencialinearv2(v1, v1, &int_val) != GEO_OK || int_val != 1) return 1; 
    if (dependencialinearv2(v1, v2, NULL) != GEO_ERR_NULL) return 1;

    // igualdade vec2 
    if (igualdadev2(v1, v1, &int_val) != GEO_OK || int_val != 1) return 1;
    if (igualdadev2(v1, v2, &int_val) != GEO_OK || int_val != 0) return 1;
    if (igualdadev2(v1, v2, NULL) != GEO_ERR_NULL) return 1;

    // soma, subtracao e produto vetorial vec3 
    if (somavec3(v3_a, v3_b, &res3) != GEO_OK || !geo_approx_equal(res3.x, 3.0) || !geo_approx_equal(res3.y, 6.0) || !geo_approx_equal(res3.z, 9.0)) return 1;
    if (somavec3(v3_a, v3_b, NULL) != GEO_ERR_NULL) return 1;
    if (produtovetorialv3(v3_a, v3_b, &res3) != GEO_OK || !geo_approx_equal(res3.x, 0.0) || !geo_approx_equal(res3.y, 0.0) || !geo_approx_equal(res3.z, 0.0)) return 1;
    if (produtovetorialv3(v3_a, v3_b, NULL) != GEO_ERR_NULL) return 1;

    // subtracao, multiplicacao escalar, produto escalar e norma vec3
    if (subtraivec3(v3_b, v3_a, &res3) != GEO_OK || !geo_approx_equal(res3.x, 1.0) || !geo_approx_equal(res3.y, 2.0) || !geo_approx_equal(res3.z, 3.0)) return 1;
    if (subtraivec3(v3_b, v3_a, NULL) != GEO_ERR_NULL) return 1;
    if (multescalarv3(v3_a, 2.0, &res3) != GEO_OK || !geo_approx_equal(res3.x, 2.0) || !geo_approx_equal(res3.y, 4.0) || !geo_approx_equal(res3.z, 6.0)) return 1;
    if (multescalarv3(v3_a, 2.0, NULL) != GEO_ERR_NULL) return 1;
    if (produtoescalarv3(v3_a, v3_b, &d_val) != GEO_OK || !geo_approx_equal(d_val, 28.0)) return 1;
    if (produtoescalarv3(v3_a, v3_b, NULL) != GEO_ERR_NULL) return 1;
    vec3 v236 = {2.0, 3.0, 6.0}; // norma = 7
    if (normav3(v236, &d_val) != GEO_OK || !geo_approx_equal(d_val, 7.0)) return 1;
    if (normav3(zero3, &d_val) != GEO_OK || !geo_approx_equal(d_val, 0.0)) return 1;
    if (normav3(v236, NULL) != GEO_ERR_NULL) return 1;

    // angulo vec3
    vec3 e1 = {1.0, 0.0, 0.0}, e2 = {0.0, 1.0, 0.0}, menos_e1 = {-1.0, 0.0, 0.0};
    if (angulovec3(e1, e2, &d_val) != GEO_OK || !geo_approx_equal(d_val, GEO_PI / 2.0)) return 1;
    if (angulovec3(e1, e1, &d_val) != GEO_OK || !geo_approx_equal(d_val, 0.0)) return 1;
    if (angulovec3(e1, menos_e1, &d_val) != GEO_OK || !geo_approx_equal(d_val, GEO_PI)) return 1;
    if (angulovec3(zero3, e2, &d_val) != GEO_ERR_DEGENERATE) return 1;
    if (angulovec3(e1, e2, NULL) != GEO_ERR_NULL) return 1;

    // dependencia linear e normalizacao vec3 
    if (dependencialinearv3(v3_a, v3_b, &int_val) != GEO_OK || int_val != 1) return 1; 
    if (dependencialinearv3(v3_a, v3_b, NULL) != GEO_ERR_NULL) return 1;
    if (normalizav3(zero3, &res3) != GEO_ERR_DEGENERATE) return 1;
    if (normalizav3(v3_a, NULL) != GEO_ERR_NULL) return 1;

    // igualdade vec3 
    if (igualdadev3(v3_a, v3_a, &int_val) != GEO_OK || int_val != 1) return 1;
    if (igualdadev3(v3_a, v3_b, &int_val) != GEO_OK || int_val != 0) return 1;
    if (igualdadev3(v3_a, v3_b, NULL) != GEO_ERR_NULL) return 1;

    printf(" todas as funcoes foram testadas com sucesso.\n");
    return 0;
}
