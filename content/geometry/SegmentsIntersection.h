/**
 * Author: kobor
 * Date: 2024-07-12
 * License: CC0
 * Description: Finds one of segments intersections.
 *	You should change dirSeg's comparator, to compare segments at their left end.
 * Time: $O(N \log N)$
 * Status: tested on Timus:1469
 */
#pragma once

#include "SegmentIntersection.h"
#include "directedSegment.h"

template<class P>
pii segmentsIntersect(vector<pair<P, P>> segments) {
	vector<tuple<P, int, int>> eve; // {point, event_type, id}
	vector<dirSeg<P>> segs;
	for(auto &[s, e]: segments) {
		dirSeg<P> seg(s, e);
		eve.push_back({seg.s,0,sz(segs)});
    eve.push_back({seg.e,1,sz(segs)});
		segs.push_back(seg);
	}
	sort(all(eve));
	auto inter = [](auto a, auto b) {
		return sz(segInter(a->first.s, a->first.e,b->first.s, b->first.e));
	};
	auto cmp = [](auto a, auto b) {
		return make_pair(a.first.cmp(b.first),a.second)<make_pair(0, b.second);
	};
	set<pair<dirSeg<P>, int>, decltype(cmp)> s(cmp);
	for(auto &[_, eve_tp, id]: eve) {
		if(eve_tp == 0) {	// add segment
			auto it = s.insert({segs[id], id}).first;
			if(next(it) != s.end() && inter(it, next(it)))
				return {it->second, next(it)->second};
			if(it != s.begin() && inter(it, prev(it)))
				return {it->second, prev(it)->second};
		}
		if(eve_tp == 1) {	// del segment
			auto it = s.erase(s.find({segs[id], id}));
			if(it!=s.begin() && it!=s.end() && inter(it, prev(it)))
				return {it->second, prev(it)->second};
		}
	}
	return {-1, -1};
}