// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Exception.h"




string Exception::get_msg()         {return msg;}
int    Exception::get_line()        {return line;}
string Exception::get_fileName()    {return fileName;}
void   Exception::makeNull()        {msg=" " ; line=-1 ; fileName=" ";}
ReadFileError::ReadFileError (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName; line = _line;}
    


ErrorInTsdHeaderFile::ErrorInTsdHeaderFile (string _msg,string _fileName,int _line) {msg=_msg;  fileName = _fileName; line=_line;}


ErrorInTsdFooterFile ::ErrorInTsdFooterFile (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName; line=_line;}

WrongInput::WrongInput (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName;line=_line;}
   
WrongExecution::WrongExecution (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName;line=_line;}

InequalityInNumberOFLabelsAndData::InequalityInNumberOFLabelsAndData (string _msg,string _fileName,int _line)  {msg=_msg; fileName = _fileName;line=_line;}

OutputFileError::OutputFileError (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName;line=_line;}

WrongClassifier::WrongClassifier (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName;line=_line;}

WrongMeasureSimilarity::WrongMeasureSimilarity (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName;line=_line;}

WrongNumberOfDataset::WrongNumberOfDataset (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName;line=_line;}


WrongDimension::WrongDimension (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName;line=_line;}

wrongInputNumber::wrongInputNumber (string _msg,string _fileName,int _line) {msg=_msg; fileName = _fileName;line=_line;}





