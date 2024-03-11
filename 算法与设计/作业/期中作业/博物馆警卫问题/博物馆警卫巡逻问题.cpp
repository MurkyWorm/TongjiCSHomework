#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

struct LOC {
	int x;
	int y;
}; 
double** array;
void initial(vector<LOC>& locations){
    int n;

    n=locations.size();
    array=(double**)malloc(n*sizeof(double*));
    if(!array)
        exit(-1);
    for(int i=0;i<n;++i)
    {
        *(array+i)=(double*)malloc(n*sizeof(double));
        if(!*(array+i))
            exit(-1);
    }
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            array[i][j]=0;
}
double count(vector<LOC>& locations,int i,int j)
{
    double min=10000000,S,left,right;

    if(j-i<=1)
        return 0;
    if(array[i][j]!=0)
        return array[i][j];
    if(j-i==2)
    {
        array[i][j]=sqrt(double(pow(locations[i].x-locations[i+1].x,2)+pow(locations[i].y-locations[i+1].y,2)))
                   +sqrt(double(pow(locations[i+1].x-locations[i+2].x,2)+pow(locations[i+1].y-locations[i+2].y,2)))
                   +sqrt(double(pow(locations[i].x-locations[i+2].x,2)+pow(locations[i].y-locations[i+2].y,2)));
        return array[i][j];
    }
    for(int k=i+1;k<j;++k)
    {
        S=sqrt(double(pow(locations[i].x-locations[j].x,2)+pow(locations[i].y-locations[j].y,2)))
         +sqrt(double(pow(locations[j].x-locations[k].x,2)+pow(locations[j].y-locations[k].y,2)))
         +sqrt(double(pow(locations[i].x-locations[k].x,2)+pow(locations[i].y-locations[k].y,2)));
        left=count(locations,i,k);
        right=count(locations,k,j);
        S=S+left+right;
        if(S<min)
            min=S;
    }
    array[i][j]=min;

    return min;
}
double minScoreTriangulation(vector<LOC>& locations) {
    initial(locations);
    return count(locations,0,locations.size()-1);
}
int main()
{
	int n;
	cin >> n;
	vector<LOC> locations(n);
	for (int i = 0; i < n; ++i) {
		cin >> locations[i].x;
		cin >> locations[i].y;
	}
	cout<<minScoreTriangulation(locations);
	
	return 0;
}
