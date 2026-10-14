/**
* @file GeoEspacial.h 
* @brief Módulo: Geometria Espacial: Áreas e volumes.
*/ 

#ifndef GEOESPACIAL_H
#define GEOESPACIAL_H


/**
* @brief Calcula a área de um cubo.
* @param aresta comprimento da aresta.
* @return Área do cubo em uma unidade arbitrária.
* @pre aresta > 0
*/ 
double areaCubo(double aresta);

/**
* @brief Calcula a área de um paralelepipedo reto retângulo.
* @param comprimento Medida do comprimento do sólido
* @param largura Medida da largura do sólido.
* @param altura Medida da altura do sólido. 
* @return Área do paralelepipedo.
* @pre comprimento > 0.
* @pre largura > 0.
* @pre altura > 0.
*/ 
double areaParalelepipedo(double comprimento, double largura, double altura);


/**
* @brief Calcula área de uma esfera.
* @param raio Raio da esfera.  
* @return Área da Esfera.
* @pre raio > 0.
* @note A função usa 3.14 como valor de π(pi).
*/ 
double areaEsfera(double raio);

/**
* @brief Calcula área de um cilindro.
* @param r Raio do cilindro.
* @param h Altura do cilindro
* @return Área do Cilindro.
* @pre r > 0.
* @pre h > 0
* @note A função usa 3.14 como valor de π(pi).
*/ 
double areaCilindro(double r, double h);

/**
* @brief Calcula área de um cone.
* @param r Raio do cone.
* @param g Medida da geratriz do cone.  
* @return Área do Cone.
* @pre r > 0.
* @pre g > 0.
* @note A função usa 3.14 como valor de π(pi).
*/ 
double areaCone(double r, double g);

/**
* @brief Calcula área de um Tetraedro regular.
* @param a Medida da arestra.  
* @return Área do tetraedro regular.
* @pre a > 0.
* @note A função usa 1,73 como valor de raiz de 3.
*/ 
double areaTetraedro(double a);

/**
* @brief Calcula área de um tronco de cone.
* @param rMaior Medida do raio da base maior.
* @param rMenor Medida do raio da base menor.
* @param g Medida da geratriz do tronco de cone.  
* @return Área do tronco de cone.
* @pre rMaior >= rMenor > 0.
* @pre g > 0.
* @note A função usa 1,73 como valor de raiz de 3.
*/ 
double areaTroncoCone(double rMaior, double rMenor, double g);
#endif /* GEOESPACIAL_H */