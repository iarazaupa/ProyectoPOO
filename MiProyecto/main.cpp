#include <iostream>
#include <vector>
#include "Cliente.h"
#include "Venta.h"
#include "Producto.h"

using namespace std;

int main() {
	
	int opcion;
	int id;
	string nombre;
	string email;
	string telefono;
	
	Cliente gestor;
	
	
	do {
		cout << endl;
		cout << "----- MENU -----" << endl;
		cout << "1 - Agregar cliente" << endl;
		cout << "2 - Buscar cliente" << endl;
		cout << "3 - Probar venta" << endl;
		cout << "4 - Listar clientes" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		
		// AGREGAR CLIENTE
		if (opcion == 1) {
			
			cout << "id: ";
			cin >> id;
			cin.ignore();
			
			if (gestor.existeID(id)) {
				cout << "Ese ID ya existe" << endl;
			} else {
				cout << "nombre: ";
				getline(cin, nombre);
				
				cout << "email: ";
				getline(cin, email);
				
				cout << "telefono: ";
				getline(cin, telefono);
				
				Cliente c(id, nombre, email, telefono);
				c.guardarArchivo();
				
				cout << "Cliente guardado!!" << endl;
			}
		}
		
		// BUSCAR CLIENTE
		else if (opcion == 2) {
			
			cout << "id a buscar: ";
			cin >> id;
			
			Cliente encontrado = gestor.buscarCliente(id);
			
			if (encontrado.getID() != 0) {
				cout << "Cliente encontrado" << endl;
				cout << "id: " << encontrado.getID() << endl;
				cout << "nombre: " << encontrado.getNombre() << endl;
				cout << "email: " << encontrado.getEmail() << endl;
				cout << "telefono: " << encontrado.getTelefono() << endl;
			} else {
				cout << "No se encontro :(" << endl;
			}
		}
		
		// PROBAR VENTA
		else if (opcion == 3) {
			
			cout << "id del cliente para la venta: ";
			cin >> id;
			
			Cliente clienteVenta = gestor.buscarCliente(id);
			
			if (clienteVenta.getID() == 0) {
				cout << "Cliente no existe" << endl;
			} else {
				Producto producto(100, "producto prueba", 15000, 10);
				
				Venta v(1, &clienteVenta);
				v.AgregarProducto(&producto, 2);
				v.ConfirmarVenta();
				
				cout << v.MostrarTicket();
			}
		}
		
		// LISTAR CLIENTES
		else if (opcion == 4) {
			
			vector<Cliente> lista = gestor.cargarLista();
			
			if (lista.empty()) {
				cout << "No hay clientes cargados" << endl;
			} else {
				cout << "----- LISTA DE CLIENTES -----" << endl;
				for (int i = 0; i < lista.size(); i++) {
					cout << "ID: " << lista[i].getID()
						<< " | Nombre: " << lista[i].getNombre()
						<< endl;
				}
			}
		}
		
		else if (opcion == 0) {
			cout << "Saliendo del programa..." << endl;
		}
		
		else {
			cout << "Opcion invalida" << endl;
		}
		
	} while (opcion != 0);
	
	return 0;
}
