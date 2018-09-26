
//*******************************************************************
// Neural Network model

// Error bars are calculated using the blocking technique.
// Let ' \chi^2 = \sum_{t=1}^{T} <(O_t -<O>)^2> ' be the squared chi for
// 'T' blocks of observable 'O'. Assuming each block of data is independent
// of each other, the error bar of 'O' is given by 'Dev = \sqrt{\chi^2/T(T-1)}.

// Reliabity of the obtained errors is monitored by t=1 correlation,
// for which tolerance is set by variable 'tol' (default: tol=0.20d0).

// Composite quantities like Binder ratios are calculated in each block, and
// the associated error bars are obtained from their fluctuations.

// Results are written into a special file 'dat.***' if the number of
// blocks is less than 125 or correlation is too big. Data in each
// block will be also printed out in this case.

// Default number of extensive simulation is 'NBlck=1024'.

// For test purpose, for which huge amount of information will be
// printed out, 'NBlck' should be set smaller but >2.

//  For new project, some functions need to be changed.
//  Look for 'PROJECT-DEPENDENT'.

//  Author: Qi Yang
//  Date  : Sept 3rd, 2018.
//*******************************************************************

// Look for 'PROJECT-DEPENDENT' for different projects
#include <vector>
#include<iostream>
#include"my_rng.h"
#include <math.h>
#include "Eigen/Dense"
#ifndef _MY_VRBLS_
#define _MY_VRBLS_
//Useful function
extern int Ipow(int, int);

//-------Parameters used in Output----
//-------Project-depended---
extern char	      ident[];							//Project name
extern char		  data_file[] ;						//File for proper data
extern char		  cor_data_file[] ;					//File for big correlation data
extern bool		  prt;								//indicate whether we which file we need to out put to


//-------Parameters used in Science----
//-------Project-independed---
extern int      Mxint ;								// maximum int
extern int      Mnint;								// minimum int
extern double   tm32 ;			
extern double   eps ;								//very small number
extern double   tol ;								//tolerance of correlation
extern double   Pi ;

//-------Parameters used in Monte Carlo simulation----
//-------Project-independed---
extern int NBlck;
extern int NSample;
extern int TotalSample;
extern int NToss;
extern int TossThrown;

extern int MxBlck;
extern int MnBlck;
//-------Parameters used in Markov Cahin---
//-------Project-depended//----

extern double p;
//-------Dynamical Parameters in Markov Chain--

//-------Prameters used in Simulation----
//-------Project-depended//----
extern	int			N ;						//Size
extern int			Vol;
extern  int*		Block;
extern int* up;
extern int* left;
extern int* set;
extern int* count;
extern int** CORES;
//--parameters and variables------------------------------------ -
//THIS IS PROJECT - DEPENDENT
//-----------------------------------------------------------------

//--Statistics and measurement---------------------------------------
//THIS IS PROJECT - DEPENDENT
extern int NObs_b;								//#basic     observables
extern int NObs_c;								//#composite observables
extern int NObs;									//#total     observables
extern Eigen::ArrayXd  Quan;							//Measured quantities
extern Eigen::ArrayXXd Obs;								//1st--#quan.  2nd--#block
extern Eigen::ArrayXd  Ave, Dev, Cor;					//average, error bars, and correlation of observables
//-----------------------------------------------------------------


#endif 
