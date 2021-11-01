#include<set>
#include<vector>
#include<algorithm>
#include<cfloat>

using std::vector;
using std::set;
using std::pair;

struct segment;
struct point{
    double x=DBL_MIN;
    int e=0;
    double y=DBL_MIN;
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
inline double direction(point pi,point pj,point pk){
    return (pk-pi)*(pj-pi);
}
inline bool on_seg(point pi,point pj,point pk){
    if(min(pi.x,pj.x)<=pk.x&&pk.x<=max(pi.x,pj.x)&&min(pi.y,pj.y)<=pk.y&&pk.y<=max(pi.y,pj.y)) return true;
    return false;
}
bool p_sort (point a,point b);
bool seg_sort (segment a,segment b);

void display(const vector<segment> &s);
void display(const segment &s);
void display(const set<segment,decltype(cmp)> &T);
