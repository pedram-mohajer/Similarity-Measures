// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Wdtw.hpp"
#include "limits"
#include <iostream>
#include <cmath>
#include "Functions.hpp"

class TimeSeries;
using namespace std;

//-------------------------------------------------------------------------------------------------


void Wdtw::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double  _wdtwDist;
    int     _wdtwLen;
    
    unique_ptr <TimeSeries> timeseries ( path.back().get() );
    
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
                if (winSize != -1)
                    winSize = (int) tmp + n2 * winRatio;
            }
            else
            {
                if (winSize != -1)
                    winSize = (int) tmp + n1 * winRatio;
            }
            
            compute( path[i].get(), path[j].get() ,  _wdtwDist, _wdtwLen);
            wdtwDist[i][j] = _wdtwDist;
            wdtwLen[i][j]  = _wdtwLen;
            
        }
        
    }
}
//-------------------------------------------------------------------------------------------------

void Wdtw::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _wdtwDist,int &_wdtwLen )
{
    
    
    
    int n1 =   (int)Ts1->getSize();
    int n2 =   (int)Ts2->getSize();

    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Wdtw \n");

    vector<vector <string>>  timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector<vector <string>>  timeSerieDataSecond  = Ts2->getTimeSerieData();

    
    double D[n1 + 1][n2 + 1];
    int L[n1 + 1][n2 + 1];
    int i, j;
    int jS, jF;
    double euclDist, weightVal;
    int lenDiff;
    
    
    
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
            D[i][j] = INFINITY;
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
            weightVal = weightCalculate(i, j, n1, n2, g, weightMax);
           
            euclDist = euclideanCalculate(timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, i-1, j-1);

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
            D[i][j] += weightVal * euclDist;
            L[i][j] += 1;
            
        }
    }
    
    
    _wdtwDist = D[n1][n2];
    _wdtwLen = L[n1][n2];
}


//-------------------------------------------------------------------------------------------------

double Wdtw::getParam()
{
    return winSize;
}

//-------------------------------------------------------------------------------------------------

vector< vector<int> > * Wdtw::addressRepoLen()
{
    return &wdtwLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  Wdtw::addressRepoDist()
{
    return &wdtwDist;
}

//-------------------------------------------------------------------------------------------------
Wdtw::~Wdtw()
{
    
}
//-------------------------------------------------------------------------------------------------

Wdtw::Wdtw(int size,double  * _winSize ,double * _winRatio ,double * _weightMax,double * _g)
{
    
    winSize    = _winSize[0];
    winRatio   = _winRatio[0];
    weightMax  = _weightMax[0];
    g = _g[0];
    
    wdtwLen.resize(size);
    wdtwDist.resize(size);
    for(int i=0;i<size;i++)
    {
        wdtwLen[i].resize(size);
        wdtwDist[i].resize(size);
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            wdtwLen[i][j] = -1;
            wdtwDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------

double Wdtw::euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2)
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


double Wdtw::weightCalculate(int i, int j, int n1, int n2, double g, double weightMax)
{
    double output;
    double diff, len;
    
    diff = (double) abs(i - j);
    len = (double) (n1 + n2);
    len = len / 2;
    output = weightMax / ( 1 + exp(-g * (diff - (len / 2) ) ) );
    
    return output;
}
//-------------------------------------------------------------------------------------------------

