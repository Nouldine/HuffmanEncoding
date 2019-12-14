
#include "HuffManEncoding.c++"

int main() { 

	 HuffManEncoding H; 

	 std::string test = "It is fun to know ssisjdfnfnewibfkolf Mf;SJfejKbEOIIIIIIIIIIIBF Cl kc  KDffoeohow to code.";
	 
	 std::unordered_map< char, std::string > encoding;

	 H.createEncodingMap( test, encoding );
	 
	 std::cout <<"test length: " << test.length() << std::endl; 

	 H.printStatistics( test, test.length() ); 

	 return 0;
}
