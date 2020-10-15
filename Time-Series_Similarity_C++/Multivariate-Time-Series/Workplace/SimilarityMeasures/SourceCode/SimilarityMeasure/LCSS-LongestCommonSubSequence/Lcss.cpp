// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "cmath"
#include "Lcss.hpp"
#include "limits"
#include <iostream>
#include "Functions.hpp"


class TimeSeries;
using namespace std;

//-------------------------------------------------------------------------------------------------


void Lcss::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double  _lcssDist;
    int     _lcssLen;
    
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
            
            
            compute( path[i].get(), path[j].get() ,  _lcssDist, _lcssLen);
            lcssDist[i][j] = _lcssDist;
            lcssLen[i][j]  = _lcssLen;
            
        }
        
    }

}
//-------------------------------------------------------------------------------------------------

void Lcss::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _lcssDist,int &_lcssLen )
{
    
    
    int n1 =   (int)Ts1->getSize();
    int n2 =   (int)Ts2->getSize();
    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Lcss \n");
    
    vector<vector <string>>  timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector<vector <string>>  timeSerieDataSecond  = Ts2->getTimeSerieData();

    
    
    vector<vector<double> > D( n1+1 , vector<double> (n2+1, 0));


    
    int i, j;
    int jS, jF;
    double euclDist;
    int lenDiff;
    double tmp;
    
    
    if (n1 - n2 > 0)
    {
         lenDiff = n1 - n2;
        tmp = (double) n2;
    }
    else
    {
         lenDiff = n2 - n1;
        tmp = (double) n1;
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
            euclDist = euclideanCalculate(timeSerieDataFirst, n1, timeSerieDataSecond, n2, dim1, i-1, j-1);
            if (euclDist < epsilon)
            {
                D[i][j] = D[i-1][j-1] + 1;
            }
            else
            {
                if (D[i][j-1] > D[i-1][j])
                {
                    D[i][j] = D[i][j-1];
                }
                else
                {
                    D[i][j] = D[i-1][j];
                }
            }
            
        }
    }
    
    
    _lcssDist = 1 - (D[n1][n2] / tmp);
    
    
    
}



//-------------------------------------------------------------------------------------------------

double Lcss::getParam()
{
    return winSize;
}

//-------------------------------------------------------------------------------------------------

vector< vector<int> > * Lcss::addressRepoLen()
{
    return &lcssLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  Lcss::addressRepoDist()
{
    return &lcssDist;
}

//-------------------------------------------------------------------------------------------------
Lcss::~Lcss()
{
    
}
//-------------------------------------------------------------------------------------------------

Lcss::Lcss(int size,double * _winSize ,double * _winRatio ,double * _epsilon)
{
    
    winSize  = _winSize[0];
    winRatio = _winRatio[0];
    epsilon  = _epsilon[0];
    
    lcssLen.resize(size);
    lcssDist.resize(size);
    for(int i=0;i<size;i++)
    {
        lcssLen[i].resize(size);
        lcssDist[i].resize(size);
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            lcssLen[i][j] = -1;
            lcssDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------
double Lcss::euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2)
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
