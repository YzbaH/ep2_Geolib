/**
 * @file main.c
 * @brief Aplicação cliente da Geolib: menu que demonstra os cinco módulos da biblioteca.
 *
 */

#include <stdio.h>
#include <math.h>

#include "geo_common.h"
#include "geo_plane.h"
#include "GeoAnalitica2D.h"
#include "vecoperations.h"
#include "geo_analytic3d.h"
#include "GeoEspacial.h"

/* ---------- Utilitários de entrada ---------- */

// Descarta o que sobrou na linha de entrada depois de uma leitura inválida
static void limpar_linha(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // só consome os caracteres 
    }
}

// Lê um número. Devolve 1 se leu corretamente e 0 caso contrário 
static int ler_double(const char *rotulo, double *v) {
    printf("%s: ", rotulo);
    if (scanf("%lf", v) != 1) {
        limpar_linha();
        printf("Entrada invalida.\n");
        return 0;
    }
    return 1;
}

// Lê dois números (ponto ou vetor 2D)
static int ler_xy(const char *rotulo, double *x, double *y) {
    printf("%s: ", rotulo);
    if (scanf("%lf %lf", x, y) != 2) {
        limpar_linha();
        printf("Entrada invalida.\n");
        return 0;
    }
    return 1;
}

// Lê três números (ponto, vetor ou coeficientes). 
static int ler_xyz(const char *rotulo, double *x, double *y, double *z) {
    printf("%s: ", rotulo);
    if (scanf("%lf %lf %lf", x, y, z) != 3) {
        limpar_linha();
        printf("Entrada invalida.\n");
        return 0;
    }
    return 1;
}

/* ------- Utilitários de saída -------- */

static double graus(double rad) {
    return rad * 180.0 / GEO_PI;
}

static const char *sim_nao(int v) {
    return v ? "sim" : "nao";
}

// Traduz um geo_status em texto para o usuário
static const char *texto_status(geo_status s) {
    switch (s) {
        case GEO_OK:             return "sucesso";
        case GEO_ERR_NULL:       return "ponteiro nulo";
        case GEO_ERR_INVALID:    return "valor invalido (ex.: raio ou aresta <= 0, reta vertical, vetor nulo)";
        case GEO_ERR_DEGENERATE: return "forma degenerada (ex.: pontos colineares ou vetor nulo)";
    }
    return "erro desconhecido";
}

// Se st != GEO_OK, avisa o usuário e devolve 1; caso contrário devolve 0
static int falhou(const char *operacao, geo_status st) {
    if (st == GEO_OK) return 0;
    printf("  [erro em %s] %s\n", operacao, texto_status(st));
    return 1;
}

static const char *texto_triangulo(geo_triangle_type t) {
    switch (t) {
        case GEO_TRIANGLE_EQUILATERAL: return "equilatero";
        case GEO_TRIANGLE_ISOSCELES:   return "isosceles";
        case GEO_TRIANGLE_SCALENE:     return "escaleno";
    }
    return "?";
}

static const char *texto_pos_circulo(geo_point_circle_pos p) {
    switch (p) {
        case GEO_POINT_INSIDE_CIRCLE:  return "dentro da circunferencia";
        case GEO_POINT_ON_CIRCLE:      return "sobre a circunferencia";
        case GEO_POINT_OUTSIDE_CIRCLE: return "fora da circunferencia";
    }
    return "?";
}

static const char *texto_retas2d(posicao_retas r) {
    switch (r) {
        case RETAS_CONCORRENTES: return "concorrentes";
        case RETAS_PARALELAS:    return "paralelas";
        case RETAS_COINCIDENTES: return "coincidentes";
    }
    return "?";
}

static const char *texto_retas3d(geo_lines_relation r) {
    switch (r) {
        case GEO_LINES_COINCIDENT: return "coincidentes";
        case GEO_LINES_PARALLEL:   return "paralelas";
        case GEO_LINES_CONCURRENT: return "concorrentes";
        case GEO_LINES_SKEW:       return "reversas";
    }
    return "?";
}

