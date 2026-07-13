#include "Sistema.h"
#include <iostream>
#include <string>
#include "Cliente.h"
#include "Producto.h"
using namespace std;

int main() {
	
	Sistema sistema;
	
	int opcion;
	
	do{
		
		int Dni;
		string nombre;
		string email;
		string telefono;
		
		//No se pa q sirve
//		Cliente gestor;
//		Producto gestorProductos(0, "", "", 0, 0);
		
		cout << endl;
		cout << "----- INICIO DE SESION -----" << endl;
		cout << "1 - Usuario normal" << endl;
		cout << "2 - Administrador" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
	
		if(opcion == 1){

/*			sistema.menuNormal();*/
			
			cout << endl;
			cout << "----- MENU -----" << endl;
			cout << "1 - Agregar cliente" << endl;
			cout << "2 - Buscar cliente" << endl;
			cout << "3 No completado - Vender" << endl;
			cout << "4 - Listar clientes" << endl;
			cout << "5 - Ver stock" << endl;
			cout << "6 No completado - Modificar Datos del cliente" << endl;
			cout << "0 - Salir" << endl;
			cout << "Opcion: ";
			cin>>opcion;
			
			switch (opcion) {
			case 1: {
				///Agregar Cliente
				bool clienteAgg = false;
				
				while (!clienteAgg) {
					cout << "DNI: ";
					
					// Validación de que es un número
					while (!(cin >> Dni)) {
						cout << "Error: ingrese un DNI valido (solo numeros): ";
						cin.clear();
						cin.ignore(10000, '\n');
					}
					
					cin.ignore(); // limpiar el salto de línea
					
					cout << "Nombre: ";
					getline(cin, nombre);
					
					cout << "Email: ";
					getline(cin, email);
					
					cout << "Telefono: ";
					getline(cin, telefono);
					
					clienteAgg = sistema.agregarCliente(Dni, nombre, email, telefono);
					
					if (!clienteAgg) {
						cout << "Error: ya existe un cliente con ese DNI. Intente nuevamente.\n\n";
					}
				}
				cout << "Usuario agregado correctamente.\n";
			}
			break;
			case 2: {
				///Buscar Cliente 
				cout << "DNI a buscar: ";
				
				//validacion de que es un numero
				while (!(cin >> Dni)) {
					cout << "Error: ingrese un DNI valido (solo numeros): ";
					cin.clear();
					cin.ignore(10000, '\n');
				}
				
				cin.ignore();
				
				Cliente encontrado = sistema.BuscarCliente(Dni);
				
				if (encontrado.GetID() != 0) {
					
					cout << "Cliente encontrado" << endl;
					cout << "DNI: " << encontrado.GetID() << endl;
					cout << "Nombre: " << encontrado.getNombre() << endl;
					cout << "Email: " << encontrado.getEmail() << endl;
					cout << "Telefono: " << encontrado.getTelefono() << endl;
				}
				else {
					cout << "No se encontro :(" << endl;
				}
			}
			break;
			case 3: {
				///Vender
				
			}
			break;
			case 4: {
				///Listar Clientes
				vector<Cliente> clientes;
				if (sistema.ListarClientes(clientes)) {
					for (int i = 0; i < clientes.size(); i++) {
						cout << "DNI: " << clientes[i].GetID()
							<< " | Nombre: " << clientes[i].getNombre()
							<< " | Telefono: " << clientes[i].getTelefono() << endl;
					}
				} else {
					cout << "No hay clientes registrados" << endl;
				}
			}
			break;
			case 5: {
				///Ver Stock
				vector<Producto> productos;
				if (sistema.ListarProductos(productos)) {
					
					for (int i = 0; i < productos.size(); i++) {
						cout << productos[i].GetID() << " "
							<< productos[i].GetNombre() << " "
							<< productos[i].GetCategoria() << " "
							<< productos[i].GetPrecio() << " "
							<< productos[i].GetStock() << endl;
					}
				} else {
					cout << "No hay productos" << endl;
				}
			}
			break;
			case 6: {
				///Modificar Cliente
				
			}
			break;
			default:
				cout << "ola" << endl;
			break;
			}
			
		} else if (opcion == 2) {
			string pass;
			cout<<"ingrese la contrasenia";
			cin>>pass;
			if (!sistema.verificarPassword(pass)) {
				cout << "Password incorrecta" << endl;
				return -1;
			}else{
				sistema.menuAdmin();
			}
		}
	} while(opcion != 0);
	return 0;
}
