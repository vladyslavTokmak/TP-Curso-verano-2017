/* 	Se tiene un un archivo binario ordenado de menor a mayor por el codigo de afiliado.
	El archivo contiene los siguientes campos: codigo de afiliado , nombre y deporte.
	
	Realizar un programa q indique la cantidad de afiliados.
	Ademas debera hacer una busqueda por codigo de afiliado la cual mostrara 
	los datos de aquell afiliado y en que posicion se encontraba dentro del archivo.
 */

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include<iomanip>
using namespace std;

typedef char str20[21];

struct StructDatos {
	int conAfi;
	str20 	nombre,
			deporte;
};

void ObtDatos(StructDatos &);

int main() {
	FILE *Datos;
	StructDatos sDatos;

	Datos = fopen("Datos.bin","rb");

	int cantidadRegistros;
	int posicion = -1;
	int	principio = 0;
	int numBuscar;
	 
	fseek(Datos,0,SEEK_END);
	
	cantidadRegistros = ftell(Datos) / sizeof(sDatos);
	
	cout<<"La cantidad de registros que posee el archivo es: "<<cantidadRegistros <<endl<<endl;
	
	fseek(Datos,0,SEEK_SET);	
	cout<<"Ingrese codigo de afiliado que busca: ";
	cin>> numBuscar;
	
	while((posicion == -1) && principio <= cantidadRegistros){
		
		int mitad = (principio + cantidadRegistros)/2;
		fseek(Datos,mitad*sizeof(sDatos),SEEK_SET);
		fread(&sDatos,sizeof(sDatos),1,Datos);
		if(sDatos.conAfi == numBuscar)
		{
			posicion = mitad;
		}
		else
		{
			if(numBuscar > sDatos.conAfi)
			{
				principio = mitad + 1;
			}
			else{
				cantidadRegistros = mitad - 1;
			}
		}
	}
	if(posicion == -1){
		cout<<"No se pudo encontrar tal codigo de afiliado"<<endl;
	}
	else{
			cout<<endl<<"El dato se encuentra en la posicion: "<< posicion <<endl<<endl;
			fseek(Datos,posicion*sizeof(sDatos),SEEK_SET);
			cout<< setw(10) << "Codigo de afiliado" << setw(15) << "Deporte" << setw(15) << "Nombre" << endl<<endl;
			cout<< setw(9) << sDatos.conAfi << " " << setw(14) << sDatos.deporte << " " << setw(14) << sDatos.nombre << endl;
	}
	
	fclose(Datos);
}

