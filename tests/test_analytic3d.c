/**
 * @file test_analytic3d.c
 * @brief Testes automatizados do módulo de Geometria Analítica 3D.
 */

#include <stdio.h>
#include "geo_analytic3d.h"

static int total = 0;
static int falhas = 0;

/* Registra uma verificação e mostra a linha onde ela falhou. */
#define VERIFICA(cond)                                                   \
    do {                                                                 \
        total++;                                                         \
        if (!(cond)) {                                                   \
            falhas++;                                                    \
            printf("  [FALHA] linha %d: %s\n", __LINE__, #cond);         \
        }                                                                \
    } while (0)

int main(void) {
    geo_point3d o = {0, 0, 0}, ex = {1, 0, 0}, ey = {0, 1, 0}, ez = {0, 0, 1};
    geo_point3d p345 = {3, 4, 0}, p122 = {1, 2, 2};
    geo_point3d q5 = {0, 0, 5}, x2 = {2, 0, 0};
    geo_point3d z1 = {0, 0, 1}, y1z1 = {0, 1, 1}, d45 = {1, 1, 0};
    geo_point3d reta_y = {0, 5, 0}, pt_x2 = {2, 0, 0};
    geo_line3d eixo_x, eixo_y, eixo_z, reversa, diag, paralela_x, mesma_x, nula;
    geo_plane3d xy, xz, yz, xy_alto, xy_dobro, invalido;
    geo_lines_relation rel_retas;
    geo_planes_relation rel_planos;
    geo_line_plane_relation rel_rp;
    double d = -1.0, ang = -1.0;

    /* ---- geo_dist_points3d ---- */
    VERIFICA(geo_dist_points3d(o, p122, &d) == GEO_OK && geo_approx_equal(d, 3.0));
    VERIFICA(geo_dist_points3d(o, o, &d) == GEO_OK && geo_approx_equal(d, 0.0));
    VERIFICA(geo_dist_points3d(o, p345, &d) == GEO_OK && geo_approx_equal(d, 5.0));
    VERIFICA(geo_dist_points3d(o, p122, NULL) == GEO_ERR_NULL);

    /* ---- geo_line3d_from_points ---- */
    VERIFICA(geo_line3d_from_points(o, ex, &eixo_x) == GEO_OK);
    VERIFICA(geo_line3d_from_points(o, ey, &eixo_y) == GEO_OK);
    VERIFICA(geo_line3d_from_points(o, ez, &eixo_z) == GEO_OK);
    VERIFICA(geo_line3d_from_points(z1, y1z1, &reversa) == GEO_OK);
    VERIFICA(geo_line3d_from_points(o, d45, &diag) == GEO_OK);
    VERIFICA(geo_line3d_from_points(ez, (geo_point3d){1, 0, 1}, &paralela_x) == GEO_OK);
    VERIFICA(geo_line3d_from_points(x2, (geo_point3d){5, 0, 0}, &mesma_x) == GEO_OK);
    VERIFICA(geo_line3d_from_points(o, o, &nula) == GEO_ERR_DEGENERATE);
    VERIFICA(geo_line3d_from_points(o, ex, NULL) == GEO_ERR_NULL);
    nula.point = o;
    nula.dir = o;   // reta com vetor diretor nulo, so para testar os erros */

    /* ---- geo_plane3d_from_points ---- */
    VERIFICA(geo_plane3d_from_points(o, ex, ey, &xy) == GEO_OK);
    VERIFICA(geo_plane3d_from_points(o, ex, ez, &xz) == GEO_OK);
    VERIFICA(geo_plane3d_from_points(o, ey, ez, &yz) == GEO_OK);
    VERIFICA(geo_plane3d_from_points(z1, (geo_point3d){1, 0, 1}, (geo_point3d){0, 1, 1}, &xy_alto) == GEO_OK);
    VERIFICA(geo_plane3d_from_points(o, ex, x2, &invalido) == GEO_ERR_DEGENERATE);  // colineares 
    VERIFICA(geo_plane3d_from_points(o, ex, ey, NULL) == GEO_ERR_NULL);
    xy_dobro = xy;
    xy_dobro.a *= 2.0; xy_dobro.b *= 2.0; xy_dobro.c *= 2.0; xy_dobro.d *= 2.0;
    invalido.a = 0.0; invalido.b = 0.0; invalido.c = 0.0; invalido.d = 1.0;

    /* ---- geo_dist_point_plane ---- */
    VERIFICA(geo_dist_point_plane(&xy, q5, &d) == GEO_OK && geo_approx_equal(d, 5.0));
    VERIFICA(geo_dist_point_plane(&xy, (geo_point3d){0, 0, -5}, &d) == GEO_OK && geo_approx_equal(d, 5.0));
    VERIFICA(geo_dist_point_plane(&xy_dobro, q5, &d) == GEO_OK && geo_approx_equal(d, 5.0));
    VERIFICA(geo_dist_point_plane(&xy, ex, &d) == GEO_OK && geo_approx_equal(d, 0.0));
    VERIFICA(geo_dist_point_plane(NULL, q5, &d) == GEO_ERR_NULL);
    VERIFICA(geo_dist_point_plane(&xy, q5, NULL) == GEO_ERR_NULL);
    VERIFICA(geo_dist_point_plane(&invalido, q5, &d) == GEO_ERR_INVALID);

    /* ---- geo_dist_point_line3d ---- */
    VERIFICA(geo_dist_point_line3d(&eixo_x, reta_y, &d) == GEO_OK && geo_approx_equal(d, 5.0));
    VERIFICA(geo_dist_point_line3d(&eixo_x, pt_x2, &d) == GEO_OK && geo_approx_equal(d, 0.0));
    VERIFICA(geo_dist_point_line3d(NULL, reta_y, &d) == GEO_ERR_NULL);
    VERIFICA(geo_dist_point_line3d(&eixo_x, reta_y, NULL) == GEO_ERR_NULL);
    VERIFICA(geo_dist_point_line3d(&nula, reta_y, &d) == GEO_ERR_INVALID);

    /* ---- geo_angle_lines3d ---- */
    VERIFICA(geo_angle_lines3d(&eixo_x, &diag, &ang) == GEO_OK && geo_approx_equal(ang, GEO_PI / 4.0));
    VERIFICA(geo_angle_lines3d(&eixo_x, &eixo_y, &ang) == GEO_OK && geo_approx_equal(ang, GEO_PI / 2.0));
    VERIFICA(geo_angle_lines3d(&eixo_x, &eixo_x, &ang) == GEO_OK && geo_approx_equal(ang, 0.0));  // sem NaN 
    VERIFICA(geo_angle_lines3d(NULL, &eixo_x, &ang) == GEO_ERR_NULL);
    VERIFICA(geo_angle_lines3d(&eixo_x, &nula, &ang) == GEO_ERR_INVALID);

    /* ---- geo_angle_planes ---- */
    VERIFICA(geo_angle_planes(&xy, &xz, &ang) == GEO_OK && geo_approx_equal(ang, GEO_PI / 2.0));
    VERIFICA(geo_angle_planes(&xy, &xy_dobro, &ang) == GEO_OK && geo_approx_equal(ang, 0.0));
    VERIFICA(geo_angle_planes(&xy, NULL, &ang) == GEO_ERR_NULL);
    VERIFICA(geo_angle_planes(&xy, &invalido, &ang) == GEO_ERR_INVALID);

    /* ---- geo_lines3d_position ---- */
    VERIFICA(geo_lines3d_position(&eixo_x, &eixo_y, &rel_retas) == GEO_OK && rel_retas == GEO_LINES_CONCURRENT);
    VERIFICA(geo_lines3d_position(&eixo_x, &reversa, &rel_retas) == GEO_OK && rel_retas == GEO_LINES_SKEW);
    VERIFICA(geo_lines3d_position(&eixo_x, &paralela_x, &rel_retas) == GEO_OK && rel_retas == GEO_LINES_PARALLEL);
    VERIFICA(geo_lines3d_position(&eixo_x, &mesma_x, &rel_retas) == GEO_OK && rel_retas == GEO_LINES_COINCIDENT);
    VERIFICA(geo_lines3d_position(&eixo_x, NULL, &rel_retas) == GEO_ERR_NULL);
    VERIFICA(geo_lines3d_position(&eixo_x, &nula, &rel_retas) == GEO_ERR_INVALID);

    /* ---- geo_planes_position ---- */
    VERIFICA(geo_planes_position(&xy, &xz, &rel_planos) == GEO_OK && rel_planos == GEO_PLANES_SECANT);
    VERIFICA(geo_planes_position(&xy, &xy_alto, &rel_planos) == GEO_OK && rel_planos == GEO_PLANES_PARALLEL);
    VERIFICA(geo_planes_position(&xy, &xy_dobro, &rel_planos) == GEO_OK && rel_planos == GEO_PLANES_COINCIDENT);
    VERIFICA(geo_planes_position(NULL, &xy, &rel_planos) == GEO_ERR_NULL);
    VERIFICA(geo_planes_position(&xy, &invalido, &rel_planos) == GEO_ERR_INVALID);

    /* ---- geo_line_plane_position ---- */
    VERIFICA(geo_line_plane_position(&eixo_z, &xy, &rel_rp) == GEO_OK && rel_rp == GEO_LINE_CROSSES_PLANE);
    VERIFICA(geo_line_plane_position(&eixo_x, &xy, &rel_rp) == GEO_OK && rel_rp == GEO_LINE_IN_PLANE);
    VERIFICA(geo_line_plane_position(&paralela_x, &xy, &rel_rp) == GEO_OK && rel_rp == GEO_LINE_PARALLEL_PLANE);
    VERIFICA(geo_line_plane_position(&eixo_x, NULL, &rel_rp) == GEO_ERR_NULL);
    VERIFICA(geo_line_plane_position(&nula, &xy, &rel_rp) == GEO_ERR_INVALID);
    VERIFICA(geo_line_plane_position(&eixo_x, &invalido, &rel_rp) == GEO_ERR_INVALID);

    /* ---- resultado ---- */
    if (falhas == 0) {
        printf("[PASS] test_analytic3d: %d verificacoes, 10 funcoes testadas.\n", total);
        return 0;
    }
    printf("[FAIL] test_analytic3d: %d de %d verificacoes falharam.\n", falhas, total);
    return 1;
}
