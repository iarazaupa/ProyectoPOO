#include <iostream>
#include <string>
#include "Cliente.h"

using namespace std;

int main() {
	
	Cliente c1(4, "PEPITO", "pepeP@gmail.com", "834741");
	c1.guardarArchivo();
	
	cout<<"cliente guardado"<<endl;
	
	int idBuscar;
	cout<<"ingrese id a buscar: ";
	cin>>idBuscar;
	cout<<"lista"<<endl;
	
	Cliente* encontrado;
	encontrado = c1.buscarCliente(idBuscar);
	
	if (encontrado != nullptr) {
		cout<<"cliente encontrado:"<<endl;
		cout << encontrado->mostrar();
		
		delete encontrado;
	} else {
		cout<<"cliente no encontrado"<<endl;
	}
	
	return 0;
}
