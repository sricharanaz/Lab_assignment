//Huffman Coding
#include <stdio.h>
#include <stdlib.h>
 
#define height 100
 
struct basnode {
    char data;
    unsigned freq;
    struct basnode *left, *right;
};
 
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct basnode** array;
};
 
struct basnode* newNode(char data, unsigned freq)
{
    struct basnode* temp = (struct basnode*)malloc(
        sizeof(struct basnode));
 
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
 
    return temp;
}
 
struct MinHeap* createMinHeap(unsigned capacity)
 
{
    struct MinHeap* minHeap
        = (struct MinHeap*)malloc(sizeof(struct MinHeap));
 
    minHeap->size = 0;
 
    minHeap->capacity = capacity;
 
    minHeap->array = (struct basnode**)malloc(
        minHeap->capacity * sizeof(struct basnode*));
    return minHeap;
}
 
void swapbasnode(struct basnode** a,
                     struct basnode** b)
 
{
    struct basnode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap* minHeap, int idx)
{
 
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < minHeap->size
        && minHeap->array[left]->freq
               < minHeap->array[smallest]->freq)
        smallest = left;
 
    if (right < minHeap->size
        && minHeap->array[right]->freq
               < minHeap->array[smallest]->freq)
        smallest = right;
 
    if (smallest != idx) {
        swapbasnode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
 
int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}
 
struct basnode* extractMin(struct MinHeap* minHeap)
 
{
    struct basnode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return temp;
}
 
void insertMinHeap(struct MinHeap* minHeap,
                   struct basnode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
 
    while (i
           && minHeapNode->freq
                  < minHeap->array[(i - 1) / 2]->freq) {
 
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
 
    minHeap->array[i] = minHeapNode;
}
 
void buildMinHeap(struct MinHeap* minHeap)
 
{
    int n = minHeap->size - 1;
    int i;
 
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
 
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
 
    printf("\n");
}
 
int isLeaf(struct basnode* root)
 
{
    return !(root->left) && !(root->right);
}
 
struct MinHeap* createAndBuildMinHeap(char data[],
                                      int freq[], int size)
 
{
 
    struct MinHeap* minHeap = createMinHeap(size);
 
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
 
    minHeap->size = size;
    buildMinHeap(minHeap);
 
    return minHeap;
}
 
struct basnode* huffmanntree(char data[],
                                     int freq[], int size)
 
{
    struct basnode *left, *right, *top;
 
    struct MinHeap* minHeap
        = createAndBuildMinHeap(data, freq, size);
 
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
 
        top = newNode('$', left->freq + right->freq);
 
        top->left = left;
        top->right = right;
 
        insertMinHeap(minHeap, top);
    }
 
    return extractMin(minHeap);
}
 
void printCodes(struct basnode* root, int arr[],
                int top)
 
{
    if (root->left) {
 
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
 
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
 
    if (isLeaf(root)) {
 
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}
 
void huffmann(char data[], int freq[], int size)
 
{
    struct basnode* root
        = huffmanntree(data, freq, size);
 
    int arr[height], top = 0;
 
    printCodes(root, arr, top);
}
 
int main()
{
 
    char arr[] = { 'x', 'y', 'z', 'a', 'b', 'c' };
    int freq[] = { 10, 19, 22, 23, 26, 59 };
 
    int size = sizeof(arr) / sizeof(arr[0]);
 
    huffmann(arr, freq, size);
 
    return 0;
}
