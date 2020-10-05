// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Facade.hpp


#ifndef Facade_hpp
#define Facade_hpp

#include <string>
#include <vector>
#include "Interface.hpp"
#include <memory>

using namespace std;

using std::vector;

class Log;

class Facade
{
    private :
    
        int methodNumber;
        int userChoiceInt;
        int numberOfTimeseriesInt;
        string userChoiceStr;
        vector <double *> param;
        vector <string >  path;

        unique_ptr <Interface> interface;
    
        void chooseFunction();
        void doInterfaceFunction();

        void setNumberOfDimension(string);
        void setWinSize(string);
        void setEpsilon(string);

        void setWinRatio(string);
        void setCost(string _cost);
        void setLambda(string _lambda);
        void setNu(string _nu);
        void setGapc(string _gapc);
        void setEpc(string _epc);
        void setReward(string _reward);
        void setGap(string _gap);
        void setWeightMax(string _weightMax);
        void setG(string _g);

        void setFoldNumber(string _foldNumber);
        void setIterNumber(string _setIterNumber);
    
        void setParam(vector <string> );

        void freeInterface();
        void createInterface();

        void setMethodNumber(string _methodName);
        void convertMethodNameToLowercase();
    

        void setInputPath(string);
        void setLablesPath(string );
        void setClassiferNumber(string);

        void setNumberOfDataset(string);



    public :
        Facade();
        void preProcessing(vector<string>);

    
    
};
#endif /* Facade_hpp */










