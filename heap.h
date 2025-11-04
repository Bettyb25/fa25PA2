//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        data[size] = idx;
        upheap(size,weightArr);
        size++;
    }
    // Remove and return the index with the smallest weight

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if(size == 0)
            return -1;
        int minIdx = data[0];
        // Replace root with last element
        data[0] = data[size -1];
        // Update heap size
        size --;
        downheap(0, weightArr);
        // Return the smallest index
        return minIdx;
    }
    // Move a node upward while it’s smaller than its parent
    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            // if child < parent swap them
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                swap(data[pos], data[parent]);
                pos = parent;
            } else {
                // Stop when parent is smaller
                break;
            }
        }
    }
    // Move a node downward while it’s larger than either child
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int left = 2 * pos + 1;
            int right = 2 * pos + 2;
            int smallest = pos;
            // Compare with left child
            if (left < size && weightArr[data[left]] < weightArr[data[smallest]])
                smallest = left;
            // Compare with right child

            if (right < size && weightArr[data[right]] < weightArr[data[smallest]])
                smallest = right;
            // If a smaller child is found swap and continue
            if (smallest != pos) {
                swap(data[pos], data[smallest]);
                pos = smallest;
            } else {
                break;
            }
        }
    }

};

#endif