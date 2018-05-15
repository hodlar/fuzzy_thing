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
	printf("\n");
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

	for(i = 0; i < y; i++)
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
	//		printf("valor=%lf dir=%x\n", *(matrix + FUZZY_NUMBER*k + j), (matrix + FUZZY_NUMBER*k + j));
		}
		*(resultado + j) = tmp/expertos;
	}
}

void calculate_sum(double *resultado, double **matrix, int fac_comp)
{
	int i, j, k, cont = 0;
	double tmp;
	for(i = 0; i < fac_comp; i++)
	{
		for(j = 0; j < 3; j++)
		{
			*(resultado + cont) = 0;
			for(k = 0; k < fac_comp; k++)
			{
				*(resultado + cont) += *(*(matrix + k*fac_comp + i) + j);
//				printf("val = %lf sum=%d\n", *(*(matrix + k*fac_comp + i) + j), cont);
			}
			cont += 1;
		}
	}
}

void sum_triangular(double **resultado, double **matrix, int fac_comp)
{
	int i, j, k;
	for(i = 0; i < fac_comp; i++)
	{
		for(j = 0; j < 3; j++)
		{
			*(*(resultado + i) + j) = 0;
			for(k = 0; k < fac_comp; k++)
			{
				*(*(resultado +  i) + j) += *(*(matrix + k + i*fac_comp) + j);
				printf("y=%i x=%i \n", i, k*fac_comp+j);
			}
		}
	}
}

void sum_column(double *resultado, double **matrix, int col_size)
{
	int i, j, k;
	for(i = 0; i < FUZZY_NUMBER; i++)
	{
		*(resultado + i) = 0;
		for(k = 0; k < col_size; k++)
		{
			*(resultado + i) += *(*(matrix + k) + i);
		}
	}
}

void invert_sc(double *inv_sc, double *sc)
{
	int i;
	for( i = 0; i < FUZZY_NUMBER; i++)
	{
		inv_sc[i] = 1/sc[i];
	}
}

void calculate_s_exclamation(double **s_exclamation, double **s, double *inverse_sc, int fac_comp)
{
	int i, j, k;
	for( i = 0; i < fac_comp; i++)
	{
		for( j = 0; j < 3; j++)
		{
			*(*(s_exclamation + i ) + j )  = *(*(s + i) + j) * *(inverse_sc + (2 - j));
		}
	}
}

int main()
{
	int cant_expertos, i, fac_comp, fuzzy_number, tmp, j, k;
	char *palabras;
	//factores de comparacion max 9
	//numero de expertos infinito	
	//generar matrix promedio de cada columna
	double **eval_mat, **avg_matrix, *sumatoria, **triangular, **s_exclamation;
	double col_sum[3], inv_sc[3];


	printf("cantidad de expertos? ");
	scanf("%i", &cant_expertos);
	printf("introduce el numero de factores de comparacion (max 9) ");
	scanf("%i", &fac_comp);
	
	palabras = (char*)malloc( fac_comp*15 * sizeof(char) );
	eval_mat = crea_mat_2d(fac_comp*fac_comp, cant_expertos * 3);
	avg_matrix = crea_mat_2d(fac_comp*fac_comp, FUZZY_NUMBER);
	sumatoria = (double*)malloc( fac_comp*3 * sizeof(double) );
	triangular = crea_mat_2d(fac_comp, 3);
	s_exclamation = crea_mat_2d(fac_comp, 3);

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
		calculate_avg_matrix(*(avg_matrix + j), *(eval_mat+j), cant_expertos);
	}

	calculate_sum(sumatoria, avg_matrix, fac_comp);
	sum_triangular(triangular, avg_matrix, fac_comp);
	sum_column(col_sum,triangular,fac_comp);
	invert_sc(inv_sc,col_sum);
	calculate_s_exclamation(s_exclamation, triangular, inv_sc, fac_comp);

	despliega_mat_2d( eval_mat, fac_comp*fac_comp, cant_expertos*3);
	despliega_mat_2d(avg_matrix, fac_comp*fac_comp, FUZZY_NUMBER);
	printf("\nSumatoria\n");
	despliega_mat_1d(sumatoria,fac_comp*3);
	printf("\nSuma de numeros triangulares");
	despliega_mat_2d(triangular, fac_comp, FUZZY_NUMBER);
	printf("\nSC\n");
	despliega_mat_1d(col_sum,FUZZY_NUMBER);
	printf("\n1/SC\n");
	despliega_mat_1d(inv_sc,FUZZY_NUMBER);
	printf("\nS!");
	despliega_mat_2d(s_exclamation, fac_comp, FUZZY_NUMBER);
	return 0;
}
