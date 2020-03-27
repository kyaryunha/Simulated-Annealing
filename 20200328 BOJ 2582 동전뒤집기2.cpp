#include<bits/stdc++.h>
#define magic ios_base::sync_with_stdio(false);cin.tie(nullptr)
using namespace std;
#define pii pair<int,int>
double p,k,T,colder_k;
int numcnt;

int N;

struct child{
    int score;
    char arr[33][33];
}first,E1,E2,best,lastbest;

int calc_score(child &a){
    int score = 0;
    for(int i=1;i<=N;i++){
        int cnt = 0;
        for(int j=1;j<=N;j++){
            cnt += a.arr[i][j];
        }
        score += max(cnt,N-cnt);
    }
    return score;
}

child make_child(child &a){
    child ret = a;
    int num = rand()%2+1;
    while(num--){
        int dire = 1;
        int idx = rand()%N+1;
        if(dire){
            for(int i=1;i<=N;i++){
                ret.arr[i][idx] = !ret.arr[i][idx];
            }
        }
        else{
            for(int i=1;i<=N;i++){
                ret.arr[idx][i] = !ret.arr[idx][i];
            }
        }
    }
    ret.score = calc_score(ret);
    return ret;
}

void print_child(child &a){
    cout<<"=======================\n";
    cout<<"Score "<<a.score<<'\n';
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cout<<a.arr[i][j];
        } cout<<'\n';
    } cout<<'\n';
}


int main(void){
    srand((unsigned)time(NULL));
    magic;
    cin>>N;
    for(int i=1;i<=N;i++){
        string str;
        cin>>str;
        int ssiz = str.size();
        for(int j=1;j<=N;j++){
            first.arr[i][j] = str[j-1]=='H'?1:0;
        }
    }
    first.score = calc_score(first);
    E1 = first;
    best = first;

    numcnt = 0;
    k = 500.0;
    T = 0.01;
    colder_k = 0.99999;
    int cnt = 0;
    /// print_child(best);
    while(k>T){
        cnt++;
        E2 = make_child(E1);
        if(best.score<E2.score){
            best = E2;
            /// print_child(best);
        }
        p = exp((E2.score-E1.score)/T*k);
        if(p>rand()%1000000/1000000.0) E1 = E2;
        k *= colder_k; numcnt++;

    }
    /// cout<<cnt<<'\n';
    /// print_child(best);
    cout<<(N*N-best.score);
}
