const int N=1901;
class Hash{
int keys[N]={0}, values[N]={0};
public:
    Hash(){
        memset(values, 0, sizeof(values));
    }
    int& operator [](int n){
        int idx = (n%N + N)%N, cnt=1;
        while(keys[idx]!=n && values[idx]!=0){
            idx = (idx+cnt*cnt)%N;
            cnt += 1;
        }
        keys[idx] = n;
        return values[idx];
    }
};
class Solution {
public:
    Solution() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
    }
    int numberOfBoomerangs(vector<vector<int>>& points) {
        if(points.size()<3) return 0;
        const int n=points.size();
        int res=0;
        for(int i=0;i<n;++i){
            Hash m;
            for(int j=0;j<n;++j){
                if(j==i) continue;
                int ax=points[i][0],bx=points[j][0],ay=points[i][1],by=points[j][1];
                unsigned int d=(ax-bx)*(ax-bx)+(ay-by)*(ay-by);
                ++m[d];
                res+=m[d]-1;
            }
        }
        return 2*res;
    }
};
