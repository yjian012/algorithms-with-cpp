#include "geometry_intersect.h"

bool seg_intersect(const segment &a,const segment &b){
    point p1=a.p1;point p2=a.p2;point p3=b.p1;point p4=b.p2;
    double d1=direction(p3,p4,p1);
    double d2=direction(p3,p4,p2);
    double d3=direction(p1,p2,p3);
    double d4=direction(p1,p2,p4);
    if(d1*d2<0&&d3*d4<0) return true;
    else if(d1==0&&on_seg(p3,p4,p1)) return true;
    else if(d2==0&&on_seg(p3,p4,p2)) return true;
    else if(d3==0&&on_seg(p1,p2,p3)) return true;
    else if(d4==0&&on_seg(p1,p2,p4)) return true;
    else return false;
}
const segment* above(const set<segment,decltype(cmp)> &T,const segment &s){
    auto it=T.find(s);
    if(it==T.end()) return nullptr;
    if(it==T.begin()) return nullptr;
    --it;
    return &(*it);
}
const segment* below(const set<segment,decltype(cmp)> &T,const segment &s){
    auto it=T.find(s);
    if(it==T.end()) return nullptr;
    ++it;
    if(it==T.end()) return nullptr;
    return &(*it);
}
pair<segment,segment> intersect(const vector<segment> &input){//p1 must be to the left of p2, with pointers initialized to segments
    vector<point> points;
    for(int i=0;i<input.size();i++){
        points.push_back(input[i].p1);
        points.push_back(input[i].p2);
    }
    sort(points.begin(),points.end(),p_sort);
    
    set<segment,decltype(cmp)> T(cmp);
    for(int p=0;p<points.size();p++){
        segment s=*(points[p].seg);
        const segment* ab;
        const segment* be;
        if(points[p].e==0){
            auto test=T.insert(s);
            if(ab=above(T,s)){
                if(seg_intersect(*ab,s)){
                    return std::make_pair(*ab,s);
                }
            }
            if(be=below(T,s)){
                if(seg_intersect(*be,s)){
                    return std::make_pair(*be,s);
                }
            }
        }
        else{
            if(ab=above(T,s)){
                if(be=below(T,s)){
                    if(seg_intersect(*ab,*be)) return std::make_pair(*ab,*be);
                }
            }
            T.erase(s);
        }
    }
    point z;
    segment g={z,z};
    pair<segment,segment> r=std::make_pair(g,g);
    return r;
}
