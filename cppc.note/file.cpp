                      
/* 
 * The stream object hierarchy
 * header file
 * <fstream>
 * <sstream>
 * <iostream>, automatically include <ios>,<streambuf>, 
				 <istream>, <ostream>...
               +-------+                          +-------+ 
      	       |ostream|       		          |istream| 
              /+--+----+                          +--+----+\
             /    |             +--------+           |      \
       +--------+ |     	|iostream|           | +--------+
       |ofstream| |            /+--------+ \         | |ifstream|
       +--------+ | +---------/--+     +----\--+     | +--------+
		  | |stringstream|     |fstream|     |
                  | +------------+     +-------+     |
               +--------------+                +--------------+
	       |ostringstream | 	       |istringstream |
               +--------------+                +--------------+
*/


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	ifstream file("myFile.txt");
	string str; 

	int i = 0;

	while ( getline(file, str) )
	{
		istringstream iss(str);

		vector<string> tokens;

		// Template param indicates what 
		// data type can be read from stream
		copy( istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter<vector<string> >(tokens) );

		string fist = tokens.front();
		string end = tokens.back();

		cout << first << ' ' << end << endl;
		++i;
	}
}
