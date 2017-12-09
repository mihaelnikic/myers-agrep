#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 9999999

using namespace std;

char P[1000];
char T[1000];

int n;

int C[1000][1000];
int bio[1000][1000];

int solve(int posP, int posT){
    //printf ("%d %d\n",posP,posT);
    if (bio[posP][posT] == 1){
       return C[posP][posT];
    }
    
    bio[posP][posT] = 1;
    
    if (posP == 0){
        C[posP][posT] = 0;
        return C[posP][posT];
    }
    
    int sameChar = 1;
    if (P[posP-1]==T[posT-1]) sameChar = 0;
    //+ ( 1-int(P[posP]==T[posT]) 
    
    if (posP>0 && posT>0){
        C[posP][posT] = min ( solve(posP-1,posT-1) + sameChar , C[posP][posT] );
    }
    
    if (posP>0){
        C[posP][posT] = min ( solve(posP-1,posT) + 1, C[posP][posT] );
    }
    
    if (posT>0){
        C[posP][posT] = min ( solve(posP,posT-1) + 1, C[posP][posT] );
    }
    
    return C[posP][posT];
    
}

int main(){
    scanf ("%s",T);
    scanf ("%s",P);
    int k;
    scanf("%d",&k);
    
    int lenT = strlen(T);
    int lenP = strlen(P);
    
    for (int i=0;i<=lenP;++i){
        for (int j=0;j<=lenT;++j){
            C[i][j] = INF;
        }
    }
    
    for (int i=0;i<=lenT;++i){
        solve(lenP,i);
        printf ("%d: %d\n",i,C[lenP][i]);
    }
    
    printf ("Output:\n");
    for (int i=0;i<=lenT;++i){
        solve(lenP,i);
        if ( C[lenP][i] <= k ){
            printf ("%d ",i-1);
        }
    }
    printf ("\n-----\n");
    
    for (int i=0;i<=lenT;++i) printf ("%d ",i);
    printf ("\n");
    for (int i=0;i<=lenP;++i){
        for (int j=0;j<=lenT;++j){
            solve(i,j);
            printf ("%d ",C[i][j]);
        }
        printf ("\n");
    }
    
    return 0;
}
