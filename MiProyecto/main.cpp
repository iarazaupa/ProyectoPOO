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
			int opcionMenu;
			
			do {
/*			sistema.menuNormal();*/
				cout << endl;
				cout << "----- MENU -----" << endl;
				cout << "1 - Agregar cliente" << endl;
				cout << "2 - Buscar cliente" << endl;
				cout << "3 No completado - Vender" << endl;
				cout << "4 - Listar clientes" << endl;
				cout << "5 - Ver stock" << endl;
				cout << "6 - Modificar Datos del cliente" << endl;
				cout << "0 - Salir" << endl;
				cout << "Opcion: ";
				cin>>opcionMenu;
			
				switch (opcionMenu) {
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
					int idModificar;
					string nuevoNombre;
					string nuevoEmail;
					string nuevoTelefono;
					int respuesta;
					
					cout << "DNI del cliente a modificar: ";
					cin >> idModificar;
					cin.ignore();
					
					Cliente clienteActual = sistema.BuscarCliente(idModificar);
					
					if (clienteActual.GetID() == 0) {
						cout << "No existe un cliente con ese DNI" << endl;
					}
					else {
						// Mostrar datos
						cout << "DNI: " << clienteActual.GetID() << endl;
						cout << "Nombre: " << clienteActual.getNombre() << endl;
						cout << "Email: " << clienteActual.getEmail() << endl;
						cout << "Telefono: " << clienteActual.getTelefono() << endl;
						cout << endl;
						
						nuevoNombre = clienteActual.getNombre();
						nuevoEmail = clienteActual.getEmail();
						nuevoTelefono = clienteActual.getTelefono();
						
						bool huboCambios = false;
						
						cout << "Modificar nombre? (1=si / 0=no): ";
						cin >> respuesta;
						cin.ignore();
						
						if (respuesta == 1) {
							cout << "Nuevo nombre: ";
							getline(cin, nuevoNombre);
							huboCambios = true;
						}
						
						cout << "Modificar email? (1=si / 0=no): ";
						cin >> respuesta;
						cin.ignore();
						
						if (respuesta == 1) {
							cout << "Nuevo email: ";
							getline(cin, nuevoEmail);
							huboCambios = true;
						}
						
						cout << "Modificar telefono? (1=si / 0=no): ";
						cin >> respuesta;
						cin.ignore();
						
						if (respuesta == 1) {
							cout << "Nuevo telefono: ";
							getline(cin, nuevoTelefono);
							huboCambios = true;
						}
						
						if (huboCambios) {
							
							if (sistema.ModificarCliente(idModificar,
														 nuevoNombre,
														 nuevoEmail,
														 nuevoTelefono))
								cout << "Cliente modificado correctamente";
							else
								cout << "Error al modificar";
						}
					}
				}
				break;
				default:
				break;
				}
			} while (opcionMenu != 0);
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
