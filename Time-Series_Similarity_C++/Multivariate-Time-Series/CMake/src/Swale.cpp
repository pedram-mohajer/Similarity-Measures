// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Swale.hpp"
#include "limits"
#include <iostream>
#include <cmath>
#include "Functions.hpp"

class TimeSeries;
using namespace std;

//-------------------------------------------------------------------------------------------------


void Swale::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double  _swaleDist;
    int     _swaleLen;
    
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
            
            compute( path[i].get(), path[j].get() ,  _swaleDist, _swaleLen);
            swaleDist[i][j] = _swaleDist;
            swaleLen[i][j]  = _swaleLen;

        }
        
    }
    
}
//-------------------------------------------------------------------------------------------------

void Swale::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _swaleDist,int &_swaleLen )
{
    
    
    int n1 =   (int)Ts1->getSize();
    int n2 =   (int)Ts2->getSize();
    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Swale \n");

    vector<vector <string>>  timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector<vector <string>>  timeSerieDataSecond  = Ts2->getTimeSerieData();

    double D[n1 + 1][n2 + 1];
    int i, j;
    int jS, jF;
    int lenDiff;
    double tmp;
    
    
    
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
    for ( i = 0; i <= n1; i++)
    {
        for ( j = 0; j <= n2; j++)
        {
            D[i][j] = 0;
            
            if (i == 0)
            {
                D[i][j] = gapC * j;
            }
            if (j == 0)
            {
                D[i][j] = gapC * i;
            }
        }
    }
    
    
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
            tmp = euclideanCalculate(timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, i-1, j-1);
            
            if (tmp < eps)
            {
                D[i][j] = D[i-1][j-1] + reward;
            }
            else
            {
                D[i][j] = D[i][j-1] + gapC;
                
                if (D[i][j] < D[i-1][j] + gapC)
                {
                    D[i][j] = D[i-1][j] + gapC;
                }
            }

        }
    }

    _swaleDist = D[n1][n2];

}


//-------------------------------------------------------------------------------------------------

double Swale::getParam()
{
    return winSize;
}

//-------------------------------------------------------------------------------------------------

vector< vector<int> > * Swale::addressRepoLen()
{
    return &swaleLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  Swale::addressRepoDist()
{
    return &swaleDist;
}

//-------------------------------------------------------------------------------------------------
Swale::~Swale()
{
    
}
//-------------------------------------------------------------------------------------------------

Swale::Swale(int size,double  * _winSize ,double * _winRatio ,double * _eps,double * _gapC,double * _reward)
{
    
    winSize  = _winSize[0];
    winRatio = _winRatio[0];
    eps  = _eps[0];
    gapC = _gapC[0];
    reward = _reward[0];
    
    swaleLen.resize(size);
    swaleDist.resize(size);
    
    for(int i=0;i<size;i++)
    {
        swaleLen[i].resize(size);
        swaleDist[i].resize(size);
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            swaleLen[i][j] = -1;
            swaleDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------

double Swale::euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2)
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

