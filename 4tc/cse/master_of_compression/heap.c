/**
 * heap.c
 *
 * Utility functions to build and use a min heap.
 *
 * Author : Rémy Hidra
 *
 * 2018/2019
 */

#include "heap.h"

/**
 * new_node()
 * Create a new node for the tree.
 */
NODE* new_node(char symbol[], int freq) {
    NODE *node = (NODE*) malloc(sizeof(NODE));
    int i;
    for (i = 0; i < BYTES_PER_SYMBOL; i++) {
        node->symbol[i] = symbol[i];
    }
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * init_heap()
 * Initialize a new min heap using the data passed as parameter.
 */
HEAP* init_heap(char **data, int freq[], int size) {
    HEAP *heap = (HEAP*) malloc(sizeof(HEAP));
    heap->size = 0;
    heap->capacity = size;
    heap->nodes = (NODE**) malloc(sizeof(NODE*) * heap->capacity);

    int i;
    for (i = 0; i < size; i++) {
        heap->nodes[i] = new_node(data[i], freq[i]);
    }
    heap->size = size;

    for (i = (heap->size - 2) / 2; i >= 0; i--)
        heapify(heap, i);

    return heap;
}

/**
 * heapify()
 * Recursive function which keep the min heap coherent.
 */
void heapify(HEAP *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left]->freq < heap->nodes[smallest]->freq)
        smallest = left;
    if (right < heap->size && heap->nodes[right]->freq < heap->nodes[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        SWAP(&heap->nodes[smallest], &heap->nodes[idx]);
        heapify(heap, smallest);
    }
}

/**
 * extract()
 * Extract the first element of the heap (the minimal element).
 */
NODE* extract(HEAP *heap) {
    NODE *tmp = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return tmp;
}

/**
 * insert()
 * Insert a new node in the heap.
 */
void insert(HEAP *heap, NODE *node) {
    heap->size++;
    int i = heap->size - 1;

    while (i && node->freq < heap->nodes[(i-1) / 2]->freq) {
        heap->nodes[i] = heap->nodes[(i-1) / 2];
        i = (i-1) / 2;
    }
    heap->nodes[i] = node;
}

/**
 * height_tree()
 * Return the depth of the Huffman tree.
 */
int height_tree(NODE *tree) {
    if (tree == NULL)
        return 0;
    return MAX(height_tree(tree->left), height_tree(tree->right)) + 1;
}

/**
 * free_tree()
 * Free the memory allocated for the heap and the tree.
 */
void free_tree(NODE *tree) {
    if (tree->left != NULL)
        free_tree(tree->left);
    if (tree->right != NULL)
        free_tree(tree->right);
    free(tree);
}
