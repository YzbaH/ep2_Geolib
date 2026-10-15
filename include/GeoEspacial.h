/**
* @file GeoEspacial.h 
* @brief Módulo: Geometria Espacial: Áreas e volumes.
*/ 

#ifndef GEOESPACIAL_H
#define GEOESPACIAL_H


/** @brief Tolerância para comparações de double */
#define GEO_EPS 1e-9

typedef enum {
    GEO_OK = 0,        /**< Operação realizado com sucesso*/ 
    GEO_ERR_NULL,       /**< Ponteiro nulo*/ 
    GEO_ERR_INVALID,    /**< Número invalido*/
    GEO_ERR_DEGENERATE  /**< Forma geometrica degenerada*/ 
} geo_status;

/** Cubo */
typedef struct {
    double aresta;
} geo_cubo;

/** Paralelepipedo */
typedef struct {
    double comprimento;
    double largura;
    double altura;
} geo_paralelepipedo;

/** Esfera */
typedef struct {
    double raio;
} geo_esfera;

/** Cilindro */
typedef struct {
    double raio;
    double altura;
} geo_cilindro;

/** Cone */
typedef struct {
    double raio;
    double altura;
    double geratriz;
} geo_cone;

/** Tetraedro regular */
typedef struct {
    double aresta;
} geo_tetraedro;

/**
* @brief Calcula a área de um cubo.
* @param a Ponteiro para um cubo com a medida de sua aresta.
* @param area Ponteiro para armazenar a área calculada.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se a ou area for NULL;
*         GEO_ERR_INVALID se a->aresta <= 0.
* @pre a != NULL.
* @pre area != NULL.
* @pre a->aresta > 0
*/ 
geo_status areaCubo(const geo_cubo *a, double *area);

/**
* @brief Calcula a área de um paralelepipedo reto retângulo.
* @param p Ponteiro para um paralelepípedo com suas medidas.
* @param area Ponteiro para armazenar a área calculada.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se p ou area for NULL;
*         GEO_ERR_INVALID se p->comprimento <= 0, p->largura <= 0 ou p->altura <= 0.
* @pre p->comprimento > 0.
* @pre p->largura > 0.
* @pre p->altura > 0.
* @pre p != NULL.
* @pre area != NULL.
*/ 
geo_status areaParalelepipedo(const geo_paralelepipedo *p, double *area);


/**
* @brief Calcula área de uma esfera.
* @param e Ponteiro para uma esfera com a medida do seu raio.
* @param area Ponteiro para armazenar a área calculada. 
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se e ou area for NULL;
*         GEO_ERR_INVALID se e->raio <= 0.
* @pre e->raio > 0.
* @pre e != NULL.
* @pre area != NULL.
* @note A função usa 3.14 como valor de π(pi).
*/ 
geo_status areaEsfera(const geo_esfera *e, double *area);

/**
* @brief Calcula área de um cilindro.
* @param c Ponteiro para um cilindro com seu raio e altura.
* @param area Ponteiro para armazenar a área calculada.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se c ou area for NULL;
*         GEO_ERR_INVALID se c->raio <= 0 ou c->altura <= 0.
* @pre c->raio > 0.
* @pre c->altura > 0.
* @pre c != NULL.
* @pre area != NULL.
* @note A função usa 3.14 como valor de π(pi).
*/ 
geo_status areaCilindro(const geo_cilindro *c, double *area);

/**
* @brief Calcula área de um cone.
* @param c Ponteiro para cone com seu raio e geratriz.
* @param area Ponteiro para armazenar a área calculada. 
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se c ou area for NULL;
*         GEO_ERR_INVALID se c->raio <= 0 ou c->geratriz <= 0
* @pre c->raio > 0.
* @pre c->geratriz > 0.
* @pre c != NULL.
* @pre area != NULL.
* @note A função usa 3.14 como valor de π(pi).
*/ 
geo_status areaCone(const geo_cone *c, double *area);

