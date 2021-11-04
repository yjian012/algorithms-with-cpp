#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include<set>
#include<vector>
#include<algorithm>
//#include<cfloat>
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
inline point operator-(const point &p1,const point &p2){
    point p;
    p.x=p1.x-p2.x;
    p.y=p1.y-p2.y;
    return p;
}
inline point operator+(const point &p1,const point &p2){
    point p;
    p.x=p1.x+p2.x;
    p.y=p1.y+p2.y;
    return p;
}
struct segment{
    point p1;
    point p2;
};

vector<vector<segment>> read_input(istream &is);
inline double direction(const point &pi,const point &pj,const point &pk){
    return (pk-pi)*(pj-pi);
}
inline bool on_seg(const point &pi,const point &pj,const point &pk){
    if(std::min(pi.x,pj.x)<=pk.x&&pk.x<=std::max(pi.x,pj.x)&&std::min(pi.y,pj.y)<=pk.y&&pk.y<=std::max(pi.y,pj.y)) return true;
    return false;
}
bool p_sort (const point &a,const point &b);
bool seg_sort (const segment &a,const segment &b);

void display(const vector<segment> &s);
void display(const segment &s);

auto cmp=[](const segment &a,const segment &b){
    if(a.p1.x<b.p1.x) return direction(a.p1,b.p1,a.p2)>0;
    return direction(b.p1,a.p1,b.p2)<0;
};
void display(const set<segment,decltype(cmp)> &T);

#endif
