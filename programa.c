#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FUZZY_NUMBER 3

void init_arr(double *arr, int size, double val1, double val2, double val3)
{
	int i;
	for(i = 0; i < size; i++)
	{ 
		*(arr + i*3) = val1; 
		*(arr + i*3 + 1) = val2;
		*(arr + i*3 + 2) = val3;
	}
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

void despliega_short_mat_1d(short *arr, int size)
{
	int k;
	for(k = 0; k < size; k++)
	{
		printf("%hi ", *(arr + k) );
	}
	printf("\n");
}

void despliega_short_mat_2d(short **mat, int y, int x)
{
	int j;
	printf("\n");
	for(j = 0; j < y; j++)
	{
		despliega_short_mat_1d( *(mat + j), x);
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

short** crea_short_mat_2d(int y, int x)
{
	short **mat;
	int i, j, k;
	
	mat = (short**)malloc(y * sizeof(short*));

	for(i = 0; i < y; i++)
	{ 
		*(mat + i) = (short*)malloc(x * sizeof(short)); 
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
	double tmp = 1;
	double expertos_doub, aux[90];
	expertos_doub = (double) expertos;

/*	
	for(j = 0; j < expertos; j++)
	{
		aux[j] = *(matrix + 3*j) + 4 * *(matrix + 1 + 3*j) + *(matrix + 2 + 3*j);
		aux[j] /= 6;
	}

	for(j =  0; j < expertos; j++)
	{
		tmp *= aux[j];
	}
	*resultado = pow(tmp, 1/expertos_doub);
*/
	
	for(j = 0; j < FUZZY_NUMBER; j++)
	{
		tmp = 1;
		for(k = 0; k < expertos; k++)
		{
			tmp *=  *(matrix + FUZZY_NUMBER*k + j);
//			printf("valor=%lf tmp=%lf dir=%x\n ", *(matrix + FUZZY_NUMBER*k + j), tmp, (matrix + FUZZY_NUMBER*k + j));
		}
		*(resultado + j) = pow(tmp,1/expertos_doub);
//		*(resultado + j) = tmp/expertos;
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
//				printf("y=%i x=%i \n", i, k*fac_comp+j);
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

void generate_logic_matrix(short **results, double **s_exclamation, int fac_comp)
{
	int i, j, k1, k2, cont;
	for(i = 0; i < 3; i++)
	{
		cont = 0;
		for(j = 0; j < fac_comp; j++)
		{
			for(k1 = 0; k1 < j; k1++)
			{
				*(*(results+cont)+i) = *(*(s_exclamation+j)+i) > *(*(s_exclamation+k1)+i);
				cont++;
			}
			for(k2 = j+1; k2 < fac_comp; k2++)
			{
				*(*(results+cont)+i) = *(*(s_exclamation+j)+i) > *(*(s_exclamation+k2)+i);
				cont++;
			}
		}
	}
}


void logic_test(double *pesos, double **s_exclamation, int s_size)
{
	int j, k1, k2;
	double tmp1, tmp2;
	for( j = 0; j < s_size; j++)
	{
		tmp1 = 1;
		tmp2 = 1;
		for(k1 = 0; k1 < j; k1++)
		{
				if(	*(*(s_exclamation+j)+1) >= *(*(s_exclamation+k1)+1) )
				{ tmp2 = 1; }
				else if( *(*(s_exclamation+k1)+0) >= *(*(s_exclamation+j)+2) )
				{ tmp2 = 0; }
				else
				{  tmp2 = (*(*(s_exclamation+k1)) - *(*(s_exclamation+j)+2)) / 
				(  (*(*(s_exclamation+j)+1) - *(*(s_exclamation+j)+2) ) - 
					( *(*(s_exclamation+k1)+1) - *(*(s_exclamation+k1)+0) ) );
				}
				if (tmp2 < tmp1)
				{ tmp1 = tmp2; }
		}
		
		for(k2 = j+1; k2 < s_size; k2++)
		{
				if(	*(*(s_exclamation+j)+1) >= *(*(s_exclamation+k2)+1) )
				{ tmp2 = 1; }
				else if( *(*(s_exclamation+k2)+0) >= *(*(s_exclamation+j)+2) )
				{ tmp2 = 0; }
				else
				{  tmp2 = (*(*(s_exclamation+k2)) - *(*(s_exclamation+j)+2)) / 
				(  (*(*(s_exclamation+j)+1) - *(*(s_exclamation+j)+2) ) - 
					( *(*(s_exclamation+k2)+1) - *(*(s_exclamation+k2)+0) ) );
				}
				if(tmp2 < tmp1)
				{ tmp1 = tmp2; }
		}
		*(pesos + j) = tmp1;
	}
}

void calcula_final(double *resultados, double *pesos, int size)
{
	int j, k;
	double sum = 0;
	for(j = 0; j < size; j++)
	{
		sum += *(pesos + j);
	}
	for(j = 0; j < size; j++)
	{
		*(resultados + j) = *(pesos + j)/sum;
	}
	printf("\nSUMA%lf\n", sum);
}

int main()
{
	int cant_expertos, i, fac_comp, fuzzy_number, tmp, j, k;
	double val1, val2, val3;
	short **desition_matrix;
	char *palabras;
	//factores de comparacion max 9
	//numero de expertos infinito	
	//generar matrix promedio de cada columna
	double **eval_mat, **avg_matrix, *sumatoria, **triangular, **s_exclamation, pesos[9];
	double col_sum[3], inv_sc[3], resultado_final[9];


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
	desition_matrix = crea_short_mat_2d(fac_comp*(fac_comp-1),3);

	for (i = 0; i < fac_comp * 15; i++)
	{ 
		*(palabras + i) = 0; 
	}

	for(i = 0; i < fac_comp; i++)
	{
		printf("nombre de factor de comparacion #%i ", i + 1);
		scanf("%s", (palabras + 15*i) );
	}

	tmp = (fac_comp * (fac_comp - 1)) / 2;	

	printf("introduce los valores triangulares de la matriz igualdad ");
	scanf("%lf", &val1);
	scanf("%lf", &val2);
	scanf("%lf", &val3);

	for(i = 0; i < fac_comp; i++)
	{
		init_arr( *(eval_mat + i + fac_comp*i ), cant_expertos, val1, val2, val3);
	}

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
	generate_logic_matrix(desition_matrix, s_exclamation, fac_comp);
	logic_test(pesos, s_exclamation, fac_comp);
	calcula_final(resultado_final, pesos, fac_comp);


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
	printf("\ndesition_matrix");
	despliega_short_mat_2d(desition_matrix, fac_comp*(fac_comp-1), FUZZY_NUMBER);
	printf("\npesos\n");
	despliega_mat_1d(pesos,fac_comp);
	printf("\nResultado final\n");
	despliega_mat_1d(resultado_final,fac_comp);

	for(k = 0; k < fac_comp; k++)
	{
		printf("%lf, %s \n", *(resultado_final + k), palabras + 15*k);
	}
	
	scanf("%i", &cant_expertos);
	return 0;
}
