#include "Huffman.h"

Node::Node(char ch, int freq, Node* left, Node* right) {
	m_ch = ch;
	m_freq = freq;
	m_left = left;
	m_right = right;
}

Node::Node(const Node& other) {
	m_ch = other.getChar();
	m_freq = other.getFreq();
	if (other.m_left != nullptr)
		m_left = new Node(*other.m_left);
	else
		m_left = nullptr;

	if (other.m_right != nullptr)
		m_right = new Node(*other.m_right);
	else
		m_right = nullptr;
}

Node::~Node() {
	if (m_left != nullptr)
		delete m_left;
	if (m_right != nullptr)
		delete m_right;
}

char Node::getChar() const {
	return m_ch;
}

int Node::getFreq() const {
	return m_freq;
}

bool Node::isLeaf() const {
	return !(m_left || m_right);
}

Node* Node::getRight() const {
	return m_right;
}

Node* Node::getLeft() const {
	return m_left;
}

void Node::setFreq(int newFreq) {
	m_freq = newFreq;
}

void Node::print(int i)
{
	std::cout << std::setfill('\t') << std::setw(i) << " ";
	isLeaf() ? std::cout <<  m_ch : std::cout << "IN";
	std::cout << "|" << m_freq << "\n";
	std::cout << std::setfill(' ');
	if (m_left != nullptr)
		m_left->print(i + 1);
	if (m_right != nullptr)
		m_right->print(i + 1);
}

HuffmanTree::HuffmanTree() {
	isHeap = false;
}

HuffmanTree::~HuffmanTree() {
	clear();
}

void HuffmanTree::clear() {
	codeMap.clear();
	int size = (int)forest.size();
	for (int i = 0; i < size; i++) {
		if (forest[i]) {
			delete forest[i];
			forest[i] = 0;
		}
	}
	forest.clear(); 
	isHeap = false;
}

std::string HuffmanTree::encodeData(std::string data) {
	clear(); 
	std::ostringstream oss;
	int size = (int)data.size();
	for (int i = 0; i < size; i++)
		add(data[i]);
	generateCodeMap();
	
	for (int i = 0; i < size; i++) 
		oss << encode(data[i]) << DELIM;

	return oss.str();
}

std::string HuffmanTree::decodeData(std::string data) {
	std::ostringstream oss;
	int size = (int)data.size();
	for (int i = 0; i < size; i++) {
		std::string code = "";
		char sym = 0;
		while (i < size && data[i] != DELIM) {
			code.push_back(data[i]);
			i++;
		}
		sym = decode(code);
		oss << sym;
	}
	return oss.str();
}

std::string HuffmanTree::encode(char key) {
	return codeMap[key];
}

char HuffmanTree::decode(std::string code) {
	char c = 0;
	int size = (int)forest.size();
	if (isHeap && size > 0)
		c = decode(forest[0], code);
	return c;
}

char HuffmanTree::decode(Node* root, std::string code) {
	char c = 0;
	int size = (int)code.size();
	if (root && size >= 0) {
		if (size == 0 && root->isLeaf())
			return root->getChar();
		else
		{
			char d = code[0];
			code.erase(code.begin());
			if (d == '0')
				c = decode(root->getLeft(), code);
			else if (d == '1')
				c = decode(root->getRight(), code);
		}
	}
	return c;
}
void HuffmanTree::generateCodeMap() {
	heapify();	
	if (forest.size() > 0)
		encode(forest[0], "");
}

void HuffmanTree::encode(Node* root, std::string code) {
	if (root) {
		if (root->isLeaf())codeMap[root->getChar()] = code;
		std::string cL = code;
		std::string cR = code;
		cL.push_back('0');
		cR.push_back('1');
		encode(root->getLeft(), cL);
		encode(root->getRight(), cR);
	}
}
void HuffmanTree::print() {
	std::cout << "#Code Table\n| Sym | Code    |\n| --- | ------- |\n";
	std::map<char, std::string>::iterator it = codeMap.begin();
	while (it != codeMap.end()) {
		std::cout << "| " << std::setw(3) << it->first << " | " << std::setw(7) << (it->second) << " |\n";
		++it;
	}
}
void HuffmanTree::printForest() {
	int size = (int)forest.size();
	for (int i = 0; i < size; i++) {
		std::cout << i << ":";
		if (forest[i])forest[i]->print();
		std::cout << std::endl;
	}
}

void HuffmanTree::add(char c, int freq) {
	if (isHeap) return;
	Node* node = nullptr;
	int i = 0;
	int size = (int)forest.size();
	while (i < size && !node)
	{
		if (forest[i] && forest[i]->getChar() == c)
			node = forest[i];
		else
			i++;
	}
	if (node)
		node->setFreq(node->getFreq() + freq);
	else
		forest.push_back(new Node(c, freq));
}

void HuffmanTree::add(Node* node) {
	if (isHeap) return;
	if (node)forest.push_back(node);
}

void HuffmanTree::heapify() {
	while (forest.size() >= 2) {
		Node* minB = popMin();
		Node* minA = popMin();
		Node* internal = HuffmanTree::merge(minA, minB);
		add(internal);
		minA = minB = 0;
	}
	isHeap = true;
}

Node* HuffmanTree::merge(Node* left, Node* right) {
	if (left && right)
		return new Node(0, left->getFreq() + right->getFreq(), left, right);
	else
		return 0;
}

Node* HuffmanTree::popMin() {
	int size = (int)forest.size();
	if (size <= 0)
		return 0;
	int i = 0;
	for (int j = 0; j < size; j++)
	{
		if (forest[i]->getFreq() > forest[j]->getFreq())
			i = j;
	}
	Node* n = forest[i];

	forest.erase(forest.begin() + i);
	return n;
}