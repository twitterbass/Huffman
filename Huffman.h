#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <iomanip>
#include <map> 
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <iterator>

#define DELIM ' '

class Node {
public:
	Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr);
	Node(const Node& other);
	~Node();
	void  setFreq(int newFreq);
	char getChar() const;
	bool isLeaf() const;
	int getFreq() const;
	Node* getRight()const;
	Node* getLeft()const;
	void print(int i = 0);
private:
	char m_ch;
	int m_freq; 
	Node* m_left;
	Node* m_right; 
};


class HuffmanTree {
public:
	HuffmanTree();
	~HuffmanTree();
	std::string decodeData(std::string data);
	std::string encodeData(std::string data);
	void print();
	void printForest();
	void clear();

protected:
	void add(char ch, int freq = 1);
	void add(Node* pNode);
	void generateCodeMap();
	char decode(std::string code);
	std::string encode(char key);
	char decode(Node* root, std::string code);
	void encode(Node* root, std::string code);
	void heapify();
	Node* popMin(); 
	static Node* merge(Node* left, Node* right);

private:
	bool isHeap;
	std::map<char, std::string> codeMap;  
	std::vector<Node*> forest;
};

#endif 
