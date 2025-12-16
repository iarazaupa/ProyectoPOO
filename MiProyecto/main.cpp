#include<iostream>
#include "Cliente.h"
using namespace std;

#include "Producto.h"

int main (int argc, char *argv[]) {
	Cliente c1(1, "iara lopez", "iaraALZ@mail.com", "111111");
	c1.guardarArchivo();
	cout<<"cliente guardado"<<endl;
	
	vector<Cliente> lista;
	lista = c1.cargarLista();
	
	cout << "lista:" << endl;
	for (int i = 0; i < lista.size(); i++) {
		lista[i].mostrar();
	}
	int idBuscar;
	cout << "ingrese id a buscar: ";
	cin >> idBuscar;
	
	Cliente* encontrado;
	encontrado = c1.buscarCliente(idBuscar);
	
	if (encontrado != nullptr) {
		cout << endl << "cliente encontrado:" << endl;
		encontrado->mostrar();
		delete encontrado;
	} else {
		cout << "cliente no encontrado" << endl;
	}
	return 0;
}

