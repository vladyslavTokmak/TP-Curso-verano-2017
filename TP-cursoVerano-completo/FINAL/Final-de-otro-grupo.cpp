#include <iostream>
#include <dir.h>
#include<stdlib.h>
#include<string>
#include <stdio.h>
#include <iomanip>

using namespace std;

struct venta{
	int id;
	char categoria[31];
	char producto[31];
	float monto;
	int cantVendida;
};
struct nodo{
	venta info;
	nodo * sgte;
};
venta ventaR;
venta ventaNull;

void crearCarpetas();
void obtenerDatos(venta &);
void dondeGuardar(int,int,char *,char *);
void mostrarEnTxt(FILE *,char *);
void push(nodo* &,venta);
venta pop(nodo* &);

int main()
{
	//auxiliares para dia y mes
	int mesAux,mes1,mes2,dia1,diaAux,diasMes;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//ingreso de fecha y opcion para switch
	int opcion,fecha;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Sacar cual es el dia y mes
	char dia[2],mes[15],dondeGuardarDatos_dat[31]={},dondeGuardarDatos_txt[31]={};
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Ingreso de datos no supero los 100 registros y cant de registros para busqueda
	int cantRegistros = 0;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Datos a guardar
	int idIngresar,cantVendidaIngresar;
	float montoIngresar;
	char catIngresar[31],prodIngresar[31];
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Busueda
	int posicion = 0;
	int numBuscar;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//crea las carpetas
	crearCarpetas();
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	FILE * archivo;
	FILE * auxFile;
	//FILE * archivo = fopen("Enero/dia1.dat","wb+");
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Ingreso de la fecha
	cout<<"Introdusca una fecha en formato AAAAMMDD: ";
	cin>>fecha;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//vVriables aux para eliminar una venta
	int numEliminar;
	nodo * pila;
	nodo * pilaAux;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Variables para minimo maximo promedio y suam del dia 
	float suma=0,promedio=0,mayor,menor;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Calculo los valores del dia y mes, y compruebo si fueron bien ingresados.
	mes1 = (fecha / 1000) - (fecha/10000)*10;
	mes2 = (fecha / 100) - (fecha/1000)*10;
	dia1 = (fecha / 10) - (fecha/100)*10;
	mesAux = mes1*10 + mes2;
	diaAux = dia1*10 + (fecha - (fecha/10)*10);	
	while(mesAux > 12 || diaAux > 31){	
		cout<<"ERROR, se ingreso mal el mes\nIngrese nuevamente: ";
		cin>>fecha;
		mes1 = (fecha / 1000) - (fecha/10000)*10;
		mes2 = (fecha / 100) - (fecha/1000)*10;
		dia1 = (fecha / 10) - (fecha/100)*10;
		mesAux = mes1*10 + mes2;
		diaAux = dia1*10 + (fecha - (fecha/10)*10);
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Genero una cadena de caracteres la cual indica la direccion en la cual se guardara el archivo
	dondeGuardar(mesAux,diaAux,dondeGuardarDatos_dat,dondeGuardarDatos_txt);
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	system("cls");
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Muestro el menu e ingreso la opcion	
	cout<<"1-crear venta"<<endl;
	cout<<"2-eliminar venta"<<endl;
	cout<<"3-buscar venta"<<endl;
	cout<<"4-MAXIMO MINIMO PROMEDIO Y TOTAL DE VENTAS DEL DIA"<<endl;
	cout<<"5-MAXIMO MINIMO PROMEDIO Y TOTAL DE VENTAS DEL MES"<<endl;
	cout<<"6-cambiar fecha"<<endl;
	cout<<"7-Generar archivo de venta del dia tipo txt"<<endl;
	cout<<"0-Finalizar programa"<<endl;
	cout<<"Ingrese su opcion: ";
	cin>>opcion;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	system("cls");
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Un ciclo while el cual pemitira usar la funciones del menu tantas veces cuantas se quiera hasta que se ingrese un valor que haga que se termine
	while(opcion > 0 && opcion < 8){
		switch(opcion){
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
			//case 1 permite generar un nuevo registro en un archivo nuevo o uno ya creado
			case 1:
				cantRegistros = 0;
				auxFile = fopen(dondeGuardarDatos_dat,"r");
				if(auxFile != NULL){
					cout<<"El archivo existe"<<endl<<endl;
					archivo = fopen(dondeGuardarDatos_dat,"rb+");
					fseek(archivo,0,SEEK_END);
					cantRegistros = ftell(archivo)/sizeof(ventaR);
					if(cantRegistros != 100){
						fseek(archivo,0,SEEK_END);
						obtenerDatos(ventaR);
						fwrite(&ventaR,sizeof(ventaR),1,archivo);
					}
					else{
						cout<<"Este archivo ya tiene 100 registros,\nsi quiere ingresar elimine un registro"<<endl;
					}
				}
				else{
					cout<<"El archivo no existe"<<endl<<endl;
					archivo = fopen(dondeGuardarDatos_dat,"wb+");
					obtenerDatos(ventaR);
					fwrite(&ventaR,sizeof(ventaR),1,archivo);
				}
				fclose(archivo);
				break;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
			//Elimina un registro del archivo
			case 2:
				pila = NULL;
				pilaAux = pila;
				archivo = fopen(dondeGuardarDatos_dat,"rb+");
				cout<<"Ingrese el numero de id el cual desea eliminar: ";
				cin>>numEliminar;
				while(fread(&ventaR,sizeof(ventaR),1,archivo)){
					if(ventaR.id != numEliminar){
						push(pila,ventaR);
					}	
				}				
				fseek(archivo,0,SEEK_SET);
				while(pila != NULL){
					ventaR = pila->info;
					fwrite(&ventaR,sizeof(ventaR),1,archivo);
					pila = pila->sgte;
				}
				fseek(archivo,sizeof(ventaR)*(-1),SEEK_END);
				fwrite(&ventaNull,sizeof(ventaNull),1,archivo);
				fclose(archivo);				
				break;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
			//Permite buscar por id un registro del archivo
			case 3:
				cantRegistros = 0;
				cout<<"Ingrese numero de id que busca: ";
				cin>> numBuscar;
				archivo = fopen(dondeGuardarDatos_dat,"rb");
				
				cout<< left <<setw(10) << "Id" << " | " << setw(30) << "Producto" << " | " << setw(30) << "Categoria" << " | " << setw(10) << "Monto" << " | " <<setw(25) << "Cantidad Vendidos"<<endl;
				cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
				while(fread(&ventaR,sizeof(ventaR),1,archivo)){
					if(ventaR.id == numBuscar){
					cout<< setw(10) << ventaR.id << " | " << setw(30) << ventaR.producto << " | " << setw(30) << ventaR.categoria << " | " << setw(10) << ventaR.monto << " | " << setw(25) << ventaR.cantVendida << endl;
					cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
					posicion = ftell(archivo)/sizeof(ventaR);
					break;
					}
				}
				
				fclose(archivo);
				break;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
			//Muestra el minimo, el mayor, la suma de todas las ventas y el promedio del dia
			case 4:
				archivo = fopen(dondeGuardarDatos_dat,"rb");
				fseek(archivo,0,SEEK_END);
				cantRegistros = ftell(archivo)/sizeof(ventaR);
				fseek(archivo,0,SEEK_SET);
				fread(&ventaR,sizeof(ventaR),1,archivo);
				menor = ventaR.monto;
				mayor = ventaR.monto;
				fseek(archivo,0,SEEK_SET);
				while(fread(&ventaR,sizeof(ventaR),1,archivo)){
					if(ventaR.monto > mayor){
						mayor = ventaR.monto;
					}
					if(ventaR.monto < menor){
						menor = ventaR.monto;
					}
					suma = suma + (ventaR.monto * ventaR.cantVendida);
				}
				promedio = suma / cantRegistros;	
				cout<<"El mayor monto del dia es: "<<mayor<<endl;
				cout<<"El menor monto del dia es: "<<menor<<endl;
				cout<<"La suma de lo vendido en el dia es: "<<suma<<endl;
				cout<<"El promedio es: "<<promedio<<endl;
				break;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
			//Muestra el minimo, el mayor, la suma de todas las ventas y el promedio de todo el mes
			case 5:
				diasMes = 1;
				for(int i=1;i<32;i++){
					dondeGuardar(mesAux,i,dondeGuardarDatos_dat,dondeGuardarDatos_txt);
					archivo = fopen(dondeGuardarDatos_dat,"rb");
					if(archivo != NULL){
						fseek(archivo,0,SEEK_END);
						cantRegistros = ftell(archivo)/sizeof(ventaR);
						fseek(archivo,0,SEEK_SET);
						fread(&ventaR,sizeof(ventaR),1,archivo);
						menor = ventaR.monto;
						mayor = ventaR.monto;
						fseek(archivo,0,SEEK_SET);
						while(fread(&ventaR,sizeof(ventaR),1,archivo)){
							if(ventaR.monto > mayor){
								mayor = ventaR.monto;
							}
							if(ventaR.monto < menor){
								menor = ventaR.monto;
							}
							suma = suma + (ventaR.monto * ventaR.cantVendida);
						}
						promedio = suma / cantRegistros;
					}
					else{
						cout<<"El archivo "<<i<<".dat no existe"<<endl;
					}
					fclose(archivo);
				}
				cout<<"El mayor monto del dia es: "<<mayor<<endl;
				cout<<"El menor monto del dia es: "<<menor<<endl;
				cout<<"La suma de lo vendido en el dia es: "<<suma<<endl;
				cout<<"El promedio es: "<<promedio<<endl;
				break;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
			//Permite ingresar una nueva fecha
			case 6:
				cout<<"Introdusca una fecha en formato AAAAMMDD: ";
				cin>>fecha;
				mes1 = (fecha / 1000) - (fecha/10000)*10;
				mes2 = (fecha / 100) - (fecha/1000)*10;
				dia1 = (fecha / 10) - (fecha/100)*10;
				while(mes1>1 || mes2 > 2 || dia1>3 ){
			
					cout<<"ERROR, se ingreso mal el mes\nIngrese nuevamente: ";
					cin>>fecha;
					mes1 = (fecha / 1000) - (fecha/10000)*10;
					mes2 = (fecha / 100) - (fecha/1000)*10;
					dia1 = (fecha / 10) - (fecha/100)*10;
				}
				system("cls");
				break;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
			//Permite mostrar las ventas de un dia por medio de un txt
			case 7:
				freopen(dondeGuardarDatos_txt,"w",stdout);
				mostrarEnTxt(archivo,dondeGuardarDatos_dat);
				fclose(stdout);
				break;
			defaul:
				break;
		}
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
		//se muestra nuevamente el menu y se ingresa la opcion
		cout<<"1-crear venta"<<endl;
		cout<<"2-eliminar venta"<<endl;
		cout<<"3-buscar venta"<<endl;
		cout<<"4-MAXIMO MINIMO PROMEDIO Y TOTAL DE VENTAS DEL DIA"<<endl;
		cout<<"5-MAXIMO MINIMO PROMEDIO Y TOTAL DE VENTAS DEL MES"<<endl;
		cout<<"6-cambiar fecha"<<endl;
		cout<<"7-Generar archivo de venta del dia tipo txt"<<endl;
		cout<<"0-Finalizar programa"<<endl;
		cout<<"Ingrese su opcion: ";
		cin>>opcion;
		system("cls");
	}	
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//Funcion que crea las carpetas de los 12 meses
void crearCarpetas(){	
	mkdir("Enero");
	mkdir("Febrero");
	mkdir("Marzo");
	mkdir("Abril");
	mkdir("Mayo");
	mkdir("Junio");
	mkdir("Julio");
	mkdir("Agosto");
	mkdir("Septiembre");
	mkdir("Octubre");
	mkdir("Noviembre");
	mkdir("Diciembre");
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//Funcion para obtener los datos, los cuales se guardaran en el archivo
void obtenerDatos(venta &rDatos){
	cout<<"Ingrese la id: ";
	cin>>rDatos.id;
	while(rDatos.id < 0){
		cout<<"ERROR, se ingreso mal la id\nIngrese nuevamente: ";
		cin>>rDatos.id;
	}		
	cout<<"Ingrese el monto: ";
	cin>>rDatos.monto;
	while(rDatos.monto < 0){
		cout<<"ERROR, se ingreso mal el monto\nIngrese nuevamente: ";
		cin>>rDatos.monto;
	}
	cout<<"Ingrese la cantidad vendida: ";
	cin>>rDatos.cantVendida;
	while(rDatos.cantVendida < 0){
		cout<<"ERROR, se ingreso mal la cantidad vendida\nIngrese nuevamente: ";
		cin>>rDatos.cantVendida;
	}
	cout<<"Ingrese el producto: ";
	cin>>rDatos.producto;
	cout<<"Ingrese la categoria: ";
	cin>>rDatos.categoria;					
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//Funcin que genera una cadena de caracteres, que sera la direccion en la cual se guardaran los archivo
void dondeGuardar(int mes,int dia,char * dondeGuardarDat,char * dondeGuardarTxt){
	char aux1[21]={};
	char aux2[21]={};
	char diaAux[2];
	switch(mes){
		case 1:
			strcat(aux1,"Enero");
			strcat(aux2,"Enero");
			break;
		case 2:
			strcat(aux1,"Febrero");
			strcat(aux2,"Febrero");
			break;
		case 3:
			strcat(aux1,"Marzo");
			strcat(aux2,"Marzo");
			break;
		case 4:
			strcat(aux1,"Abril");
			strcat(aux2,"Abril");
			break;
		case 5:
			strcat(aux1,"Mayo");
			strcat(aux2,"Mayo");
			break;
		case 6:
			strcat(aux1,"Junio");
			strcat(aux2,"Junio");
			break;
		case 7:
			strcat(aux1,"Julio");
			strcat(aux2,"Julio");
			break;
		case 8:
			strcat(aux1,"Agosto");
			strcat(aux2,"Agosto");
			break;
		case 9:
			strcat(aux1,"Septiembre");
			strcat(aux2,"Septiembre");
			break;
		case 10:
			strcat(aux1,"Octubre");
			strcat(aux2,"Octubre");
			break;
		case 11:
			strcat(aux1,"Noviembre");
			strcat(aux2,"Noviembre");
			break;
		case 12:
			strcat(aux1,"Diciembre");
			strcat(aux2,"Diciembre");
			break;				
	}
	strcat(aux1,"/");
	itoa(dia,diaAux,10);
	strcat(aux1,diaAux);
	strcat(aux1,".dat");
	strcat(dondeGuardarDat,aux1);
	strcat(aux2,"/");
	itoa(dia,diaAux,10);
	strcat(aux2,diaAux);
	strcat(aux2,".txt");
	strcat(dondeGuardarTxt,aux2);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//Funcion que permite mostrar las ventas de un dia por medio de un txt
void mostrarEnTxt(FILE * archivoDeDia,char * dondeGuardar){
	archivoDeDia = fopen(dondeGuardar,"rb");
	cout<< left <<setw(10) << "Id" << " | " << setw(30) << "Producto" << " | " << setw(30) << "Categoria" << " | " << setw(10) << "Monto" << " | " <<setw(25) << "Cantidad Vendidos"<<endl;
	cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
	while(fread(&ventaR,sizeof(ventaR),1,archivoDeDia)){
		cout<< setw(10) << ventaR.id << " | " << setw(30) << ventaR.producto << " | " << setw(30) << ventaR.categoria << " | " << setw(10) << ventaR.monto << " | " << setw(25) << ventaR.cantVendida << endl;
		cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//Funcion push
void push(nodo* &p,venta vR){
	nodo * nuevo = new nodo();
	nuevo->info = vR;
	nuevo->sgte = p;
	p = nuevo;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//Funcion pop
venta pop(nodo* &p){
	nodo* aux = p;
	venta vR = aux->info;
	p = aux->sgte;
	delete aux;
	return vR;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//																																																								//
//                                                                               When I wrote this, only God and I understood that was doin																						//
//                                                                                                  Now, God only knows																											//
//																																																								//	
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
