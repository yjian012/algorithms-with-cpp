//Note: https://hyper-meta.blogspot.com/2022/03/efficient-solution-to-range-minimum.html
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <utility>
#include <unordered_map>
using namespace std;
template<typename T>
class SparseTable{
    vector<T> copy;
    vector<vector<size_t>> tab;
    bool _modeMin=true;
public:
    SparseTable(bool modeMin=true):_modeMin(modeMin){}
    SparseTable(const vector<T>& A,bool modeMin=true):copy(A),_modeMin(modeMin){
        build();
    }
    SparseTable(vector<T>&& A,bool modeMin=true):copy(A),_modeMin(modeMin){
        build();
    }
    void build(const vector<T>& A,bool modeMin=true){
        _modeMin=modeMin;
        copy=A;
        build();
    }
    void build(vector<T>&& A,bool modeMin=true){
        _modeMin=modeMin;
        copy=A;
        build();
    }
    void build(){
        const size_t n=copy.size();
        if(n==0) return;
        tab.reserve(8*sizeof(int)-__builtin_clz(n));
        vector<size_t> temp(n);
        for(size_t i=0;i<n;++i){
            temp[i]=i;
        }
        tab.emplace_back(move(temp));
        int l=2;
        while(l<n){
            vector<size_t> t(n-l+1);
            for(size_t i=0;i<n-l+1;++i){
                auto a=tab.back()[i],b=tab.back()[i+l/2];
                t[i]=comp(copy[a],copy[b])?a:b;
            }
            tab.emplace_back(move(t));
            l*=2;
        }
        if(tab.back().size()>1){
            auto a=tab.back().front(),b=tab.back().back();
            tab.emplace_back(vector<size_t>{comp(copy[a],copy[b])?a:b});
        }
    }
    bool comp(T a,T b){
        if(_modeMin) return a<b;
        return a>b;
    }
    size_t queryIdx(size_t i,size_t j){
        if(i>=copy.size()||j>copy.size()||i==j) throw std::out_of_range("range error");
        if(i>j){
            cout<<"Lower bound is larger than upper bound. Bounds are swapped."<<endl;
            swap(i,j);
        }
        int d=8*sizeof(int)-__builtin_clz(j-i)-1;
        auto a=tab[d][i],b=tab[d][j-(1<<d)];
        return comp(copy[a],copy[b])?a:b;
    }
    T query(size_t i,size_t j){
        return copy[queryIdx(i,j)];
    }
    string mode(){
        return _modeMin?"Minimum query":"Maximum query";
    }
};

