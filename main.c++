
#include "HuffManEncoding.c++"

int main() { 

	 HuffManEncoding H; 

	 std::string test = "Programming is cool";
	 
	 std::unordered_map< char, std::string > encoding;

	 H.createEncodingMap( test, encoding );
	 
	 H.printStatistics( test, test.length() ); 

	 return 0;
}
