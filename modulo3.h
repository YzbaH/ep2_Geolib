//modulo3.h
#ifndef MODULO3_H
#define MODULO3_H
#define GEO_EPS 1e-9

typedef struct {
    double x;
    double y;
}vec2;
typedef struct {
    double x;
    double y;
    double z;
}vec3;

//OPERAÇÕES VEC2

vec2 somavec2(vec2 a, vec2 b);
vec2 subtraivec2(vec2 a, vec2 b);
vec2 multescalarv2(vec2 a, double b);
double produtoescalarv2(vec2 a, vec2 b);
int dependencialinearv2(vec2 a, vec2 b);
double normav2(vec2 a);
double angulovec2(vec2 a, vec2 b);
vec2 normalizav2(vec2 a);
int igauldadev2(vec2 a, vec2 b);

//OPERAÇÕES VEC3

vec3 somavec3(vec3 a, vec3 b);
vec3 subtraivec3(vec3 a, vec3 b);
vec3 multescalarv3(vec3 a, double b);
double produtoescalarv3(vec3 a, vec3 b);
vec3 produtovetorialv3(vec3 a, vec3 b); 
int dependencialinearv3(vec3 a, vec3 b);
double normav3(vec3 a);
double angulovec3(vec3 a, vec3 b);   
vec3 normalizav3(vec3 a);
int igauldadev3(vec3 a, vec3 b);


#endif //MODULO3_H
