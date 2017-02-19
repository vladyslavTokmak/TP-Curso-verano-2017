#include <iostream>

using namespace std;

struct listaInfo{
	int valor;
};

struct nodo {
	listaInfo info;
	nodo *sgte;
};

int main()
{

	nodo*lista;   
	
	int nodosLista = 0;
	
	while(lista != null)
		nodosLista++;
	
	if(nodosLista == 100){
		while(lista != null){
			cout << lista->info.valor << " ";
		}
	}
	else{
		nodo *aux;
   		nodo *p;
   
   		aux = NULL; 
   		while (lista != null){
      		p->sgte = aux;
      		aux = p;
   		}
   		lista = aux;
   		
   		while(lista != null){
			cout << lista->info.valor << " ";
		}
	}
	return 0;
}
