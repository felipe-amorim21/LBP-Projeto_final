#include "filtro.h"

int getElement(unsigned char *p, int l, int c, int n)
{
	if ((l < 0 || l >= n * n) || (c < 0 || c >= n * n))
		return 0;
	return p[l * n + c];
}

int *getNeighbors(unsigned char *p, int i, int j, int n, int neighbors[8], int binary[8])
{
	neighbors
			[0] = getElement(p, i, j - 1, n); // Esquerda
	neighbors
			[7] = getElement(p, i - 1, j - 1, n); // Cima
	neighbors
			[6] = getElement(p, i - 1, j, n);
	neighbors
			[5] = getElement(p, i - 1, j + 1, n);
	neighbors
			[4] = getElement(p, i, j + 1, n); // Direita
	neighbors
			[3] = getElement(p, i + 1, j + 1, n); // Baixo
	neighbors
			[2] = getElement(p, i + 1, j, n);
	neighbors
			[1] = getElement(p, i + 1, j - 1, n);
	for (int k = 0; k < 8; k++)
	{
		if (neighbors[k] >= getElement(p, i, j, n))
		{
			binary[k] = 1;
		}
		else
		{
			binary[k] = 0;
		}
	}
	return neighbors;
}

int getDecimal(int binary[8])
{
	int i = 0;
	int decimal = 0;
	for (int k = 7; k >= 0; k--)
	{
		if (binary[k] == 1)
		{
			decimal += pow(2, i);
		}
		i++;
	}
	return decimal;
}

void matrizDecimal(int *pv2, int c, int l, int *pb)
{
	for (int k = 0; k < l * c; k++)
	{
		*(pv2 + k) = getDecimal(pb);
	}
}