
#include "mt_cpu.h"

 


void init_coords(float x[][N_d], float y[][N_d], float t[][N_d]);
int compare_results(float x_1[][N_d], float y_1[][N_d], float t_1[][N_d],
						float x_2[][N_d], float y_2[][N_d], float t_2[][N_d] );
											
						
void print_coords(FILE *f_p, float x[][N_d], float y[][N_d], float t[][N_d]);


						

#define BUF_LEN_B		4096	


float x_1[13][N_d];
float y_1[13][N_d];
float t_1[13][N_d];


// во время дебага TOTAL_STEPS можно делать меньше
#define STEPS_TO_WRITE		30000			// через это значение шагов сравниваем координаты и выводим в файл

#define N				5			// количчество  запусков функций mt_cpu и mt_fpga

#define TOTAL_STEPS			(STEPS_TO_WRITE*N)		// полное количество шагов по времени


#define MARGIN		0.01f

	
int main(int argc, char *argv[])
{
	int dev, ret_val;

	
	double dt_c[N];
	double dt_f[N];

	double t_cpu; 

	 FILE *f_u, *f_p;
	 int i,j;

	 int error = 0;

	 f_p = fopen ("MT_coords_CPU1.txt","w");
	 if (f_p==NULL) {

		 printf("Error opening file!\n");
		 return -1;
	 }


	printf("TOTAL_STEPS = %d\nSTEPS_TO_WRITE = %d\n", TOTAL_STEPS, STEPS_TO_WRITE);



	init_coords(x_1,y_1,t_1);




	 for(int k=0; k<N; k++) {

		mt_cpu(STEPS_TO_WRITE,1,x_1,y_1,t_1,x_1,y_1, t_1);
		
		

		print_coords(f_p, x_1, y_1, t_1);
		

	}
	

	fclose(f_p);


	return 0; 

}



void print_coords(FILE *f_p, float x[][N_d], float y[][N_d], float t[][N_d])
{
	int i,j;

	for (i=0; i<13; i++) {
		for (j=0; j<N_d; j++)
			fprintf(f_p,"%.2f\t  ", x[i][j]);

		for (j=0; j<N_d; j++)
			fprintf(f_p,"%.2f\t  ", y[i][j]);

		for (j=0; j<N_d; j++)
			fprintf(f_p,"%.2f\t  ", t[i][j]);
	}

	fprintf(f_p,"\n");

}




void init_coords(float x[][N_d], float y[][N_d], float t[][N_d])
{
	int i,j;


	// задание y координаты для нижней спирали
	for (i=0; i<13; i++)
		y[i][0] = 2.0f*6/13*(i+1);


	// задание y координат для остальных молекул до половины высоты трубочки
	for (j=1; j<N_d-4; j++)
		for (i=0; i<13; i++)
			y[i][j] = y[i][j-1] + 2.0f*Rad;


	// задание x и teta координат так чтобы был цилиндр до половины высоты трубочки
	for (j=0; j<N_d-5; j++)
		for (i=0; i<13; i++)  {

			x[i][j] = 0.0;
			t[i][j] = 0.0;
		}


	//
	for (i=0; i<13; i++)  {

		x[i][N_d-5] = 0.6;
		t[i][N_d-5] = 0.2;

	}


	for (j=N_d-4; j<N_d; j++)
		for (i=0; i<13; i++)  {

			x[i][j] = x[i][j-1] + 2*Rad*sinf(t[i][j-1]);
			y[i][j] = y[i][j-1] + 2*Rad*cosf(t[i][j-1]);
			t[i][j] = t[i][j-1];

		}


}





int compare_results(float x_1[][N_d], float y_1[][N_d], float t_1[][N_d],
						float x_2[][N_d], float y_2[][N_d], float t_2[][N_d] )
{

	int error = 0;
	for(int i = 0; i<13; i++)
		for(int j = 0; j<N_d; j++) {

			if (fabs(x_1[i][j] - x_2[i][j]) > MARGIN)
				error++;
			if (fabs(y_1[i][j] - y_2[i][j]) > MARGIN)
				error++;
			if (fabs(t_1[i][j] - t_2[i][j]) > MARGIN)
				error++;

		}


	return error;
}


