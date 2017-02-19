#include <iostream>
using namespace std;

struct pila
{
	int valor;
};
struct nodo
{
	pila info;
	nodo*sgte;
};

void push (nodo*&,int);
int pop (nodo*&);

int main ()
{
	int x,y,num;
	nodo*pila= NULL;
	nodo*pila2=NULL;
	for(int i=0;i<20;i++)
	{
		cout << "Ingrese un valor(0 para terminar): ";
		cin>>num;
		if (num==0)
			break;
		push (pila, num);
	}
	
	cout << "Ingrese valor x: ";
		cin>>x;
	cout << "Ingrese valor y: ";
		cin>>y;
	
	while (pila!=NULL)
	{
		int aux = pop(pila);
		if(aux == x)
			push(pila2, y);
		else
			push (pila2, aux);
	}
	
}

int pop(nodo*&pila)
{
	int z;
	nodo*p=pila;
	z=p->info.valor;
	pila=p->sgte;
	delete p;
	return z;
}
void push (nodo*&pila, int valor)
{
	nodo*p=new nodo();
	p->info.valor=valor;
	p->sgte=pila;
	pila=p;
}
