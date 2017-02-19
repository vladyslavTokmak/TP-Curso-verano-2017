#include <iostream>
using namespace std;
int main()
{
	int n,suma=0,cont=0,may=0,filaMay,colMay,minFila,maxCol=0,princ=0,sec=0;
	float promedio;
	cout << "Ingrese cuantas filas y columnas tendra la matriz: ";
	cin >> n;
	int mat[n][n];
	cout << "Ingrese los valores: ";
	for(int i=0;i<n;i++)
	{
		cout<< "Fila "<<i<<endl;
		for(int j=0;j<n;j++)
		{
			cin>> mat[i][j];
			minFila = mat[i][0];
			
			suma+=mat[i][j];
			cont++;
			if(mat[i][j]>may)
			{
				may=mat[i][j];
				filaMay=i;
				colMay=j;
			}
			if (mat[i][j] < minFila)
         		minFila = mat[i][j];
         
        	
		}
		cout << "Minimo de la fila "<<i<<": "<<minFila<<endl;
		
	}

	promedio= float(suma)/cont;
	cout << "La sumatoria de los elementos es: "<<suma;
	cout <<"\nEl promedio de los elementos es: "<<promedio;
	cout << "\nEl maximo elemento es "<<may<<" y se encuentra en la fila "<<filaMay<<" columna "<<colMay<<endl;
	for(int l=0;l<n;l++)
	{
		for(int k=0;k<n;k++)
		{
			if (mat[k][l]>maxCol)
				maxCol=mat[k][l];
			if (l==k && mat[k][l]>0)
				princ++;
		}
		cout << "Maximo de la columna "<<l<<": "<<maxCol<<endl;
		maxCol=0;
	}
	cout << "\nEn la diagonal principal hay "<<princ<<" elementos positivos";
	for(int o=n;o>=0;o--)
	{
		for (int p=0;p<n;p++)
		{
			if (mat[o][p]<0)
				sec++;
		}
	}
	cout << "\nEn la diagonal secundaria hay "<<sec-1<<" elementos negativos";
	return 0;
}
