#include "geo_common.h"

int geo_approx_equal(double a, double b) {
    return fabs(a - b) < GEO_EPS;
}
