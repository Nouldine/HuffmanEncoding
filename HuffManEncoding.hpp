
#ifndef HUFFMAN_CODING_H
#define HUFFMAN_CODING_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <experimental/filesystem> 

namespace file_sys = std::experimental::filesystem;

struct BinaryNode  {

	BinaryNode *left; 
	BinaryNode *right; 
	char my_char;
	int char_freq; 

	~BinaryNode() { 

		delete left; 
		delete right;
	}
};


struct compare {

	 bool operator()( BinaryNode * left, BinaryNode * right ) {

		 return left->char_freq > right->char_freq;
	 }
};

class HuffManEncoding { 

	public: 
		HuffManEncoding() = default; 
		
		BinaryNode* BuildBinaryNode( char, int, BinaryNode*, BinaryNode* ); 
		void encode( BinaryNode *, std::unordered_map< char, std::string > &, std::string ); 

		void decode( BinaryNode*, int & , std::string ); 
		int log2( int ); 
		BinaryNode * buildTree( std::string );
		std::unordered_set<char> getAlphabet( std::string, int ); 
		bool checker( std::string original_msg, std::string decoded_msg, int );
		void printStatistics( std::string, int );
	 	void createEncodingMap( std::string, std::unordered_map< char, std::string > );
		std::string readFile( std::ifstream & );
		void printLargeScaleStatistics( std::string, int );
		 
		~HuffManEncoding() {}
	private:

		std::priority_queue< BinaryNode*, std::vector<BinaryNode*>,  compare >  min_heap;
		// std::priority_queue< BinaryNode*, std::vector<BinaryNode*>,  std::greater<BinaryNode*> >  min_heap;
		std::unordered_map< char, int > freq_map;
		std::unordered_map< char, std::string > encode_msg_map;
		int encoding_length = 0;

};

#endif 


