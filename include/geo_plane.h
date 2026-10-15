/**
 * @file geo_plane.h 
 * @brief Módulo 1: Geometria Plana (áreas, perímetros, triângulos e círculos).
 */ 

#ifndef GEO_PLANE_H
#define GEO_PLANE_H

#include "geo_common.h"

/** @brief Triângulo definido por três pontos 2D */
typedef struct {
    geo_point2d a;
    geo_point2d b;
    geo_point2d c;
} geo_triangle2d;

/** @brief Círculo definido por centro e raio */ 
typedef struct {
    geo_point2d center;
    double radius;
} geo_circle2d;

/** @brief Tipos de triângulos */ 
typedef enum {
    GEO_TRIANGLE_EQUILATERAL,
    GEO_TRIANGLE_ISOSCELES,
    GEO_TRIANGLE_SCALENE
} geo_triangle_type;

/** @brief Posição relativa de um ponto em relação ao círculo */ 
typedef enum {
    GEO_POINT_INSIDE_CIRCLE,
    GEO_POINT_ON_CIRCLE,
    GEO_POINT_OUTSIDE_CIRCLE
} geo_point_circle_pos;

/**
 * @brief Verifica se três pontos são colineares no plano.
 * @param a,b,c Pontos no plano.
 * @param out_collinear [out] Recebe 1 se colinear, 0 caso contrário.
 * @return GEO_OK ou GEO_ERR_NULL.
 */ 
geo_status geo_points_collinear(geo_point2d a, geo_point2d b, geo_point2d c, int *out_collinear);

/**
 * @brief Cria e valida um triângulo.
 * @param a,b,c Vértices do triângulo.
 * @param out_triangle [out] Triângulo resultante.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_DEGENERATE (se colineares).
 */
geo_status geo_triangle_create(geo_point2d a, geo_point2d b, geo_point2d c, geo_triangle2d *out_triangle);

/**
 * @brief Calcula a área de um triângulo.
 * @param t Triângulo de entrada.
 * @param out_area [out] Área calculada.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_DEGENERATE (se degenerado).
 */
geo_status geo_triangle_area(const geo_triangle2d *t, double *out_area);

/**
* @brief Calcula a distância entre dois pontos no plano.
* @param a,b Pontos no plano
* @param out_dist [out] Distância calculada
* @return GEO_OK ou GEO_ERR_NULL
*/
geo_status geo_dist_points(geo_point2d a, geo_point2d b, double *out_dist);

/**
 * @brief Calcula o perímetro de um triângulo.
 * @param t Triângulo de entrada.
 * @param out_perimeter [out] Perímetro calculado.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_DEGENERATE (se degenerado).
 */
geo_status geo_triangle_perimeter(const geo_triangle2d *t, double *out_perimeter);

/**
 * @brief Classifica o triângulo (equilátero, isósceles ou escaleno).
 * @param t Triângulo avaliado.
 * @param out_type [out] Classificação resultante.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_DEGENERATE (se degenerado).
 */
geo_status geo_triangle_classify(const geo_triangle2d *t, geo_triangle_type *out_type);

/**
 * @brief Cria e valida uma circunferência 2D (exige raio > 0).
 * @param center Ponto central.
 * @param radius Raio da circunferência.
 * @param out_circle [out] Circunferência gerada.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se raio <= 0).
 */
geo_status geo_circle_create(geo_point2d center, double radius, geo_circle2d *out_circle);

/**
 * @brief Calcula a área de uma circunferência.
 * @param c Circunferência de entrada.
 * @param out_area [out] Área calculada.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se raio <= 0).
 */
geo_status geo_circle_area(const geo_circle2d *c, double *out_area);

/**
 * @brief Calcula o perímetro de uma circunferência.
 * @param c Circunferência de entrada.
 * @param out_perimeter [out] Perímetro calculado.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se raio <= 0).
 */
geo_status geo_circle_perimeter(const geo_circle2d *c, double *out_perimeter);

/**
 * @brief Determina se um ponto está dentro, na borda ou fora de uma circunferência.
 * @param c Circunferência de referência.
 * @param p Ponto avaliado.
 * @param out_pos [out] Posição relativa do ponto.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se raio <= 0).
 */
geo_status geo_circle_point_position(const geo_circle2d *c, geo_point2d p, geo_point_circle_pos *out_pos);

#endif /* GEO_PLANE_H */
