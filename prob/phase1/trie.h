#include <bits/stdc++.h> 
using namespace std; 

struct TrieNode { 

	// pointer array for child nodes of each node 
	TrieNode* childNode[26]; 
	int wordCount; 

	TrieNode() 
	{ 
		// constructor 
		// initialize the wordCnt variable with 0 
		// initialize every index of childNode array with 
		// NULL 
		wordCount = -1; 
		for (int i = 0; i < 26; i++) { 
			childNode[i] = NULL; 
		} 
	} 
}; 

void insert_key(TrieNode* root, string& key, int val) 
{ 
	// Initialize the currentNode pointer 
	// with the root node 
	TrieNode* currentNode = root; 

	// Iterate across the length of the string 
	for (auto c : key) { 

		// Check if the node exist for the current 
		// character in the Trie. 
        int b = c - 'A';
        if (b > 26) b = b - 32;
		if (currentNode->childNode[b] == NULL) { 

			// If node for current character does not exist 
			// then make a new node 
			TrieNode* newNode = new TrieNode(); 

			// Keep the reference for the newly created 
			// node. 
			currentNode->childNode[b] = newNode; 
		} 

		// Now, move the current node pointer to the newly 
		// created node. 
		currentNode = currentNode->childNode[b]; 
	} 

	// Increment the wordEndCount for the last currentNode 
	// pointer this implies that there is a string ending at 
	// currentNode. 
	currentNode->wordCount = val; 
} 

int search_key(TrieNode* root, string& key) 
{ 
	// Initialize the currentNode pointer 
	// with the root node 
	TrieNode* currentNode = root; 

	// Iterate across the length of the string 
	for (auto c : key) { 

        int b = c - 'A';
        if (b > 26) b = b - 32;

		// Check if the node exist for the current 
		// character in the Trie. 
		if (currentNode->childNode[b] == NULL) { 

			// Given word does not exist in Trie 
			return -1; 
		} 

		// Move the currentNode pointer to the already 
		// existing node for current character. 
		currentNode = currentNode->childNode[b]; 
	} 

	return currentNode->wordCount; 
}