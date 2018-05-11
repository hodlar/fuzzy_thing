#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FUZZY_NUMBER 3

void init_arr(double *arr, int size, double value)
{
	int i;
	for(i = 0; i < size; i++)
	{ *(arr+i) = value; }
}

void despliega_mat_1d(double *arr, int size)
{
	int k;
	for(k = 0; k < size; k++)
	{
		printf("%lf ", *(arr + k) );
	}
	printf("\n");
}

void despliega_mat_2d(double **mat, int y, int x)
{
	int j;
	for(j = 0; j < y; j++)
	{
		despliega_mat_1d( *(mat + j), x);
	}
}

void lee_arr(double *arr, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{ scanf("%lf", arr+i); }
}

double** crea_mat_2d(int y, int x)
{
	double **mat;
	int i, j, k;
	
	mat = (double**)malloc(y * sizeof(double*));

	for(i = 0; i < 3*x; i++)
	{ 
		*(mat + i) = (double*)malloc(x * sizeof(double)); 
	}

	return mat;
}

void matriz_inversa(double *resultado, double *matriz, int xsize, int ysize)
{
	int j, k;
	for(j = 0; j < ysize; j++)
	{
		for(k = 0; k < xsize; k++)
		{
			*(resultado + k + j*xsize) = 1 / *(matriz + xsize - 1 - k + j*xsize);
		}
	}
}

void calculate_avg_matrix(double *resultado, double *matrix, int expertos)
{
	int i, j, k;
	double tmp;
	double expertos_doub;
	for(j = 0; j < FUZZY_NUMBER; j++)
	{
		tmp = 0;
		for(k = 0; k < expertos; k++)
		{
			tmp += *(matrix + FUZZY_NUMBER*k + j);
		}
		*(resultado + j) = tmp/expertos;
	}
}

int main()
{
	int cant_expertos, i, fac_comp, fuzzy_number, tmp, j, k;
	char *palabras;
	//factores de comparacion max 9
	//numero de expertos infinito	
	//generar matrix promedio de cada columna
	double **eval_mat, **avg_matrix;


	printf("cantidad de expertos? ");
	scanf("%i", &cant_expertos);
	printf("introduce el numero de factores de comparacion (max 9) ");
	scanf("%i", &fac_comp);
	
	palabras = (char*)malloc( fac_comp*15 * sizeof(char) );
	eval_mat = crea_mat_2d(fac_comp*fac_comp, cant_expertos * 3);
	avg_matrix = crea_mat_2d(fac_comp, fac_comp*FUZZY_NUMBER);

	for (i = 0; i < fac_comp * 15; i++)
	{ 
		*(palabras + i) = 0; 
	}

	for(i = 0; i < fac_comp; i++)
	{
		init_arr( *(eval_mat + i + fac_comp*i ), cant_expertos * 3, 1);
	}

	for(i = 0; i < fac_comp; i++)
	{
		printf("nombre de factor de comparacion #%i ", i + 1);
		scanf("%s", (palabras + 15*i) );
	}

	/*
	for(i = 0; i < 15 * fac_comp; i++)
	{ 
		printf("%c", *(palabras + i)) ; 
	}
	*/
//24
	tmp = (fac_comp * (fac_comp - 1)) / 2;
	for(j = 0; j < fac_comp; j++)
	{
		for(k = j + 1; k < fac_comp; k++)
		{
			printf("\nintroduce la matriz de %s vs %s\n", palabras + 15*j, palabras + 15*k);
			lee_arr( *(eval_mat + fac_comp * j + k), cant_expertos*3 );
			matriz_inversa( *(eval_mat + fac_comp*k + j), *(eval_mat + fac_comp*j +k), FUZZY_NUMBER, cant_expertos);
		}
	}

	for(j = 0; j < fac_comp*fac_comp; j++)
	{
		calculate_avg_matrix(*(avg_matrix)+3*j, *(eval_mat+j), cant_expertos);
	}

// matriz_inversa
	despliega_mat_2d( eval_mat, fac_comp*fac_comp, cant_expertos*3);
	printf("\n");
	despliega_mat_2d(avg_matrix, fac_comp, fac_comp*3);

	return 0;
}
