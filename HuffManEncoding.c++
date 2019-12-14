
#include "HuffManEncoding.hpp"

BinaryNode* HuffManEncoding::BuildBinaryNode( char my_char, int char_freq, BinaryNode * left, BinaryNode * right ) { 

	// std::cout <<"Calling BinaryNode* HuffManEncoding::BuildBinaryNode( char my_char, int char_freq, BinaryNode * left, BinaryNode * right )" << std::endl; 

	BinaryNode* my_node = new BinaryNode(); 
	my_node->my_char = my_char; 
	my_node->char_freq = char_freq;
	my_node->left = left;
	my_node->right = right; 

	return my_node;

}


void HuffManEncoding::encode( BinaryNode * root, std::unordered_map< char, std::string > & encoding, std::string my_str ) { 

	// std::cout <<"Calling BinaryNode* HuffManEncoding::encode( BinaryNode * root, std::string & my_str )"; 

	if( root == nullptr )
		return; 
	
	if( !root->left && !root->right ) 
		 encoding[ root->my_char ] = my_str;

	encode( root->left,  encoding,  my_str + "0" );
	encode( root->right, encoding,  my_str + "1" );

}

void HuffManEncoding::decode( BinaryNode* root, int & index, std::string my_str ) { 

	// std::cout <<"Calling HuffManEncoding::decode( BinaryNode* root, int  & index, std::string & my_str )" << std::endl;
	
	if( root == nullptr )
		return;

	if( !root->left && !root->right ) {
		
		std::cout << root->my_char;
		return;

	}
	
	++index;

	if( my_str[ index ] == '0' )
		decode( root->left, index, my_str );

	else
		decode( root->right, index, my_str );

}

BinaryNode * HuffManEncoding::buildTree( std::string & text_to_encode ) { 
	// std::cout << "Calling HuffManEcoding::buildTree( std::string text_to_encode )" << std::endl;
	 for( char content : text_to_encode )
		++frep_map[ content ]; 

	 for( auto content : frep_map )
		 min_heap.push( BuildBinaryNode( content.first, content.second, nullptr, nullptr ));

	 while( min_heap.size() > 1 ) {

		BinaryNode * first_min_node = min_heap.top(); 
		min_heap.pop(); 
		BinaryNode * second_min_node = min_heap.top(); 
		min_heap.pop();

		int parent_freq = first_min_node->char_freq + second_min_node->char_freq; 

		BinaryNode * parent = BuildBinaryNode('\0', parent_freq, first_min_node, second_min_node );

		min_heap.push(parent);
	 }

	 return min_heap.top();

}

int HuffManEncoding::log2( int my_n ) { 

	std::cout << "Calling int HuffManEncoding::log2( int my_n )" << std::endl;

 	if( my_n <= 2 )
		return 1; 

	int my_x = 1; 
	int count = 0; 

	while( my_x < my_n ) { 

		my_x = my_x * 2;
		++count;
	}

	return count;

}	

std::unordered_set<char> HuffManEncoding::getAlphabet( std::string my_text, int my_length ){ 
	
	std::cout <<"Calling unordered_set< char >  getAlphabet(std::string  my_text, int my_length ) "<< std::endl;

	std::unordered_set<char> alphabet; 
	
	for( int iter = 0; iter < my_length; ++iter )
		alphabet.insert( my_text[ iter ] ); 

	return alphabet; 
}

bool HuffManEncoding::checker( std::string original_msg, std::string decoded_msg, int my_length ) {
	
	std::cout <<" Calling bool checker( std::string original_msg, std::string decoded_msg, int my_length )" << std::endl;

	for( int iter = 0; iter < my_length; ++iter ) {

		if( original_msg[ iter ] != decoded_msg[ iter ] )
			return false;
	}

	return true;
}

void  HuffManEncoding::createEncodingMap( std::string my_text, std::unordered_map<char, std::string > encoding_map ) {

         BinaryNode * node = buildTree( my_text );
         encode( node, encoding_map, "");
         std::string encoding_result = "";

         for( auto content : my_text )
                  encoding_result += encoding_map[ content ];

        std::cout <<"Result: " << encoding_result << std::endl;
	
	encoding_length = encoding_result.length();

	int index = -1;

        std::cout <<"Decoding: " << std::endl;

        while( index < (int)encoding_result.size() - 2 )
                decode( node, index, encoding_result );

}

void HuffManEncoding::printStatistics( std::string my_text, int my_length ) { 

	int sigma = ( getAlphabet( my_text, my_length ) ).size();
 	std::string encoded_msg = ""; 
	int encoding_length = 0;

	for( int iter = 0; iter < my_length; ++iter ) {
		encoded_msg += frep_map.find( my_text[ iter ])->second;
	}

	int encoded_ascii = my_length * 8; 

	int fixed_len = ( my_length * log2( sigma ) + sigma  *  ( 8 + log2( sigma )));
	
	int huffman_encoding = ( encoded_msg.length() + sigma * 8 + encoding_length );	
	std::cout <<"ASCII encoding needs: " << encoded_ascii << " bits" << std::endl; 

	std::cout <<"Fixed length encoding bits: " << fixed_len << std::endl;
	std::cout <<"Huffman Encoding: " << huffman_encoding << std::endl;

}



















