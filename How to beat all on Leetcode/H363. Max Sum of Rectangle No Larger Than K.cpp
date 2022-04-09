class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int sum=0;
        int res=INT_MIN;
        int* t=new int[matrix[0].size()];
        memset(t,0,sizeof(int)*matrix[0].size());
        for(int i=0;i<matrix.size();++i){
            for(int j=i;j<matrix.size();++j){
                for(int r=0;r<matrix[0].size();++r){
                    t[r]+=matrix[j][r];
                    sum=t[r];
                    if(sum==k) return k;
                    if(sum<k) res=max(sum,res);
                    for(int l=r-1;l>=0;--l){
                        sum+=t[l];
                        if(sum==k) return k;
                        if(sum<k) res=max(sum,res);
                    }
                }
            }
            memset(t,0,sizeof(int)*matrix[0].size());
        }
        delete[] t;
        return res;
    }
};
