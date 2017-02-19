#include <iostream>

using namespace std;

struct listaInfo{
	int legajo;
};

struct nodo {
	listaInfo info;
	nodo *sgte;
};

int main()
{
	nodo*listA;
	nodo*listB;
	nodo*listC;
	
	while(listA != null && listB != null){
		if(listA->info.legajo < listB->info.legajo){
			listC->info.legajo = listA->info.legajo;
			listA = listA->sgte;
		}
		else{
			listC->info.legajo = listB->info.legajo;
			listB = listB->sgte;
		}
	}
	while(listA != null){
		listC->info.legajo = listA->info.legajo;
		listA = listA->sgte;
	}
		while(listB != null){
		listC->info.legajo = listB->info.legajo;
		listB = listB->sgte;
	}
	
	delete(listA);
	delete(listB);
	return 0;
}
