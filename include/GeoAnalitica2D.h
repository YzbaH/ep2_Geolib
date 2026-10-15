/**
* @file GeoAnalitica2D.h 
* @brief Módulo: Geometria Analítica 2D 
*/ 

#ifndef GEOANALITICA2D_H
#define GEOANALITICA2D_H

/* Códigos de status */ 
typedef enum {
    GEO_OK = 0,        /**< Operação realizada com sucesso*/ 
    GEO_ERR_NULL,       /**< Ponteiro nulo*/ 
    GEO_ERR_INVALID,    /**< Número invalido*/
    GEO_ERR_DEGENERATE  /**< Forma geometrica degenerada*/ 
} geo_status;

/**Ponto 2D*/
typedef struct{
  double x;
  double y;
} geo_ponto2d;

/** Equação da reta na forma ax + by + c = 0 */
typedef struct{
    double coefX;
    double coefY;
    double c;
} geo_eqGeralReta;

typedef enum {
    RETAS_CONCORRENTES,
    RETAS_PARALELAS,
    RETAS_COINCIDENTES
} posicao_retas;

/**
* @brief Calcula o coeficiente angular de uma reta a partir de 2 pontos.
* @param a Coordenadas do primeiro ponto.
* @param b Coordenadas do segundo ponto.
* @param coefA Ponteiro para armazenar o coeficiente angular.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se coefA for NULL;
*         GEO_ERR_INVALID se a reta for vertical.
* @pre coefA != NULL.
* @pre b.x - a.x != 0.
*/
geo_status calculaCoefAngular(geo_ponto2d a, geo_ponto2d b, double *coefA);

/**
* @brief Calcula a distancia de 2 pontos em E².
* @param a Coordenadas do primeiro ponto.
* @param b Coordenadas do segundo ponto.
* @param dist Ponteiro que armazena a distância entre os pontos.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se dist for NULL.
* @pre dist != NULL.
*/
geo_status distPontoPonto(geo_ponto2d a, geo_ponto2d b, double *dist);

/**
* @brief Calcula a distância entre um ponto e uma reta.
* @param r Ponteiro para os coeficientes a, b e c da reta na forma ax + by + c = 0.
* @param p Coordenadas do ponto.
* @param dist Ponteiro que armazena a distância entre a reta e o ponto.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se r ou dist for NULL;
*         GEO_ERR_INVALID se os coeficients a e b forem ambos nulos.
* @pre r != NULL.
* @pre dist != NULL.
* @pre (r->coefX)² + (r->coefY)² != 0.
*/
geo_status distPontoReta(const geo_eqGeralReta *r, geo_ponto2d p, double *dist);

/**
* @brief Estuda a posição relativa entre duas retas em E²
* @param r Ponteiro para os coeficientes a, b e c da primeira reta na forma ax + by + c = 0.
* @param s Ponteiro para os coeficientes k, l e m da segunda reta na forma kx + ly + m = 0.
* @param posicao Ponteiro que armazenará a posição relativa entre as retas.
* @param interseccao Ponteiro que armazenará o ponto de intersecção caso exista.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se r, s ou posicao for NULL;
*         GEO_ERR_INVALID se a equação de uma das retas for inválida.
* @pre r->coefX e r->coefY não podem ser ambos nulos.
* @pre s->coefX e s->coefY não podem ser ambos nulos.
* @note Se o valor de entrada de interseccao for NULL, a função não calcula o ponto de encontro das retas.
*/
geo_status posicaoRelativaRetas(const geo_eqGeralReta *r, const geo_eqGeralReta *s, posicao_retas *posicao, geo_ponto2d *interseccao);

/**
* @brief Dada duas retas na forma ax + by + c = 0 que são concorrentes, calcula o ponto de encontro das retas.
* @param r Ponteiro para os coeficientes da primeira reta.
* @param s Ponteiro para os coeficientes da segunda reta.
* @param solucao Ponteiro para armazenar o ponto de encontro
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se r, s ou solucao for NULL;
*         GEO_ERR_INVALID se a equação de uma das retas for inválida ou se as retas não forem concorrentes.
* @pre r->coefX e r->coefY não podem ser ambos nulos.
* @pre s->coefX e s->coefY não podem ser ambos nulos.
*/
geo_status pontoEncontro(const geo_eqGeralReta *r, const geo_eqGeralReta *s, geo_ponto2d *solucao);


/**
* @brief Calcula o ponto médio entre 2 pontos conhecidos.
* @param a Coordenadas do primeiro ponto.
* @param b Coordenadas do segundo ponto.
* @param pMedio Ponteiro que armazena as coordenadas do ponto médio.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se pMedio for NULL.
* @pre pMedio != NULL.
*/
geo_status pontoMedio(geo_ponto2d a, geo_ponto2d b, geo_ponto2d *pMedio);


#endif /* GEOANALITICA2D_H */