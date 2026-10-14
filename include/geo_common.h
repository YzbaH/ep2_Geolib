/**
 * @file geo_common.h
 * @brief Tipos primitivos, códigos de status, constantes e utilitários compartilhados.
 */

#ifndef GEO_COMMON_H
#define GEO_COMMON_H

#include <stddef.h>
#include <math.h>

/** @brief Tolerância para comparações de double */
#define GEO_EPS 1e-9

/** @brief Pi com alta precisão */
#define GEO_PI 3.14159265358979323846

/** @brief Códigos de retorno de todas as funções */
typedef enum {
    GEO_OK = 0,         /**< Operação realizada com sucesso */
    GEO_ERR_NULL,       /**< Ponteiro nulo */
    GEO_ERR_INVALID,    /**< Número inválido */
    GEO_ERR_DEGENERATE  /**< Forma geométrica degenerada */
} geo_status;

/** @brief Ponto no espaço 2D */
typedef struct {
    double x;
    double y;
} geo_point2d;

/** @brief Ponto ou vetor no espaço 3D */
typedef struct {
    double x;
    double y;
    double z;
} geo_point3d;

/**
* @brief Compara se dois números são aproximadamente iguais sob a tolerância epsilon.
* @param a,b Valores
* @return 1 se forem iguais, 0 caso contrário.
*/
int geo_approx_equal(double a, double b);


#endif /* GEO_COMMON_H */
