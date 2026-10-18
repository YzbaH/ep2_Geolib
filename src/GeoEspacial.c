#include "GeoEspacial.h"
#include <stddef.h>


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
    if (e == NULL || area == NULL) return GEO_ERR_NULL;
    if (e->raio <= 0) return GEO_ERR_INVALID;

    *area = 4.0 * GEO_PI * (e->raio) * (e->raio);

    return GEO_OK;
}

geo_status areaCilindro(const geo_cilindro *c, double *area){
    if (c == NULL || area == NULL) return GEO_ERR_NULL;
    if (c->raio <= 0 || c->altura <= 0) return GEO_ERR_INVALID;

    *area = 2.0 * GEO_PI * (c->raio) * ((c->raio) + (c->altura));

    return GEO_OK;
}

geo_status areaCone(const geo_cone *c, double *area){
    if (c == NULL || area == NULL) return GEO_ERR_NULL;
    if (c->raio <= 0 || c->geratriz <= 0) return GEO_ERR_INVALID;

    *area = GEO_PI * (c->raio) * ((c->raio) + (c->geratriz));

    return GEO_OK;
}

geo_status areaTetraedro(const geo_tetraedro *t, double *area){
    if (t == NULL || area == NULL) return GEO_ERR_NULL;
    if (t->aresta <= 0) return GEO_ERR_INVALID;

    *area = (t->aresta) * (t->aresta) * SQRT3;

    return GEO_OK;
}

geo_status volumeCubo(const geo_cubo *a, double *volume){
    if (a == NULL || volume == NULL) return GEO_ERR_NULL;
    if (a->aresta <= 0) return GEO_ERR_INVALID;

    *volume = (a->aresta) * (a->aresta) * (a->aresta);

    return GEO_OK;
}

geo_status volumeParalelepipedo(const geo_paralelepipedo *p, double *volume){
    if (p == NULL || volume == NULL) return GEO_ERR_NULL;
    if (p->comprimento <= 0 || p->largura <= 0 || p->altura <= 0) return GEO_ERR_INVALID;

    *volume = (p->comprimento) * (p->largura) * (p->altura);

    return GEO_OK;
}

geo_status volumeEsfera(const geo_esfera *e, double *volume){
    if (e == NULL || volume == NULL) return GEO_ERR_NULL;
    if (e->raio <= 0) return GEO_ERR_INVALID;

    double r = e->raio;
    *volume = (4.0 * GEO_PI * r * r * r) / 3.0;

    return GEO_OK;
}

geo_status volumeCilindro(const geo_cilindro *c, double *volume){
    if (c == NULL || volume == NULL) return GEO_ERR_NULL;
    if (c->raio <= 0 || c->altura <= 0) return GEO_ERR_INVALID;

    *volume = GEO_PI * (c->raio) * (c->raio) * (c->altura);

    return GEO_OK;
}

geo_status volumeCone(const geo_cone *c, double *volume){
    if (c == NULL || volume == NULL) return GEO_ERR_NULL;
    if (c->raio <= 0 || c->altura <= 0) return GEO_ERR_INVALID;

    *volume = (GEO_PI * (c->raio) * (c->raio) * (c->altura)) / 3.0;

    return GEO_OK;
}

geo_status volumeTetraedro(const geo_tetraedro *t, double *volume){
    if (t == NULL || volume == NULL) return GEO_ERR_NULL;
    if (t->aresta <= 0) return GEO_ERR_INVALID;

    double a = t->aresta;
    *volume = (a * a * a * SQRT2) / 12.0;

    return GEO_OK;
}
