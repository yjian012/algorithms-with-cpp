#include "geometry.h"
#include<iostream>
#include<fstream>
#include<string>

using std::cin;
using std::cout;
using std::string;
using std::istream;

void display(const vector<segment> &s){
    for(int i=0;i<s.size();i++){
        cout<<"{{"<<s[i].p1.x<<','<<s[i].p1.y<<"},{"<<s[i].p2.x<<','<<s[i].p2.y<<"}} ";
    }
}
void math_display(const vector<segment> &seg){
    cout<<"Graphics[{";
    for(int i=0;i<seg.size();i++){
        cout<<"{Line[{{"<<seg[i].p1.x<<','<<seg[i].p1.y<<"},{"<<seg[i].p2.x<<','<<seg[i].p2.y<<"}}]},";
    }
    cout<<"}]\n";
}
void display(const segment &s){
    cout<<"{"<<s.p1.x<<","<<s.p1.y<<"},{"<<s.p2.x<<','<<s.p2.y<<"}\n";
}
void display(const set<segment,decltype(cmp)> &T){
    auto it=T.begin();
    while(it!=T.end()){
        display(*it);
        it++;
    }
    return;
}
vector<vector<segment>> read_input(istream &is){
    char t;
    double x1,y1,x2,y2;
    segment k;
    vector<segment> s;
    vector<vector<segment>> r;
    //int count=0;
    while(is>>t){
        //if(count>100000) break;
        //count++;
        while(t!='['&&t!='b') {is>>t;}
        if(t=='b'){
            r.push_back(s);
            s.clear();
            continue;
        }
        is>>t;
        is>>t;
        is>>x1>>t>>y1>>t>>t>>t>>x2>>t>>y2;
        k.p1.x=x1;k.p1.y=y1;k.p2.x=x2;k.p2.y=y2;
        s.push_back(k);
    }
    return r;
}
bool p_sort (point a,point b) {
    if(a.x<b.x) return true;
    else if(a.x==b.x){
        if(a.e<b.e) return true;
        else if(a.e==b.e){
            if(a.y<b.y) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}
bool seg_sort (segment a,segment b) {//make sure p1.x<p2.x in both a and b
    if(a.p1.x<b.p1.x) return true;
    else if(a.p1.x==b.p1.x){
        if(a.p2.x<b.p2.x) return true;
        else if(a.p1.x==b.p2.x){
            if(a.p1.y<b.p2.y) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}
