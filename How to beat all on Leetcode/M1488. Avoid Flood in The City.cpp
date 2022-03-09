const int N=360007;
int keys[N]={0}, values[N]={0};
class Solution {
    int& hash(int n){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int idx = (n%N + N)%N, cnt=1;
        while(keys[idx]!=n && values[idx]!=0){
            idx = (idx+cnt*cnt)%N;
            cnt += 1;
        }
        keys[idx] = n;
        return values[idx];
    }
public:
    vector<int> avoidFlood(vector<int>& rains) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        memset(values, 0, sizeof(values));
        const int l=rains.size();
        set<int> zeros;
        for(int i=0;i<l;++i){
            if(rains[i]==0){
                zeros.insert(i);
            }
            else if(hash(rains[i])==0){
                hash(rains[i])=i+1;
            }
            else{
                auto it=zeros.lower_bound(hash(rains[i])-1);
                if(it==zeros.end()) return {};
                else{
                    hash(rains[i])=i+1;
                    rains[*it]=-rains[i];
                    zeros.erase(it);
                }
            }
        }
        for(int i=0;i<l;++i){
            if(rains[i]>0) rains[i]=-1;
            else if(rains[i]==0) rains[i]=1;
            else rains[i]=-rains[i];
        }
        return rains;
    }
};
