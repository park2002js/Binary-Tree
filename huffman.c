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
    // leaf node�� ���
    if(!current->left && !current->right){
        str[level] = '\0';
        // ������� encoding�� ���ڿ� str��, encode ���ڿ� �迭�� ����
        // �̶� ���ԵǴ� �迭�� �ε���(����)�� 0�� A, 25�� Z�� ���ڿ� �迭�̴�.
        strcpy(encode[(current->ascii)-'A'], str);

        // encode[(current->ascii)-'A'] = str; <- �̷��� �ϸ�?
    }
}

void decoding(HuffNode* root, char* encode, char* decode){
    
    int index=0;
    HuffNode* current = root;  // ���߿� �������� ���ƿ��� ���ؼ� root�� ����
    for(int i=0; i<strlen(encode); i++){
        if(encode[i]=='1'){
            current = current->left;
        } else if (encode[i]=='0'){
            current = current->right;
        }

        if(!current->left && !current->right){
            decode[index++] = current->ascii;   // '=' �����ڰ� �����Ѱ�?
            current = root;
        }
    }
    decode[index]='\0';
    
}


HuffNode* makeHuffmanTree(char* line){

    // 1. �� ���ں� �󵵼� ���ϱ�
    HuffNode* arrayHuff[alpha] = {NULL}; // ��� ���Ҹ� NULL�� �ʱ�ȭ
    int count = 0; // ���� ���� ����, �� arrayHuff�� ��ȿ ���� ���� ���� ����
    
    // �� ���ڿ� �ش��ϴ� �ε����� Node�� �����ϰ� �󵵼��� ������Ŵ
    for(int i=0; i<strlen(line); i++){

        int index = line[i]-'A';

        if(arrayHuff[index] != NULL) {  // ������ ��� �󵵼� ����

            arrayHuff[index]->freq++;

        } else {    // node�� �������� ���� ��� (���ݱ��� ���ڿ����� �ȳ��� ����) ���� Node�� ����

            arrayHuff[index] = makeNode();
            arrayHuff[index]->freq = 1;
            arrayHuff[index]->ascii = line[i];
            count++;
        }
    }

    int lastNodeIndex = 0; // �Ʒ��� �ݺ����� ���� ���������� ���� ����� �ε����� ����

    // 4. �Ʒ��� ������ arrayHuff �迭�� ���Ұ� �ϳ� ���� ������ �ݺ�
    while(count>1){
        count--;    // �Ʒ��� ������ ��ġ�� �迭�� ���Ұ� �ϳ� �پ�� ���̹Ƿ�

        // 2. �󵵼��� ���� ���� ���� ã�� �� ���� �ι�°�� ���� ���� ã��
        int min = 0;    // ���� �󵵼��� ���� index�� �� �󵵼�
        int minFreq = 0;
        int min2 = 0;   // �ι�°�� �󵵼��� ���� index�� �� �󵵼�
        int minFreq2 = 0;

        for(int i=0; i<alpha; i++) {
            
            if(arrayHuff[i] != NULL) { // �����ϴ� ���ڿ� ���ؼ��� �󵵼� ã�� ����

                if(minFreq == 0) {
                    minFreq = arrayHuff[i]->freq;
                    min = i;
                } else if (minFreq2 == 0){
                    minFreq2 = arrayHuff[i]->freq;
                    min2 = i;

                    if(minFreq > minFreq2) { // minFreq2�� �� ���� ���� ����� ��� minFreq�� �� ���� ���� ����ǵ��� ��ȯ
                        int temp = minFreq2;
                        minFreq2 = minFreq;
                        minFreq = temp;

                        temp = min2;
                        min2 = min;
                        min = temp;
                    }
                } else {
                    if(minFreq > arrayHuff[i]->freq){
                        // ���� ���� ���� �߰������Ƿ� min�� ������ �ִ� ���� �ڿ����� �ι���� ���� ���� ��
                        minFreq2 = minFreq;
                        min2 = min;
                        
                        minFreq = arrayHuff[i]->freq;
                        min = i;
                    }
                }
            }
        }

        // 3. �󵵼��� ���� ���� �� ���� ���� �߰����� ����
        HuffNode* internalNode = makeNode();    // �߰� ��� ����
        internalNode->freq = minFreq + minFreq2;    // �߰� ��忡 ����� freq�� �� ����� freq�� ��

        // �󵵼��� �������� �������� ���Ľ�, ���� ���� ���� �������̹Ƿ� min�� right, min2�� left
        internalNode->right = arrayHuff[min];
        internalNode->left = arrayHuff[min2];

        // �߰� ���� ���� ���� ���� �־��� ����ü �迭 �ε����� �Ҵ�, �������� NULL�� ������ ����
        arrayHuff[min] = internalNode;
        arrayHuff[min2] = NULL;
        lastNodeIndex = min;
    }

    // arrayHuff�� �����Ҵ��� ��������, �ȿ� �����ϴ� ������ ��� �����Ҵ�� ���̹Ƿ� �� �Լ��� ����ǵ� �������� ������?
    return arrayHuff[lastNodeIndex]; 
    
}

int main() {
    char* line;         // ���� ���ڿ�
    char* code[alpha];     // �� ���ĺ��� �����ڵ� ���� �迭
    char encode[1024] = "";  // ���ĺ� -> ���� �ڵ� ���ڿ��� ���� : ������ ���� �迭�� ������ <- �����ͷ� ������ �� ������ ���̹Ƿ� ������ �������� ����
    char decode[256] = "";  // �����ڵ� -> ���ĺ� ���ڿ��� ���� : �� ���� ������ ���� �迭�� ���� <- decoding �Լ����� decode[] = ascii �κ��� �����ϱ� ����

    HuffNode* root;     // ȣ���� ��ȣȭ Ʈ�� ���� root

    // �����Ҵ� �ϰ� ���ϰ��� ����? 
    for(int i=0; i<alpha; i++){
        code[i] = (char*)calloc(1, sizeof(char));
    }

    // �Է��� ���ڿ�
    line = "AAABBBBCCD";

    root = makeHuffmanTree(line); // ȣ���� ��ȣȭ Ʈ�� ����

    // NULL�� �ʱ�ȭ�� ���, str�� ���� �Ҵ����� �ʴ� �̻� ���� ���� �߻�, \0 �� �ΰ��̶�� ���� ���ͷ��� ���� ��
    // �����Ͱ� �ƴ� �迭�� ������ ������ encoding���� str�� ���� ������ 0 �Ǵ� 1�� �Ҵ��ؾ� �ϱ� ����
    char str[10]="";   
    encoding(root, str, 0, code);  // code�� �� ���ĺ� �� �����ڵ� ����

    printf("ȣ���� ��ȣȭ Ʈ�� ��� : \n");
    for(int i=0; i<alpha; i++){
        if(code[i]!=0) {
            printf("'%c' : %s\n", i+'A', code[i]);
        }
    }



    printf("��ȣȭ : ");
    // �Է¹��� ���ڿ��� code�� ������ ���� �ڵ�� ��ȣȭ
    for(int i=0; line[i] != '\0'; i++){
        // strcat�� ����� encode ���ڿ��� �����ڵ� ����, ����� ���ڿ� �ڿ� �ڵ����� �� ���ڰ� ����
        strcat(encode, code[line[i] - 'A']);
        printf("%s ",code[line[i] - 'A']);
    }
    printf("\n");


    printf("��ȣȭ : ");
    decoding(root, encode, decode);
    printf("%s \n", decode);
    return 0;
}