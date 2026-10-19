/**
 * @file vecoperations.h
 * @brief realiza opeações basicas com vetores 2D e 3D
 */

#ifndef VECOPERATIONS_H
#define VECOPERATIONS_H

#include "geo_common.h"

/**
 * @brief vetor 2D
 */
typedef struct vec2 {
    double x;
    double y;
}vec2;
/**
 *@brief vetor 3D
 */
typedef struct vec3 {
    double x;
    double y;
    double z;
}vec3;

//OPERAÇÕES VEC2

/**
 * @brief soma 2 vetores 2D
 * @param a vetor 2D 1
 * @param b vetor 2D 2
 * @param outresult ponteiro que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL.
 */ 
geo_status somavec2(vec2 a, vec2 b,vec2 *outresult);
/**
 * @brief subtrai 2 vetores 2D
 * @param a vetor 2D 1
 * @param b vetor 2D 2
 * @param outresult ponteiro que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL.
 */
geo_status subtraivec2(vec2 a, vec2 b,vec2 *outresult);
/**
 * @brief multiplica um vetor 2D por um numero escalar doublle
 * @param a vetor 2D
 * @param b escalar double
 * @param outresult ponteiro que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL.
 */
geo_status multescalarv2(vec2 a, double b,vec2 *outresult);
/**
 * @brief calcula o produto escalar entre dois vetores 2D
 * @param a vetor 2D 1
 * @param b vetor 2D 2
 * @param outresult ponteiro que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL.
 */
geo_status produtoescalarv2(vec2 a, vec2 b, double *outresult );
/**
 * @brief verifica se dois vetores 2D são LI ou LD
 * @param a vec 2D 1
 * @param b vec 2D 2
 * @param eld ponteiro int (*eld = 1(LD), *eld = 0(LI))
 * @return GEO_OK ou GEO_ERR_NULL
 */
geo_status dependencialinearv2(vec2 a, vec2 b, int *eld);
/**
 * @brief calcula a norma do vetor
 * @param a vec 2D
 * @param outresult ponteiro double que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL 
 */
geo_status normav2(vec2 a,double *outresult);
/**
 * @brief calcula o angulo entre dois vetores
 * @param a vec 2D
 * @param outresult ponteiro double que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL ou GEO_ERR_DEGENERATE
 * 
 */
geo_status angulovec2(vec2 a, vec2 b, double *outresult);
/**
 * @brief calcula um vetor de norma 1 com mesma direção e sentido do vetor passado
 * @param a vec 2D
 * @return GEO_OK ou GEO_ERR_NULL ou GEO_ERR_DEGENERATE se o vetor for 0
 * @pre a não pode ser igual a 0
 * @post a norma do vetor será 1 respeitando GEO_EPS 
 */
geo_status normalizav2(vec2 a, vec2 *outresult);
/**
 * @brief avalia se dois vetroes são iguais ou não
 * @param a vetor 2D
 * @param b vetor 2D
 * @param igual ponteiro que aponta para o resultado (*igual = 1(são iguais))
 * @return GEO_OK ou GEO_ERR_NULL
 */
geo_status igualdadev2(vec2 a, vec2 b,int *igual);

//OPERAÇÕES VEC3

/**
 * @brief soma 2 vetores 3D
 * @param a vetor 3D 1
 * @param b vetor 3D 2
 * @param outresult ponteiro que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL.
 */ 
geo_status somavec3(vec3 a, vec3 b, vec3 *outresult);
/**
 * @brief subtrai 2 vetores 3D
 * @param a vetor 3D 1
 * @param b vetor 3D 2
 * @param outresult ponteiro que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL.
 */
geo_status subtraivec3(vec3 a, vec3 b,vec3 *outresult);
/**
 * @brief multiplica um vetor 3D por um numero escalar doublle
 * @param a vetor 3D
 * @param b escalar double
 * @param outresult ponteiro que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL.
 */
geo_status multescalarv3(vec3 a, double b,vec3 *outresult);
/**
 * @brief calcula o produto escalar entre sois vetores 3D
 * @param a vetor 3D 1
 * @param b vetor 3D 2
 * @param outresult ponteiro que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL.
 */
geo_status produtoescalarv3(vec3 a, vec3 b, double *outresult);
/**
 * @brief Calcula o produto vetorial entre dois vetores 3D.
 * @param a Vetor 3D 1
 * @param b Vetor 3D 2
 * @param outresult Ponteiro que aponta para o vetor 3D resultado
 * @return GEO_OK ou GEO_ERR_NULL
 */
geo_status produtovetorialv3(vec3 a, vec3 b, vec3 *outresult); 
/**
 * @brief verifica se 2 vetores 3D são LI ou LD
 * @param a vec 3D 1
 * @param b vec 3D 2
 * @param eld ponteiro int (*eld = 1 se LD, *eld = 0 se LI)
 * @return GEO_OK ou GEO_ERR_NULL
 */
geo_status dependencialinearv3(vec3 a, vec3 b, int *eld);
/**
 * @brief calcula a norma do vetor
 * @param a vec 3D
 * @param outresult ponteiro que aponta para o resultado
 * @return GEO_OK ou GEO_ERR_NULL 
 */
geo_status normav3(vec3 a, double *outresult);
/**
 * @brief calcula angulo entre dois vetores 3D
 * @param a vec 3D 1
 * @param b vec 3D 2
 * @param outresult aponta para resultado
 * @return GEO_OK ou GEO_ERR_NULL ou GEO_ERR_DEGENERATE 
 */
geo_status angulovec3(vec3 a, vec3 b, double *outresult);
/**
 * @brief calcula um vetor de norma 1 com mesma direção e sentido do vetor passado
 * @param a vec 3D
 * @return GEO_OK ou GEO_ERR_NULL ou GEO_ERR_DEGENERATE se algum dos vetores for 0
 * @pre a não pode ser igual a 0
 * @post a norma do vetor será um respeitando GEO_EPS 1e-9
 */   
geo_status normalizav3(vec3 a,vec3 *outresult);
/**
 * @brief avalie se dois vetroes são iguais ou não
 * @param a vetor 3D
 * @param b vetor 3D
 * @param igual ponteiro que aponta para o resultadoou (*igual = 1 se sao iguais, 0 caso contrario)
 * @return GEO_OK ou ou GEO_ERR_NULL
 */
geo_status igualdadev3(vec3 a, vec3 b, int *igual);


#endif //VECOPERATIONS_H
