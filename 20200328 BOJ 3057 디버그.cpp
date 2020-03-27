#include<bits/stdc++.h>
#define magic ios_base::sync_with_stdio(false);cin.tie(nullptr)
using namespace std;
#define pii pair<int,int>
double p,k,T,colder_k;
int numcnt;

int R,C;
int arr[305][305];
struct child{
    int score;
    pii start;
    int len;
}first,E1,E2,best,lastbest;

int calc_score(child &a){
    int score = 0;
    for(int i=0;i<a.len;i++){
        for(int j=0;j<a.len;j++){
            if(arr[a.start.first + i][a.start.second + j] != arr[a.start.first + (a.len - i - 1)][a.start.second + (a.len - j - 1)])
                return 0;
        }
    }
    return a.len;
}

child make_child(child &a){
    child ret = a;
    ret.start = { a.start.first + rand()%10-5, a.start.second + rand()%10-5};
    ret.len = a.len + rand()%3;

    while(!(1<=ret.start.first&&ret.start.first<=R)){
        ret.start.first = a.start.first + rand()%10-5;
    }

    while(!(1<=ret.start.second&&ret.start.second<=C)){
        ret.start.second = a.start.second + rand()%10-5;
    }

    if(ret.start.first + ret.len - 1 > R){
        ret.len = R - ret.start.first + 1;
    }

    if(ret.start.second + ret.len - 1 > C){
        ret.len = R - ret.start.second + 1;
    }

    ret.score = calc_score(ret);
    return ret;
}

void print_child(child &a){
    cout<<"=======================\n";
    cout<<"Score "<<a.score<<'\n';
    cout<<a.start.first<<' '<<a.start.second<<' '<<a.len<<'\n';
}


int main(void){
    srand((unsigned)time(NULL));
    magic;
    cin>>R>>C;
    for(int i=1;i<=R;i++){
        string str;
        cin>>str;
        int ssiz = str.size();
        for(int j=1;j<=C;j++){
            arr[i][j] = str[j-1];
        }
    }
    first.start = {1,1};
    first.score = 1;
    E1 = first;
    best = first;

    numcnt = 0;
    k = 100.0;
    T = 0.01;
    colder_k = 0.00003;
    while(k>T){
        if(numcnt%1000==0){
            E1 = best;
        }
        /** if(numcnt%10000==0){
            cout<<k<<' '<<T<<' '<<numcnt<<'\n';
        } **/
        E2 = make_child(E1);
        if(best.score<E2.score){
            best = E2;
            /// print_child(best);
        }
        p = exp((E2.score-E1.score)/T*k);
        if(p>rand()%1000000/1000000.0) E1 = E2;
        k -= colder_k; numcnt++;
        if(k<10&&colder_k==0.00001) colder_k = 0.00005;
        if(k<3&&colder_k==0.00005) colder_k = 0.000001;

    }
    /// print_child(best);
    if(best.score<=1) cout<<-1;
    else cout<<best.score;
}
