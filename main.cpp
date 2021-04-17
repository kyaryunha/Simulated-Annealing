/// Template File (write by kyaryunha)

#include<bits/stdc++.h>
#define magic ios_base::sync_with_stdio(false);cin.tie(nullptr)
using namespace std;
using ll = long long;
#define MOD 1000000007
#define INF 2000000000000000000
#define ll long long
#define pll pair<ll, ll>
ll N, M, A, B, ans;
double p,k,T,colder_k;
ll numcnt;

pll arr[200005];
ll N, K;

struct child{
    ll score;
    char arr[33][33];
}first,E1,E2,best,lastbest;

ll calc_score(child &a) {
}

child make_child(child &a) {
}

void print_child(child &a) {
}


int main(void){
    magic;
    srand((unsigned)time(NULL));
    cin>>N>>K;

    /// 입출력 및 초기값 first 생성

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
    cout<<best.score;
}
