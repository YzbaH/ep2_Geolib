#include "geo_analytic3d.h"
#include <math.h>

/* ---------- Funções auxiliares internas ---------- */

// Subtração de vetores: a - b 
static geo_point3d vec_sub(geo_point3d a, geo_point3d b) {
    geo_point3d r = { a.x - b.x, a.y - b.y, a.z - b.z };
    return r;
}

// Produto escalar 
static double vec_dot(geo_point3d a, geo_point3d b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Produto vetorial 
static geo_point3d vec_cross(geo_point3d a, geo_point3d b) {
    geo_point3d r = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return r;
}

// Norma (comprimento) do vetor 
static double vec_norm(geo_point3d a) {
    return sqrt(vec_dot(a, a));
}

// 1 se o vetor é (aproximadamente) nulo 
static int vec_is_zero(geo_point3d v) {
    return vec_norm(v) < GEO_EPS;
}

// 1 se |value| é desprezível em relação a scale (tolerância relativa) 
static int is_zero_rel(double value, double scale) {
    return fabs(value) <= GEO_EPS * scale;
}

// Ângulo agudo entre duas direções não nulas, em [0, pi/2] 
static double acute_angle(geo_point3d u, geo_point3d v) {
    double c = fabs(vec_dot(u, v)) / (vec_norm(u) * vec_norm(v));
    if (c > 1.0) c = 1.0;   // evita NaN no acos por erro de arredondamento 
    return acos(c);
}

/* ---------------------------- API pública ---------------------------- */

geo_status geo_dist_points3d(geo_point3d a, geo_point3d b, double *out_dist) {
    if (out_dist == NULL) return GEO_ERR_NULL;
    *out_dist = vec_norm(vec_sub(b, a));
    return GEO_OK;
}

geo_status geo_line3d_from_points(geo_point3d a, geo_point3d b, geo_line3d *out_line) {
    if (out_line == NULL) return GEO_ERR_NULL;

    geo_point3d dir = vec_sub(b, a);
    if (vec_is_zero(dir)) return GEO_ERR_DEGENERATE;

    out_line->point = a;
    out_line->dir = dir;
    return GEO_OK;
}

geo_status geo_plane3d_from_points(geo_point3d a, geo_point3d b, geo_point3d c, geo_plane3d *out_plane) {
    if (out_plane == NULL) return GEO_ERR_NULL;

    geo_point3d n = vec_cross(vec_sub(b, a), vec_sub(c, a));
    if (vec_is_zero(n)) return GEO_ERR_DEGENERATE;   // pontos colineares 

    out_plane->a = n.x;
    out_plane->b = n.y;
    out_plane->c = n.z;
    out_plane->d = -vec_dot(n, a);
    return GEO_OK;
}

geo_status geo_dist_point_plane(const geo_plane3d *pl, geo_point3d pt, double *out_dist) {
    if (pl == NULL || out_dist == NULL) return GEO_ERR_NULL;

    geo_point3d n = { pl->a, pl->b, pl->c };
    double norm = vec_norm(n);
    if (norm < GEO_EPS) return GEO_ERR_INVALID;

    *out_dist = fabs(vec_dot(n, pt) + pl->d) / norm;
    return GEO_OK;
}

geo_status geo_dist_point_line3d(const geo_line3d *r, geo_point3d pt, double *out_dist) {
    if (r == NULL || out_dist == NULL) return GEO_ERR_NULL;
    if (vec_is_zero(r->dir)) return GEO_ERR_INVALID;

    geo_point3d ap = vec_sub(pt, r->point);
    *out_dist = vec_norm(vec_cross(ap, r->dir)) / vec_norm(r->dir);
    return GEO_OK;
}

geo_status geo_angle_lines3d(const geo_line3d *r, const geo_line3d *s, double *out_angle) {
    if (r == NULL || s == NULL || out_angle == NULL) return GEO_ERR_NULL;
    if (vec_is_zero(r->dir) || vec_is_zero(s->dir)) return GEO_ERR_INVALID;

    *out_angle = acute_angle(r->dir, s->dir);
    return GEO_OK;
}

geo_status geo_angle_planes(const geo_plane3d *pl1, const geo_plane3d *pl2, double *out_angle) {
    if (pl1 == NULL || pl2 == NULL || out_angle == NULL) return GEO_ERR_NULL;

    geo_point3d n1 = { pl1->a, pl1->b, pl1->c };
    geo_point3d n2 = { pl2->a, pl2->b, pl2->c };
    if (vec_is_zero(n1) || vec_is_zero(n2)) return GEO_ERR_INVALID;

    *out_angle = acute_angle(n1, n2);
    return GEO_OK;
}

geo_status geo_lines3d_position(const geo_line3d *r, const geo_line3d *s, geo_lines_relation *out_pos) {
    if (r == NULL || s == NULL || out_pos == NULL) return GEO_ERR_NULL;
    if (vec_is_zero(r->dir) || vec_is_zero(s->dir)) return GEO_ERR_INVALID;

    geo_point3d u = r->dir;
    geo_point3d v = s->dir;
    geo_point3d diff = vec_sub(s->point, r->point);  
    geo_point3d cross = vec_cross(u, v);

    int parallel = is_zero_rel(vec_norm(cross), vec_norm(u) * vec_norm(v));

    if (parallel) {
        // paralelas: coincidem se o ponto de s também está sobre r 
        geo_point3d w = vec_cross(diff, u);
        if (is_zero_rel(vec_norm(w), vec_norm(diff) * vec_norm(u)))
            *out_pos = GEO_LINES_COINCIDENT;
        else
            *out_pos = GEO_LINES_PARALLEL;
    } else {
        // não paralelas: concorrentes se estão no mesmo plano, reversas se não 
        double triple = vec_dot(diff, cross);
        if (is_zero_rel(triple, vec_norm(diff) * vec_norm(cross)))
            *out_pos = GEO_LINES_CONCURRENT;
        else
            *out_pos = GEO_LINES_SKEW;
    }
    return GEO_OK;
}

geo_status geo_planes_position(const geo_plane3d *pl1, const geo_plane3d *pl2, geo_planes_relation *out_pos) {
    if (pl1 == NULL || pl2 == NULL || out_pos == NULL) return GEO_ERR_NULL;

    geo_point3d n1 = { pl1->a, pl1->b, pl1->c };
    geo_point3d n2 = { pl2->a, pl2->b, pl2->c };
    if (vec_is_zero(n1) || vec_is_zero(n2)) return GEO_ERR_INVALID;

    int parallel = is_zero_rel(vec_norm(vec_cross(n1, n2)), vec_norm(n1) * vec_norm(n2));

    if (!parallel) {
        *out_pos = GEO_PLANES_SECANT;
        return GEO_OK;
    }

    // normais paralelas: o mesmo plano se (d2 * n1 - d1 * n2) for nulo 
    geo_point3d w = {
        pl2->d * n1.x - pl1->d * n2.x,
        pl2->d * n1.y - pl1->d * n2.y,
        pl2->d * n1.z - pl1->d * n2.z
    };
    double scale = fabs(pl2->d) * vec_norm(n1) + fabs(pl1->d) * vec_norm(n2);

    if (is_zero_rel(vec_norm(w), scale))
        *out_pos = GEO_PLANES_COINCIDENT;
    else
        *out_pos = GEO_PLANES_PARALLEL;
    return GEO_OK;
}

geo_status geo_line_plane_position(const geo_line3d *r, const geo_plane3d *pl, geo_line_plane_relation *out_pos) {
    if (r == NULL || pl == NULL || out_pos == NULL) return GEO_ERR_NULL;

    geo_point3d n = { pl->a, pl->b, pl->c };
    if (vec_is_zero(n) || vec_is_zero(r->dir)) return GEO_ERR_INVALID;

    double n_dot_u = vec_dot(n, r->dir);

    if (!is_zero_rel(n_dot_u, vec_norm(n) * vec_norm(r->dir))) {
        *out_pos = GEO_LINE_CROSSES_PLANE;
        return GEO_OK;
    }

    // reta paralela ao plano: está contida se um ponto dela satisfaz a equação 
    double val = vec_dot(n, r->point) + pl->d;
    double scale = vec_norm(n) * vec_norm(r->point) + fabs(pl->d);

    if (is_zero_rel(val, scale))
        *out_pos = GEO_LINE_IN_PLANE;
    else
        *out_pos = GEO_LINE_PARALLEL_PLANE;
    return GEO_OK;
}
