#include <iostream>
using namespace std;
int main()
{
    int cont=0;
	int vect[100],mayor=0,mayorSig=0,posMayor,posMayorSig;
	do{
        cout << "Ingrese el numero " << cont + 1 << ":";
        cin>> vect[cont];
        if(vect[cont] == 0){
            break;
        }
        if(vect[cont]>mayor){
			mayor = vect[cont];
			posMayor = cont;
		}
        cont++;
    }
    while(cont < 100 || vect[cont] == 0);

	for(int i=0;i<cont;i++){
		if(vect[i]<mayor && vect[i]>mayorSig){
			mayorSig = vect[i];
			posMayorSig = i;
		}	
	}
	
	cout << "El mayor es: " << mayor << " y se encuentra en la posicion " << posMayor << endl;
	cout << "El otro mayor es: " << mayorSig << " y se encuentra en la posicion " << posMayorSig;
	
}
