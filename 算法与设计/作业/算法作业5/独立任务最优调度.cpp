#include <iostream>
using namespace std;

bool*** store;

int main()
{
	int n,*array_a,*array_b;
	
	cin>>n;
	array_a=(int*)malloc(n*sizeof(int));
	if(!array_a)
		exit(-1);
	array_b=(int*)malloc(n*sizeof(int));
	if(!array_b)
		exit(-1);
	for(int i=0;i<n;++i)
		cin>>array_a[i];
	for(int i=0;i<n;++i)
		cin>>array_b[i];//输入作业数量n和两台机器的处理时间
		
	int sum_a=0;
	for(int i=0;i<n;++i)
		sum_a=sum_a+array_a[i];
	int sum_b=0;
	for(int i=0;i<n;++i)
		sum_b=sum_b+array_b[i];
	store=(bool***)malloc((sum_a+1)*sizeof(bool**));
	if(!store)
		exit(-1);
	for(int i=0;i<=sum_a;++i)
	{
		store[i]=(bool**)malloc((sum_b+1)*sizeof(bool*));
		if(!store[i])
			exit(-1);
	}
	for(int i=0;i<=sum_a;++i)
	{
		for(int j=0;j<=sum_b;++j)
		{
			store[i][j]=(bool*)malloc(n*sizeof(bool));
			if(!store[i][j])
				exit(-1);
		}
	}
	for(int i=0;i<=sum_a;++i)
    {
		for(int j=0;j<=sum_b;++j)
	    {
	    	if(i>=array_a[0]||j>=array_b[0])
				store[i][j][0]=true;
			else
				store[i][j][0]=false;
		}
	}
	for(int k=1;k<n;++k)
	{
		for(int i=0;i<=sum_a;++i)
     	{
		    for(int j=0;j<=sum_b;++j)
	    	{
	    		if(i-array_a[k-1]>=0)
					store[i][j][k]=store[i-array_a[k-1]][j][k-1];
				if(j-array_b[k-1]>=0)
					store[i][j][k]=store[i][j][k]||store[i][j-array_b[k-1]][k-1];
		    }
	    }
	}
	int min=1000000;
	for(int i=0;i<=sum_a;++i)
	{
		for(int j=0;j<=sum_b;++j)
		{
			if(store[i][j][n-1]==true)
			{
				int max;
				if(i>j)
					max=i;
				else
					max=j;
				if(min>max)
					min=max;
			}
		}
	}
	cout<<min;
		
	return 0;
}
