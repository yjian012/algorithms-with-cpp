class Solution {
public:
    int findCircleNum(vector<vector<int>>& isc) {
        const int n=isc.size();
        bool done[n];
        memset(done,false,sizeof(done));
        unordered_set<int> miss;
        for(int i=0;i<n;++i) miss.insert(i);
        int t[n];
        //memset(t,-1,sizeof(t));
        int l=0,r=1,re=0;
        
        while(miss.size()>0){
            ++re;
            //memset(t,-1,sizeof(t));
            l=0;
            r=1;
            t[0]=*miss.begin();
            done[t[0]]=true;
            miss.erase(t[0]);
            while(l<r){
                int c=t[l];
                for(int i=0;i<n;++i){
                    if(!done[i]&&isc[c][i]){
                        t[r]=i;
                        done[i]=true;
                        ++r;
                        miss.erase(i);
                    }
                }
                ++l;
            }
        }
        return re;
    }
};
