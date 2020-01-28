#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

#define N 1000

int mat1[N][N];
int mat2[N][N];
int mat3[N][N];

void parallelmultiplication(int mat1[N][N],int mat2[N][N],int mat3[N][N])
{
    int i,j,k;
    float s_time = omp_get_wtime();
    #pragma omp parallel for private(i,j,k) shared(mat1,mat2,mat3)
    
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            for(k=0;k<N;k++){
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    float e_time = omp_get_wtime();
    printf("Time taken by parallel = %f\n",e_time-s_time);
}

void serialmultiplication(int mat1[N][N],int mat2[N][N],int mat3[N][N])
{
    int i,j,k;
    float s_time = omp_get_wtime();
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            for(k=0;k<N;k++){
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    float e_time = omp_get_wtime();
    printf("Time taken by serial = %f",e_time-s_time);
}

int main()
{
    int i,j,k;
    
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            mat1[i][j] = rand()%100;
            mat2[i][j] = rand()%100;
        }
    }

    parallelmultiplication(mat1,mat2,mat3);

    serialmultiplication(mat1,mat2,mat3);
	  
}
