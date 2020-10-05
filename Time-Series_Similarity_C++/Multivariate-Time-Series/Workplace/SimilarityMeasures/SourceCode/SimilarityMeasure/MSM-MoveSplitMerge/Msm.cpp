// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Msm.hpp"
#include "limits"
#include <iostream>
#include <cmath>
#include "Functions.hpp"

class TimeSeries;
using namespace std;


//-------------------------------------------------------------------------------------------------
double Msm::msmCost(vector<vector <string>> &tsA, int nA, vector<vector <string>> &tsB, int nB, vector<vector <string>> & tsC, int nC, int dim, double cost, int idxA, int idxB, int idxC)
{
    double ax, ay, bx, by, cx, cy;
    double output, tmp1, tmp2;
    
    ax = stod(tsA[0][idxA]);
    ay = stod(tsA[1][idxA]);
    bx = stod(tsB[0][idxB]);
    by = stod(tsB[1][idxB]);
    cx = stod(tsC[0][idxC]);
    cy = stod(tsC[1][idxC]);
    
    if ( (bx <= ax && by <= ay && ax <= cx && ay <= cy) || (cx <= ax && cy <= ay && ax <= bx && ay <= by) )
    {
        output = cost;
    }
    else
    {
        tmp1 = euclideanCalculate(tsA, nA, tsB, nB, dim, idxA, idxB);
        tmp2 = euclideanCalculate(tsA, nA, tsC, nC, dim, idxA, idxC);
        
        if (tmp1 < tmp2)
        {
            output = cost + tmp1;
        }
        else
        {
            output = cost + tmp2;
        }
    }
    return output;
}

//-------------------------------------------------------------------------------------------------


void Msm::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double  _msmDist;
    int     _msmLen;
    
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
            
            
            int n2 =(int) path[j].get()->getSize();
            
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
            
            compute( path[i].get(), path[j].get() ,  _msmDist, _msmLen);
            msmDist[i][j] = _msmDist;
            msmLen[i][j]  = _msmLen;
            
        }
        
    }
    
}
//-------------------------------------------------------------------------------------------------

void Msm::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _msmDist,int &_msmLen )
{
    
    
    int n1 =   (int)Ts1->getSize();
    int n2 =   (int)Ts2->getSize();
    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Msm \n");
    
    vector<vector <string>>  timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector<vector <string>>  timeSerieDataSecond  = Ts2->getTimeSerieData();

    
    

    double D[n1][n2];
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
    
    D[0][0] = euclideanCalculate(timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, 0, 0);
    
    for (i = 1; i < n1; i++)
    {
        D[i][0] = D[i-1][0] + msmCost(timeSerieDataFirst, n1, timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, cost, i, i-1, 0);
    }
    
    for (j = 1; j < n2; j++)
    {
        D[0][j] = D[0][j-1] + msmCost(timeSerieDataSecond, n2, timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, cost, j, 0, j-1);
    }
    
    for (i = 1; i < n1; i++)
    {
        if (winSize == -1)
        {
            jS = 1;
            jF = n2;
        }
        else
        {
            jS = i - winSize > 1 ? i - winSize : 1;
            jF = i + winSize < n2 ? i + winSize + 1 : n2;
        }
        
        for (j = jS; j < jF; j++)
        {
            tmp = euclideanCalculate(timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, i, j);
            D[i][j] = D[i-1][j-1] + tmp;
            
            tmp = D[i-1][j] + msmCost(timeSerieDataFirst, n1, timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, cost, i, i-1, j);
            
            if (tmp < D[i][j])
            {
                D[i][j] = tmp;
            }
            
            tmp = D[i][j-1] + msmCost(timeSerieDataSecond, n2, timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, cost, j, i, j-1);
            
            if (tmp < D[i][j])
            {
                D[i][j] = tmp;
            }
            
            
        }
    }
    
    
    _msmDist = D[n1-1][n2-1];
    
    
}

//-------------------------------------------------------------------------------------------------

double Msm::getParam()
{
    return winSize;
}

//-------------------------------------------------------------------------------------------------

vector< vector<int> > * Msm::addressRepoLen()
{
    return &msmLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  Msm::addressRepoDist()
{
    return &msmDist;
}

//-------------------------------------------------------------------------------------------------
Msm::~Msm()
{
    
}
//-------------------------------------------------------------------------------------------------

Msm::Msm(int size,double * _winSize ,double * _winRatio ,double * _cost)
{
    
    winSize  = _winSize[0];
    winRatio = _winRatio[0];
    cost  = _cost[0];
    
    msmLen.resize(size);
    msmDist.resize(size);
    for(int i=0;i<size;i++)
    {
        msmLen[i].resize(size);
        msmDist[i].resize(size);
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            msmLen[i][j] = -1;
            msmDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------

double Msm::euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2)
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

