#include "modulo1.h"

geo_status geo_points_collinear(geo_point2d a, geo_point2d b, geo_point2d c, int *out_collinear) {
    return GEO_ERR_INVALID;
}

geo_status geo_triangle_create(geo_point2d a, geo_point2d b, geo_point2d c, geo_triangle2d *out_triangle) {
    return GEO_ERR_INVALID;
}

geo_status geo_triangle_area(const geo_triangle2d *t, double *out_area) {
    return GEO_ERR_INVALID;
}

geo_status geo_triangle_perimeter(const geo_triangle2d *t, double *out_perimeter) {
    return GEO_ERR_INVALID;
}

geo_status geo_triangle_classify(const geo_triangle2d *t, geo_triangle_type *out_type) {
    return GEO_ERR_INVALID;
}

geo_status geo_circle_create(geo_point2d center, double radius, geo_circle2d *out_circle) {
    return GEO_ERR_INVALID;
}

geo_status geo_circle_area(const geo_circle2d *c, double *out_area) {
    return GEO_ERR_INVALID;
}

geo_status geo_circle_perimeter(const geo_circle2d *c, double *out_perimeter) {
    return GEO_ERR_INVALID;
}

geo_status geo_circle_point_position(const geo_circle2d *c, geo_point2d p, geo_point_circle_pos *out_pos) {
    return GEO_ERR_INVALID;
}
