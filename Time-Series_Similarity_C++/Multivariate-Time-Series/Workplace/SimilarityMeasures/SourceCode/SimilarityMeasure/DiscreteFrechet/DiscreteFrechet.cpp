// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "DiscreteFrechet.hpp"
#include "limits"
#include <iostream>
#include <cmath>
#include "Functions.hpp"

class TimeSeries;
using namespace std;

//-------------------------------------------------------------------------------------------------

double DiscreteFrechet::recursiveFunc(TimeSeries *Ts1,size_t n1,TimeSeries *Ts2, size_t n2,size_t dim, vector<double> ca,size_t idx1 ,size_t idx2)
{
    double output;
    double tmp, tmp1, tmp2;
    size_t i;
    
    
    vector<vector <string>>  timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector<vector <string>>  timeSerieDataSecond  = Ts2->getTimeSerieData();


    if (ca[idx1 + n1 * idx2] > -1)
    {
        output = ca[idx1 + n1 * idx2];
        return output;
    }
    else if ( idx1 == 0 && idx2 == 0)
    {
        tmp1 = 0;
        for ( i = 0; i < dim; i++)
        {
            tmp2 = stod(timeSerieDataFirst[i][idx1]) - stod(timeSerieDataSecond[i][idx2]);
            tmp1 +=  tmp2 * tmp2;
        }
        
        ca[idx1 + n1 * idx2] = sqrt(tmp1);
    }
    else if ( idx1 > 0 && idx2 == 0)
    {
        tmp = recursiveFunc(Ts1, n1, Ts2, n2, dim, ca, idx1-1 , idx2);
        tmp1 = 0;
        for ( i = 0; i < dim; i++)
        {



            tmp2 = stod(timeSerieDataFirst[i][idx1]) - stod(timeSerieDataSecond[i][idx2]);
            tmp1 +=  tmp2 * tmp2;
        }
        if (tmp > sqrt(tmp1))
        {
            ca[idx1 + n1 * idx2] = tmp;
        }
        else
        {
            ca[idx1 + n1 * idx2] = sqrt(tmp1);
        }
    }
    else if ( idx1 == 0 && idx2 > 0)
    {
        tmp = recursiveFunc(Ts1, n1, Ts2, n2, dim, ca, idx1 , idx2-1);
        tmp1 = 0;
        for ( i = 0; i < dim; i++)
        {



            tmp2 = stod(timeSerieDataFirst[i][idx1]) - stod(timeSerieDataSecond[i][idx2]);
            tmp1 +=  tmp2 * tmp2;
        }
        if (tmp > sqrt(tmp1))
        {
            ca[idx1 + n1 * idx2] = tmp;
        }
        else
        {
            ca[idx1 + n1 * idx2] = sqrt(tmp1);
        }
    }
    else if ( idx1 > 0 && idx2 > 0)
    {
        tmp = recursiveFunc(Ts1, n1,  Ts2, n2, dim, ca, idx1-1, idx2-1);
        tmp1 = recursiveFunc(Ts1, n1, Ts2, n2, dim, ca, idx1-1, idx2);
        tmp2 = recursiveFunc(Ts1, n1, Ts2, n2, dim, ca, idx1, idx2-1);
        if ( tmp1 < tmp)
        {
            tmp = tmp1;
        }
        if (tmp2 < tmp)
        {
            tmp = tmp2;
        }
        
        tmp1 = 0;
        for ( i = 0; i < dim; i++)
        {
            tmp2 = stod(timeSerieDataFirst[i][idx1]) - stod(timeSerieDataSecond[i][idx2]);
            tmp1 +=  tmp2 * tmp2;
        }
        if (tmp > sqrt(tmp1))
        {
            ca[idx1 + n1 * idx2] = tmp;
        }
        else
        {
            ca[idx1 + n1 * idx2] = sqrt(tmp1);
        }
    }
    output = ca[idx1 + n1 * idx2];
    return output;
}
//-------------------------------------------------------------------------------------------------
DiscreteFrechet::DiscreteFrechet(size_t size)
{
    discreteFrechetLen.resize(size);
    discreteFrechetDist.resize(size);
    for(size_t i=0;i<size;i++)
    {
        discreteFrechetLen[i].resize(size);
        discreteFrechetDist[i].resize(size);
    }
    for(size_t i=0;i<size;i++)
        for(size_t j=0;j<size;j++)
        {
            discreteFrechetLen[i][j] = -1;
            discreteFrechetDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------


void DiscreteFrechet::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double  _discreteFrechetDist;
    int     _discreteFrechetLen;
    
    size_t size = path.size();
    
    for(size_t i=0 ; i< size  ; i++)
        for(size_t j=i ; j<  size ;j++)
        {
                compute( path[i].get(), path[j].get() ,  _discreteFrechetDist, _discreteFrechetLen);
                discreteFrechetDist[i][j] = _discreteFrechetDist;
                discreteFrechetLen[i][j]  = _discreteFrechetLen;

        }
}

//-------------------------------------------------------------------------------------------------

void DiscreteFrechet::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _discreteFrechetDist,int &_discreteFrechetLen )
{
    
    int n1 =   (int)Ts1->getSize();
    int n2 =   (int)Ts2->getSize();
    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Dtw \n");

    vector<double>  ca( n1 * n2 );



    int i, j;
    
    for ( i = 0; i < n1; i++)
    {
        for ( j = 0; j < n2; j++)
        {
            ca[i + n1 * j] = -1;
        }
    }
    _discreteFrechetDist = recursiveFunc(Ts1, n1, Ts2, n2, dim1, ca, n1 -1 , n2 -1);
}
//-------------------------------------------------------------------------------------------------

vector< vector<int> > * DiscreteFrechet::addressRepoLen()
{
    return &discreteFrechetLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  DiscreteFrechet::addressRepoDist()
{
    return &discreteFrechetDist;
}

//-------------------------------------------------------------------------------------------------
DiscreteFrechet::~DiscreteFrechet()
{
    
}
//-------------------------------------------------------------------------------------------------

