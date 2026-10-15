#include "GeoAnalitica2D.h"
#include <math.h>
#include <stddef.h>

geo_status calculaCoefAngular(geo_ponto2d a, geo_ponto2d b, double *coefA){
    if (coefA == NULL) return GEO_ERR_NULL;
    if(fabs(b.x - a.x) < GEO_EPS) return GEO_ERR_INVALID;

    *coefA = (b.y - a.y) / (b.x - a.x);

    return GEO_OK;
}

geo_status distPontoPonto(geo_ponto2d a, geo_ponto2d b, double *dist){
    if (dist == NULL) return GEO_ERR_NULL;
    
    double difX = (b.x - a.x) * (b.x - a.x);
    double difY = (b.y - a.y) * (b.y - a.y);

    *dist = sqrt(difX + difY);
    
    return GEO_OK;
}

geo_status distPontoReta(const geo_eqGeralReta *r, geo_ponto2d p, double *dist){
    if (r == NULL || dist == NULL) return GEO_ERR_NULL;
    if (fabs(r->coefX) < GEO_EPS && fabs(r->coefY) < GEO_EPS) return GEO_ERR_INVALID;

    double numerador = (r->coefX) * p.x + (r->coefY) * p.y + r->c;
    double denominador = sqrt( (r->coefX)*(r->coefX) + (r->coefY)*(r->coefY) );
    if (numerador < 0) numerador = -numerador;
    
    *dist = numerador/denominador;

    return GEO_OK;
}

geo_status posicaoRelativaRetas(const geo_eqGeralReta *r, const geo_eqGeralReta *s, posicao_retas *posicao, geo_ponto2d *interseccao){
    if(r == NULL || s == NULL || posicao == NULL) return GEO_ERR_NULL;
    if (fabs(r->coefX) < GEO_EPS && fabs(r->coefY) < GEO_EPS) return GEO_ERR_INVALID;
    if (fabs(s->coefX) < GEO_EPS && fabs(s->coefY) < GEO_EPS) return GEO_ERR_INVALID;

    double det = (r->coefX) * (s->coefY) - (r->coefY) * (s->coefX);

    if (fabs(det) >= GEO_EPS){
        *posicao = RETAS_CONCORRENTES;

        if(interseccao != NULL){
            geo_status retorno = pontoEncontro(r, s, interseccao);

            if(retorno != GEO_OK) return retorno;
        }   
    } else {
        double r2 = (r->coefX)*(s->c) - (r->c)*(s->coefX);
        double r3 = (r->coefY)*(s->c) - (r->c) * (s->coefY);

        if(fabs(r2) < GEO_EPS && fabs(r3) < GEO_EPS){
            *posicao = RETAS_COINCIDENTES;
        } else {
            *posicao = RETAS_PARALELAS;
        }
        
        
    }

    return GEO_OK;
}

geo_status pontoEncontro(const geo_eqGeralReta *r, const geo_eqGeralReta *s, geo_ponto2d *solucao){
    if (r == NULL || s == NULL || solucao == NULL) return GEO_ERR_NULL;
    if (fabs(r->coefX) < GEO_EPS && fabs(r->coefY) < GEO_EPS) return GEO_ERR_INVALID;
    if (fabs(s->coefX) < GEO_EPS && fabs(s->coefY) < GEO_EPS) return GEO_ERR_INVALID;

    double det = (r->coefX) * (s->coefY) - (r->coefY) * (s->coefX);

    if (fabs(det) >= GEO_EPS){
        double dx = (- r->c ) * (s->coefY) - ( -s->c ) * (r->coefY);
        double dy = (r->coefX) * (- s->c ) - (s->coefX) * (- r->c ); 

        solucao->x = dx / det;
        solucao->y = dy / det;
    } else {
        return GEO_ERR_INVALID;
    }

    return GEO_OK;
}

geo_status pontoMedio(geo_ponto2d a, geo_ponto2d b, geo_ponto2d *pMedio){
    if(pMedio == NULL) return GEO_ERR_NULL;

    pMedio->x = (a.x + b.x) / 2.0;
    pMedio->y = (a.y + b.y) / 2.0;

    return GEO_OK;
}