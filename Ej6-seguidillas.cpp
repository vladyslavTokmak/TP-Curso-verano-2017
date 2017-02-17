#include <iostream>

using namespace std;

int main() {
	int n;
	cout << "Ingrese el cuantos valores tendra el vector (max 30): ";
	cin >> n;
	while(n < 0 && n > 30){
		cout << "ERROR\nIngrese nuevamente: ";
		cin >> n;
	}
	int vect[n],suma;
	for(int i=0;i<n;i++){
		cout << "Ingrese un valor: ";
		cin >> vect[i];
		suma += vect[i];
	}
	
	cout << "La suma de todos los valores es: " << suma << endl;
	cout << "El promedio es: " << 1.0*suma/n;
	return 0;
}
