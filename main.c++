
#include "HuffManEncoding.c++"

int main() { 

	 HuffManEncoding H; 

	 //std::string test = "Y2XEYX2XYX2CEXEX2Y2ZYX2ZYZE2Y2ZEYXEX2YZYCY2ZEX";
	 //std::string test = "BCCABBDDAECCBBAEDDCC";
	 
	 std::string my_test_string;
	 std::string path = "DataFiles/Test";
	 std::ifstream my_file;

	 for( const auto & entry : file_sys::directory_iterator(path) )
	 {
		my_file.open( entry.path(), std::ios_base::in );
		std::cout <<"File: " << entry.path() << std::endl;
		 
		my_test_string = H.readFile( my_file ); 
	 	std::unordered_map< char, std::string > encoding;
	 	H.createEncodingMap( my_test_string, encoding );
	 
	 	std::cout <<"test length: " << my_test_string.length() << std::endl; 

	 	// H.printStatistics( my_test_string, my_test_string.length() ); 
		H.printLargeScaleStatistics( my_test_string, my_test_string.length() ); 
	
	}

	return 0;
}
