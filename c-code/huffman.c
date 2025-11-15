#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100
#define MAX_CHAR 256

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapNodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;
    if (smallest != idx) {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* node) {
    minHeap->size++;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i-1)/2]->freq) {
        minHeap->array[i] = minHeap->array[(i-1)/2];
        i = (i-1)/2;
    }
    minHeap->array[i] = node;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n-1)/2; i >= 0; i--)
        minHeapify(minHeap, i);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; i++)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (minHeap->size > 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void storeCodes(struct MinHeapNode* root, int arr[], int top, char codes[MAX_CHAR][MAX_TREE_HT]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top+1, codes);
    }
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top+1, codes);
    }
    if (!root->left && !root->right) {
        for (int i=0; i<top; i++)
            codes[(unsigned char)root->data][i] = arr[i] + '0';
        codes[(unsigned char)root->data][top] = '\0';
    }
}

int calcFreq(char str[], char data[], int freq[]) {
    int count[MAX_CHAR] = {0};
    int n = strlen(str);
    for (int i=0; i<n; i++)
        count[(unsigned char)str[i]]++;
    int size = 0;
    for (int i=0; i<MAX_CHAR; i++) {
        if (count[i]) {
            data[size] = (char)i;
            freq[size] = count[i];
            size++;
        }
    }
    return size;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: No input string\n");
        return 1;
    }

    char* input = argv[1];
    char data[MAX_CHAR];
    int freq[MAX_CHAR];
    int size = calcFreq(input, data, freq);

    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    char codes[MAX_CHAR][MAX_TREE_HT];
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0, codes);

    // Print encoded string
    int n = strlen(input);
    for (int i=0; i<n; i++)
        printf("%s", codes[(unsigned char)input[i]]);

    // Print sizes
    int originalBits = n * 8;
    int encodedBits = 0;
    for (int i=0; i<n; i++)
        encodedBits += strlen(codes[(unsigned char)input[i]]);
    
    printf("__STATS__\nOriginal:%d\nEncoded:%d\n", originalBits, encodedBits);


    return 0;
}
