// ----------------------------------------------------------------------------------------------
//     Author
// -----------------
//     Pedram MohajerAnsari
//     Sirjan University of Technology, Sirjan, Kerman, Iran,  Dept. of Computer Engineering
//     Email :  pmohaje@g.clemson.edu
//              pedram.mohajer@outlook.com
//              
// ----------------------------------------------------------------------------------------------


#include "Hausdorff.hpp"
#include "limits"
#include <iostream>
#include <cmath>
#include "Functions.hpp"

class TimeSeries;
using namespace std;

//-------------------------------------------------------------------------------------------------
Hausdorff::Hausdorff(int size)
{
    hausdorffLen.resize(size);
    hausdorffDist.resize(size);
    for(int i=0;i<size;i++)
    {
        hausdorffLen[i].resize(size);
        hausdorffDist[i].resize(size);
    }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            hausdorffLen[i][j] = -1;
            hausdorffDist[i][j] = -1;
        }
    
}
//-------------------------------------------------------------------------------------------------


void Hausdorff::computeAll(vector < unique_ptr <TimeSeries> > & path)
{
    double haus1,haus2;
    double  _hausdorffDist;
    int     _hausdorffLen;
    
    int size = (int)path.size();

    
    for(int i=0 ; i< size  ; i++)
        for(int j=i ; j<  size ;j++)
        {
            compute( path[i].get(), path[j].get() ,  _hausdorffDist, _hausdorffLen);
            haus1 = _hausdorffDist;
            compute( path[j].get(), path[i].get() ,  _hausdorffDist, _hausdorffLen);
            haus2 = _hausdorffDist;
            if (haus1 > haus2)
            {
                hausdorffDist[i][j] = haus1;
            }
            else
            {
                hausdorffDist[i][j] = haus2;
            }
            
            
        }
}

//-------------------------------------------------------------------------------------------------

void Hausdorff::compute(TimeSeries *Ts1, TimeSeries *Ts2 ,double & _hausdorffDist,int &_hausdorffLen )
{
    
    int n1   =   (int)Ts1->getSize() ;
    int n2   =   (int)Ts2->getSize();
    int dim1 = (int)Ts1->getDimensional();
    int dim2 = (int)Ts2->getDimensional();
    
    if (dim1 != dim2)
        throw("Two time series dimension must be the same in Dtw \n");
    
    
    vector <string> timeSerieDataFirst   = Ts1->getTimeSerieData();
    vector <string>  timeSerieDataSecond = Ts2->getTimeSerieData();
    
    double *timeSerieDataFirstDouble  =  VectorToDouble(timeSerieDataFirst);
    double *timeSerieDataSecondDouble =  VectorToDouble(timeSerieDataSecond);
    
    
    
    
    int i, j;
    double tmp, tmpMin, tmpSum = 0;
    
    for (i = 0; i < n1; i++)
    {
        tmpMin = INFINITY;
        for (j = 0; j < n2 - 1; j++)
        {
            tmp = point2SegmentDistance(timeSerieDataFirstDouble, n1, timeSerieDataSecondDouble, n2, dim1, i, j);
            if (tmp < tmpMin)
            {
                tmpMin = tmp;
            }
        }
        tmpSum += tmpMin;
    }
    
    _hausdorffDist = tmpSum;
    
}


//-------------------------------------------------------------------------------------------------

vector< vector<int> > * Hausdorff::addressRepoLen()
{
    return &hausdorffLen;
}

//-------------------------------------------------------------------------------------------------

vector< vector<double> > *  Hausdorff::addressRepoDist()
{
    return &hausdorffDist;
}

//-------------------------------------------------------------------------------------------------
Hausdorff::~Hausdorff()
{
    
}
//-------------------------------------------------------------------------------------------------
double Hausdorff::point2SegmentDistance(double *ts1, int n1, double *ts2, int n2, int dim, int idx1, int idx2)
{
    
    double A, B, C, D, E, F, G, H;
    double dotProd, lenSq, tmp, param, distStart, distEnd;
    double xProj, yProj;
    
    A = ts1[idx1 + n1 * 0] - ts2[idx2 + n2 * 0];
    B = ts1[idx1 + n1 * 1] - ts2[idx2 + n2 * 1];
    C = ts2[(idx2 + 1) + n2 * 0] - ts2[idx2 + n2 * 0];
    D = ts2[(idx2 + 1) + n2 * 1] - ts2[idx2 + n2 * 1];
    
    E = ts1[idx1 + n1 * 0] - ts2[(idx2 + 1) + n2 * 0];
    F = ts1[idx1 + n1 * 1] - ts2[(idx2 + 1) + n2 * 1];
    
    dotProd = A * C + B * D;
    lenSq = C * C + D * D;
    
    if (lenSq == 0)
    {
        tmp = sqrt(A * A + B * B);
        return tmp;
    }
    else
    {
        param = dotProd / lenSq;
        if (param < 0.00001 || param > 1)
        {
            
            distStart = sqrt(A * A + B * B);
            distEnd = sqrt(E * E + F * F);
            
            
            if (distStart > distEnd)
            {
                return distEnd;
            }
            else
            {
                return distStart;
            }
        }
        xProj = ts2[idx2 + n2 * 0] + param * C;
        yProj = ts2[idx2 + n2 * 1] + param * D;
        
        G = ts1[idx1 + n1 * 0] - xProj;
        H = ts1[idx1 + n1 * 1] - yProj;
        tmp = sqrt(G * G + H * H);
        return tmp;
    }
    
}

//-------------------------------------------------------------------------------------------------

