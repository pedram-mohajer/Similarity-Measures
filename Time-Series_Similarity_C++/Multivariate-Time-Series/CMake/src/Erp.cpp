// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Erp.hpp"
#include "limits"
#include <iostream>
#include <cmath>
#include "Functions.hpp"


class TimeSeries;
using namespace std;

//-------------------------------------------------------------------------------------------------


void Erp::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double  _erpDist;
    int     _erpLen;
    
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
            
            compute( path[i].get(), path[j].get() ,  _erpDist, _erpLen);
            erpDist[i][j] = _erpDist;
            erpLen[i][j]  = _erpLen;
            
        }
        
    }
}

//-------------------------------------------------------------------------------------------------

void Erp::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _erpDist,int &_erpLen )
{
    
    
    int n1 =   (int)Ts1->getSize();
    int n2 =   (int)Ts2->getSize();
    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Erp \n");

    vector<vector <string>>  timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector<vector <string>>  timeSerieDataSecond  = Ts2->getTimeSerieData();

    vector <vector<string>> Gap(dim1);
    for(int i=0 ; i<dim1 ; i++)
    	Gap[i].push_back( to_string(gap[0]) );
    
    double tmp;
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
    
    
    double D[n1 + 1][n2 + 1];
    int i, j;
    int jS, jF;
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
            D[i][j] = 0;
            
            if (i == 0 && j >= 1)
            {
                D[0][j] = D[0][j-1] + euclideanCalculate(timeSerieDataSecond, n2, Gap, 1, dim1, j-1, 0);
            }
            if (j == 0 && i>= 1)
            {
                D[i][0] = D[i-1][0] + euclideanCalculate(timeSerieDataFirst, n1, Gap, 1, dim1, i-1, 0);
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
            D[i][j] = D[i-1][j-1] + euclideanCalculate(timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, i-1, j-1);
            
            tmp = D[i][j-1] + euclideanCalculate(timeSerieDataSecond, n2, Gap, 1, dim1, j-1, 0);
            if (tmp < D[i][j])
            {
                D[i][j] = tmp;
            }
            tmp = D[i-1][j] + euclideanCalculate(timeSerieDataFirst, n1, Gap, 1, dim1, i-1, 0);
            if (tmp < D[i][j])
            {
                D[i][j] = tmp;
            }
            
        }
    }
    
    _erpDist = D[n1][n2];
    
}



//-------------------------------------------------------------------------------------------------

double Erp::getParam()
{
    return winSize;
}

//-------------------------------------------------------------------------------------------------

vector< vector<int> > * Erp::addressRepoLen()
{
    return &erpLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  Erp::addressRepoDist()
{
    return &erpDist;
}

//-------------------------------------------------------------------------------------------------
Erp::~Erp()
{
    
}
//-------------------------------------------------------------------------------------------------

Erp::Erp(int size,double * _winSize ,double * _winRatio,double * _gap)
{
    winSize  = _winSize[0];
    winRatio = _winRatio[0];
    gap = _gap;
    
    erpLen.resize(size);
    erpDist.resize(size);
    for(int i=0;i<size;i++)
    {
        erpLen[i].resize(size);
        erpDist[i].resize(size);
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            erpLen[i][j] = -1;
            erpDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------
double Erp::euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2)
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

