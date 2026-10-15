#include "geo_plane.h"
#include <stdio.h>

int main(void) {
    geo_point2d p1 = {0, 0}, p2 = {1, 1}, p3 = {2, 2}, p4 = {0, 3}, p5 = {4, 0};
    geo_point2d c_pt = {0, 0}, inside = {1, 1}, on = {2, 0}, out_pt = {3, 3};
    geo_triangle2d t;
    geo_circle2d c;
    geo_triangle_type type;
    geo_point_circle_pos pos;
    int col = 0;
    double area = 0, perim = 0, d = 0;

    /* colinearidade */
    if (geo_points_collinear(p1, p2, p3, &col) != GEO_OK || col != 1) return 1;
    if (geo_points_collinear(p1, p2, p4, &col) != GEO_OK || col != 0) return 1;
    if (geo_points_collinear(p1, p2, p3, NULL) != GEO_ERR_NULL) return 1;

    /* criacao e degeneracao de triangulo */
    if (geo_triangle_create(p1, p2, p3, &t) != GEO_ERR_DEGENERATE) return 1;
    if (geo_triangle_create(p1, p4, p5, &t) != GEO_OK) return 1;
    if (geo_triangle_create(p1, p4, p5, NULL) != GEO_ERR_NULL) return 1;

    /* area, perimetro e classificacao (triangulo 3-4-5) */
    if (geo_triangle_area(&t, &area) != GEO_OK || !geo_approx_equal(area, 6.0)) return 1;
    if (geo_triangle_perimeter(&t, &perim) != GEO_OK || !geo_approx_equal(perim, 12.0)) return 1;
    if (geo_triangle_classify(&t, &type) != GEO_OK || type != GEO_TRIANGLE_SCALENE) return 1;

    /* triangulo nulo */
    if (geo_triangle_area(NULL, &area) != GEO_ERR_NULL) return 1;
    if (geo_triangle_perimeter(NULL, &perim) != GEO_ERR_NULL) return 1;
    if (geo_triangle_classify(NULL, &type) != GEO_ERR_NULL) return 1;

    /* distancia entre pontos */
    if (geo_dist_points(c_pt, on, &d) != GEO_OK || !geo_approx_equal(d, 2.0)) return 1;
    if (geo_dist_points(c_pt, on, NULL) != GEO_ERR_NULL) return 1;

    /* criacao de circulo e validacao */
    if (geo_circle_create(c_pt, -1.0, &c) != GEO_ERR_INVALID) return 1;
    if (geo_circle_create(c_pt, 0.0, &c) != GEO_ERR_INVALID) return 1;
    if (geo_circle_create(c_pt, 2.0, &c) != GEO_OK) return 1;
    if (geo_circle_create(c_pt, 2.0, NULL) != GEO_ERR_NULL) return 1;

    /* area e perimetro de circulo */
    if (geo_circle_area(&c, &area) != GEO_OK || !geo_approx_equal(area, GEO_PI * 4.0)) return 1;
    if (geo_circle_perimeter(&c, &perim) != GEO_OK || !geo_approx_equal(perim, 2.0 * GEO_PI * 2.0)) return 1;

    /* posicao relativa de ponto ao circulo */
    if (geo_circle_point_position(&c, inside, &pos) != GEO_OK || pos != GEO_POINT_INSIDE_CIRCLE) return 1;
    if (geo_circle_point_position(&c, on, &pos) != GEO_OK || pos != GEO_POINT_ON_CIRCLE) return 1;
    if (geo_circle_point_position(&c, out_pt, &pos) != GEO_OK || pos != GEO_POINT_OUTSIDE_CIRCLE) return 1;
    if (geo_circle_point_position(NULL, on, &pos) != GEO_ERR_NULL) return 1;

    printf("[PASS] test_plane: 10 funcoes testadas com sucesso.\n");
    return 0;
}
