/*
Input format: Line segments generated by Mathematica so it's easy to check visually if the result is correct. (e.g., "For[i = 0, i < 30, i++, Print[table = Table[{Line[RandomReal[1, {2, 2}]]}, {6}]];Print["b"]; Print[Graphics[table]]]" ).
Added 'b' as seperator.
Output: The two line segments that are found to intersect. If there's no intersect, it displays the message "No intersection".
Compile with ../geometry_functions.cpp and ../geometry_intersect_func.cpp .
*/

#include "../geometry.h"
#include "../geometry_intersect.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using std::ifstream;
using std::istream;
using std::vector;
using std::pair;
using std::string;
int main(){
    string filename="Detect segments intersects Sample.txt";
    ifstream fs;
    fs.open(filename);
    vector<vector<segment>> segments=read_input(fs);
    fs.close();
    /*pair<segment,segment> res0=intersect(segments[4]);
    //math_display(segments[4]);
    //cout<<"{"<<res0.first.p1.x<<","<<res0.first.p1.y<<"},{"<<res0.first.p2.x<<","<<res0.first.p2.y<<"} <-> {"<<res0.second.p1.x<<","<<res0.second.p1.y<<"},{"<<res0.second.p2.x<<","<<res0.second.p2.y<<"}\n";
    //display(segments[0]);
    for(int i=0;i<segments.size();i++){
        display(segments[i]);
        cout<<endl;
    }*/
    vector<pair<segment,segment>> result;
    for(int i=0;i<segments.size();i++){
        result.push_back(intersect(segments[i]));
    }
    for(int i=0;i<result.size();i++){
        if(result[i].first.p1.x==DBL_MIN){std::cout<<"No intersection\n*****************************\n";continue;}
        std::cout<<"{"<<result[i].first.p1.x<<","<<result[i].first.p1.y<<"},{"<<result[i].first.p2.x<<","<<result[i].first.p2.y<<"} <-> {"<<result[i].second.p1.x<<","<<result[i].second.p1.y<<"},{"<<result[i].second.p2.x<<","<<result[i].second.p2.y<<"}\n";
        std::cout<<"*****************************"<<std::endl;
    }
    return 0;
}
