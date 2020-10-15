// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Functions.hpp


#ifndef Functions_hpp
#define Functions_hpp

#include <string>
#include <vector>

using std::vector;
using namespace std;

bool      isNumber(const std::string &str);
vector <double>    VectorToDouble(vector <string> timeSeriesString);
void      strTostr(string &desStr,string &srcStr);
void      validateTimeSeriesData(string filePath);
void 	  validateLabelData(string filePath, vector <string>  &);
bool      isInteger(const string & s);
bool      isPositiveInteger(const string & s);



#endif /* Functions_hpp */