static const char *texto_planos(geo_planes_relation r) {
    switch (r) {
        case GEO_PLANES_COINCIDENT: return "coincidentes";
        case GEO_PLANES_PARALLEL:   return "paralelos";
        case GEO_PLANES_SECANT:     return "secantes";
    }
    return "?";
}

static const char *texto_reta_plano(geo_line_plane_relation r) {
    switch (r) {
        case GEO_LINE_IN_PLANE:       return "reta contida no plano";
        case GEO_LINE_PARALLEL_PLANE: return "reta paralela ao plano";
        case GEO_LINE_CROSSES_PLANE:  return "reta transversal ao plano";
    }
    return "?";
}

/* ---------- Módulo 1: Geometria Plana ---------- */

static void demo_plana(void) {
    geo_point2d a, b, c, centro, p;
    geo_triangle2d tri;
    geo_triangle_type tipo;
    geo_circle2d circ;
    geo_point_circle_pos pos;
    double valor = 0.0, raio = 0.0;
    int colinear = 0;

    printf("\n--- Geometria Plana ---\n");
    printf("Triangulo: informe os vertices A, B e C.\n");
    if (!ler_xy("Ponto A (x y)", &a.x, &a.y) ||
        !ler_xy("Ponto B (x y)", &b.x, &b.y) ||
        !ler_xy("Ponto C (x y)", &c.x, &c.y)) {
        return;
    }

    if (!falhou("distancia A-B", geo_dist_points(a, b, &valor)))
        printf("Distancia A-B ............. %.4f\n", valor);

    if (!falhou("colinearidade", geo_points_collinear(a, b, c, &colinear)))
        printf("A, B e C colineares? ...... %s\n", sim_nao(colinear));

    if (!falhou("triangulo ABC", geo_triangle_create(a, b, c, &tri))) {
        if (!falhou("area do triangulo", geo_triangle_area(&tri, &valor)))
            printf("Area do triangulo ......... %.4f\n", valor);
        if (!falhou("perimetro do triangulo", geo_triangle_perimeter(&tri, &valor)))
            printf("Perimetro do triangulo .... %.4f\n", valor);
        if (!falhou("classificacao", geo_triangle_classify(&tri, &tipo)))
            printf("Tipo do triangulo ......... %s\n", texto_triangulo(tipo));
    }

    printf("\nCircunferencia: informe o centro, o raio e um ponto P.\n");
    if (!ler_xy("Centro (x y)", &centro.x, &centro.y) ||
        !ler_double("Raio", &raio) ||
        !ler_xy("Ponto P (x y)", &p.x, &p.y)) {
        return;
    }

    if (falhou("circunferencia", geo_circle_create(centro, raio, &circ))) return;

    if (!falhou("area do circulo", geo_circle_area(&circ, &valor)))
        printf("Area do circulo ........... %.4f\n", valor);
    if (!falhou("perimetro do circulo", geo_circle_perimeter(&circ, &valor)))
        printf("Perimetro do circulo ...... %.4f\n", valor);
    if (!falhou("posicao de P", geo_circle_point_position(&circ, p, &pos)))
        printf("Posicao de P .............. %s\n", texto_pos_circulo(pos));
}

/* ---------- Módulo 2: Geometria Analítica 2D ---------- */

