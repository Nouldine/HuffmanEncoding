
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
		 my_file.open(entry.path(), std::ios_base::in);
		 std::cout << "File: " << entry.path() << std::endl;
		 my_test_string = H.readFile(my_file);

		 //std::cout <<"Test1" << std::endl;
		 std::unordered_map<char, std::string> encoding;
		 H.createEncodingMap(my_test_string, encoding);

		 // std::cout <<"Test length:" << my_test_string.length() << std::endl;
		 H.printLargeScaleStatistics(my_test_string, my_test_string.length());
		 H.eraseContainer();

		 my_file.close();
		 my_test_string = "";
	}

	return 0;
}
