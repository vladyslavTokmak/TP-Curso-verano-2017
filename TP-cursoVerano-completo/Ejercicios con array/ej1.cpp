#include <iostream>

using namespace std;


int main()
{
	int n;
	cout << "Ingrese el valor n: ";
	cin >> n;
	
	while(n > 25 || n <= 0){
		cout << "Error. Ingrese nuevamente: ";
		cin >> n;
	}
	
	float vectA[n],vectB[n],vectC[n],vectD[n];
	
	for(int i=0;i<n;i++){
		cout << "Ingrese un valor en el primer vector: ";
		cin >> vectA[i];
	}
	cout << endl << endl;
	for(int y=0;y<n;y++){
		cout << "Ingrese un valor en el segundo vector: ";
		cin >> vectB[y];
	}
	
	for(int j=0;j<n;j++){
		if(j%2 == 0){
			vectC[j] = vectB[j];
		}
		else{
			vectC[j] = vectA[j];
		}
			
		if(vectA[j] == vectB[j]){
			vectD[j] = 0;
		}
		else{
			if(j%2 == 0)
				vectD[j] = vectB[j];
			else
				vectD[j] = vectA[j];
		}
	}
	cout <<endl<< "Vectro C" << endl;
	for(int z=0;z<n;z++)
		cout << vectC[z] << " ";
	
	cout << endl << "Vector D"<<endl;
	for(int x=0;x<n;x++)
		cout << vectD[x] << " ";
	return 0;
}
