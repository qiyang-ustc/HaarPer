#include <math.h>
#include "my_vrbls.h"
#include "Eigen/Dense"
//============= = Measurement ======================================== =
//THIS IS PROJECT - DEPENDENT
double ave()
{
	int sum = 0;
	
	for (int i = 0;i < Vol;i++)
	{
		sum += Block[i];
		//std::cout << Block[i] << "\n";
	}
	return 1.0*sum / Vol;
}

double HaarDecomposition(int index_cores)
{
	int sum = 0;
	for (int i = 0;i < Vol;i++)
	{
		sum += Block[i] * CORES[index_cores-1][i];
	}
	return 1.0*sum / Vol;
}
void measure()
{
	Quan(0) = fabs(ave());
	//std::cout << Quan(0) << std::endl;
	for(int i = 1;i < NObs_b;i++)
	{
		Quan(i) = fabs(HaarDecomposition(i));
	}
}

void cal_Q(int jb, int b1, int b2, int epo)
{
	int k;
	double tmp;

	//--Average----------------------------------------------------
	tmp = pow(Ave[b1], epo);   if (fabs(tmp) > eps) tmp = Ave[b2] / tmp;
	Ave[jb] = tmp;

	//--Obs(j, k) series--------------------------------------------
	for (k = 0;k < NBlck;k++) 
	{
		tmp = pow(Obs(b1,k), epo);   if (fabs(tmp) > eps) tmp = Obs(b2,k) / tmp;
		Obs(jb,k) = tmp;
	}
}
//===================================================================== =

//============= = Calculate Binder ratio 2================================
//Q = <(o - <o>) ^ 4> / <(o - <o>) ^ 2> ^ 4
//THIS IS PROJECT - DEPENDENT
void Cal_QE(int jb,int b1,int b2,int b3,int b4)
{
	int k;
	double a1, a2, a3, a4, q0, q1;
	//--Average----------------------------------------------------
	a1 = Ave(b1);  a2 = Ave(b2);  a3 = Ave(b3);   a4 = Ave(b4);
	q0 = a4 - 4 * a3*a1 + 6 * a2*a1*a1 - 3 * pow(a1, 4.0);
	q1 = a2 - a1*a1;   q1 = q1*q1;
	Ave(jb) = 2.0;   if (q1 > eps) Ave(jb) = q0 / q1;

	//--Obs(j, k) series--------------------------------------------
	for(k = 0;k < NBlck;k++)
	{
		a1 = Obs(b1,k);  a2 = Obs(b2,k);  a3 = Obs(b3,k);   a4 = Obs(b4,k);
		q0 = a4 - 4 * a3*a1 + 6 * a2*a1*a1 - 3 * pow(a1, 4.0);
		q1 = a2 - a1*a1;   q1 = q1*q1;
		Obs(jb,k) = 2.0;   
		if (q1 > eps) Obs(jb,k) = q0 / q1;
	}
}
//======================================================================

void Cal_Obs_Comp()
{
	//int jb, b2, b3, b1;
	//--calculate the average----------------------------------------
	//jb = NObs_b + 1;   call cal_QE(jb, 1, 2, 3, 4)           //Qe = <E ^ 4> / <E ^ 2> ^ 2
}//===================================================================
