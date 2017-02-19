#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std; 

struct Arribo{
	int arribo;
};

struct Nodo{
	Arribo info;
	Nodo*sgte;
};

void agregar(Nodo*&fte, Nodo*&fin, Arribo v){
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
	Arribo v;
	Nodo*q=fte;
	v=q->info;
	fte=q->sgte;
	
	if(fte==NULL){
		fin=NULL;
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
	
	while(colAfin!=colAfte && colBfin!=colBfte){
		if(colAfte->info.arribo<colBfte->info.arribo){
			agregar(colABfte, colABfin, suprimir(colAfte, colAfin));
		}else{
			agregar(colABfte, colABfin, suprimir(colBfte, colBfin));
		}
	}
	return 0;
}