template<typename T>
class RMQ{
    vector<T> copy;
    bool _modeMin=true;
    struct node{
        size_t parent;
        size_t left=-1;
        size_t right=-1;
    };
    vector<node> tree;
    size_t root;
    vector<size_t> EulerSeq,Level,VisitOrd;
    SparseTable<size_t> ST;
    int blockLength=0;
    vector<size_t> BlockMinInd;
    vector<unsigned int> TypeTab;
    unordered_map<unsigned int,vector<vector<int>>> LookUpTab;
    bool comp(T a,T b){
        if(_modeMin) return a<b;
        return a>b;
    }
    void RMQtoLCAT(){
        EulerSeq.resize(2*tree.size()-1);
        Level.resize(2*tree.size()-1);
        VisitOrd.resize(tree.size());
        size_t l=0,h=0;
        EulerTour(l,h,root);
        if(debug) printTour();
        blockLength=(8*sizeof(int)-__builtin_clz(Level.size())-1)/2;
        if(debug) cout<<"blockLength="<<blockLength<<endl;
    }
    void EulerTour(size_t &l,size_t &h,size_t node){
        EulerSeq[h]=node;
        Level[h]=l;
        VisitOrd[node]=h;
        if(tree[node].left!=-1){
            ++l;
            ++h;
            EulerTour(l,h,tree[node].left);
            --l;
            ++h;
            EulerSeq[h]=node;
            Level[h]=l;
            VisitOrd[node]=h;
        }
        if(tree[node].right!=-1){
            ++l;
            ++h;
            EulerTour(l,h,tree[node].right);
            --l;
            ++h;
            EulerSeq[h]=node;
            Level[h]=l;
            VisitOrd[node]=h;
        }
    }
    void LCATtoRMQL(){
        int rest=Level.size()%blockLength;
        while(rest<blockLength){
            Level.emplace_back(Level.back()+1);
            ++rest;
        }
        vector<size_t> BlockMin;
        size_t l=Level.size()/blockLength;
        BlockMin.resize(l);
        BlockMinInd.resize(l);
        TypeTab.resize(l);
        for(size_t i=0;i<l;++i){
            size_t k=i*blockLength;
            BlockMin[i]=Level[k];
            BlockMinInd[i]=k;
            unsigned int temp=0;
            vector<int> t;
            for(int j=1;j<blockLength;++j){
                if(Level[k+j]<BlockMin[i]){
                    BlockMin[i]=Level[k+j];
                    BlockMinInd[i]=k+j;
                }
                if(Level[k+j]>Level[k+j-1]){
                    ++temp;
                }
                temp<<=1;
                t.emplace_back(Level[k+j]);
            }
            TypeTab[i]=temp;
            if(LookUpTab.find(temp)==LookUpTab.end()) LookUpTab[temp]=makeTable(t,BlockMinInd[i]-k);
        }
        if(debug){
            cout<<"BlockMin=";
            print(BlockMin);
            cout<<"BlockMinInd=";
            print(BlockMinInd);
        }
        ST.build(BlockMin);
    }
    vector<vector<int>> makeTable(vector<int> &t,int mIdx){
        if(debug){
            cout<<"input +- config:";
            print(t);
        }
        vector<vector<int>> res(blockLength);
        for(int i=0;i<blockLength;++i){
            vector<int> c(blockLength);
            int u=i;
            c[i]=u-mIdx;
            for(int j=i+1;j<blockLength;++j){
                if(t[j]<t[u]) u=j;
                c[j]=u-mIdx;
            }
            res[i]=move(c);
        }
        if(debug){
            cout<<"LookUpTab returned:\n";
            print(res);
        }
        return res;
    }
    size_t queryRMQL(size_t a,size_t b){//from a to b, inclusive
        bool lrest=a%blockLength,rrest=(b+1)%blockLength;
        int l=a/blockLength+lrest,r=b/blockLength-rrest;
        if(debug) cout<<"query l="<<l<<",r="<<r<<endl;
        size_t res=-1;
        if(l>r+1){
            res=BlockMinInd[ST.queryIdx(l-1,l)]+LookUpTab[TypeTab[l-1]][a%blockLength][b%blockLength];
            if(debug) cout<<"in one block, result="<<res<<endl;
            return res;
        }
        if(l<r+1){
            res=BlockMinInd[ST.queryIdx(l,r+1)];
            if(debug) cout<<"block query, result="<<res<<endl;
        }
        if(lrest){
            size_t temp=BlockMinInd[ST.queryIdx(l-1,l)]+LookUpTab[TypeTab[l-1]][a%blockLength][blockLength-1];
            if(res==-1||Level[res]>Level[temp]) res=temp;
            if(debug) cout<<"left query, temp="<<temp<<", result="<<res<<endl;
        }
        if(rrest){
            size_t temp=BlockMinInd[ST.queryIdx(r+1,r+2)]+LookUpTab[TypeTab[r+1]][0][b%blockLength];
            if(res==-1||Level[res]>Level[temp]) res=temp;
            if(debug) cout<<"right query, temp="<<temp<<", result="<<res<<endl;
        }
        return res;
    }
    void printTour(){
        cout<<"pare :";
        for(auto i:tree){
            cout<<setw(2)<<(int)i.parent<<" ";
        }
        cout<<endl;
        cout<<"left :";
        for(auto i:tree){
            cout<<setw(2)<<(int)i.left<<" ";
        }
        cout<<endl;
        cout<<"right:";
        for(auto i:tree){
            cout<<setw(2)<<(int)i.right<<" ";
        }
        cout<<endl;
    }
    void print(const vector<size_t> &v){
        for(auto i:v){
            cout<<(int)i<<" ";
        }
        cout<<endl;
    }
    void print(const vector<int> &v){
        for(auto i:v){
            cout<<i<<" ";
        }
        cout<<endl;
    }
    void print(const vector<vector<int>> &v){
        for(auto &i:v){
            for(auto j:i)
                cout<<j<<" ";
            cout<<endl;
        }
    }
public:
    bool debug=false;
    RMQ(bool modeMin=true):_modeMin(modeMin){}
    RMQ(const vector<T> &A,bool modeMin=true):copy(A),_modeMin(modeMin){
        build();
    }
    RMQ(vector<T> &&A,bool modeMin=true):copy(A),_modeMin(modeMin){
        build();
    }
    void build(const vector<T> &A,bool modeMin=true){
        copy=A;
        _modeMin=modeMin;
        build();
    }
    void build(vector<T> &&A,bool modeMin=true){
        copy=A;
        _modeMin=modeMin;
        build();
    }
    void build(){
        if(copy.size()<=2) return;
        tree.resize(copy.size());
        vector<size_t> st(copy.size());
        long k,top=-1;
        for(size_t i=0;i<copy.size();++i){
            k=top;
            while(k>=0&&comp(copy[i],copy[st[k]])) --k;
            if(k!=-1) {tree[i].parent=st[k];tree[st[k]].right=i;}
            if(k<top) {tree[st[k+1]].parent=i;tree[i].left=st[k+1];}
            st[++k]=i;
            top=k;
        }
        tree[st[0]].parent=-1;
        root=st[0];
        RMQtoLCAT();
        if(debug){
            cout<<"E="; print(EulerSeq);
            cout<<"L="; print(Level);
            cout<<"H="; print(VisitOrd);
        }
        LCATtoRMQL();
    }
    size_t queryIdx(size_t u,size_t v){//from u to v, inclusive
        if(copy.empty()||u>=copy.size()||v>=copy.size())  throw std::out_of_range("range error");
        if(u>v){
            cout<<"Lower bound is larger than upper bound. Bounds are swapped."<<endl;
            swap(u,v);
        }
        if(copy.size()==1) return 0;
        if(copy.size()==2) return copy[u]<=copy[v]?u:v;
        if(u==v) return u;
        if(VisitOrd[u]>VisitOrd[v]) swap(u,v);
        if(debug){
            cout<<"sending queryRMQL("<<VisitOrd[u]<<","<<VisitOrd[v]<<")\n";
        }
        return EulerSeq[queryRMQL(VisitOrd[u],VisitOrd[v])];
    }
    T query(size_t u,size_t v){//from u to v, inclusive
        return copy[queryIdx(u,v)];
    }
    string mode(){
        return _modeMin?"Minimum query":"Maximum query";
    }
};
int main()
{
    vector<int> A{4,48,6,94,75,6,39,7,1,0,4,78,56,91,73,1,3,73,57,8,2,62,7,1,0,7,75,478,52,97,274,19,84,68,75,9,37,4};
    cout<<"input size: "<<A.size()<<endl;
    cout<<"input:";
    for(auto i:A) cout<<setw(2)<<i<<" ";
    cout<<endl;
    cout<<"index:";
    for(int i=0;i<A.size();++i) cout<<setw(2)<<i<<" ";
    cout<<endl;
    RMQ<int> r;
    r.debug=0;
    r.build(A,false);
    /*
    cout<<"query result: ";
    cout<<r.queryMin(0,8)<<endl;
    */
    SparseTable<int> st(A,false);
    for(int i=0;i<A.size()-1;++i){
        for(int j=i+1;j<A.size();++j){
            int r1=r.query(i,j),r2=st.query(i,j+1);
            if(r1!=r2){
                cout<<"i="<<i<<",j="<<j<<",r1="<<r1<<",r2="<<r2<<endl;
                return 0;
            }
        }
    }
    cout<<"Alright!\n";
    return 0;
}
