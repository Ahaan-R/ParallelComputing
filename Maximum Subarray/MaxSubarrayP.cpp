

#include<iostream>
#include<cstring>
#include <pthread.h>
#include <omp.h>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
int leftSum = -9999;
int rightSum = -9999;
int crossSum = -9999;
int Sum = 0;
int max(int a,int b)
{
	return (a>b) ? a : b;
}
int max(int a,int b,int c)
{
	return max(max(a,b),c);
}
int findMaximumSubarrayCrossing(int *A,int low,int mid,int high)
{
	
//	calculating left sum 
	int INT_MIN;
   /*#pragma omp sections
	{					//running the 2 for loops in parallel sections
	#pragma omp section
	{   */
	int sum= 0 ;
	int l_sum = INT_MIN;
		#pragma omp parallel private(l_sum) num_threads(10) 
	for(int i = mid;i>=low;i--)              
	{
		sum+=A[i];
		if(sum>=l_sum)
			l_sum = sum;
	}
	
	//	calculating right sum 
	//#pragma omp section
	
	
	int r_sum=INT_MIN;
		#pragma omp parallel private(r_sum) num_threads(10)
	for(int i=mid+1;i<=high;i++)
	{
		sum+=A[i];
		if(sum>=r_sum)
			r_sum = sum;
	}
	
//	 adding left sum and right sum in order to get the maximum sum across middle element;
	return l_sum+r_sum;
}

int findMaximumSubarray(int *A,int low,int high)
{
	if(low==high)
		return A[low];   		
	else
	{
		int mid = (low+high)/2;     					
		leftSum = findMaximumSubarray(A,low,mid);         		
		rightSum  =findMaximumSubarray(A,mid+1,high);			
 		crossSum = findMaximumSubarrayCrossing(A,low,mid,high);	     
		return max(leftSum,rightSum,crossSum);				
	}
			
	return 0;	
}
int main(void)
{
	omp_set_num_threads(10);
	int A[]={10,-16,5,2,-1,7,-8,-5,3};
	int n = sizeof(A)/sizeof(A[0]);
	int low=0;
	int high = n-1;
	cout<<findMaximumSubarray(A,low,high);
}
