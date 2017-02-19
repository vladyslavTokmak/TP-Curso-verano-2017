/*
	Se tiene un archivo binario de datos "Datos.dat",desordenado, se pide realizar 
	un programa que genere una estructura de incdices "Indice.idx"( este mismo tendra 
	tantas componentes como tenga el archivo Datos.dat), para que lo ordene en forma asendente. 
	El archivo Datos.dat tendra los siguientes campos: int cmpClv, int cmp1, float cmp2, char cmp3[21].

	Luego se pide que se obtenga un listado ordenado desendentemente segun 
	la estructura de indice y que emita los datos contenidos en el archivo 
	binario "Datos.dat" por pantalla y tambien los guarde en un archivo "Datos.txt".

	Por ultimo crear un archivo binario "Menores .dat", que a partir del archivo "Datos.dat" 
	desordenado pero ordenado logicamente por la estructura de indices, se pida ingresar un numero 
	real y que compara el cmp2 con el valor ingresado. En caso de ser menor al numero ingresado, 
	entonces se genera una nueva componente en el archivo "Menores.dat", pero ordenado por el valor 
	del cmpClv en forma asendente. Ademas guardarlo en un archivo "Menores.txt".
*/
#include <iostream>
#include <iomanip>
using namespace std;

typedef char str20[21];

struct structDatos{
	int cmpClv,
		cmp1;
	float cmp2;
	str20 cmp3;
};

struct structIndice{
	int cmpClv,
		referencia;
};

structDatos sDatos;
structIndice sIndice;

void insertarClave(FILE *,structIndice,int);
void crearIndice(FILE *,FILE *);
void listar(FILE *,FILE *);
void menores(FILE *,FILE *,FILE *,float);

int main() {
	
	float numero = 0;
	cout << "Ingrese un numero para comparar con el cmp2: ";
	cin >> numero;
	
	FILE *archivoDatos = fopen("Datos.dat","rb");
	FILE *archivoIndice = fopen("Indice.idx","wb+");
	FILE *archivoMenores = fopen("Menores.dat","w+b");
	
	crearIndice(archivoIndice,archivoDatos);
	freopen("Listado.txt","w",stdout);
	listar(archivoIndice,archivoDatos);
	fclose(stdout);
	
	freopen("Menores.txt","w",stdout);
	menores(archivoIndice,archivoDatos,archivoMenores,numero);
	fclose(stdout);
	fcloseall();
	
	return 0;
}

void crearIndice(FILE *archivoIndice,FILE *archivoDatos){
	
	int cantidad = 0;
	
	while(fread(&sDatos,sizeof(sDatos),1,archivoDatos)){
		sIndice.cmpClv = sDatos.cmpClv;
		sIndice.referencia = ftell(archivoDatos)/sizeof(sDatos)-1;
		insertarClave(archivoIndice,sIndice,cantidad);
		cantidad += 1;
	}
}

void insertarClave(FILE *archivoIndice,structIndice stInd,int cantidadElementos){
	
	if(cantidadElementos > 0){
		fseek(archivoIndice,(cantidadElementos-1)*sizeof(sIndice),SEEK_SET);
		fread(&sIndice,sizeof(sIndice),1,archivoIndice);
	}
	while(cantidadElementos > 0 && stInd.cmpClv < sIndice.cmpClv){
		fseek(archivoIndice,cantidadElementos*sizeof(sIndice),SEEK_SET);
		fwrite(&sIndice,sizeof(sIndice),1,archivoIndice);
		cantidadElementos += 1;
		if(cantidadElementos>0){
			fseek(archivoIndice,(cantidadElementos-1)*sizeof(sIndice),SEEK_SET);
			fread(&sIndice,sizeof(sIndice),1,archivoIndice);
		}
	}
	fseek(archivoIndice,cantidadElementos*sizeof(sIndice),SEEK_SET);
	fwrite(&stInd,sizeof(stInd),1,archivoIndice);
}

void listar(FILE *archivoIndice,FILE *archivoDatos){
	
	int posArchivo = 0,registros = 0;
	cout << "Listado: "<<endl<<endl;
	cout<<right<<setw(15)<<"cmpClv:"<<setw(15)<<"cmp1:"<<setw(15)<<"cmp2:"<<setw(20)<<"cmp3:"<<endl<<endl;
	fseek(archivoIndice,0,SEEK_SET);
	registros = ftell(archivoIndice)/sizeof(structIndice);
	posArchivo = ftell(archivoIndice) - sizeof(structIndice);
	while(fread(&sIndice,sizeof(structIndice),1,archivoIndice) || registros >0 ){
		fseek(archivoDatos,sIndice.referencia*sizeof(structDatos),SEEK_SET);
		fread(&sDatos,sizeof(sDatos),1,archivoDatos);
		cout<<right<<setw(15)<<sDatos.cmpClv<<setw(15)<<sDatos.cmp1<<setw(15)<<sDatos.cmp2<<setw(20)<<sDatos.cmp3<<endl;
		posArchivo -= sizeof(structIndice);
		fseek(archivoIndice,posArchivo,SEEK_SET);
		registros -= 1;
	}
}

void menores(FILE *archivoIndice,FILE *archivoDatos,FILE *archivoMenores,float numero){
	
	rewind(archivoIndice);
	while(fread(&sIndice,sizeof(sIndice),1,archivoIndice)){
		fseek(archivoDatos,sIndice.referencia*sizeof(sDatos),SEEK_SET);
		fread(&sDatos,sizeof(sDatos),1,archivoDatos);
		if(numero > sDatos.cmp2)
			fwrite(&sDatos,sizeof(sDatos),1,archivoMenores);
	}
	rewind(archivoMenores);
	int cont = 1;
	cout << "Listado de menores a "<< numero << ":"<<endl<<endl;
	cout << right << setw(3)<<"Num"<<setw(15)<<"cmpClv:"<<setw(15)<<"cmp1:"<<setw(15)<<"cmp2:"<<setw(20)<<"cmp3:"<<endl<<endl;
	while(fread(&sDatos,sizeof(sDatos),1,archivoMenores)){
		cout << right << setw(3)<<cont<<setw(15)<<sDatos.cmpClv<<setw(15)<<sDatos.cmp1<<setw(15)<<sDatos.cmp2<<setw(20)<<sDatos.cmp3<<endl<<endl;
		cont += 1;
	} 
}
