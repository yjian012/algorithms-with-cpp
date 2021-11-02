#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include<set>
#include<vector>
#include<algorithm>
#include<limits>

using std::vector;
using std::set;
using std::pair;
using std::istream;

struct segment;
struct point{
    double x=std::numeric_limits<double>::signaling_NaN();
    int e=0;
    double y=std::numeric_limits<double>::signaling_NaN();
    segment* seg=nullptr;
    point operator-(const point &p2){
        point p;
        p.x=x-p2.x;
        p.y=y-p2.y;
        return p;
    }
    point operator+(const point &p2){
        point p;
        p.x=x+p2.x;
        p.y=y+p2.y;
        return p;
    }
    double operator*(const point &p2){
        return (x*p2.y-p2.x*y);
    }
};
struct segment{
    point p1;
    point p2;
};

vector<vector<segment>> read_input(istream &is);
inline double direction(point pi,point pj,point pk){
    return (pk-pi)*(pj-pi);
}
inline bool on_seg(point pi,point pj,point pk){
    if(std::min(pi.x,pj.x)<=pk.x&&pk.x<=std::max(pi.x,pj.x)&&std::min(pi.y,pj.y)<=pk.y&&pk.y<=std::max(pi.y,pj.y)) return true;
    return false;
}
bool p_sort (point a,point b);
bool seg_sort (segment a,segment b);

void display(const vector<segment> &s);
void display(const segment &s);


auto cmp=[](segment a,segment b){
    if(a.p1.x<b.p1.x) return direction(a.p1,b.p1,a.p2)>0;
    return direction(b.p1,a.p1,b.p2)<0;
};
void display(const set<segment,decltype(cmp)> &T);

#endif
