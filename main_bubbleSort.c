#include<stdio.h>
#include<omp.h>
#include<math.h>

#define max 100000

int arr[max];

void populate(int arr[])
{
 int i=0;
 for(i=0;i<max;i++)
  {
    arr[i]=max-i;
  }
}


void display(int arr[])
{
 for(int i=0;i<max;i++)
  {
   printf("%d",arr[i]);
   printf(" ");
  }
}

void serial_bubble(int arr[])
{
	printf("Serial Execution\n");
    float s_time= omp_get_wtime();
    printf("\nStart of execution: \n%f\n", s_time);
    int temp;
    for(int i =0; i<max; i++)
    {
        for(int j = 0; j<max-i-1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
 float e_time= omp_get_wtime();
 printf("\nEnd of execution: \n%f\n", e_time);
 printf("\nTime Taken by Serial Execution: \n%f\n", (e_time - s_time));
 //display(arr);
   
}


void parallel_bubblesort(int arr[])
{
printf("Parallel Execution\n");
float s_time= omp_get_wtime();
printf("\nStart of execution: \n%f\n", s_time);
 for(int i=0;i<(max+1)/2; i++)
  {

       
       
       #pragma omp parallel for
       for(int k=0;k<max-1;k+=2)
       {
       		int temp;
			if(arr[k]>arr[k+1])
			{
				temp=arr[k+1];
				arr[k+1]=arr[k];
				arr[k]=temp;
			}
		}

        #pragma omp parallel for      
  		for(int j=1;j<max-1;j+=2)
		{
			int temp2;
			if(arr[j]>arr[j+1])
			{
				temp2=arr[j+1];
				arr[j+1]=arr[j];
				arr[j]=temp2;
			}
		}
  }
  
 float e_time= omp_get_wtime();
 printf("\nEnd of execution: \n%f\n", e_time);
 printf("\nTime Taken by Parallel Execution: \n%f\n", (e_time - s_time));
 
}


int main()
{
 populate(arr);
 //printf("numbers are :-\n");
 //display(arr);
 serial_bubble(arr);
 printf("\n");
 parallel_bubblesort(arr);
 printf("\n");
 //printf("sorted array :-\n");
 //display(arr);
 printf("\n");
 return 0;
}



