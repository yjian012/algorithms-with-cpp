const int N=35023;
int ind[N]={0};
int values[N][26];
static bool first=true;
class Solution {
    int c=1;
    bool check_zero(const int* value){
        for(int i=0;i<26;++i){
            if(value[i]!=0) return false;
        }
        return true;
    }
    bool check_equal(const int* value1,const int* value2){
        for(int i=0;i<26;++i){
            if(value1[i]!=value2[i]) return false;
        }
        return true;
    }
    int insert(const int* value, bool &t){
        int idx = 0,cnt=1;
        for(int i=0;i<26;++i){
            idx=(idx+cnt*(value[i]))%N;
            cnt=cnt*101%N;
        }
        cnt=1;
        while(!check_zero(values[idx])){
            if(check_equal(values[idx],value)){
                if(ind[idx]>0){
                    t=false;
                    return ind[idx]-1;
                }
                else{
                    t=true;
                    ind[idx]=c;
                    c++;
                    return c-2;
                }
            }
            idx = (idx+cnt*cnt)%N;
            cnt += 1;
        }
        for(int i=0;i<26;++i){
            values[idx][i]=value[i];
        }
        t=true;
        ind[idx]=c;
        c++;
        return c-2;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs){
        vector<vector<string>> res;
        bool empty=false;
        int e_l=0;
        c=1;
        memset(ind,0,sizeof(ind));
        if(first){
            memset(values,0,sizeof(values));
            first=false;
        }
        bool ins=false;
        for (auto& word : strs){
            if(word.size()==0){
                if(empty) res[e_l].emplace_back("");
                else{
                    e_l=res.size();
                    res.emplace_back(vector<string>{""});
                    empty=true;
                }
                c++;
                continue;
            }
            int t[26]={0};
            for(auto c:word){
                ++t[c-'a'];
            }
            int g=insert(t,ins);
            if(ins) res.emplace_back();
            res[g].emplace_back(word);
        }
        return res;
    }
};
