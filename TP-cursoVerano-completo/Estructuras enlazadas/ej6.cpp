#include <iostream>
using namespace std;

struct dato
{
	int c1;
};

struct nodo
{
	dato info;
	nodo*sgte;
};

void agregar(nodo*&,nodo*&,int);

int main()
{	
	nodo*cola=NULL;
	nodo*fte=NULL;
	nodo*fin=NULL;
	nodo*cola2=NULL;
	nodo*fte2=NULL;
	nodo*fin2=NULL;
	int c1,n;
	cout << "Ingrese cuantas colas va a usar: ";
	cin>>n;
	dato vector[n];
	for (int i=0;i<n;i++)
	{
		cout << "Ingrese valor: ";
		cin>>c1;
		agregar(fte,fin,c1);	
	}
	int j=0,k=0;
	while(j<n&&k<n)
	{
		if(vector[j].c1<vector[k].c1)
		{
			agregar(fte2,fin2,vector[j].c1);
			j++;
		}
		else
		{
			agregar(fte2,fin2,vector[k].c1);
			k++;
		}
	}
	return 0;
}

void agregar(nodo*&fte,nodo*&fin,int valor)
{
	nodo*p=new nodo();
	p->info.c1=valor;
	p->sgte=NULL;
	if (fte==NULL)
	{
		fte=p;
	}
	else
	{
		fin->sgte=p;
	}
	fin=p;
}