static void demo_analitica2d(void) {
    geo_ponto2d a, b, p, medio, encontro;
    geo_eqGeralReta r, s;
    posicao_retas pos;
    double valor = 0.0;

    printf("\n--- Geometria Analitica 2D ---\n");
    printf("Informe os pontos A e B.\n");
    if (!ler_xy("Ponto A (x y)", &a.x, &a.y) ||
        !ler_xy("Ponto B (x y)", &b.x, &b.y)) {
        return;
    }

    if (!falhou("distancia A-B", distPontoPonto(a, b, &valor)))
        printf("Distancia A-B ............. %.4f\n", valor);
    if (!falhou("ponto medio", pontoMedio(a, b, &medio)))
        printf("Ponto medio de AB ......... (%.4f, %.4f)\n", medio.x, medio.y);
    if (!falhou("coeficiente angular", calculaCoefAngular(a, b, &valor)))
        printf("Coeficiente angular de AB . %.4f\n", valor);

    printf("\nRetas na forma ax + by + c = 0 e um ponto P.\n");
    if (!ler_xyz("Reta r (a b c)", &r.coefX, &r.coefY, &r.c) ||
        !ler_xyz("Reta s (a b c)", &s.coefX, &s.coefY, &s.c) ||
        !ler_xy("Ponto P (x y)", &p.x, &p.y)) {
        return;
    }

    if (!falhou("distancia P-r", distPontoReta(&r, p, &valor)))
        printf("Distancia de P a r ........ %.4f\n", valor);

    /* NULL no ultimo parametro: so classifica, sem calcular a intersecao */
    if (!falhou("posicao de r e s", posicaoRelativaRetas(&r, &s, &pos, NULL))) {
        printf("Posicao de r e s .......... %s\n", texto_retas2d(pos));
        if (pos == RETAS_CONCORRENTES && !falhou("ponto de encontro", pontoEncontro(&r, &s, &encontro)))
            printf("Ponto de encontro ......... (%.4f, %.4f)\n", encontro.x, encontro.y);
    }
}

/* ---------- Módulo 3: Vetores ---------- */

static void demo_vec2(void) {
    vec2 u, v, res;
    double k = 0.0, valor = 0.0;
    int flag = 0;

    printf("\n--- Vetores 2D ---\n");
    if (!ler_xy("Vetor u (x y)", &u.x, &u.y) ||
        !ler_xy("Vetor v (x y)", &v.x, &v.y) ||
        !ler_double("Escalar k", &k)) {
        return;
    }

    if (!falhou("u + v", somavec2(u, v, &res)))
        printf("u + v ..................... (%.4f, %.4f)\n", res.x, res.y);
    if (!falhou("u - v", subtraivec2(u, v, &res)))
        printf("u - v ..................... (%.4f, %.4f)\n", res.x, res.y);
    if (!falhou("k * u", multescalarv2(u, k, &res)))
        printf("k * u ..................... (%.4f, %.4f)\n", res.x, res.y);
    if (!falhou("produto escalar", produtoescalarv2(u, v, &valor)))
        printf("Produto escalar u . v ..... %.4f\n", valor);
    if (!falhou("norma de u", normav2(u, &valor)))
        printf("Norma de u ................ %.4f\n", valor);
    if (!falhou("normalizacao de u", normalizav2(u, &res)))
        printf("u normalizado ............. (%.4f, %.4f)\n", res.x, res.y);
    if (!falhou("angulo entre u e v", angulovec2(u, v, &valor)))
        printf("Angulo entre u e v ........ %.4f rad (%.2f graus)\n", valor, graus(valor));
    if (!falhou("dependencia linear", dependencialinearv2(u, v, &flag)))
        printf("u e v sao ................. %s\n",
               flag ? "linearmente dependentes (LD)" : "linearmente independentes (LI)");
    if (!falhou("igualdade", igualdadev2(u, v, &flag)))
        printf("u e v sao iguais? ......... %s\n", sim_nao(flag));
}

