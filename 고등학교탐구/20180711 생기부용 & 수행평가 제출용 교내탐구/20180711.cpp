/** Include **/
#include<bits/stdc++.h>
using namespace std;

/** Declare Variables and Constants **/
#define undefined 101111111
#define INF 101111110
int N,maxiLength;
int dosiDosiLength[505][505];
double p,k = 1000.0, T = 0.01,colder_k = 0.9995; int numcnt;
struct child{ bool isConnected[505][505]; int shortestPastHap; bool allConnected; }_first,E1,E2,best;

/** Declare Functions **/
child makeFirstChild();
bool checkAllConnectWithFloyd(child a);
bool checkLessThenMaxiLength(child a);
child calcScore(child a);
child makeChild(child a);
void printBest(child a);

/** Define Function **/

/*** 첫 번째 자식을 생성하는 함수 ***/
child makeFirstChild()
{
    child imsi;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            imsi.isConnected[i][j]=false;
    imsi.shortestPastHap = undefined;
    imsi.allConnected = false;
    while(imsi.allConnected==false)
    {
        int firstDosi = rand()%N+1;
        int secondDosi = rand()%N+1;
        while(firstDosi==secondDosi) secondDosi = rand()%N+1;
        if(imsi.isConnected[firstDosi][secondDosi]==false)
        {
            imsi.isConnected[firstDosi][secondDosi]=true,imsi.isConnected[secondDosi][firstDosi]=true;
            imsi.allConnected = checkAllConnectWithFloyd(imsi);
        }
    }
    imsi = calcScore(imsi);
    return imsi;
}

/*** 플로이드 워셜 알고리즘을 통해 임의의 도시 A와 B가 모두 연결되어졌는지 확인하는 함수 ***/
bool checkAllConnectWithFloyd(child a)
{
    int arrayForFloyd[505][505];
    bool isPos=true;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(a.isConnected[i][j])
                arrayForFloyd[i][j]=dosiDosiLength[i][j];
            else
                arrayForFloyd[i][j]=INF;
    for(int k=1;k<=N;k++)
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                if(i!=j)
                    if((arrayForFloyd[i][k]<INF)&&(arrayForFloyd[k][j]<INF)&&(arrayForFloyd[i][j]<arrayForFloyd[i][k]+arrayForFloyd[k][j]))
                        arrayForFloyd[i][j]=arrayForFloyd[i][k]+arrayForFloyd[k][j];
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(i!=j && arrayForFloyd[i][j]>INF)
                isPos = false;
    return isPos;
}

/*** 선택된 간선의 합이 k보다 작은지 계산하는 함수 ***/
bool checkLessThenMaxiLength(child a)
{
    int arrayForFloyd[505][505];
    int sumLength = 0;
    bool isPos=true;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(a.isConnected[i][j])
                sumLength +=dosiDosiLength[i][j];
    return (sumLength<=maxiLength)?true:false;
}

/*** 점수를 산출하는 함수. 점수는 모든쌍 최단경로의 합이다. ***/
child calcScore(child a)
{
    int arrayForFloyd[505][505];
    int sumLength = 0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(a.isConnected[i][j])
                arrayForFloyd[i][j]=dosiDosiLength[i][j];
            else
                arrayForFloyd[i][j]=INF;
    for(int k=1;k<=N;k++)
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                if(i!=j)
                    if((arrayForFloyd[i][k]<INF)&&(arrayForFloyd[k][j]<INF)&&(arrayForFloyd[i][j]<arrayForFloyd[i][k]+arrayForFloyd[k][j]))
                        arrayForFloyd[i][j]=arrayForFloyd[i][k]+arrayForFloyd[k][j];
    for(int i=1;i<=N;i++)
        for(int j=1;j<=i;j++)
            if(i!=j&&arrayForFloyd[i][j]<INF)
                sumLength+=arrayForFloyd[i][j];
    a.shortestPastHap = sumLength;
    return a;
}

/*** 부모 a로부터 새로운 자식을 생성하는 함수 ***/
child makeChild(child a)
{
    int cnt = (N==1?1:2*N);
    while(cnt--)
    {
        int firstDosi = rand()%N+1;
        int secondDosi = rand()%N+1;
        while(firstDosi==secondDosi) secondDosi = rand()%N+1;
        if(a.isConnected[firstDosi][secondDosi]==true)
        {
            a.isConnected[firstDosi][secondDosi]=false,a.isConnected[secondDosi][firstDosi]=false;

        }
    }
    a.allConnected = checkAllConnectWithFloyd(a);
    while(a.allConnected==false)
    {
        int firstDosi = rand()%N+1;
        int secondDosi = rand()%N+1;
        while(firstDosi==secondDosi) secondDosi = rand()%N+1;

        if(a.isConnected[firstDosi][secondDosi]==false)
        {
            a.isConnected[firstDosi][secondDosi]=true,a.isConnected[secondDosi][firstDosi]=true;
            a.allConnected = checkAllConnectWithFloyd(a);
        }
    }
    a = calcScore(a);
    return a;
}
/*** 어느 길이 연결되었는지 출력하는 함수 ***/
void printBest(child a)
{
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
            printf(" %d",a.isConnected[i][j]?1:0);
        printf("\n");
    }
}

/** Main Function **/
/*** 시뮬레이티드 어닐링이 돌아가는 메인 함수 ***/
int main(void)
{
    srand((unsigned)time(NULL));

    /** Input **/
    scanf("%d",&N);
    scanf("%d",&maxiLength);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            scanf("%d",&dosiDosiLength[i][j]);

    /** Simulated Annealing **/
    E1=makeFirstChild();
    best = E1;
    while(k>T){
        E2 = makeChild(E1);
        if(best.shortestPastHap<E2.shortestPastHap) best=E2;
        p = exp((E2.shortestPastHap-E1.shortestPastHap)/T*k);
        if(p>rand()%1000000/1000000.0) E1 = E2;
        k*=colder_k; numcnt++;
    }

    /** Output **/
    printBest(best);
    printf("%d %d\n",best.allConnected?1:0,best.shortestPastHap);
    printf("numcnt : %d",numcnt);
}
