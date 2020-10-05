// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------

//  Similarity.hpp


#ifndef Similarity_hpp
#define Similarity_hpp
#include "Facade.hpp"
#include "Log.hpp"
#include "Input.hpp"
#include "Output.hpp"

#include <memory>

using namespace std;



class Similarity
{
    private :
        unique_ptr <Facade> facade;
        unique_ptr <Log>    log;
        unique_ptr <Input>  input;
        unique_ptr <Output> output;
    
    
    
    public :
        Similarity();
        void processing(int argc, const char * argv[]);
        void freeSimilarityObject();
        void HandleException(Exception exception);
};

#endif /* Similarity_hpp */
