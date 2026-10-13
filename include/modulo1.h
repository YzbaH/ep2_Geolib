/**
* @file modulo1.h 
* @brief Módulo 1: Geometria Plana (áreas, perimetros, triângulos e circulos)
*/ 

#ifndef MODULO1_H
#define MODULO1_H 

#define GEO_EPS 1e-9 /** Tolerância paras operções com ponto flutuante*/ 

/* Códigos de status */ 
typedef enum {
    GEO_OK = 0,        /**< Operação realizado com sucesso*/ 
    GEO_ERR_NULL,       /**< Ponteiro nulo*/ 
    GEO_ERR_INVALID,    /**< Número invalido*/
    GEO_ERR_DEGENERATE  /**< Forma geometrica degenerada*/ 
} geo_status;

/** Ponto 2d*/
typedef struct {
    double x;
    double y;
} geo_point2d;

/** Triângulo */
typedef struct {
    geo_point2d a;
    geo_point2d b;
    geo_point2d c;
} geo_triangle2d;

/** Circulo */ 
typedef struct{
    geo_point2d center;
    double radius;
} geo_circle2d;

/*tipos de trângulos*/ 
typedef enum{
    TRIANGLE_EQULATERAL,
    TRIANGLE_ISOSCELES,
    TRIANGLE_SCALENE
} geo_triangle_type;

/* Posição relativa ponto circulo */ 
typedef enum{
    POINT_INSIDE_CIRCLE,
    POINT_ON_CIRCLE,
    POINT_OUTSIDE_CIRCLE
} geo_point_circle_pos;



/**
* @brief Verifica se os três pontos são colineares no plano.
* @param a, b, c pontos do triângulo 
* @param out_collinear 1 se colinear, 0 caso contrário. 
* @return GEO_OK ou GEO_ERR_NULL
*/ 
geo_status geo_points_collinear(geo_point2d a, geo_point2d b, geo_point2d c, int *out_collinear);

/**
* @brief Cria e valida um triângulo.
* @param a,b,c Vértices.
* @param out_triangle Triângulo resultante.
* @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_DEGENERATE (se colineares).
*/
geo_status geo_triangle_create(geo_point2d a, geo_point2d b, geo_point2d c, geo_triangle2d *out_triangle);

/**
* @brief Calcula a área de um triângulo.
* @param t Triângulo
* @param out_area [out] Área
* @return GEO_OK ou GEO_ERR_NULL.
*/
geo_status geo_triangle_area(const geo_triangle2d *t, double *out_area);

/**
* @brief Calcula o perímetro de um triângulo.
* @param t Triângulo
* @param out_perimeter [out] Perímetro
* @return GEO_OK ou GEO_ERR_NULL.
*/
geo_status geo_triangle_perimeter(const geo_triangle2d *t, double *out_perimeter);

/**
* @brief Classifica o triângulo (equilátero, isósceles ou escaleno).
* @param t Triângulo 
* @param out_type [out] Classificação
* @return GEO_OK ou GEO_ERR_NULL.
*/
geo_status geo_triangle_classify(const geo_triangle2d *t, geo_triangle_type *out_type);

/**
* @brief Cria e valida uma circunferência 2D (exige raio > 0).
* @param center ponto Centro
* @param radius Raio
* @param out_circle [out] Circunferência gerada.
* @return GEO_OK, GEO_ERR_NULL ou GEO_ERR_INVALID (raio <= 0)
*/
geo_status geo_circle_create(geo_point2d center, double radius, geo_circle2d *out_circle);

/**
* @brief Calcula a área de uma circunferência.
* @param c Circunferência
* @param out_area [out] Área
* @return GEO_OK ou GEO_ERR_NULL.
*/
geo_status geo_circle_area(const geo_circle2d *c, double *out_area);

/**
* @brief Calcula o perímetro de uma circunferência.
* @param c Circunferência
* @param out_perimeter [out] Perímetro
* @return GEO_OK ou GEO_ERR_NULL.
*/
geo_status geo_circle_perimeter(const geo_circle2d *c, double *out_perimeter);

/**
* @brief Determina se um ponto está dentro, na borda ou fora de uma circunferência.
* @param c Circunferência
* @param p Ponto
* @param out_pos [out] Posição relativa.
* @return GEO_OK ou GEO_ERR_NULL.
*/
geo_status geo_circle_point_position(const geo_circle2d *c, geo_point2d p, geo_point_circle_pos *out_pos);

#endif /* MODULO1_H */
