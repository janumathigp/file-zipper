#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

struct HuffmanNode{
    char ch; 
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f): ch(c), freq(f),left(nullptr),right(nullptr){}

};

struct Compare{
    bool operator()(HuffmanNode* l, HuffmanNode* r){
        return l->freq > r->freq;
    }

};

void buildFreqTable(const string& fileData,map<char,int>& freqTable){
    for(char ch: fileData){
        freqTable[ch] += 1;
    }   
}

HuffmanNode* buildHuffmanTree(const map<char,int>& freqTable){

    priority_queue<HuffmanNode*, vector<HuffmanNode*>,Compare> minHeap;

    for(const auto& pair: freqTable){
        minHeap.push(new HuffmanNode(pair.first,pair.second));
    }

    while(minHeap.size() > 1){
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top();minHeap.pop();

        HuffmanNode* top = new HuffmanNode('\0',left->freq+right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }
    return minHeap.top();
    
}

void generateHuffmanCodes(HuffmanNode* root, const string& str, map<char,string>& huffmanCodes){
    if(!root) return;

    if(root->ch != '\0'){
        huffmanCodes[root->ch] = str;
    }

    generateHuffmanCodes(root->left,str + "0",huffmanCodes);
    generateHuffmanCodes(root->right,str + "1",huffmanCodes);
}

string compressFile(const string& fileData,const map<char,string>& huffmanCodes){
    string encodedString;
    for(char ch: fileData){
        encodedString += huffmanCodes.at(ch);
    }

    cout<<"Encoded String: "<< encodedString<<endl;
    return encodedString;

    
}

void decompressFile(const string& encodedString, HuffmanNode* root){

    string decodedString;
    HuffmanNode* current = root;
    for(char bit: encodedString){
        if(bit=='0'){
            current = current->left;
        }
        else{
            current = current->right;
        }

        if(current->left == nullptr && current->right == nullptr){
            decodedString += current->ch;
            current = root;
        }

    }
        cout<<"Decompressed String: "<< decodedString<<endl;
    
}
int main(){
     // string fileData = "Explanation of Key Fields name: The name of this configuration, which you can set to anything you like. type: Set to cppdbg for using GDB or LLDB. request: Specifies the type of request; launch starts the debugging session.program: Path to the executable to debug. ${fileDirname}/${fileBasenameNoExtension}.exe will use the file name of the currently open file and assume the executable is in the same directory.";
    string fileData = "janumathi";
    map<char,int>freqTable;
    buildFreqTable(fileData, freqTable);
    HuffmanNode* root = buildHuffmanTree(freqTable);

    map<char,string> huffmanCodes;

    generateHuffmanCodes(root,"",huffmanCodes);
    

     string encodedString = compressFile(fileData,huffmanCodes); // This should be the result from compressFile function
    decompressFile(encodedString, root);
   

}
