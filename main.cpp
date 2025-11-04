//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
// until only one root node remains, representing the full tree.
int buildEncodingTree(int nextFree) {
    // TODO:
    MinHeap heap;
    for (int i = 0; i < nextFree; ++i)
        heap.push(i, weightArr);
    while (heap.size > 1) {
        // Pop two smallest nodes based on weight
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);
        // Create a new parent node combining their weights
        int parent = nextFree++;
        weightArr[parent] = weightArr[left] + weightArr[right];
        // Link children to the parent
        leftArr[parent] = left;
        rightArr[parent] = right;
        // Push the new parent back into the heap
        heap.push(parent, weightArr);
    }
    return heap.pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
// A stack is used to build 0 and 1 paths from the root to each leaf node.
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    stack<pair<int, string>> s;
    s.push({root, ""});
    while (!s.empty()) {
        auto [node, code] = s.top();
        s.pop();
        if (node == -1)
            continue;
        // If both children are -1, it's a leaf node so assign its code
        if (leftArr[node] == -1 && rightArr[node] == -1) {
                int letterIndex = charArr[node] - 'a';
                codes[letterIndex] = code;

        } else {
            // Traverse right child add 1 and left child add 0
            s.push({rightArr[node], code + "1"});
            s.push({leftArr[node], code + "0"});
        }
    }

}

// Step 5: Print table and encoded message
// Each letter is replaced by its corresponding binary code.
void encodeMessage(const string& filename, string codes[]) {
    // Print the character-to-code mapping
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }


    cout << "\nEncoded message:\n";


    ifstream file(filename);
    char ch;
    // Read each character and print its binary code
    while (file.get(ch)) {
        // uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        // Output code for each  letter
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();

}
