#include <iostream>
using namespace std;
int main()
{
    int cont=0;
	float vect[100],maxNeg=0,minPos=0;
	do{
        cout << "Ingrese el numero " << cont + 1 << ":";
        cin>> vect[cont];
        if(vect[cont] == 0){
            break;
        }
        cont++;
    }
    while(cont < 100 || vect[cont] == 0);
    int i=0;
    float aux[i];
    minPos=vect[0];
    for(int j=0;j<cont;j++){
    	if(vect[j] < maxNeg){
    		aux[i] = vect[j];
    		i++;
		}
		if(vect[j] < minPos && vect[j] > 0){
			minPos = vect[j];
		}
	}
    
	maxNeg = aux[0];
    for(int h=0;h<i;h++){
    	if(aux[h] > maxNeg){
    		maxNeg = aux[h];
		}
	}
	
    cout << "El maximo negativo es: " << maxNeg << endl;
	cout << "El minimo positivo es: " << minPos <<endl;
}
