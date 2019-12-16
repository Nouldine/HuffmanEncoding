
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

};

class HuffManEncoding { 

	public: 
		HuffManEncoding() = default; 
		
		BinaryNode* BuildBinaryNode( char, int, BinaryNode*, BinaryNode* ); 
		void encode( BinaryNode *, std::unordered_map< char, std::string > &, std::string ); 

		void decode( BinaryNode*, int & , std::string ); 
		BinaryNode * buildTree( std::unordered_set<char> );
		int log2( int ); 
		std::unordered_set<char> getAlphabet( std::string, int ); 
		bool checker( std::string original_msg, std::string decoded_msg, int );
		void printStatistics( std::string, int );
	 	void createEncodingMap( std::string, std::unordered_map< char, std::string > );

		std::string readFile( std::ifstream & );

	private:

		std::priority_queue<BinaryNode*, std::vector<BinaryNode*>, std::greater<BinaryNode*>>  min_heap;
		std::unordered_map< char, int > frep_map;
		std::unordered_map< char, std::string > encode_msg_map;
		int encoding_length = 0;

};

#endif 


