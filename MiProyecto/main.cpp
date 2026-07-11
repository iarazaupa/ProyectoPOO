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
		
		Cliente gestor;
		Producto gestorProductos(0, "", "", 0, 0);
		
		cout << endl;
		cout << "----- INICIO DE SESION -----" << endl;
		cout << "1 - Usuario normal" << endl;
		cout << "2 - Administrador" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
	

	
		if(opcion == 1){

			sistema.menuNormal();
			
			/// opcion de agregar clientes ///
			cout<<"ponga la opcion de la accion que desea realizar";
			cin>>opcion;
			if (opcion == 1) {
				
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
			}else if(opcion == 2){
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
			/// opcion de agregar clientes ///

		
		}else if(opcion == 2) {
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
