#ifndef _GEOMETRY_INTERSECT_H
#define _GEOMETRY_INTERSECT_H

#include "geometry.h"

bool seg_intersect(const segment &a, const segment &b);
const segment* above(const set<segment,decltype(cmp)> &T,const segment &s);
const segment* below(const set<segment,decltype(cmp)> &T,const segment &s);
pair<segment,segment> intersect(vector<segment> &input);

#endif
