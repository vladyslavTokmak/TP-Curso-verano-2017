#include <iostream>
using namespace std;

int main()
{
	
	int may=0,aux;
	int numSoc[100];
	int codigo[100];
	int deporte[20]={0};
	for (int i=0;i<100;i++)
	{
		cout << "Ingrese el numero de socio(0 para terminar): ";
		cin>>numSoc[i];
		if (numSoc[i]==0)
		break;
		cout<< "Ingrese codigo de deporte: ";
		cin>>codigo[i];
		if (codigo[i]<1 && codigo[i]>20)
		{
		cout << "Codigo incorrecto. Ingrese los datos nuevamente.";
		i--;
		}
		else
		{
			deporte[codigo[i]-1]=deporte[codigo[i]-1]+1;
		}
	}

	cout << "Cantidad de inscriptos: "<<endl;
	for(int k=0;k<20;k++)
	{
		cout<<"Codigo de deporte "<<k+1<<" : "<<deporte[k]<<endl;
		if(deporte[k]>may)
		{
		may=deporte[k];
		aux=k+1;
		}
	}
	cout << "El codigo del deporte con mas inscriptos es: "<<aux;
	return 0;
}
