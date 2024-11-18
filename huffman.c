#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define alpha 26

typedef struct HuffNode {
    char ascii;
    int freq;
    struct HuffNode* left;
    struct HuffNode* right;    
} HuffNode;

HuffNode* makeNode(){
    HuffNode* newNode = (HuffNode*)malloc(sizeof(HuffNode));
    newNode->ascii = '\0';
    newNode->freq = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void encoding(HuffNode* current, char* str, int level, char* encode[]){

    if(current->left != NULL){
        str[level] = '1';
        encoding(current->left, str, level+1, encode);
    }
    if(current->right != NULL){
        str[level] = '0';
        encoding(current->right, str, level+1, encode);
    }
    // leaf node일 경우
    if(!current->left && !current->right){
        str[level] = '\0';
        // 현재까지 encoding한 문자열 str을, encode 문자열 배열에 삽입
        // 이때 삽입되는 배열의 인덱스(원소)는 0이 A, 25가 Z인 문자열 배열이다.
        strcpy(encode[(current->ascii)-'A'], str);

        // encode[(current->ascii)-'A'] = str; <- 이렇게 하면?
    }
}

void decoding(HuffNode* root, char* encode, char* decode){
    
    int index=0;
    HuffNode* current = root;  // 나중에 원본으로 돌아오기 위해서 root를 보존
    for(int i=0; i<strlen(encode); i++){
        if(encode[i]=='1'){
            current = current->left;
        } else if (encode[i]=='0'){
            current = current->right;
        }

        if(!current->left && !current->right){
            decode[index++] = current->ascii;   // '=' 연산자가 안전한가?
            current = root;
        }
    }
    decode[index]='\0';
    
}


HuffNode* makeHuffmanTree(char* line){

    // 1. 각 문자별 빈도수 구하기
    HuffNode* arrayHuff[alpha] = {NULL}; // 모든 원소를 NULL로 초기화
    int count = 0; // 문자 종류 갯수, 즉 arrayHuff의 유효 원소 갯수 저장 정수
    
    // 각 문자에 해당하는 인덱스에 Node를 생성하고 빈도수를 증가시킴
    for(int i=0; i<strlen(line); i++){

        int index = line[i]-'A';

        if(arrayHuff[index] != NULL) {  // 존재할 경우 빈도수 증가

            arrayHuff[index]->freq++;

        } else {    // node가 존재하지 않을 경우 (지금까지 문자열에서 안나온 문자) 새로 Node를 생성

            arrayHuff[index] = makeNode();
            arrayHuff[index]->freq = 1;
            arrayHuff[index]->ascii = line[i];
            count++;
        }
    }

    int lastNodeIndex = 0; // 아래의 반복문을 거쳐 최종적으로 남은 노드의 인덱스를 저장

    // 4. 아래의 과정을 arrayHuff 배열의 원소가 하나 남을 때까지 반복
    while(count>1){
        count--;    // 아래의 과정을 거치면 배열의 원소가 하나 줄어들 것이므로

        // 2. 빈도수가 가장 작은 수를 찾고 그 다음 두번째로 작은 수를 찾기
        int min = 0;    // 가장 빈도수가 작은 index와 그 빈도수
        int minFreq = 0;
        int min2 = 0;   // 두번째로 빈도수가 작은 index와 그 빈도수
        int minFreq2 = 0;

        for(int i=0; i<alpha; i++) {
            
            if(arrayHuff[i] != NULL) { // 존재하는 문자에 대해서만 빈도수 찾기 진행

                if(minFreq == 0) {
                    minFreq = arrayHuff[i]->freq;
                    min = i;
                } else if (minFreq2 == 0){
                    minFreq2 = arrayHuff[i]->freq;
                    min2 = i;

                    if(minFreq > minFreq2) { // minFreq2에 더 작은 값이 저장된 경우 minFreq에 더 작은 값이 저장되도록 교환
                        int temp = minFreq2;
                        minFreq2 = minFreq;
                        minFreq = temp;

                        temp = min2;
                        min2 = min;
                        min = temp;
                    }
                } else {
                    // 가장 작은 값인 minFreq와 같거나 더 작을 경우
                    if(minFreq >= arrayHuff[i]->freq){
                        // 가장 작은 것을 발견했으므로 min이 가지고 있는 값은 자연스레 두번재로 작은 값이 됨
                        minFreq2 = minFreq;
                        min2 = min;
                        
                        minFreq = arrayHuff[i]->freq;
                        min = i;
                    }
                }
            }
        }

        // 3. 빈도수가 가장 낮은 두 개를 합쳐 중간노드로 생성
        HuffNode* internalNode = makeNode();    // 중간 노드 생성
        internalNode->freq = minFreq + minFreq2;    // 중간 노드에 저장된 freq는 두 노드의 freq의 합

        // 빈도수를 내림차순 기준으로 정렬시, 가장 낮은 것은 오른쪽이므로 min이 right, min2가 left
        internalNode->right = arrayHuff[min];
        internalNode->left = arrayHuff[min2];

        // 중간 노드는 가장 낮은 값이 있었던 구조체 배열 인덱스에 할당, 나머지는 NULL로 연결을 끊음
        arrayHuff[min] = internalNode;
        arrayHuff[min2] = NULL;
        lastNodeIndex = min;
    }

    // arrayHuff는 동적할당을 안했지만, 안에 존재하는 노드들은 모두 동적할당된 것이므로 이 함수가 종료되도 유지되지 않을까?
    return arrayHuff[lastNodeIndex]; 
    
}

int main() {
    char* line;         // 원본 문자열
    char* code[alpha];     // 각 알파벳별 이진코드 저장 배열
    char encode[1024] = "";  // 알파벳 -> 이진 코드 문자열로 저장 : 수정을 위해 배열로 선언함 <- 포인터로 선언할 시 참조할 뿐이므로 원본을 수정하지 못함
    char decode[256] = "";  // 이진코드 -> 알파벳 문자열로 저장 : 이 역시 수정을 위해 배열로 선언 <- decoding 함수에서 decode[] = ascii 부분이 존재하기 때문

    HuffNode* root;     // 호프만 부호화 트리 저장 root

    // 동적할당 하고 안하고의 차이? 
    for(int i=0; i<alpha; i++){
        code[i] = (char*)calloc(1, sizeof(char));
    }

    // 입력할 문자열
    line = "AAABBBBCCD";

    root = makeHuffmanTree(line); // 호프만 부호화 트리 생성

    // NULL로 초기화할 경우, str에 새로 할당하지 않는 이상 접근 오류 발생, \0 은 널값이라는 문자 리터럴을 가진 것
    // 포인터가 아닌 배열로 선언한 이유는 encoding에서 str의 원소 접근해 0 또는 1을 할당해야 하기 때문
    char str[10]="";   
    encoding(root, str, 0, code);  // code에 각 알파벳 별 이진코드 저장

    printf("호프만 부호화 트리 결과 : \n");
    for(int i=0; i<alpha; i++){
        if(code[i]!=0) {
            printf("'%c' : %s\n", i+'A', code[i]);
        }
    }



    printf("부호화 : ");
    // 입력받은 문자열을 code를 참조해 이진 코드로 부호화
    for(int i=0; line[i] != '\0'; i++){
        // strcat을 사용해 encode 문자열에 이진코드 복사, 복사된 문자열 뒤에 자동으로 널 문자가 붙음
        strcat(encode, code[line[i] - 'A']);
        printf("%s ",code[line[i] - 'A']);
    }
    printf("\n");


    printf("복호화 : ");
    decoding(root, encode, decode);
    printf("%s \n", decode);
    return 0;
}
