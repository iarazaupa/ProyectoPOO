#include<iostream>
#include "Cliente.h"
using namespace std;

#include "Producto.h"

int main (int argc, char *argv[]) {
	Producto mateDeAlgarrobo(0, "mate de algarrobo", 16.00, 4);
	cout<<"probando a ver si se puede hacer commmit de un solo archivo. xd";
	cout<<"el mate:"<<mateDeAlgarrobo.GetNombre()<<"cuesta"<<mateDeAlgarrobo.GetPrecio()<<"y hay:"<<mateDeAlgarrobo.GetStock()<<"unidades";
	
	

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

