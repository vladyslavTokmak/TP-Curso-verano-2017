#include<iostream>

using namespace std;

struct Nodo{
	int info;
	Nodo *sgte;
};

void push(Nodo*&pila, int valor){
	Nodo*p=new Nodo();
	p->info=valor;
	p->sgte=pila;
	pila=p;
	return;
}

int pop(Nodo*&pila){
	int x; 
	Nodo*p=pila;
	x=p->info;
	pila=p->sgte;
	delete p;
	return x;
}

int main(){	
	int i;
	cin >> i;
	
	Nodo*pila;
	Nodo*pilaAux=NULL;
	
	/*
		Consideramos que la pila ya esta creada y que contiene valores.
		Lo que hacemos es que ingresamos el valor en la 3 pocicion alfinal de la pila.
		Ejemplo: 1 - 2 - 3 - 4 - 5 - 6 - 7 - valor - 8 - 9.
		Lo que hacemos es que se pasamos 2 valores de la pila a una pila auxiliar
		y luego ingresamos el valor. Despues devolvemos los valores de la pila auxiliar
		a la original 
	*/
	
	
	push(pilaAux, pop(pila));
	push(pilaAux, pop(pila));
	push(pilaAux, i);
	push(pila, pop(pilaAux));
	push(pila, pop(pilaAux));
	
	if(pilaAux == null && pila != null)
		cout << "S";
	else
		cout << "N";
}
