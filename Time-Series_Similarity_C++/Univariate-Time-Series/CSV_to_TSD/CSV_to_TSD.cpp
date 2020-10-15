#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


//-------------------------------------------------------------------------------------------------
void HandleToken(const string& str, vector<string>& tokens, const char& delimiters);

//-------------------------------------------------------------------------------------------------


int main(int argc , const char * argv[])
{
	string datasetPath;
	string outputPath;
	char sep;

	if(argc == 1)
	{
		cout << "Enter Dataset Path   : "; cin >> datasetPath;
		cout << "Enter Output Path    : "; cin >> outputPath;
		cout << "Enter data separator : "; cin >> sep;
	}

	else if (argc ==4)
	{
		datasetPath = argv[1];
		outputPath  = argv[2];
		char sep	= *argv[3];
	}

	else 
	{
		cout << "The number of Parameter is Wrong\n";
		exit(1);
	}



	ifstream input(datasetPath,ios::in);
	ofstream output;

	string data;
	vector <string> token;

	int vector_size, outputFilesCounterInt=1;
	string prefix="tsdFile",outputFilesCounterStr,extension=".tsd";

	int dataNumber=0;

	while(input >> data)
	{
		HandleToken(data,token,sep);
		vector_size = token.size();
	

		for(int i=0; i<vector_size; i++)
			dataNumber++;

		if(outputFilesCounterInt<=9)
			outputFilesCounterStr=string("0"+to_string(outputFilesCounterInt) );
		else
			outputFilesCounterStr=to_string(outputFilesCounterInt);
		output.open( outputPath + string(prefix+outputFilesCounterStr+extension)) ;

		output << "VERSION" << " " << "0.01"   << endl;
		output << "FIELDS"  << " " << "X"	   << endl;
		output << "SIZE"    << " " <<  "16"    << endl;
		output << "COUNT"   << " " <<  "1"     << endl;
		output << "TYPE"    << " " <<  "2"	   << endl;
		output << "SAMPLES" << " " <<  dataNumber   << endl;
		output << "DATA"    << " " <<  "ASCII" << endl;

		
		for(int i=0; i<vector_size; i++)	
			output << token[i] << endl;
	
		outputFilesCounterInt++;
		token.clear();
		output.close();
		
		
	}

	cout << "The Number of tsd files :" << outputFilesCounterInt << endl;

	return 0;
}
// -----------------------------------------------------------------------------
void HandleToken(const string& str, vector<string>& tokens, const char& delimiters)
{
    size_t lastPos = str.find_first_not_of(delimiters, 0);
    size_t pos = str.find_first_of(delimiters, lastPos);
    
    while (string::npos != pos || string::npos != lastPos)
    {
        if( str.substr(lastPos, pos - lastPos).compare("\r"))
            tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
    if( tokens[tokens.size()-1][ (tokens[tokens.size()-1]).length()-1] == '\r')
        tokens[tokens.size()-1] = tokens[tokens.size()-1].substr(0,(tokens[tokens.size()-1]).length()-1) ;
    
}
// -----------------------------------------------------------------------------

