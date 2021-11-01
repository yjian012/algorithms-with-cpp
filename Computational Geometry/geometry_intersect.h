#ifndef _GEOMETRY_INTERSECT_H
#define _GEOMETRY_INTERSECT_H

#include "geometry.h"

bool seg_intersect(segment a, segment b);
const segment* above(set<segment,decltype(cmp)> &T,segment s);
const segment* below(set<segment,decltype(cmp)> &T,segment s);
pair<segment,segment> intersect(vector<segment> &input);

#endif
