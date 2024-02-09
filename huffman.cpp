#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency, Node *l = nullptr, Node *r = nullptr)
        : ch(character), freq(frequency), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void encode(Node* root, string str, map<char, string> &huffmanCode) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str.length() > 0 ? str : "1";
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

int calculateFixedLengthBits(int uniqueChars) {
    return uniqueChars * 8; // Assuming 8 bits per character for fixed-length encoding
}

int calculateVariableLengthBits(const string &text, const map<char, string> &huffmanCode) {
    int totalBits = 0;
    for (char ch : text) {
        totalBits += huffmanCode.at(ch).length();
    }
    return totalBits;
}

int main() {
    string text ={};
    cout << "Enter the text: ";
    cin >> text;
    map<char, int> freq;

    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    Node* root = pq.top();

    map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Character\tFrequency\tHuffman Code\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << "\t\t" << freq[pair.first] << "\t\t" << pair.second << "\n";
    }

    int fixedBits = calculateFixedLengthBits(freq.size()) * text.length();
    int variableBits = calculateVariableLengthBits(text, huffmanCode);

    cout << "Total bits required (Fixed-length encoding): " << fixedBits << " bits\n";
    cout << "Total bits required (Variable-length encoding): " << variableBits << " bits\n";

    return 0;
}
