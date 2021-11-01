#include "geometry_intersect.h"

bool seg_intersect(segment a, segment b){
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
const segment* above(set<segment,decltype(cmp)> &T,segment s){
    auto it=T.find(s);
    if(it==T.end()) return nullptr;
    if(it==T.begin()) return nullptr;
    --it;
    return &(*it);
}
const segment* below(set<segment,decltype(cmp)> &T,segment s){
    auto it=T.find(s);
    if(it==T.end()) return nullptr;
    ++it;
    if(it==T.end()) return nullptr;
    return &(*it);
}
pair<segment,segment> intersect(vector<segment> &input){
    point z;
    segment g={z,z};
    pair<segment,segment> r=make_pair(g,g);
    for(int i=0;i<input.size();i++){//p1 must be to the left of p2
        if(input[i].p1.x>input[i].p2.x){
            point temp=input[i].p1;
            input[i].p1=input[i].p2;
            input[i].p2=temp;
        }
        input[i].p2.e=1;
        input[i].p1.seg=input[i].p2.seg=&input[i];
    }
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
                    return make_pair(*ab,s);
                }
            }
            if(be=below(T,s)){
                if(seg_intersect(*be,s)){
                    return make_pair(*be,s);
                }
            }
        }
        else{
            if(ab=above(T,s)){
                if(be=below(T,s)){
                    if(seg_intersect(*ab,*be)) return make_pair(*ab,*be);
                }
            }
            T.erase(s);
        }
    }
    return r;
}
