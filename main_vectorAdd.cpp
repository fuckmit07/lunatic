#include<iostream>
#include<fstream>
#include<omp.h>
#include<vector>
#include<string>
using namespace std;

void populateFile(int n){
	ofstream file1,file2;
	file1.open("numbers_1.txt");
	file2.open("numbers_2.txt");
	for(int i=0;i<n;i++){
		file1<<rand()%100<<"\n";
		file2<<rand()%100<<"\n";
	}
	file1.close();
	file2.close();
}

void insert(vector<int>numbers , string file){
	string number;
	ifstream myfile (file);
	if(myfile.is_open()){
		while(getline (myfile,number)){
			numbers.push_back(stoi(number));
			// stoi is used to convert string to an integer
		}
	}

}

// --SERIAL EXECUTION
void serial_add(vector<int>num1 , vector<int>num2 , int size){
	int temp[size];
	int i;	
	for(i =0;i<size;i++){
		temp[i] = num1[i]+num2[i];
	}
}


void serial_sub(vector<int>num1 , vector<int>num2 , int size){
	int temp[size];
	int i;
	for(i =0;i<size;i++){
		temp[i] = num1[i]-num2[i];
	}
}

void serial_mul(vector<int>num1 , vector<int>num2 , int size){
	int temp[size];
	int i;
	for(i =0;i<size;i++){
		temp[i]=num1[i]*num2[i];
	}
}

// --PARALLEL EXECUTION
/*
clause private is used so that each thread gets a local memory of the variable.
If not done , the variable will have a single instance shared among multiple threads , which would disrupt computation on line 56 and similar. 
*/
void parallel_add(vector<int>num1 , vector<int>num2 , int size){
	int temp[size];
	int j;
	#pragma omp parallel for private(j)	
	for(j=0; j<size; j++){
		temp[j]=num1[j]+num2[j];
	}
}

void parallel_sub(vector<int>num1 , vector<int>num2 , int size){
	int temp[size];
	int j;
	#pragma omp parallel for private(j)	
	for(j=0; j<size; j++){
		temp[j]=num1[j]-num2[j];
	}
}

void parallel_mul(vector<int>num1 , vector<int>num2 , int size){
	int temp[size];
	int j;
	#pragma omp parallel for private(j)	
	for(j=0; j<size; j++){
		temp[j]=num1[j]*num2[j];
	}
}

// --

int main(){
	vector<double>serial_time,parallel_time;
	vector<int>num1,num2;
	string file1,file2;
	int size,num;	
	double start;
	
	cout<<"Vector Size\t:";
	cin>>num;
	populateFile(num);
	
	file1="numbers_1.txt";
	file2="numbers_1.txt";
	insert(num1,file1);
	insert(num2,file2);
		
	size = num1.size();
	/* difference between current instance , i.e. after function ends[omp_get_wtime()] and start i.e. time before function starts gives 		us execution time*/
	// SERIAL EXECUTION
	start = omp_get_wtime();
	serial_add(num1,num2,size);
	serial_time.push_back(omp_get_wtime()-start);
	
	start = omp_get_wtime();
	serial_sub(num1,num2,size);
	serial_time.push_back(omp_get_wtime()-start);
	
	start = omp_get_wtime();
	serial_mul(num1,num2,size);
	serial_time.push_back(omp_get_wtime()-start);
	// PARALLEL EXECUTION
	start = omp_get_wtime();
	parallel_add(num1,num2,size);
	parallel_time.push_back(omp_get_wtime()-start);
	
	start = omp_get_wtime();
	parallel_sub(num1,num2,size);
	parallel_time.push_back(omp_get_wtime()-start);

	start = omp_get_wtime();
	parallel_mul(num1,num2,size);
	parallel_time.push_back(omp_get_wtime()-start);
	
	cout<<"OPE\tS\t\tP"<<endl;
	cout<<"ADD "<<serial_time[0]<<"\t"<<parallel_time[0]<<endl;
	cout<<"SUB "<<serial_time[1]<<"\t"<<parallel_time[1]<<endl;
	cout<<"MUL "<<serial_time[2]<<"\t"<<parallel_time[2]<<endl;
	return 0;
}