static void demo_vec3(void) {
    vec3 u, v, res;
    double k = 0.0, valor = 0.0;
    int flag = 0;

    printf("\n--- Vetores 3D ---\n");
    if (!ler_xyz("Vetor u (x y z)", &u.x, &u.y, &u.z) ||
        !ler_xyz("Vetor v (x y z)", &v.x, &v.y, &v.z) ||
        !ler_double("Escalar k", &k)) {
        return;
    }

    if (!falhou("u + v", somavec3(u, v, &res)))
        printf("u + v ..................... (%.4f, %.4f, %.4f)\n", res.x, res.y, res.z);
    if (!falhou("u - v", subtraivec3(u, v, &res)))
        printf("u - v ..................... (%.4f, %.4f, %.4f)\n", res.x, res.y, res.z);
    if (!falhou("k * u", multescalarv3(u, k, &res)))
        printf("k * u ..................... (%.4f, %.4f, %.4f)\n", res.x, res.y, res.z);
    if (!falhou("produto escalar", produtoescalarv3(u, v, &valor)))
        printf("Produto escalar u . v ..... %.4f\n", valor);
    if (!falhou("produto vetorial", produtovetorialv3(u, v, &res)))
        printf("Produto vetorial u x v .... (%.4f, %.4f, %.4f)\n", res.x, res.y, res.z);
    if (!falhou("norma de u", normav3(u, &valor)))
        printf("Norma de u ................ %.4f\n", valor);
    if (!falhou("normalizacao de u", normalizav3(u, &res)))
        printf("u normalizado ............. (%.4f, %.4f, %.4f)\n", res.x, res.y, res.z);
    if (!falhou("angulo entre u e v", angulovec3(u, v, &valor)))
        printf("Angulo entre u e v ........ %.4f rad (%.2f graus)\n", valor, graus(valor));
    if (!falhou("dependencia linear", dependencialinearv3(u, v, &flag)))
        printf("u e v sao ................. %s\n",
               flag ? "linearmente dependentes (LD)" : "linearmente independentes (LI)");
    if (!falhou("igualdade", igualdadev3(u, v, &flag)))
        printf("u e v sao iguais? ......... %s\n", sim_nao(flag));
}

/* ---------- Módulo 4: Geometria Analítica 3D ---------- */

static void demo_3d(void) {
    geo_point3d a, b, c, p;
    geo_line3d r, s;
    geo_plane3d pl1, pl2;
    geo_lines_relation rel_retas;
    geo_planes_relation rel_planos;
    geo_line_plane_relation rel_rp;
    double d = 0.0, ang = 0.0;

    printf("\n--- Geometria Analitica 3D ---\n");
    printf("Informe quatro pontos: A, B, C e P.\n");
    if (!ler_xyz("Ponto A (x y z)", &a.x, &a.y, &a.z) ||
        !ler_xyz("Ponto B (x y z)", &b.x, &b.y, &b.z) ||
        !ler_xyz("Ponto C (x y z)", &c.x, &c.y, &c.z) ||
        !ler_xyz("Ponto P (x y z)", &p.x, &p.y, &p.z)) {
        return;
    }

    // Constroi as figuras: reta AB, reta PC, plano ABC e plano ABP 
    if (falhou("reta AB", geo_line3d_from_points(a, b, &r))) return;
    if (falhou("reta PC", geo_line3d_from_points(p, c, &s))) return;
    if (falhou("plano ABC", geo_plane3d_from_points(a, b, c, &pl1))) return;
    if (falhou("plano ABP", geo_plane3d_from_points(a, b, p, &pl2))) return;

    printf("\nFiguras: reta r = AB, reta s = PC, plano 1 = ABC, plano 2 = ABP\n\n");

    if (!falhou("distancia A-B", geo_dist_points3d(a, b, &d)))
        printf("Distancia A-B ............. %.4f\n", d);
    if (!falhou("distancia P-r", geo_dist_point_line3d(&r, p, &d)))
        printf("Distancia de P a r ........ %.4f\n", d);
    if (!falhou("distancia P-plano 1", geo_dist_point_plane(&pl1, p, &d)))
        printf("Distancia de P ao plano 1 . %.4f\n", d);
    if (!falhou("angulo r-s", geo_angle_lines3d(&r, &s, &ang)))
        printf("Angulo entre r e s ........ %.4f rad (%.2f graus)\n", ang, graus(ang));
    if (!falhou("posicao r-s", geo_lines3d_position(&r, &s, &rel_retas)))
        printf("Posicao de r e s .......... %s\n", texto_retas3d(rel_retas));
    if (!falhou("angulo entre planos", geo_angle_planes(&pl1, &pl2, &ang)))
        printf("Angulo entre os planos .... %.4f rad (%.2f graus)\n", ang, graus(ang));
    if (!falhou("posicao dos planos", geo_planes_position(&pl1, &pl2, &rel_planos)))
        printf("Posicao dos planos ........ %s\n", texto_planos(rel_planos));
    if (!falhou("posicao s-plano 1", geo_line_plane_position(&s, &pl1, &rel_rp)))
        printf("Reta s e plano 1 .......... %s\n", texto_reta_plano(rel_rp));
}

