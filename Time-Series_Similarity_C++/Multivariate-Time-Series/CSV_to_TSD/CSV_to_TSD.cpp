#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
#include<bits/stdc++.h>

//-------------------------------------------------------------------------------------------------
void HandleToken(const string& str, vector<string>& tokens, const char& delimiters);

//-------------------------------------------------------------------------------------------------


int main(int argc , const char * argv[])
{
	string datasetPath;
	string outputPath;
	char sep=',';
	int numberOfDimensions,tmp;
	vector <int> sampleNumber;
	vector <string> sampleType;
	string temp;

	cout << "Enter Dataset Path        : "; cin >> datasetPath;
	cout << "Enter Output Path         : "; cin >> outputPath;
	cout << "Enter Data Separator      : "; cin >> sep;
	cout << "Enter Number of Dimension : "; cin >> numberOfDimensions;
	cout << "Enter Sample Number in The Corresponding Dimension...\n";
	for(int i=0; i< numberOfDimensions; i++)
	{
		cout << "Dimension " << i+1 << " : ";
		cin >> tmp;
		sampleNumber.push_back(tmp);
	}
	cout << "Enter Sample Type  in The Corresponding Dimension...\n";
	for(int i=0; i< numberOfDimensions; i++)
	{
		cout << "Dimension " << i+1 << " : ";
		cin >> temp;
		transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
		sampleType.push_back(temp);
	}



	char field='A';


	ifstream input(datasetPath,ios::in);
	ofstream output;

	string data;
	vector <string> token;

	int vector_size, outputFilesCounterInt=1;
	string prefix="tsdFile",outputFilesCounterStr,extension=".tsd";

	int dataNumber=0,sum=0;

	while(input >> data)
	{
		HandleToken(data,token,sep);
		vector_size = token.size();
	

		for(int i=0; i<vector_size; i++)
			dataNumber++;

		for(int i=0; i<sampleNumber.size(); i++)
			sum+=sampleNumber[i];

		if(sum != dataNumber)
		{
			cout << "\n The Sum of Data over Dimensions Is Not equal to dataNumber \n";
			exit(1);
		}

		if(outputFilesCounterInt<=9)
			outputFilesCounterStr=string("0"+to_string(outputFilesCounterInt) );
		else
			outputFilesCounterStr=to_string(outputFilesCounterInt);
		output.open( outputPath + string(prefix+outputFilesCounterStr+extension)) ;

		output << "VERSION" << " " << "0.01";

		output << "\nFIELDS";
		for(int i=0; i< numberOfDimensions; i++)
			output << " " <<  char(field+i)	 ;

		output << "\nSIZE";
		for(int i=0; i< numberOfDimensions; i++)
			if (sampleType[i].compare("DOUBLE")==0)
				output << " " <<  "16";
			else if (sampleType[i].compare("FLOAT")==0)
					output << " " <<  "8";
			else if (sampleType[i].compare("INT")==0)
					output << " " <<  "4"	 ;
			else
			{
				cout << "Invalid Data Type Entered\n";
				exit(1);
			}

		output << "\nCOUNT"   << " " <<  numberOfDimensions  ;

		output << "\nTYPE";
		for(int i=0; i< numberOfDimensions; i++)
			if (sampleType[i].compare("DOUBLE")==0)
				output << " " <<  "1";
			else if (sampleType[i].compare("FLOAT")==0)
					output << " " <<  "2";
			else if (sampleType[i].compare("INT")==0)
					output << " " <<  "0"	 ;
			else
			{
				cout << "Invalid Data Type Entered\n";
				exit(1);
			}

		output << "\nSAMPLES";
			for(int i=0; i< numberOfDimensions; i++)
				output << " " <<  sampleNumber[i]	 ;

		output << "\nDATA"    << " " <<  "ASCII" << "\n\n";

		int postion=0,tmp;
		for(int j=0; j<numberOfDimensions; j++)
		{
			tmp = 0 ;
			output << string("Dim")+to_string(j+1) << endl;
			for(int l=0; l<=j;l++)
				tmp+=sampleNumber[l];
			for(int k=postion ; k<tmp; k++)
			{
				output << token[k]<< endl;
				postion = k+1;
			}

		}
	
		outputFilesCounterInt++;
		token.clear();
		output.close();

	}

	cout << "The Number of tsd files :" << outputFilesCounterInt-1 << endl;

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

