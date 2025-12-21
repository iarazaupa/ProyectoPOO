#include <iostream>
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
	
	int opcion;
	int id;
	string nombre;
	string email;
	string telefono;
	
	Cliente gestor;
	
	cout << "1 - agregar cliente" << endl;
	cout << "2 - buscar cliente" << endl;
	cout << "opcion: ";
	cin >> opcion;
	
	if (opcion == 1) {
		
		cout << "id: ";
		cin >> id;
		cin.ignore();
		
		if (gestor.existeID(id)) {
			cout << "ese id ya existe" << endl;
			return 0;
		}
		
		cout << "nombre: ";
		getline(cin, nombre);
		
		cout << "email: ";
		getline(cin, email);
		
		cout << "telefono: ";
		getline(cin, telefono);
		
		Cliente c(id, nombre, email, telefono);
		c.guardarArchivo();
		
		cout << "guardado!!" << endl;
	}
	
	if (opcion == 2) {
		
		cout << "id a buscar: ";
		cin >> id;
		
		Cliente encontrado = gestor.buscarCliente(id);
		
		if (encontrado.getID() != 0) {
			cout << "cliente encontrado" << endl;
			cout << "id: " << encontrado.getID() << endl;
			cout << "nombre: " << encontrado.getNombre() << endl;
			cout << "email: " << encontrado.getEmail() << endl;
			cout << "telefono: " << encontrado.getTelefono() << endl;
		} else {
			cout << "no se encontro :(" << endl;
		}
	}
	
	return 0;
}