/* ---------- Módulo 5: Geometria Espacial ---------- */

static void mostrar_solido(geo_status st_area, double area, geo_status st_vol, double volume) {
    if (!falhou("area", st_area))
        printf("Area total ................ %.4f\n", area);
    if (!falhou("volume", st_vol))
        printf("Volume .................... %.4f\n", volume);
}

static void demo_espacial(void) {
    int solido = -1;
    double area = 0.0, volume = 0.0;
    geo_status sa = GEO_OK, sv = GEO_OK;

    printf("\n--- Geometria Espacial ---\n");
    printf("1) Cubo\n2) Paralelepipedo\n3) Esfera\n4) Cilindro\n5) Cone\n6) Tetraedro regular\n");
    printf("Solido: ");
    if (scanf("%d", &solido) != 1) {
        limpar_linha();
        printf("Entrada invalida.\n");
        return;
    }

    switch (solido) {
        case 1: {
            geo_cubo cubo;
            if (!ler_double("Aresta", &cubo.aresta)) return;
            sa = areaCubo(&cubo, &area);
            sv = volumeCubo(&cubo, &volume);
            mostrar_solido(sa, area, sv, volume);
            break;
        }
        case 2: {
            geo_paralelepipedo par;
            if (!ler_double("Comprimento", &par.comprimento) ||
                !ler_double("Largura", &par.largura) ||
                !ler_double("Altura", &par.altura)) return;
            sa = areaParalelepipedo(&par, &area);
            sv = volumeParalelepipedo(&par, &volume);
            mostrar_solido(sa, area, sv, volume);
            break;
        }
        case 3: {
            geo_esfera esf;
            if (!ler_double("Raio", &esf.raio)) return;
            sa = areaEsfera(&esf, &area);
            sv = volumeEsfera(&esf, &volume);
            mostrar_solido(sa, area, sv, volume);
            break;
        }
        case 4: {
            geo_cilindro cil;
            if (!ler_double("Raio", &cil.raio) || !ler_double("Altura", &cil.altura)) return;
            sa = areaCilindro(&cil, &area);
            sv = volumeCilindro(&cil, &volume);
            mostrar_solido(sa, area, sv, volume);
            break;
        }
        case 5: {
            geo_cone cone;
            if (!ler_double("Raio", &cone.raio) || !ler_double("Altura", &cone.altura)) return;
            // a geratriz do cone vem do teorema de Pitagoras: g^2 = r^2 + h^2 
            cone.geratriz = sqrt(cone.raio * cone.raio + cone.altura * cone.altura);
            sa = areaCone(&cone, &area);
            sv = volumeCone(&cone, &volume);
            mostrar_solido(sa, area, sv, volume);
            break;
        }
        case 6: {
            geo_tetraedro tet;
            if (!ler_double("Aresta", &tet.aresta)) return;
            sa = areaTetraedro(&tet, &area);
            sv = volumeTetraedro(&tet, &volume);
            mostrar_solido(sa, area, sv, volume);
            break;
        }
        default:
            printf("Solido invalido.\n");
    }
}

/* ---------- Menu principal ---------- */

static void mostrar_menu(void) {
    printf("\n=== Geolib ===\n");
    printf("1) Geometria Plana\n");
    printf("2) Geometria Analitica 2D\n");
    printf("3) Vetores 2D\n");
    printf("4) Vetores 3D\n");
    printf("5) Geometria Analitica 3D\n");
    printf("6) Geometria Espacial\n");
    printf("0) Sair\n");
    printf("Opcao: ");
}

int main(void) {
    int opcao = -1;

    do {
        mostrar_menu();
        if (scanf("%d", &opcao) != 1) {
            if (feof(stdin)) break;     // fim da entrada: encerra 
            limpar_linha();
            opcao = -1;
        }

        switch (opcao) {
            case 1: demo_plana();       break;
            case 2: demo_analitica2d(); break;
            case 3: demo_vec2();        break;
            case 4: demo_vec3();        break;
            case 5: demo_3d();          break;
            case 6: demo_espacial();    break;
            case 0: printf("Ate logo!\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
