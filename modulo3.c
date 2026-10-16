#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "modulo3.h"

#define GEO_EPS 1e-9

typedef enum {
    GEO_OK = 0,       
    GEO_ERR_NULL,      
    GEO_ERR_INVALID,   
    GEO_ERR_DEGENERATE   
} geo_status;


geo_status somavec2(vec2 a, vec2 b,vec2 *outresult){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    outresult->x = a.x + b.x;
    outresult->y = a.y + b.y;
    return GEO_OK;
}
geo_status subtraivec2(vec2 a, vec2 b,vec2 *outresult){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    outresult->x = a.x - b.x;
    outresult->y = a.y - b.y;
    return GEO_OK;
}
geo_status multplicaescalar(vec2 a, double b,vec2 *outresult){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    outresult->x = a.x * b;
    outresult->y = a.y * b;
    return GEO_OK;
}
geo_status produtoescalar(vec2 a, vec2 b, double *outresult ){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    *outresult = (a.x * b.x) + (a.y * b.y);
    return GEO_OK;
}
geo_status dependencialinear(vec2 a, vec2 b, int *eld){
    if (eld == NULL) {
        return GEO_ERR_NULL;
    }
    double det = (a.x * b.y) - (a.y * b.x);
    if (fabs(det) < GEO_EPS) {
        *eld = 1; // L.D.
    } else {
        *eld = 0; // L.I.
    }
    return GEO_OK;
}
geo_status normav2(vec2 a,double *outresult){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    double n = sqrt((a.x)*(a.x) + (a.y)*(a.y));
    if(n < GEO_EPS){
        *outresult = 0.0;
    }else{
        *outresult = n;
    }
    return GEO_OK;
}
geo_status angulovec2(vec2 a, vec2 b, double *outresult){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    double prodescalar;
    double n1;
    double n2;

    geo_status auxiliar;
    auxiliar = produtoescalarv2(a, b, &prodescalar);
    if(auxiliar != GEO_OK)return auxiliar;

    auxiliar = normav2(a, &n1);
    if(auxiliar != GEO_OK)return auxiliar;

    auxiliar = normav2(b, &n2);
    if(auxiliar != GEO_OK)return auxiliar;

    if(n1 < GEO_EPS || n2 < GEO_EPS){
        *outresult = 0.0;
        return GEO_ERR_DEGENERATE;
    }
    
    double cos  =(prodescalar/ (n1 * n2));
    if(cos > 1.0){cos = 1.0;}
    if(cos < -1.0){cos = -1.0;}
    double teta = acos(cos);
    if(teta < GEO_EPS){
        *outresult = 0.0;
    }else{
        *outresult = teta;
    }
    return GEO_OK;

}
geo_status normalizav2(vec2 a, vec2 *outresult){
    if (outresult == NULL) {
        return GEO_ERR_NULL;
    }
    double norma;
    geo_status st = normav2(a, &norma);
    if (st != GEO_OK) {
        return st;
    }
    if (norma < GEO_EPS) {
        outresult->x = 0.0;
        outresult->y = 0.0;
        return GEO_ERR_DEGENERATE;
    }
    outresult->x = a.x / norma;
    outresult->y = a.y / norma;
    return GEO_OK;
}
geo_status igauldadev2(vec2 a, vec2 b, int *outresult){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    if(a.x == b.x && a.y == b.y){
        *outresult = 1;
    }else{
        *outresult = 0;
    }

}
// Operações vec3
geo_status somavec3(vec3 a, vec3 b, vec3 *outresult){
     if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    outresult->x = a.x + b.x;
    outresult->y = a.y + b.y;
    outresult->z = a.z + b.z;
    return GEO_OK;
}
geo_status subtraivec3(vec3 a, vec3 b,vec3 *outresult){
     if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    outresult->x = a.x - b.x;
    outresult->y = a.y - b.y;
    outresult->z = a.z - b.z;
    return GEO_OK;
}
geo_status multescalarv3(vec3 a, double b,vec3 *outresult){
     if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    outresult->x = a.x * b;
    outresult->y = a.y * b;
    outresult->z = a.z * b;
    return GEO_OK;
}
geo_status produtoescalarv3(vec3 a, vec3 b, double *outresult){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    *outresult = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    return GEO_OK;
}
geo_status produtovetorialv3(vec3 a, vec3 b, vec3 *outresult){
    if (outresult == NULL) {
        return GEO_ERR_NULL;
    }
    outresult->x = (a.y * b.z) - (a.z * b.y);
    outresult->y = (a.z * b.x) - (a.x * b.z);
    outresult->z = (a.x * b.y) - (a.y * b.x);
    return GEO_OK;
} 
geo_status dependencialinearv3(vec3 a, vec3 b, int *eld){
    if (eld == NULL) {
        return GEO_ERR_NULL;
    }
    vec3 prodvet;
    produtovetorialv3(a, b, &prodvet);
    double norma_pv;
    normav3(prodvet, &norma_pv);
    if (norma_pv < GEO_EPS) {
        *eld = 1; 
    } else {
        *eld = 0; 
    }
    return GEO_OK;
    
    
}
geo_status normav3(vec3 a, double *outresult){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    double n = sqrt((a.x)*(a.x) + (a.y)*(a.y) + (a.z)*(a.z));
    if(n < GEO_EPS){
        *outresult = 0.0;
    }else{
        *outresult = n;
    }
    return GEO_OK;
}
geo_status angulovec3(vec3 a, vec3 b, double *outresult){
    if(outresult == NULL){
        return GEO_ERR_NULL;
    }
    double prodescalar;
    double n1;
    double n2;
    

    geo_status auxiliar;
    auxiliar = produtoescalarv3(a, b, &prodescalar);
    if(auxiliar != GEO_OK)return auxiliar;

    auxiliar = normav3(a, &n1);
    if(auxiliar != GEO_OK)return auxiliar;

    auxiliar = normav3(b, &n2);
    if(auxiliar != GEO_OK)return auxiliar;

    if(n1 < GEO_EPS || n2 < GEO_EPS){
        *outresult = 0.0;
        return GEO_ERR_DEGENERATE;
    }
    
    double cos = prodescalar/ (n1 * n2);
    if(cos > 1.0){cos = 1.0;}
    if(cos < -1.0){cos = -1.0;}
    double teta = acos(cos);
    if(teta < GEO_EPS){
        *outresult = 0.0;
    }else{
        *outresult = teta;
    }
    return GEO_OK;

}   
geo_status normalizav3(vec3 a,vec3 *outresult){
    if (outresult == NULL) {
        return GEO_ERR_NULL;
    }
    double norma;
    geo_status st = normav3(a, &norma);
    if (st != GEO_OK) {
        return st; 
    }
    if (norma < GEO_EPS) {
        outresult->x = 0.0;
        outresult->y = 0.0;
        outresult->z = 0.0;
        return GEO_ERR_DEGENERATE;
    }
    outresult->x = a.x / norma;
    outresult->y = a.y / norma;
    outresult->z = a.z / norma;

    return GEO_OK;
}
geo_status igauldadev3(vec3 a, vec3 b, int *igual){
    if(igual == NULL){
        return GEO_ERR_NULL;
    }
    if(a.x == b.x && a.y == b.y && a.z == b.z){
        *igual = 1;
    }else{
        *igual = 0;
    }
    return GEO_OK;


}

