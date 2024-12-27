/**
 * Author: Adam Soltan
 * Description: Sorts points in ascending order by angle within the interval
 * $(-\pi, \pi]$. The point $(0, 0)$ has an angle of $0$. Equivalent to sorting
 * by atan2(y, x).
 */
#pragma once

#include "Point.h"

template<class P>
bool angleCmp(P a, P b) {
  auto half = [](P p){ return sgn(p.y) ?: -sgn(p.x); };
  int A = half(a), B = half(b);
  return A == B ? a.cross(b) > 0 : A < B;
}
