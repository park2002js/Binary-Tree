#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define alpha 53

#include "huffman.h"

HuffNode* MakeNode(){
    HuffNode* newNode = (HuffNode*)malloc(sizeof(HuffNode));
    newNode->ascii = '\0';
    newNode->freq = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// a~z -> 0~25, A~Z -> 26~51, space -> 52
int AsciiCheck(char ch) {
    if(ch == ' ') {
        return 52;
    }

    if(ch >= 65 && ch <= 90) {
        return ((int)ch-39);
    }

    if(ch >= 97 && ch <= 122) {
        return ((int)ch-97);
    }
    return -1;
}

void Encoding(HuffNode* current, char* str, int level, char* binary[]){

    // left is higher freq, and '1'
    if(current->left != NULL){
        str[level] = '1';
        Encoding(current->left, str, level+1, binary);
    }

    // right is lower freq, and '0'
    if(current->right != NULL){
        str[level] = '0';
        Encoding(current->right, str, level+1, binary);
    }

    // leaf node
    if(!current->left && !current->right){
        str[level] = '\0';
        int index = AsciiCheck(current->ascii);
        binary[index] = (char*)malloc(sizeof(char)*(strlen(str)+1));
        strcpy(binary[index], str);
    }
}

void Decoding(HuffNode* root, char* encode, char* decode){
    
    int index=0;
    HuffNode* current = root;

    for(int i=0; i<strlen(encode); i++){
        if(encode[i]=='1'){
            current = current->left;
        } else if (encode[i]=='0'){
            current = current->right;
        }

        if(!current->left && !current->right){
            decode[index++] = current->ascii;
            current = root;
        }
    }
    decode[index]='\0';
    
}

int Compare(const void* a, const void* b) {

    const HuffNode* nodeA = *(const HuffNode**)a;
    const HuffNode* nodeB = *(const HuffNode**)b;

    if (nodeA == NULL) { 
        return 1;
    }
    if (nodeB == NULL) {
        return -1;
    }

    if (nodeA->freq > nodeB->freq) {
        return -1;

    } else if (nodeA->freq < nodeB->freq) {
        return 1;

    } else {
        return 0;
    }
}

HuffNode* MakeHuffmanTree(char* line){

    HuffNode* arrayHuff[alpha] = {NULL};
    int countNode = 0;
    
    // make nodes and set Frequency
    for(int i=0; i<strlen(line); i++){

        int index = AsciiCheck(line[i]);

        if(arrayHuff[index] != NULL) { 

            arrayHuff[index]->freq++;

        } else {

            arrayHuff[index] = MakeNode();
            arrayHuff[index]->freq = 1;
            arrayHuff[index]->ascii = line[i];
            countNode++;
        }
    }
    
    // create an internalnode until only one node remaines
    int lastNodeIndex = 0;
    int min = 0, minFreq = 0;
    int min2 = 0, minFreq2 = 0;
    while(countNode>1){
        countNode--;

        // quicksort for freq in descending order
        qsort(arrayHuff, alpha, sizeof(HuffNode*), Compare);

        // allocate the two lowest frequency
        min = countNode;
        min2 = countNode-1;
        minFreq = arrayHuff[min]->freq;
        minFreq2 = arrayHuff[min2]->freq;

        // create internalnode by merging the two lowest freq nodes
        HuffNode* internalNode = MakeNode();
        internalNode->freq = minFreq + minFreq2;

        internalNode->right = arrayHuff[min];
        internalNode->left = arrayHuff[min2];

        arrayHuff[min] = internalNode;
        arrayHuff[min2] = NULL;

        lastNodeIndex = min;
    }

    return arrayHuff[lastNodeIndex]; 
}

void BinaryCodeFree(char* code[alpha]){
    for(int i=0; i<alpha; i++){
        if(code[i]!=NULL) {
            free(code[i]);
        }
    }
}

void HuffTreeFree(HuffNode* root){

    if (root == NULL) return;

    HuffTreeFree(root->left);
    HuffTreeFree(root->right);

    free(root);
}

void HuffmanEncodeDecode(char* line) {

    printf("origin string : %s\n", line);
    printf("-----------------------------\n");

    char* code[alpha] = {NULL};
    char encode[1024] = "";
    char decode[256] = "";

    // make huffman binary tree
    HuffNode* root;
    root = MakeHuffmanTree(line);

    // get binary code from huffman tree
    char str[10]="";   
    Encoding(root, str, 0, code);

    printf("result of huffman binary tree : \n");
    for(int i=0; i<alpha; i++){
        if(code[i]!=NULL) {
            if(i < 26) {
                printf("'%c' : ", i+97);
            } else if ( i < 52) {
                printf("'%c' : ", i+39);
            } else {
                printf("' ' : ");
            }
                
            printf("%s\n", code[i]);
        }
    }
    printf("-----------------------------\n");

    // Encoding
    printf("Encoding : ");
    for(int i=0; line[i] != '\0'; i++){
        strcat(encode, code[AsciiCheck(line[i])]);
        printf("%s ",code[AsciiCheck(line[i])]);
    }
    printf("\n");

    // Decoding
    printf("Decoding : ");
    Decoding(root, encode, decode);
    printf("%s \n", decode);

    BinaryCodeFree(code);
    HuffTreeFree(root);
}