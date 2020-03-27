#include<bits/stdc++.h>
using namespace std;
double p,k,T,colder_k;
int numcnt;
struct child{
    int score;
    int arr[9][15];
}first,E1,E2,best,lastbest;

struct kyaryunha{
    int x,y,jari;
};

int dx[8]={-1, 0, 1,-1, 1,-1, 0, 1};
int dy[8]={-1,-1,-1, 0, 0, 1, 1, 1};
int calc_score(child &a){
    int score = 0;
    vector<bool> ischeck(10000,false);
    for(int num=1;num<10000;num++){
        if(ischeck[num]) continue;
        queue<kyaryunha> q;
        bool posi = false;
        int arr[15];
        int jari = 0;
        int nnum = num;
        int rnum = 0;
        while(nnum>0){
            arr[jari] = nnum%10;
            rnum = rnum*10 + nnum%10;
            nnum = nnum/=10;
            jari++;
        }
        reverse(arr,arr+jari);
        int N = 8; int M = 14;
        for(int i=1;i<=N;i++){
            for(int j=1;j<=M;j++){
                if(a.arr[i][j]==arr[0]){
                    q.push({i,j,1});
                }
            }
        }
        while(!q.empty()){
            int x = q.front().x;
            int y = q.front().y;
            int where = q.front().jari; q.pop();
            if(where==jari){
                posi = true;
                break;
            }
            for(int k=0;k<8;k++){
                int nx = x + dx[k];
                int ny = y + dy[k];
                if(1<=nx&&nx<=8&&1<=ny&&ny<=14){
                    if(a.arr[nx][ny]==arr[where]){
                        q.push({nx,ny,where+1});
                    }
                }
            }
        }
        if(posi){
            ischeck[num] = true;
            ischeck[rnum] = true;
        }
    }
    for(int num=1000;num<10000;num++) if(ischeck[num]) score++;
    return score;
}

child make_child(child &a){
    child ret = a;
    int num = rand()%110+1;
    while(num--){
        int i = rand()%8+1;
        int j = rand()%14+1;
        int k = rand()%10;
        ret.arr[i][j] = k;
    }
    ret.score = calc_score(ret);
    return ret;
}

void print_child(child &a){
    cout<<"=======================\n";
    cout<<"Score "<<a.score<<'\n';
    for(int i=1;i<=8;i++){
        for(int j=1;j<=14;j++){
            cout<<a.arr[i][j];
        } cout<<'\n';
    } cout<<'\n';

}


clock_t cstart,cfinish;
int main(void){
    srand((unsigned)time(NULL));
    string str;
    for(int i=1;i<=8;i++){
        cin>>str;
        int ssiz = str.size();
        for(int j=1;j<=14;j++){
            first.arr[i][j] = str[j-1]-'0';
        }
    }
    first.score = calc_score(first);
    E1 = first;
    best = first;
    print_child(best);
    numcnt = 0;
    k = 20.0;
    T = 0.01;
    colder_k = 0.0001;
    cstart = clock();
    while(k>T){
        if(numcnt%1000==0){
            E1 = best;
        }
        if(numcnt%100==0){
            cfinish = clock();
            int duration = (cfinish-cstart);
            cout<<k<<' '<<T<<' '<<duration<<' '<<numcnt<<'\n';
            cstart = clock();
        }
        E2 = make_child(E1);
        if(best.score<E2.score){
            best = E2;
            print_child(best);
        }
        p = exp((E2.score-E1.score)/T*k);
        if(p>rand()%1000000/1000000.0) E1 = E2;
        k -= colder_k; numcnt++;
        if(k<10&&colder_k==0.00001) colder_k = 0.00005;
        if(k<3&&colder_k==0.00005) colder_k = 0.000001;

        if(!(k>T)){
            k = 20;
        }
    }
    print_child(best);
}
