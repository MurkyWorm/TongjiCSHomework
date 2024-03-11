#include <iostream>
using namespace std;

int **array;

void set1(int n)
{
	int m=n/2;
	
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=m;++j)
		{
			array[i][j+m]=array[i][j]+m;
			array[i+m][j]=array[i][j+m];
			array[i+m][j+m]=array[i][j];
		}
	}
}//n/2为偶数时另外三块区域的布置方法

void set2(int n) 
{
 	int m=n/2,*b;
 	
 	b=(int*)malloc((n+1)*sizeof(int));
 	if(!b)
 	    exit(-1);
 	for(int i=1;i<=m;++i)
 	{
 		b[i]=m+i;
 		b[m+i]=b[i];
	}
	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=m+1;++j)
		{
			if(array[i][j]>m)
			{
				array[i][j]=b[i];
				array[i+m][j]=(b[i]+m)%n;//同一天的两个参赛者相互比赛  
			}
			else
		        array[i+m][j]=array[i][j]+m;//设置左下区域 
		}
		for(int j=2;j<=m;++j)
		{
			array[i][m+j]=b[i+j-1];
			array[b[i+j-1]][m+j]=i;//同一天两个参赛者相同比赛 ，设置右边区域 
		}
	}
	free(b);
}//n/2为奇数时另外三块区域的布置方法 

void setother(int n) 
{
	if(n/2%2==0||n/2<=1)
	    set1(n);
	else
	    set2(n);
}


void table(int n) 
{
	if(n==1)
	{
		array[1][1]=1;
		return;
	}
	if(n%2==1)
	{
		table(n+1);//若人数为奇数，补全为偶数 
		return;
	}
	table(n/2);//处理左上角的四分之一 
	setother(n);//根据左上角的四分之一布置另外三块区域 
}//递归生成日程表 

int main()
{
	int n,size;
	
	cin>>n;
	size=(n+1)/2*2+1;
	array=(int**)malloc(size*sizeof(int*));
	if(!array)
	    exit(-1);
	for(int i=0;i<size;++i)
	{
		*(array+i)=(int*)malloc(size*sizeof(int));
		if(!*(array+i))
		    exit(-1);
	}//创建容纳日程表的二维数组 
	cout<<endl;
	table(n);
	if(n%2==0)
	{
		for(int i=1;i<=n;++i)
    	{
		    for(int j=1;j<=n;++j)
		    {
		    	if(array[i][j]<=n) 
		    	    cout<<array[i][j]<<" ";
		    	else
		    	    cout<<0<<" ";
			}
	    	cout<<endl;
	    }
	}
	else
	{
		for(int i=1;i<=n;++i)
	    {
		    for(int j=1;j<=n+1;++j)
		    {
		    	if(array[i][j]<=n) 
		    	    cout<<array[i][j]<<" ";
		    	else
		    	    cout<<0<<" ";
			}
		    cout<<endl;
	    }
	}
	
	return 0;
}
