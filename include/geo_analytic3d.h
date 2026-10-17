/**
 * @file geo_analytic3d.h
 * @brief Módulo 4: Geometria Analítica 3D (distâncias, ângulos e posições relativas).
 *
 * Todos os ângulos são medidos em radianos.
 * Comparações com zero usam a tolerância GEO_EPS.
 */

#ifndef GEO_ANALYTIC3D_H
#define GEO_ANALYTIC3D_H

#include "geo_common.h"

/** @brief Reta no espaço: pontos X = point + t * dir, com t real */
typedef struct {
    geo_point3d point;  /**< Ponto pelo qual a reta passa */
    geo_point3d dir;    /**< Vetor diretor (não pode ser nulo) */
} geo_line3d;

/**
 * @brief Plano no espaço, na forma geral a*x + b*y + c*z + d = 0.
 * O vetor (a, b, c) é normal ao plano e não pode ser nulo.
 */
typedef struct {
    double a;
    double b;
    double c;
    double d;
} geo_plane3d;

/** @brief Posições relativas entre duas retas no espaço */
typedef enum {
    GEO_LINES_COINCIDENT,   /**< Mesma reta */
    GEO_LINES_PARALLEL,     /**< Paralelas distintas */
    GEO_LINES_CONCURRENT,   /**< Concorrentes (um único ponto em comum) */
    GEO_LINES_SKEW          /**< Reversas (não paralelas e sem ponto em comum) */
} geo_lines_relation;

/** @brief Posições relativas entre dois planos */
typedef enum {
    GEO_PLANES_COINCIDENT,  /**< Mesmo plano */
    GEO_PLANES_PARALLEL,    /**< Paralelos distintos */
    GEO_PLANES_SECANT       /**< Secantes (a interseção é uma reta) */
} geo_planes_relation;

/** @brief Posições relativas entre uma reta e um plano */
typedef enum {
    GEO_LINE_IN_PLANE,        /**< Reta contida no plano */
    GEO_LINE_PARALLEL_PLANE,  /**< Reta paralela ao plano, sem pontos em comum */
    GEO_LINE_CROSSES_PLANE    /**< Reta transversal (um único ponto em comum) */
} geo_line_plane_relation;

/**
 * @brief Calcula a distância entre dois pontos no espaço.
 * @param a,b Pontos no espaço.
 * @param out_dist [out] Distância calculada.
 * @return GEO_OK ou GEO_ERR_NULL (se out_dist for NULL).
 */
geo_status geo_dist_points3d(geo_point3d a, geo_point3d b, double *out_dist);

/**
 * @brief Cria a reta que passa por dois pontos distintos.
 * @param a,b Pontos da reta (a é o ponto base e b - a é o vetor diretor).
 * @param out_line [out] Reta resultante.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_DEGENERATE (se a e b coincidem).
 */
geo_status geo_line3d_from_points(geo_point3d a, geo_point3d b, geo_line3d *out_line);

/**
 * @brief Cria o plano que passa por três pontos não colineares.
 * @param a,b,c Pontos do plano.
 * @param out_plane [out] Plano resultante.
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_DEGENERATE (se os pontos forem colineares).
 */
geo_status geo_plane3d_from_points(geo_point3d a, geo_point3d b, geo_point3d c, geo_plane3d *out_plane);

/**
 * @brief Calcula a distância entre um ponto e um plano.
 * @param pl Plano de referência.
 * @param pt Ponto no espaço.
 * @param out_dist [out] Distância calculada (sempre >= 0).
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se o vetor normal do plano for nulo).
 */
geo_status geo_dist_point_plane(const geo_plane3d *pl, geo_point3d pt, double *out_dist);

/**
 * @brief Calcula a distância entre um ponto e uma reta no espaço.
 * @param r Reta de referência.
 * @param pt Ponto no espaço.
 * @param out_dist [out] Distância calculada (sempre >= 0).
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se o vetor diretor da reta for nulo).
 */
geo_status geo_dist_point_line3d(const geo_line3d *r, geo_point3d pt, double *out_dist);

/**
 * @brief Calcula o ângulo agudo entre duas retas (vale também para retas reversas).
 * @param r,s Retas avaliadas.
 * @param out_angle [out] Ângulo em radianos, no intervalo [0, pi/2].
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se algum vetor diretor for nulo).
 */
geo_status geo_angle_lines3d(const geo_line3d *r, const geo_line3d *s, double *out_angle);

/**
 * @brief Calcula o ângulo agudo entre dois planos (o ângulo entre suas normais).
 * @param pl1,pl2 Planos avaliados.
 * @param out_angle [out] Ângulo em radianos, no intervalo [0, pi/2].
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se alguma normal for nula).
 */
geo_status geo_angle_planes(const geo_plane3d *pl1, const geo_plane3d *pl2, double *out_angle);

/**
 * @brief Determina a posição relativa entre duas retas no espaço.
 * @param r,s Retas avaliadas.
 * @param out_pos [out] Posição relativa (coincidentes, paralelas, concorrentes ou reversas).
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se algum vetor diretor for nulo).
 */
geo_status geo_lines3d_position(const geo_line3d *r, const geo_line3d *s, geo_lines_relation *out_pos);

/**
 * @brief Determina a posição relativa entre dois planos.
 * @param pl1,pl2 Planos avaliados.
 * @param out_pos [out] Posição relativa (coincidentes, paralelos ou secantes).
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se alguma normal for nula).
 */
geo_status geo_planes_position(const geo_plane3d *pl1, const geo_plane3d *pl2, geo_planes_relation *out_pos);

/**
 * @brief Determina a posição relativa entre uma reta e um plano.
 * @param r Reta avaliada.
 * @param pl Plano avaliado.
 * @param out_pos [out] Posição relativa (contida, paralela ou transversal).
 * @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (se o vetor diretor ou a normal forem nulos).
 */
geo_status geo_line_plane_position(const geo_line3d *r, const geo_plane3d *pl, geo_line_plane_relation *out_pos);

#endif /* GEO_ANALYTIC3D_H */
