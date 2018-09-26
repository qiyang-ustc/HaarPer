#include <math.h>
#include "my_vrbls.h"
#include "measure.h"
#include "initialize.h"
int getfather(int* set, int x)
{
	int y = x;
	int z;
	while (y != set[y])
	{
		y = set[y];
	}

	while (x != set[x])
	{
		z = set[x];
		set[x] = y;
		x = z;
	}
	return y;
}
void Markov()
{
	
    /*Bond Percolation*/
	for (int i = 0;i < Vol;i++) 
	{
		set[i] = i;
		Block[i] = i;
	}
	
	
	for (int i = 0;i < Vol;i++)
	{
		if (rn() < p)
		{
			set[getfather(set, Block[up[i]])] = getfather(set, Block[i]);
		}
		if (rn() < p)
		{
			set[getfather(set, Block[left[i]])] = getfather(set, Block[i]);
		}
	}
	for (int i = 0;i < Vol;i++)
	{
	//	std::cout <<i<<"	"<< set[i] << std::endl;

		Block[i] = getfather(set,Block[i]);
	}
	//Generate Block
	int mode=0;
	for (int i = 0;i < Vol;i++)
	{
		count[Block[i]]++;
	}

	//std::cout << "count==" << std::endl;
	//for (int i = 0;i < Vol;i++)
		//std::cout << i << "\t" << count[i] << std::endl;
	for (int i = 0;i < Vol;i++)
	{
		if (count[i] > count[mode]) 
		{
			mode = i;
		}
	}
	//for (int i = 0;i < Vol;i++)
	//std::cout << i << "\t" << Block[i] << std::endl;


	for (int i = 0;i < Vol;i++)
	{
		if (Block[i] == mode)
		{
			Block[i] = 1;
		}
		else
		{
			Block[i] = 0;
		}
	}
	/*for (int i = 0;i < Vol;i++)
		std::cout << i << "\t" << Block[i] << std::endl;
	*/
	for (int i = 0;i < Vol;i++)
	{
		count[i] = 0;
	}
}