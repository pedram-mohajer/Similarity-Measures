// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Functions.hpp"
#include "Exception.h"
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

//-------------------------------------------------------------------------------------------------


void strTostr(string &desStr,string &srcStr)
{
    for(size_t i=0; i<srcStr.length(); i++)
        desStr[i] = srcStr[i];
}

//-------------------------------------------------------------------------------------------------

bool isNumber(const std::string &str)
{
    return !str.empty() && str.find_first_not_of("1234567890.+-e") == string::npos;
}



//-------------------------------------------------------------------------------------------------

int count_space(string str)
{
    int count = 0;
    size_t length = str.length();
    for (size_t i = 0; i < length; i++) {
        int c = str[i];
        if (isspace(c))
            count++;
    }
    return count;
}

//-------------------------------------------------------------------------------------------------

bool isAlpha(string str)
{
    char ch = str[0];
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ;
}


bool isAlpha(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

//-------------------------------------------------------------------------------------------------

void openFile(ifstream &iFile,string str)
{
    iFile.open(str,ios::in);
    if(!iFile)
        throw ReadFileError("File is not opened in path : ",str);
}


//-------------------------------------------------------------------------------------------------


double* VectorToDouble(vector <string> timeSeriesString)
{
    double *timeSeriesDouble = new double[timeSeriesString.size() ];

    
    for(size_t i=0 ; i < timeSeriesString.size() ; i++)
    {
        
        timeSeriesDouble[i] = stod(timeSeriesString[i]);

    }

    return timeSeriesDouble;
}



//-------------------------------------------------------------------------------------------------


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

//-------------------------------------------------------------------------------------------------

bool isInteger(const string & s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
    
    char * p ;
    strtol(s.c_str(), &p, 10) ;
    
    return (*p == 0) ;
}

//-------------------------------------------------------------------------------------------------

bool  isPositiveInteger(const string & s)
{
    if(s.empty() || ((!isdigit(s[0]))  && (s[0] != '+'))) return false ;
    
    char * p ;
    strtol(s.c_str(), &p, 10) ;
    
    return (*p == 0) ;
}

//-------------------------------------------------------------------------------------------------



void validateTimeSeriesData(string filePath)
{
    
    ifstream iFile;
    iFile.open(filePath,ios::in);
    if(!iFile)
    {
        iFile.close();
        throw ReadFileError("tsdFile is not opened in path : ",filePath);
    }
    size_t i=0,j=0;
    string data,str;
    enum typeVariable{INT,DOUBLE,FLOAT};

    vector <string> token;
    vector <int> sampleCount;
    
    size_t vector_size;

    int fieldCount=0,sizeCount=0,COUNT=0,typeVariableCount=0;
    while(++j<=7)
    {
        getline(iFile, data);
        HandleToken(data,token,' ');
        vector_size = token.size();
        i=0;

        switch(j)
        {
                
            case 1 :
            {
                i=0;
                if(vector_size!=2)
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("Number of Data in VERSION line is Invalid ",filePath);
                }
                if(token[0]!="VERSION")
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("Error in VERSION Name ");
                }
                if(!isNumber(token[1]))
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("VERSION must be a Number ");
                }
                break;
            }

            case 2 :
            {
                i=0;
                if(token[0]!="FIELDS")
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("Error in FIELDS name ");
                }
                    while(++i<vector_size)
                {
                    if(!isAlpha(token[i]))
                    {
                        iFile.close();
                        throw ErrorInTsdHeaderFile("FIELDS Data Must be a Char");
                    }
                    ++fieldCount;
                }
                break;
            }
            case 3 :
            {
                i=0;
                if(token[0]!="SIZE")
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("Error in SIZE name ");
                }
                while(++i<vector_size)
                {
                    if(!isNumber(token[i]))
                    {
                        iFile.close();
                        throw ErrorInTsdHeaderFile("SIZE Data Must be a number");
                    }
                    ++sizeCount;
                }
                if(sizeCount!=fieldCount)
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("sizeCount != fieldCount");
                }
                    break;
            }

            case 4 :
            {
                i=0;
                if(token[0]!="COUNT")
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("Error in COUNT name ");
                }
                while(++i<vector_size)
                {
                    if(!isNumber(token[i]))
                    {
                        iFile.close();
                        throw ErrorInTsdHeaderFile("Count Data Must be a number");
                    }
                }
                COUNT = stod(token[i-1]);
                break;
            }

            case 5 :
            {
                i=0;
                if(token[0]!="TYPE")
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("Error in TYPE name ");
                }
                while(++i<vector_size)
                {
                    if(!isNumber(token[i]))
                    {
                        iFile.close();
                        throw ErrorInTsdHeaderFile("Count Data Must be a number");
                    }
                    typeVariableCount++;

                }
                if(typeVariableCount!=fieldCount)
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("typeVariableCount != fieldCount ");
                }

                int *variableTypeInData = new int [typeVariableCount];
                i=1;
                int k=0;
                while(i<vector_size-1)
                {variableTypeInData[k] = stoi(token[i]);i++;k++;}
                break;
            }
            case 6 :
            {
                i=0;

				if(token[0]!="SAMPLES")
				{
					iFile.close();
					 throw ErrorInTsdHeaderFile("Error in SAMPLES name ");
				}
				while(++i<vector_size)
				{
					if(!isNumber(token[i]))
					{
						iFile.close();
						throw ErrorInTsdHeaderFile("Number of Samples must be a number");
					}
	                sampleCount.push_back(stoi(token[i]) );
				}
                break;
            }
            case 7 :
            {
                i=0;
                if(token[0]!="DATA")
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("Error in DATA name ",filePath);
                }
                if(token[1]!="ASCII")
                {
                    iFile.close();
                    throw ErrorInTsdHeaderFile("Error in ASCII name ",filePath);
                }
                break;
            }
        }
        
        token.clear();
    }// End Of While
    
    

    int counter;

    for( int currentDimInt = 0; currentDimInt<COUNT; ++currentDimInt)
    {
    	string dimension     = string("Dim").append( to_string(currentDimInt+1) );
		string nextDimension = string("Dim").append( to_string(currentDimInt+2) );

		while(data.compare(dimension) != 0)
			iFile >> data;

		counter = 0;

		while(iFile >> data)
		{
			if(data.compare(nextDimension) == 0 )
				break;

			if(!isNumber(data))
			{
				iFile.close();
				throw ErrorInTsdFooterFile("Data Type is Invalid " ,filePath);
			}


			counter++;
		}


		if(counter != sampleCount[currentDimInt])
		{
			iFile.close();
			throw ErrorInTsdFooterFile("Number Of Sample is Invalid ",filePath);
		}

    }
    iFile.close();
    
}	// End Of validateTimeSeriesData



//-------------------------------------------------------------------------------------------------

void validateLabelData(string filePath,  vector <string> & labels)

{
    ifstream iFile;
    iFile.open(filePath,ios::in);
    if(!iFile)
    {
        iFile.close();
        throw ReadFileError("lableFile is not opened in path : ",filePath);
    }

    string data,str;

     while(iFile >> data)
     {

         if(!isNumber(data))
         {
             iFile.close();
             throw ErrorInTsdFooterFile("Data Type in labelFile  is Invalid " ,filePath);
         }
         labels.push_back( data );

     }
     iFile.close();

}


//-------------------------------------------------------------------------------------------------
