// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  ResultRepository.hpp


#ifndef ResultRepository_hpp
#define ResultRepository_hpp

#include <vector>
#include "Output.hpp"
#include <memory>

using namespace std;

class ResultRepository
{
 private :
        vector <  vector< vector<double> > > resultDiagramDist;
        vector <  vector< vector<int   > > > resultDiagramLen;

        int numberOfMethod;
        Output *output;
   public :
        void addToDiagramDist(vector< vector<double> >  _resultDiagram);
        void addToDiagramLen (vector< vector<int> >  _resultDiagram);
        void addMethodNameToRepo(string _methodName);
        void increaseNumberOfMethod();
        void writeResultInOutput();
        ResultRepository(int );

        unique_ptr < vector <  vector< vector<double> > > >  uniquePtrOfDistRepo();


};
#endif /* ResultRepository_hpp */
