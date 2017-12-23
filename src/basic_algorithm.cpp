#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

unsigned long long Peq[130] ;// ascii letters
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

bool vocabSeen[130];

int main (){
    unsigned long long k;
    scanf ("%s",T);
    scanf ("%s",P);
    scanf ("%d",&k);

    vector <char> vocab;
    for (int i=0;T[i]!='\0';++i){
        if ( vocabSeen[ T[i] ] == 1 ) continue;
        vocabSeen[ T[i] ] = true;
        vocab.push_back(T[i]);
    }
    vocabSize = vocab.size();

    precompute(P);

    //for (int i=0;i<vocabSize;++i){
    //    printf("%lld\n",Peq[ vocab[i] ]);
    //}

    unsigned long long lenT = strlen(T);
    unsigned long long lenP = strlen(P);

    unsigned long long n = lenT;
    unsigned long long m = lenP;

    int score = m;
    //Mozda unsigned long long koristiti??
    unsigned long long Pv = ( 1ULL <<  m ) - 1;
    //printf ("Pv %lld\n",Pv);
    unsigned long long Mv = 0;

    unsigned long long Eq;
    unsigned long long Xv,Xh;
    unsigned long long Ph,Mh;
    for (int j=0;j<n;++j){
        Eq = Peq[ T[j] ];
        //printf ("Eq:%llu\n",Eq);
        printf ("%c %llu\n",T[j],Eq);
        Xv = Eq | Mv;
        Xh = ( ( (Eq & Pv) + Pv ) ^ Pv ) | Eq;
        printf ("Xh:%llu\n",Xh);

        Ph = Mv | ( ~ (Xh | Pv) );
        Mh = Pv & Xh;
        printf ("Ph:%llu\n",Ph);
        printf ("Mh:%llu\n",Mh);

        if ( Ph & (1ULL << (m-1) ) ){
            score += 1;
        }
        if ( Mh & (1ULL << (m-1) ) ){
            score -= 1;
        }

        Ph <<= 1ULL;
        Mh <<= 1ULL;
        Pv = Mh | ( ~ ( Xv | Ph ) );
        Mv = Ph & Xv;

        printf ("Score: %d\n",score);
        if (score <= k){
            printf ("Match at: %d\n", j );
        }

    }

    return 0;
}
