#ifndef HUFFMAN_BINARAY_TREE
#define HUFFMAN_BINARAY_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define alpha 53

typedef struct HuffNode {
    char ascii;
    int freq;
    struct HuffNode* left;
    struct HuffNode* right;    
} HuffNode;

HuffNode* MakeNode();
int AsciiCheck(char);
void Encoding(HuffNode*, char*, int, char* []);
void Decoding(HuffNode*, char*, char*);
int Compare(const void*, const void*);
HuffNode* MakeHuffmanTree(char*);
void BinaryCodeFree(char* []);
void HuffTreeFree(HuffNode*);
void HuffmanEncodeDecode(char*);


#endif