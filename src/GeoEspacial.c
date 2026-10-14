#include "GeoEspacial.h"

#define PI 3.14
#define SQRT3 1.73
#define SQRT2 1.41


geo_status areaCubo(const geo_cubo *a, double *area){
    if (a == NULL || area == NULL) return GEO_ERR_NULL;
    if (a->aresta <= 0) return GEO_ERR_INVALID;
    
    *area = 6.0 * (a->aresta) * (a->aresta);

    return GEO_OK;
}

geo_status areaParalelepipedo(const geo_paralelepipedo *p, double *area){
    if (p == NULL || area == NULL) return GEO_ERR_NULL;
    if (p->comprimento <= 0 || p->largura <= 0 || p->altura <= 0) return GEO_ERR_INVALID;

    *area = 2.0 * ((p->comprimento) * (p->largura) + (p->comprimento) * (p->altura) + (p->largura) * (p->altura));

    return GEO_OK;
}

geo_status areaEsfera(const geo_esfera *e, double *area){
    if(e == NULL || area == NULL) return GEO_ERR_NULL;
    if(e->raio <= 0) return GEO_ERR_INVALID;

    *area = 4.0 * PI * (e->raio) * (e->raio);

    return GEO_OK;
}

geo_status areaCilindro(const geo_cilindro *c, double *area){
    if(c == NULL || area == NULL) return GEO_ERR_NULL;
    if(c->raio <= 0 || c->altura <= 0) return GEO_ERR_INVALID;

    *area = 2.0 * PI * (c->raio) * ((c->raio) + (c->altura));

    return GEO_OK;
}

geo_status areaCone(const geo_cone *c, double *area){
    if(c == NULL || area == NULL) return GEO_ERR_NULL;
    if(c->raio <= 0 || c->geratriz <= 0) return GEO_ERR_INVALID;

    *area = PI * (c->raio) * ((c->raio) + (c->geratriz));

    return GEO_OK;
}

geo_status areaTetraedro(const geo_tetraedro *t, double *area){
    if (t == NULL || area == NULL) return GEO_ERR_NULL;
    if (t->aresta <= 0) return GEO_ERR_INVALID;

    *area =  (t->aresta) * (t->aresta) * SQRT3;

    return GEO_OK;
}