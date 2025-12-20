#include <iostream>
#include <string>
#include "Cliente.h"

using namespace std;

<<<<<<< HEAD
#include "Producto.h"

int main (int argc, char *argv[]) {
	Producto mateDeAlgarrobo(0, "mate de algarrobo", 16.00, 4);
<<<<<<< HEAD
	cout<<"probando a ver si se puede hacer commmit de un solo archivo. xd";
=======
	
>>>>>>> 9735ddb (prueba de que funciona el main con cliente)
	cout<<"el mate:"<<mateDeAlgarrobo.GetNombre()<<"cuesta"<<mateDeAlgarrobo.GetPrecio()<<"y hay:"<<mateDeAlgarrobo.GetStock()<<"unidades";
=======
int main() {
>>>>>>> 72c8520e51b066561c48eec710aa55560b40782e
	
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
