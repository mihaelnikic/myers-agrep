#include <cstdio>
#include <cstring>

using namespace std;


long long Peq[123] ;// ascii letters
char vocab[123];
int vocabSize;
    
void precompute(char P[]){
  
    long long bitPos = 1;
    for (int i=0;P[i]!='\0';++i){
        Peq[ P[i] ] |= bitPos;
        bitPos = bitPos << 1;
    }
} 

int main (){
    char P[64];
    scanf ("%s",P);
    scanf ("%s",vocab);

    vocabSize = strlen(vocab);
    precompute(P);
        
    for (int i=0;i<vocabSize;++i){
        printf("%lld\n",Peq[ vocab[i] ]);
    }

    return 0;
}
