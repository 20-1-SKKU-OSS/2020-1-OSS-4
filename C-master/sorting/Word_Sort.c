#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct List{
    char word[50];
    int freq;
}List;

int main(){
    int N;
    List temp;
    int ret;
    List swap;
    scanf("%d", &N); //입력할 단어 개수
    List* arr = (List*)malloc(sizeof(List)*N);

    for( int i = 0 ; i < N ; i ++ ){
        scanf("%s", arr[i].word);
        arr[i].freq = 1;
    }

    for( int i = 0 ; i < N-1 ; i ++ ){
        for( int j = i+1; j < N ; j ++ ){
            if(strcmp(arr[i].word, arr[j].word) == 0){
                arr[i].freq ++;
                for(int k = j ; k < N-1 ; k ++){
                    arr[k] = arr[k+1];
                }
                N --;
                i --;
            }
        }
    }

    for(int i = 0 ; i < N-1 ; i ++){
        for(int j = 0 ; j < N-1 ; j ++){
            if(arr[j].freq < arr[j+1].freq){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    for(int i = 0 ; i < N-1 ; i ++){
        for(int j = i+1 ; j < N ; j ++){
            if(arr[i].freq == arr[j].freq){
                ret = strcmp(arr[i].word, arr[j].word);
                if(ret>0){
                    swap = arr[i];
                    arr[i] = arr[j];
                    arr[j] = swap;
                }
            }
        }
    }

    for(int i = 0 ; i < N; i++ ){
        printf("%s\n", arr[i].word);
    }
}
