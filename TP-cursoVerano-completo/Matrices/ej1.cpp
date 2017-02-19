#include <iostream>
using namespace std;
 
int main()
{
	int result;
	int mul[10][10];
	for(int i=0; i<10; i++)
	{
		cout<<"-------------------------------"<<endl;
		for(int j=0; j<10; j++)
		{
			mul[i][j]=(i+1)*(j+1);
			cout << i+1<<" por "<<j+1<<" : "<<mul[i][j]<<endl;	
		}
	} 
cin.get();
cin.get();
}
