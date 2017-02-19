#include <iostream>

using namespace std;

int main() {
	float conjunto[20],mayor=0;
	for(int i=0;i<20;i++){
		cout << "Ingrese un numero: ";
		cin >> conjunto[i];
		if(conjunto[i]>mayor)
			mayor = conjunto[i];
	}
	cout << "El mayor del conjunto es: " << mayor;
	return 0;
}
