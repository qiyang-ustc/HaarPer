#include <math.h>
#include <vector>
#include "my_rng.h"
#include <fstream>
#include <string>
#include "Eigen/Dense"
int Ipow(int a, int b)
{
	int sum=1;
	for (int i = 0;i < b;i++)
	{
		sum *= a;
	}
	return sum;
}




//-------Parameters used in Output----
//-------Project-depended---
char	      ident[] = "HaarPer2D";	    //Project name
char		  data_file[] = "HaarPer2D.dat";		//File for proper data
char		  cor_data_file[] = "cor.dat";	//File for big correlation data
bool		  prt;							//indicate whether we which file we need to out put to


//-------Parameters used in Science----
//-------Project-independed---
int		      Mxint = 2147483647;			// maximum int
int		      Mnint = -2147483647;			// minimum int
double		   tm32 = 1.0 / Ipow(2, 32);
double		   eps = 1.0E-14;				//very small number
double		   tol = 0.20;					//tolerance of correlation
double		   Pi= 4 * atan(1.0);

//-------Parameters used in Monte Carlo simulation----
//-------Project-independed---
int NBlck;
int NSample;
int TotalSample;
int NToss;
int TossThrown;
int MxBlck = 1024;
int MnBlck = 2;
//-------Parameters used in Markov Cahin---
//-------Project-depended//----
double p;

//-------Prameters used in Simulation----
//-------Project-depended//----
int			  N = 512;								//Size of Percolation
int* Block;
int* up;
int* left;
int Vol=N*N;
int* set;
int** CORES;
int* count;
//--Statistics and measurement---------------------------------------
//THIS IS PROJECT - DEPENDENT
int NObs_b		 = 1+2*round(log(N)/log(2));								//#basic     observables
int NObs_c		 = 0;								//#composite observables
int NObs		 = NObs_b + NObs_c;					//#total     observables
Eigen::ArrayXd  Quan(NObs_b);						//Measured quantities
Eigen::ArrayXXd Obs(NObs,MxBlck);					//1st--#quan.  2nd--#block
Eigen::ArrayXd  Ave(NObs), Dev(NObs), Cor(NObs);	//average, error bars, and correlation of observables

//-----------------------------------------------------------------
