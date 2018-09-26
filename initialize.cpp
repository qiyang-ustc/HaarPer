#include <math.h>
#include "my_vrbls.h"
#include <iostream>
#include <stdio.h>
#include "Markov.h"
#include "measure.h"
//----this "find(indicator)"is highly project-dependent
//---- PROJECT - DEPENDENT---------------------------------------------
//WARNING: This model should be changed with int* find(indicator)!!

//============= = Test and Print ======================================
//!!THIS IS PROJECT - DEPENDENT
void tst_and_prt()
{
//--Test and Print---------------------------------------------- -
	if ((NBlck>MxBlck)||(NBlck<MnBlck))
	{
		std::cout << "MnBlck <= NBlck <=MxBlck?" << std::endl;
		exit(1);
	}

	if ((NBlck>200) && (NBlck != MxBlck))
	{
		std::cout << "NBlck>200 is supposed for extensive simulation. NBlck=MxBlk is suggested!" << std::endl;
		exit(1);
	}

	printf(" AT on N=%d model\n",N);
	printf(" coupling = %g\n", p);
	printf(" Will simulate \t%d steps\n", NSample*NBlck);
	printf(" Blocks        \t%d\n", NBlck);
}

//!!THIS IS PROJECT - INDEPENDENT!!!


void Initialize_Quantities()
{
	for (int i = 0;i < NObs;i++)
	{
		for (int j = 0;j < MxBlck;j++)
		{
			Obs(i, j) = 0;
		}
	}
	Vol = N*N;
}

int location(int i, int j)
{
	return (i - 1)*N + j - 1;
}
void Initialize_Lattice()
{
	Block = new int[Vol];
	up = new int[Vol];
	left = new int[Vol];
	set = new int[Vol];
	count = new int[Vol];
	for (int i = 0;i < Vol;i++)
	{
		count[i] = 0;
	}

	for (int i = 1;i <= N;i++)
	{
		for (int j = 1;j <= N;j++)
		{
			if (i == 1)
			{
				up[location(i, j)] = location(N, j);
			}
			else
			{
				up[location(i, j)] = location(i-1,j);
			}

			if (j == 1)
			{
				left[location(i, j)] = location(i, N);
			}
			else
			{
				left[location(i, j)] = location(i, j-1);
			}
		
		}
	}/*
	for (int i = 0;i < Vol;i++)
		std::cout << i<<"	"<<left[i]<<std::endl;*/
}
void Initialize_CORES()
{
	int Number_Of_Levels = round(log(N) / log(2));
	int Core_Size;

	CORES = new int*[2 * Number_Of_Levels];
	for (int i = 0;i < 2 * Number_Of_Levels;i++)
	{
		CORES[i] = new int[Vol];
	}

	Core_Size = N / 2;
	for (int i = 0;i < Number_Of_Levels;i++)//For H and V
	{
		for (int j = 0;j < Vol;j++) 
		{
			CORES[i][j] = -2*((j / Core_Size) % 2)+1;
		}
		Core_Size /= 2;
	}

	Core_Size = N / 2;
	int x, y;
	for (int i = Number_Of_Levels;i < 2*Number_Of_Levels;i++)//For D
	{
		for (int j = 0;j < Vol;j++)
		{
			x = j %N;
			y = j / N;
			CORES[i][j] = (-2 * ((x / Core_Size) % 2) + 1)*(-2 * ((y / Core_Size) % 2) + 1);
		}
		Core_Size /= 2;
	}
	//for (int i = 0;i < Vol;i++)
	//	std::cout << i<<"	"<<CORES[0][i]<<std::endl;
}
//============= = Initialization ======================================
void initialize()
{
	tst_and_prt();
	Set_RNG();
	
	Initialize_Quantities();
	Initialize_CORES();
	Initialize_Lattice();
	//Initialize_Result();
	//Initialize_Energy();
}