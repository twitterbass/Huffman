#include "Huffman.h"
using namespace std;

int main(int argc, char** argv)
{
	cout << "\nHuffman Tree"
		<< "\nencode - Prompts to encode new data string"
		<< "\ndecode - Decodes encoded string"
		<< "\nprint  - Prints code table\n"
		<< "\nexit  - Exits program\n";
	HuffmanTree h;
	string encodedData, decodedData, input;
	if (argc == 2)
		input = argv[1];

	do {
		cout << "->";
		getline(cin, input);
		if (input == "encode") {
			cout << "Data:";
			getline(cin, input);
			encodedData = h.encodeData(input);
			cout << "\nEncoded:\n" << encodedData << "\n";
		}
		else if (input == "decode") {
			decodedData = h.decodeData(encodedData);
			cout << "\nDecoded:\n" << decodedData << "\n";
		}
		else if (input == "print") {
			h.print();
			cout << "\n";
		}
	} while (input != "exit");
	return 0;
}
