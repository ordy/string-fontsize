#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string tail(string const& source, size_t const length){
  if (length >= source.size()){
        return source;
  }
  return source.substr(source.size() - length);
}

int main() {
    ofstream of_longnames;
    ifstream if_namesfiles;
    of_longnames.open("./clipping_names.txt");
    if_namesfiles.open("./full_item_list.txt");
    string ItemName;
    double string_width;

	vector<vector <char>> charSet = {
		// Set1 : 0.334
		{'i', 'l', 'I'},
		// Set2 : 0.445
		{'!', '.', ',', ':', ';'},
		// Set3 : 0.562
		{'j', '"', '-', '\\'},
		// Set4 : 0.667
		{'f', '[', ']', '(', ')', ' '},
		// Set5 : 0.781
		{'r', 't'},
		// Set6 : 0.889
		{'s', 'z', 'J', '<', '>', '='},
		// Set7 : 1.000
        {'a', 'b', 'c', 'd', 'e', 'k', 'n', 'o', 'p', 'q', 'u', 'x', 'y', 'L', 'P', '/', '~', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
		// Set8 : 1.142
		{'g', 'v', 'B', 'E', 'F', 'R', 'S', 'Z', '?'},
		// Set9 : 1.231
		{'D', 'H', 'K', 'N', 'T', 'U', 'V'},
		// Set10 : 1.334
        {'C', 'G', 'M', 'O', 'Q', 'X', 'Y', '#', '+'},
		// Set11 : 1.455
        {'m', '%'},
		// Set12 : 1.600
		{'w', 'W'},
	};
	const double charSize[12] = {0.334,0.445,0.562,0.667,0.781,0.889,1.0,1.142,1.231,1.334,1.455,1.6};

	while(getline(if_namesfiles, ItemName)){ // list of files
        if (ItemName.find("[FILENAME = ")==0){
            of_longnames << ItemName << endl;
            continue;
        }
        string_width = 0.0;
        int leadingChar = 0;
        for(char& c : ItemName) { // string_width calculation
            int i;
            for(i=0; i < 12;i++){
                int k;
                for (k=0; k < charSet[i].size();k++){
                    if (c == charSet[i][k]){
                        string_width+=charSize[i];
                        break;
                    }
                }
                if(k < charSet[i].size())
                    break;
            }
            if(i > 11)
                string_width+=charSize[6];   // unlisted characters default to 1.0
            if(string_width<=27.4)
                leadingChar+=1;
        }
        if(string_width>27.4){
            of_longnames << ItemName.substr(0,leadingChar) << "|" << tail(ItemName, (ItemName.size()-leadingChar)) << endl;
            //of_longnames << ItemName << endl;
        }
    }
    if_namesfiles.close();
    of_longnames.close();
	return 0;
}
