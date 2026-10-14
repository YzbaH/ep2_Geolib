#include "geo_plane.h"

geo_status geo_points_collinear(geo_point2d a, geo_point2d b, geo_point2d c, int *out_collinear) {
    if(out_collinear == NULL) return GEO_ERR_NULL;

    double det = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);

    if(fabs(det) < GEO_EPS) *out_collinear = 1;
    else *out_collinear = 0;

    return GEO_OK;
}

geo_status geo_triangle_create(geo_point2d a, geo_point2d b, geo_point2d c, geo_triangle2d *out_triangle) {
    if(out_triangle == NULL) return GEO_ERR_NULL;
    
    int colinear = 0;
    geo_points_collinear(a,b,c, &colinear);
    if(colinear == 1) return GEO_ERR_DEGENERATE;
    
    out_triangle->a = a;
    out_triangle->b = b;
    out_triangle->c = c;
    return GEO_OK;
}

geo_status geo_triangle_area(const geo_triangle2d *t, double *out_area) {
    if(t == NULL || out_area == NULL) return GEO_ERR_NULL;
    
    double det = (t->b.x - t->a.x) * (t->c.y - t->a.y) - (t->b.y - t->a.y) * (t->c.x - t->a.x);
    *out_area = 0.5 * fabs(det);
    return GEO_OK;
}

static double dist_points(geo_point2d a, geo_point2d b) {
    return hypot(a.x - b.x, a.y - b.y);
}

geo_status geo_dist_points(geo_point2d a, geo_point2d b, double *out_dist){
      if(out_dist == NULL) return GEO_ERR_NULL;
      *out_dist = dist_points(a, b);
      return GEO_OK;
}

geo_status geo_triangle_perimeter(const geo_triangle2d *t, double *out_perimeter) {
    if(t == NULL || out_perimeter == NULL) return GEO_ERR_NULL;
    *out_perimeter = dist_points(t->a, t->b) + dist_points(t->b, t->c) + dist_points(t->c, t->a);
    return GEO_OK;
}

geo_status geo_triangle_classify(const geo_triangle2d *t, geo_triangle_type *out_type) {
    if (t == NULL || out_type == NULL) {
        return GEO_ERR_NULL;
    }

    double ab = dist_points(t->a, t->b);
    double bc = dist_points(t->b, t->c);
    double ca = dist_points(t->c, t->a);

    double ab_eq_bc = (fabs(ab - bc) < GEO_EPS);
    double bc_eq_ca = (fabs(bc - ca) < GEO_EPS);
    double ca_eq_ab = (fabs(ca - ab) < GEO_EPS);

    if (ab_eq_bc && bc_eq_ca) *out_type = GEO_TRIANGLE_EQUILATERAL;
    else if (ab_eq_bc || bc_eq_ca || ca_eq_ab) *out_type = GEO_TRIANGLE_ISOSCELES;
    else *out_type = GEO_TRIANGLE_SCALENE;

    return GEO_OK;
}

geo_status geo_circle_create(geo_point2d center, double radius, geo_circle2d *out_circle) {
    if (out_circle == NULL) return GEO_ERR_NULL;

    if (radius <= 0.0) return GEO_ERR_INVALID;

    out_circle->center = center;
    out_circle->radius = radius;

    return GEO_OK;
}

geo_status geo_circle_area(const geo_circle2d *c, double *out_area) {
    if (c == NULL || out_area == NULL) return GEO_ERR_NULL;

    *out_area = GEO_PI * c->radius * c->radius;

    return GEO_OK;
}

geo_status geo_circle_perimeter(const geo_circle2d *c, double *out_perimeter) {
    if (c == NULL || out_perimeter == NULL) return GEO_ERR_NULL;

    *out_perimeter = 2.0 * GEO_PI * c->radius;
    return GEO_OK;
}

geo_status geo_circle_point_position(const geo_circle2d *c, geo_point2d p, geo_point_circle_pos *out_pos) {
    if(c == NULL || out_pos == NULL) return GEO_ERR_NULL;
    double d = dist_points(c->center, p);

    if (fabs(d - c->radius) < GEO_EPS) *out_pos = GEO_POINT_ON_CIRCLE;
    else if (d < c->radius) *out_pos = GEO_POINT_INSIDE_CIRCLE;
    else *out_pos = GEO_POINT_OUTSIDE_CIRCLE;
    
    return GEO_OK;
}
