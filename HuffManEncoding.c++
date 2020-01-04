
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
	
	if( my_str[ index ] == '0' )
		decode( root->left, index, my_str );
	else
		decode( root->right, index, my_str );

}

BinaryNode * HuffManEncoding::buildTree( std::string my_string ) { 
	
	// std::cout << "Calling HuffManEcoding::buildTree( std::string text_to_encode )" << std::endl;
	
	for( auto content : my_string )
		++freq_map[ content ]; 

	for( auto content : freq_map )
		 min_heap.push( BuildBinaryNode( content.first, content.second, nullptr, nullptr ));

	while( min_heap.size() > 1 ) {

		BinaryNode * first_min_node  = min_heap.top(); 
		min_heap.pop(); 
		BinaryNode * second_min_node = min_heap.top(); 
		min_heap.pop();

		//std::cout <<"first_min_node: "<< first_min_node->char_freq <<" "<<"second_min_node: "<< second_min_node->char_freq << std::endl;
		int parent_freq = first_min_node->char_freq + second_min_node->char_freq; 
		BinaryNode * parent = BuildBinaryNode('\0', parent_freq, first_min_node, second_min_node );
		min_heap.push(parent);
	 }

	 return min_heap.top();
}

int HuffManEncoding::log2( int my_n ) { 
	
	// std::cout << "Calling int HuffManEncoding::log2( int my_n )" << std::endl;
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

std::unordered_set<char> HuffManEncoding::getAlphabet( std::string my_text, int my_length ) { 
	
	//std::cout <<"Calling unordered_set< char >  getAlphabet(std::string  my_text, int my_length ) "<< std::endl;
	std::unordered_set<char> alphabet; 
	std::vector<char> my_vec; 

	for( int iter = 0; iter < my_length; ++iter )
		alphabet.insert( my_text[ iter ] ); 
	
	return alphabet; 
}

bool HuffManEncoding::checker( std::string original_msg, std::string decoded_msg, int my_length ) {
	
	// std::cout <<" Calling bool checker( std::string original_msg, std::string decoded_msg, int my_length )" << std::endl;
	for( int iter = 0; iter < my_length; ++iter ) {
		if( original_msg[ iter ] != decoded_msg[ iter ] )
			return false;
	}

	return true;
}

void HuffManEncoding::createEncodingMap( std::string my_text, std::unordered_map<char, std::string > encoding_map ) {
	 
	 // std::cout <<"Calling HuffManEncdoding::createEncodingMap( std::string my_text, std::unordered_map< char, std::string >, std::string )";
	
	 //std::cout <<"my_text: " << my_text << std::endl;
	 std::unordered_set<char> my_alphabet = getAlphabet( my_text, my_text.length() );
		
	 for( auto iter = my_alphabet.begin(); iter != my_alphabet.end(); ++iter ) 
		 std::cout <<"my_alphabet: " << *iter << std::endl;

         BinaryNode * node = buildTree( my_text );
         encode( node, encoding_map, "");
         std::string encoding_result = "";

         for( auto content : my_alphabet ) {

		 if( encoding_map.find( content ) != encoding_map.end() ) { 
			 
			 encoding_result += encoding_map.find( content )->second;
			 encoding_length += encoding_map.find( content )->second.length(); 

		 }
	 }


	 for( auto iter = encoding_map.begin(); iter != encoding_map.end(); ++iter )
		 std::cout <<"char: " << iter->first << " " <<"String: " << iter->second << std::endl;

        //std::cout <<"Result: " << encoding_result << std::endl;
	//encoding_length = encoding_result.length();
	std::cout <<"encoding_length: " << encoding_length << std::endl;
 	
	std::cout <<"encoding size: " << encoding_map.size() << std::endl;	
	encode_msg_map = encoding_map;

	std::cout <<"encoding_msg_map: " << encode_msg_map.size() << std::endl;
	
	/*	
	int index = -1;
        std::cout <<"Decoding: " << std::endl;
        while( index < (int)encoding_result.size() - 2 )
                decode( node, index, encoding_result );
	*/
}

void HuffManEncoding::printStatistics( std::string my_text, int my_length ) { 

	std::cout <<"Calling HuffManEncoding::printStatistics( std::string my_text, int my_length )" << std::endl; 

	int sigma = ( getAlphabet( my_text, my_length ) ).size();
	std::cout <<"sigma: " << sigma << std::endl;
	std::cout <<"my_length: " << my_length << std::endl;

 	std::string encoded_msg = ""; 
	//int encoding_length_2 = 0;

	for( int iter = 0; iter < my_length; ++iter ) {
		
		if( encode_msg_map.find( my_text[ iter ] ) !=  encode_msg_map.end() ) {
			encoded_msg += encode_msg_map.find( my_text[ iter ] )->second;
			// encoding_length_2 += ( encode_msg_map.find( my_text[ iter ] )->second ).length(); 
		}
	}

	std::cout <<"second length: "<< encoded_msg.length() << std::endl;
	//std::cout <<"encoding_lenght: "<< encoding_length_2 << std::endl;

	int encoded_ascii = my_length * 8; 
	int fixed_len = ( my_length * log2( sigma )) + ( sigma * ( 8 + log2( sigma )));	      
	int huffman_encoding = ( encoded_msg.length() + sigma * 8 + encoding_length );	
	
	std::cout <<"ASCII encoding needs: " << encoded_ascii << " bits" << std::endl; 
	std::cout <<"Fixed length encoding bits: " << fixed_len << " bits"<< std::endl;
	std::cout <<"Huffman Encoding: " << huffman_encoding << " bits" << std::endl;

}

void HuffManEncoding::printLargeScaleStatistics( std::string my_text, int my_length ) { 

	std::cout <<"Calling HuffManEncoding::printLargeScaleStatistics( std::string my_text, int my_length )" << std::endl;

	int sigma = ( getAlphabet( my_text, my_length ) ).size();
	int encoded_msg_length = 0;
	// std::unordered_set<int> my_alphabet = getAlphabet( my_text, my_length );

	for( char my_char : getAlphabet( my_text, my_length ) ) {

		if( freq_map.find( my_char ) != freq_map.end() and encode_msg_map.find( my_char ) != encode_msg_map.end() ) {
			
			int length = encode_msg_map.find( my_char )->second.length();
			//std::cout <<"Encode message length: " <<  length << std::endl;
			encoded_msg_length += freq_map.find( my_char )->second * encode_msg_map.find( my_char )->second.length();
		}
	}
	
	// std::cout <<"encoded_msg_length: " << encoded_msg_length << std::endl;
	// std::cout <<"encoding_length: " << encoding_length << std::endl;
	
	int ascii_encoding = my_length * 8; 
       	int fixed_encoding = my_length * log2( sigma ) + sigma * ( 8 + log2( sigma )); 
	int huffman_encoding = encoded_msg_length + sigma * 8 + encoding_length;
	
	std::cout << std::endl;
	std::cout <<"ASCII encoding needs: " << ascii_encoding << " bits."<< std::endl;
	std::cout << std::endl;
	std::cout <<"Fixed length encoding bits: " << fixed_encoding << " bits."<< std::endl;
	std::cout << std::endl;
    std::cout <<"Huffman Encoding: " << huffman_encoding << " bits."<< std::endl;

}	


void HuffManEncoding::eraseContainer() { 

	std::cout <<"Calling HuffManEncoding::eraseContaierner()" << std::endl;
	
	while(  min_heap.size() > 0 )
		min_heap.pop(); 

	freq_map.clear();
	encode_msg_map.clear();
}

std::string HuffManEncoding::readFile( std::ifstream & my_file ) { 
	 
	 // std::cout <<"Calling HuffManEncoding::readFile( std::ifstream & my_file )" << std::endl;
	 std::string string_to_encode = ""; 
	 char my_char;

	 if( my_file.is_open() ) { 

		while( !my_file.eof() ) { 

			 my_file.get(my_char);
			 string_to_encode += my_char; 
			 // std::cout <<"Encoding: " << string_to_encode << std::endl;
		}

		string_to_encode.pop_back();
		
	 }
	 
	 return string_to_encode;
}

