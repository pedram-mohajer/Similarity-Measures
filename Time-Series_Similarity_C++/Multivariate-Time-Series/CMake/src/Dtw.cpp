// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "limits"
#include "Dtw.hpp"
#include <iostream>
#include <cmath>
#include "Functions.hpp"


class TimeSeries;
using namespace std;

//-------------------------------------------------------------------------------------------------


void Dtw::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double  _dtwDist;
    int     _dtwLen;
    
    
    int size =  (int)path.size();
  
    
    
    int i,j=0;
    
    
    double tmp;

    for( i=0 ; i< size ; i++)
    {
        double percent;
        percent = (double) 100 * (i + 1) / size;
        cout << "Percent Done : %3.1f " <<  percent << endl;
        
        
         int n1 = (int)path[i].get()->getSize();

        for( j=i+1 ; j< size ;j++)
        {
            
            
                int n2 = (int)path[j].get()->getSize();
            
                tmp = fabs(n2 - n1);
                if (n1 > n2)
                {
                   // dtwLenMax[j + size * i] = n1;
                    if (winSize != -1)
                        winSize = (int) tmp + n2 * winRatio;
                }
                else
                {
                   // dtwLenMax[j + size * i] = n2;
                    if (winSize != -1)
                        winSize = (int) tmp + n1 * winRatio;
                }
            
            
                compute( path[i].get(), path[j].get() ,  _dtwDist, _dtwLen);
                dtwDist[i][j] = _dtwDist;
                dtwLen[i][j]  = _dtwLen;
        
        }
    
    }

    
}

//-------------------------------------------------------------------------------------------------

void Dtw::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _dtwDist,int &_dtwLen )
{
    int n1 =   (int)Ts1->getSize();
    int n2 =   (int)Ts2->getSize();
    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Dtw \n");




    vector<vector <string>>  timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector<vector <string>>  timeSerieDataSecond  = Ts2->getTimeSerieData();
    
    
    vector<vector<double> > D( n1+1 , vector<double> (n2+1, 0));
    vector<vector<int> > L( n1+1 , vector<int> (n2+1, 0));


    int i, j;
    int jS, jF;
    double euclDist;
    int lenDiff;
    double iNFINITY= numeric_limits <double> ::infinity();
    
    
    if (n1 - n2 > 0)
    {
         lenDiff = n1 - n2;
    }
    else
    {
         lenDiff = n2 - n1;
    }
    
    if (winSize != -1 && winSize < lenDiff)
    {
        winSize = lenDiff;
    }
    
    for (i = 0; i <= n1; i++)
    {
        for (j = 0; j <= n2; j++)
        {
            D[i][j] = iNFINITY;
            L[i][j] = 0;
        }
    }
    
    D[0][0] = 0;
    
    for (i = 1; i <= n1; i++)
    {
        if (winSize == -1)
        {
            jS = 1;
            jF = n2;
        }
        else
        {
            jS = i - winSize > 1 ? i - winSize : 1;
            jF = i + winSize < n2 ? i + winSize : n2;
        }
        for (j = jS; j <= jF; j++)
        {
            euclDist =
            euclideanCalculate(timeSerieDataFirst,n1,timeSerieDataSecond,n2,dim1,i-1,j-1);
            D[i][j] = D[i-1][j-1];
            L[i][j] = L[i-1][j-1];
            if (D[i][j] > D[i-1][j])
            {
                D[i][j] = D[i-1][j];
                L[i][j] = L[i-1][j];
            }
            if (D[i][j] > D[i][j-1])
            {
                D[i][j] = D[i][j-1];
                L[i][j] = L[i][j-1];
            }
            D[i][j] += euclDist;
            L[i][j] += 1;
            
        }
    }
    
    
    _dtwDist = D[n1][n2];
    _dtwLen  = L[n1][n2];
    
    return;
}


//-------------------------------------------------------------------------------------------------

double Dtw::getParam()
{
    return winSize;
}

//-------------------------------------------------------------------------------------------------

vector< vector<int> > * Dtw::addressRepoLen()
{
    return &dtwLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  Dtw::addressRepoDist()
{
        return &dtwDist;
}

//-------------------------------------------------------------------------------------------------
Dtw::~Dtw()
{
    
}
//-------------------------------------------------------------------------------------------------

Dtw::Dtw(int size, double * _winSize ,double * _winRatio)
{
    winSize  = _winSize[0];
    winRatio = _winRatio[0];
    
    dtwLen.resize(size);
    dtwDist.resize(size);
    for(int i=0;i<size;i++)
    {
        dtwLen[i].resize(size);
        dtwDist[i].resize(size);
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            dtwLen[i][j] = -1;
            dtwDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------
double Dtw::euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2)
{
    double euclDist = 0;
    int i;
    double tmp;
    
    for (i = 0; i < dim; i++)
    {
        tmp = stod(ts1[i][idx1]) - stod(ts2[i][idx2]);
        euclDist += tmp * tmp;
    }
    euclDist = sqrt(euclDist);
    return euclDist;
}


//-------------------------------------------------------------------------------------------------




