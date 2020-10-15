// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Similarity.hpp"

#include <memory>
using namespace std;

//-----------------------------------------------------------------------------------------------------------------------------------
Similarity::Similarity()
{
    unique_ptr <Input>  input (new Input());
    unique_ptr <Facade> facade(new Facade());
    unique_ptr <Log>    log   (new Log());
    unique_ptr <Output> output(Output::makeOutputInstance() );
    
    this->input  = move(input);
    this->facade = move(facade);
    this->log    = move(log);
    this->output = move(output);
   
}
//-----------------------------------------------------------------------------------------------------------------------------------
void Similarity::processing(int argc, const char * argv[])
{
    
    input.get() -> preProcessing(argc,argv);
    log.get()   -> preProcessing(input.get()->getLogFilePath());
    output.get()-> preProcessing(input.get()->getOutputFilePath());
    facade.get()-> preProcessing(input.get()->getInputs());

}
//-----------------------------------------------------------------------------------------------------------------------------------
void Similarity::freeSimilarityObject()
{
    facade.release();
    log.release();
    input.release();
    output.release();
}
//-----------------------------------------------------------------------------------------------------------------------------------
void Similarity::HandleException(Exception exception)
{
    log.get()->setException(exception);
    log.get()->writeExceptionInLogFile();
    log.get()->setExceptionNull();
}
//-----------------------------------------------------------------------------------------------------------------------------------





