/*
Aim of the program: Huffman coding assigns variable length code words to fixed length input characters based on their frequencies or probabilities of occurrence. Given a set of characters along with their frequency of occurrences, write a c program to construct a Huffman tree.
Note#
● Declare a structure SYMBOL having members alphabet and frequency. Create a Min-Priority Queue, keyed on frequency attributes.
● Create an array of structures where size=number of alphabets.
Input:
Enter the number of distinct alphabets: 6
Enter the alphabets: ​a ​b ​c ​d ​e ​f
Enter its frequencies: ​45 ​13 ​12 ​16 ​9 ​5
Output:
In-order traversal of the tree (Huffman): a c b f e d
*/

#include<stdio.h>
#include<stdlib.h>

struct SYMBOL
{
    char alphabet;
    int frequency;
};

struct MinHeapNode
{
    struct SYMBOL symbol;
    struct MinHeapNode *left, *right;
};

struct MinHeap
{
    int size;
    struct MinHeapNode **array;
};

struct MinHeapNode* createNode(struct SYMBOL symbol)
{
    struct MinHeapNode* newNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    newNode->symbol = symbol;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* newNode)
{
    minHeap->array[minHeap->size] = newNode;
    minHeap->size++;

    // Min-Heapify
    int i = minHeap->size - 1;
    while (i && minHeap->array[i]->symbol.frequency < minHeap->array[(i - 1) / 2]->symbol.frequency)
    {
        struct MinHeapNode* temp = minHeap->array[i];
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        minHeap->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (minHeap->size == 0)
        return NULL;

    struct MinHeapNode* root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;

    // Min-Heapify
    int i = 0;
    while (i < minHeap->size)
    {
        int smallest = i;
        if (2 * i + 1 < minHeap->size && minHeap->array[2 * i + 1]->symbol.frequency < minHeap->array[smallest]->symbol.frequency)
            smallest = 2 * i + 1;
        if (2 * i + 2 < minHeap->size && minHeap->array[2 * i + 2]->symbol.frequency < minHeap->array[smallest]->symbol.frequency)
            smallest = 2 * i + 2;
        if (smallest == i)
            break;
        struct MinHeapNode* temp = minHeap->array[i];
        minHeap->array[i] = minHeap->array[smallest];
        minHeap->array[smallest] = temp;
        i = smallest;
    }

    return root;
}

void printInOrder(struct MinHeapNode* root)
{
    if (root)
    {
        printInOrder(root->left);
        printf("%c ", root->symbol.alphabet);
        printInOrder(root->right);
    }
}



int main()
{
    int n, i;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    struct SYMBOL* symbols = (struct SYMBOL*)malloc(n * sizeof(struct SYMBOL));
    for (i = 0; i < n; i++)
    {
        printf("Enter alphabet %d: ", i + 1);
        scanf(" %c", &symbols[i].alphabet);
        printf("Enter frequency of %c: ", symbols[i].alphabet);
        scanf("%d", &symbols[i].frequency);
    }

    struct MinHeap* minHeap = createMinHeap(n);
    for (i = 0; i < n; i++)
    {
        struct MinHeapNode* newNode = createNode(symbols[i]);
        insertMinHeap(minHeap, newNode);
    }

    while (minHeap->size > 1)
    {
        struct MinHeapNode* left = extractMin(minHeap);
        struct MinHeapNode* right = extractMin(minHeap);

        struct MinHeapNode* newNode = createNode((struct SYMBOL){'\0', left->symbol.frequency + right->symbol.frequency});
        newNode->left = left;
        newNode->right = right;
        insertMinHeap(minHeap, newNode);
    }

    printf("In-order traversal of the tree (Huffman): ");
    printInOrder(extractMin(minHeap));
    printf("\n");

    free(symbols);
    free(minHeap->array);
    free(minHeap);
    return 0;
}