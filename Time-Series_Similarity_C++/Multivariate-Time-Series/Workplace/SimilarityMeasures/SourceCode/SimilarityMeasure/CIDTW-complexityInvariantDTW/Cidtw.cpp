// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Cidtw.hpp"
#include "limits"
#include "Cidtw.hpp"
#include <iostream>
#include <cmath>
#include "Functions.hpp"


class TimeSeries;
using namespace std;

//-------------------------------------------------------------------------------------------------


void Cidtw::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double  _cidtwDist;
    int     _cidtwLen;
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
            
            
            compute( path[i].get(), path[j].get() ,  _cidtwDist, _cidtwLen);
            cidtwDist[i][j] = _cidtwDist;
            cidtwLen[i][j]  = _cidtwLen;
            
        }
        
    }
    
}
//-------------------------------------------------------------------------------------------------
Cidtw::Cidtw(int size,double * _winSize ,double * _winRatio)
{
    winSize  = _winSize[0];
    winRatio = _winRatio[0];
    
    cidtwLen.resize(size);
    cidtwDist.resize(size);
    for(int i=0;i<size;i++)
    {
        cidtwLen[i].resize(size);
        cidtwDist[i].resize(size);
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            cidtwLen[i][j] = -1;
            cidtwDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------

void Cidtw::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _cidtwDist,int &_cidtwLen )
{
    
    int n1 =   (int)Ts1->getSize();
    int n2 =   (int)Ts2->getSize();
    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Dtw \n");
    
    vector<vector <string>>  timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector<vector <string>>  timeSerieDataSecond  = Ts2->getTimeSerieData();

    

    double D[n1+1][n2+1];
    int    L[n1+1][n2+1];
    int i, j;
    int jS, jF;
    double euclDist;
    int lenDiff;
    double CE1 = 0, CE2 = 0;
    double tmp;
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
            euclDist = euclideanCalculate(timeSerieDataFirst,n1,timeSerieDataSecond,n2, dim1, i-1, j-1);
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
    for ( i = 0; i < n1 - 1; i++)
    {
        for (j = 0; j <dim1; j++)
        {
            tmp = stod(timeSerieDataFirst[j][i]) - stod(timeSerieDataFirst[j][i+1]);
            CE1 += tmp * tmp;
        }
    }
    
    CE1 = sqrt(CE1);
    
    for ( i = 0; i < n2 - 1; i++)
    {
        for (j = 0; j <dim1; j++)
        {
            tmp = stod(timeSerieDataSecond[j][i]) - stod(timeSerieDataSecond[j][i+1]);
            CE2 += tmp * tmp;
        }
    }

    CE2 = sqrt(CE2);
    
    if ( CE1 > CE2)
        tmp = CE1 / CE2;
    else
        tmp = CE2 / CE1;
    
    _cidtwDist = D[n1][n2] * tmp;
    _cidtwLen = L[n1][n2];
    


}



//-------------------------------------------------------------------------------------------------

double Cidtw::getParam()
{
    return winSize;
}

//-------------------------------------------------------------------------------------------------

vector< vector<int> > * Cidtw::addressRepoLen()
{
    return &cidtwLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  Cidtw::addressRepoDist()
{
    return &cidtwDist;
}

//-------------------------------------------------------------------------------------------------
Cidtw::~Cidtw()
{
    
}
//-------------------------------------------------------------------------------------------------

double Cidtw::euclideanCalculate(vector<vector <string>> &ts1,int n1,vector<vector <string>> &ts2,int n2,int dim, int idx1,int idx2)
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



