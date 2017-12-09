#include <cstdio>
#include <cstring>

using namespace std;

long long Peq[130] ;// ascii letters
char vocab[130];
int vocabSize;
    
void precompute(char P[]){
    long long bitPos = 1;
    for (int i=0;P[i]!='\0';++i){
        Peq[ P[i] ] |= bitPos;
        bitPos = bitPos << 1;
    }
} 


char P[1000];
char T[1000];



int main (){
    int k;
    scanf ("%s",T);
    scanf ("%s",P);
    scanf ("%s",vocab);
    scanf ("%d",&k);
    
    //Makni ovo i pogledaj vocab iz inputa
    vocabSize = strlen(vocab);
    precompute(P);
    
    //for (int i=0;i<vocabSize;++i){
    //    printf("%lld\n",Peq[ vocab[i] ]);
    //}
    
    int lenT = strlen(T);
    int lenP = strlen(P);
    
    int n = lenT;
    int m = lenP;

    int score = m;
    //Mozda unsigned long long koristiti??
    long long Pv = ( 1 <<  m ) - 1;
    //printf ("Pv %lld\n",Pv);
    long long Mv = 0;

    long long Eq;
    long long Xv,Xh;
    long long Ph,Mh;
    for (int j=0;j<n;++j){
        Eq = Peq[ T[j] ];
        printf ("%c %d\n",T[j],Eq);
        Xv = Eq | Mv;
        Xh = ( ( (Eq & Pv) + Pv ) ^ Pv ) | Eq;
        
        Ph = Mv | ( ~ (Xh | Pv) );
        Mh = Pv & Xh;
        
        if ( Ph & (1 << (m-1) ) ){
            score += 1;
        }
        if ( Mh & (1 << (m-1) ) ){
            score -= 1;
        }
        
        Ph <<= 1;
        Mh <<= 1;
        Pv = Mh | ( ~ ( Xv | Ph ) );
        Mv = Ph & Xv;
        
        printf ("Score: %d\n",score);
        if (score <= k){
            printf ("Match at: %d\n", j );
        }
        
    }
    
    return 0;
}