/**
* @brief Calcula área de um Tetraedro regular.
* @param t Ponteiro para tetraedro regular.
* @param area Ponteiro para armazenar a área calculada.  
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se t ou area for NULL;
*         GEO_ERR_INVALID se t->aresta <= 0.
* @pre t->aresta > 0.
* @pre t != NULL.
* @pre area != NULL.
* @note A função usa 1,73 como valor de raiz de 3.
*/ 
geo_status areaTetraedro(const geo_tetraedro *t, double *area);

/**
* @brief Calcula o volume de um cubo.
* @param a Ponteiro para um cubo com a medida de sua aresta.
* @param volume Ponteiro para armazenar o volume calculado.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se a ou volume for NULL;
*         GEO_ERR_INVALID se a->aresta <= 0.
* @pre a != NULL.
* @pre volume != NULL.
* @pre a->aresta > 0
*/ 
geo_status volumeCubo(const geo_cubo *a, double *volume);

/**
* @brief Calcula o volume de um paralelepipedo reto retângulo.
* @param p Ponteiro para um paralelepípedo com suas medidas.
* @param volume Ponteiro para armazenar o volume calculado.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se p ou volume for NULL;
*         GEO_ERR_INVALID se p->comprimento <= 0, p->largura <= 0 ou p->altura <= 0.
* @pre p->comprimento > 0.
* @pre p->largura > 0.
* @pre p->altura > 0.
* @pre p != NULL.
* @pre volume != NULL.
*/ 
geo_status volumeParalelepipedo(const geo_paralelepipedo *p, double *volume);

/**
* @brief Calcula o volume de uma esfera.
* @param e Ponteiro para uma esfera com a medida do seu raio.
* @param volume Ponteiro para armazenar o volume calculado. 
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se e ou volume for NULL;
*         GEO_ERR_INVALID se e->raio <= 0.
* @pre e->raio > 0.
* @pre e != NULL.
* @pre volume != NULL.
* @note A função usa 3.14 como valor de π(pi).
*/ 
geo_status volumeEsfera(const geo_esfera *e, double *volume);

/**
* @brief Calcula o volume de um cilindro.
* @param c Ponteiro para um cilindro com seu raio e altura.
* @param volume Ponteiro para armazenar o volume calculado.
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se c ou volume for NULL;
*         GEO_ERR_INVALID se c->raio <= 0 ou c->altura <= 0.
* @pre c->raio > 0.
* @pre c->altura > 0.
* @pre c != NULL.
* @pre volume != NULL.
* @note A função usa 3.14 como valor de π(pi).
*/ 
geo_status volumeCilindro(const geo_cilindro *c, double *volume);

/**
* @brief Calcula o volume de um cone.
* @param c Ponteiro para cone com seu raio e altura.
* @param volume Ponteiro para armazenar o volume calculado. 
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se c ou volume for NULL;
*         GEO_ERR_INVALID se c->raio <= 0 ou c->altura <= 0
* @pre c->raio > 0.
* @pre c->altura > 0.
* @pre c != NULL.
* @pre volume != NULL.
* @note A função usa 3.14 como valor de π(pi).
*/ 
geo_status volumeCone(const geo_cone *c, double *volume);

/**
* @brief Calcula volume de um Tetraedro regular.
* @param t Ponteiro para tetraedro regular.
* @param volume Ponteiro para armazenar o volume calculado.  
* @return GEO_OK em caso de sucesso;
*         GEO_ERR_NULL se t ou volume for NULL;
*         GEO_ERR_INVALID se t->aresta <= 0.
* @pre t->aresta > 0.
* @pre t != NULL.
* @pre volume != NULL.
* @note A função usa 1,41 como valor de raiz de 2.
*/ 
geo_status volumeTetraedro(const geo_tetraedro *t, double *volume);

#endif /* GEOESPACIAL_H */