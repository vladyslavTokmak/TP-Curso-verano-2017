#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std; 

struct Nodo{
	int info;
	Nodo *sgte;
};

void agregar(Nodo*&fte, Nodo*&fin, int v){
	Nodo*p=new Nodo();
	p->info=v;
	p->sgte=NULL;
	
	if(fte==NULL){
		fte=p;
	}else{
		fin->sgte=p;
	}
	fin=p;
	return;
}

int suprimir(Nodo*&fte, Nodo*&fin){
	int v;
	Nodo*q=fte;
	v=q->info;
	fte=q->sgte;
	
	if(fte==NULL){
		fin==NULL;
	}
	delete q;
	return v;
}

int main(){
	Nodo *colAfte;
	Nodo *colAfin;
	Nodo *colBfte;
	Nodo *colBfin;
	Nodo *colABfte;
	Nodo *colABfin;
	
	while(colAfte!=colAfin){
		agregar(colABfte, colABfin, suprimir(colAfte, colAfin));
	}
	while(colBfte!=colBfin){
		agregar(colABfte, colABfin, suprimir(colBfte, colBfin));
	}
	
	
	return 0;
}
