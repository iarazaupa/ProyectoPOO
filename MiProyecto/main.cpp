#include <iostream>
#include "Cliente.h"

int main() {
	
	int opcion;
	int id;
	std::string nombre;
	std::string email;
	std::string telefono;
	
	Cliente gestor;
	
	std::cout << "1 - agregar cliente"<<std::endl;
	std::cout << "2 - buscar "<<std::endl;
	std::cout << "opcion: ";
	std::cin >> opcion;
	
	if (opcion == 1) {
		
		std::cout << "id: ";
		std::cin >> id;
		std::cin.ignore();
		
		std::cout << "nombre: ";
		std::getline(std::cin, nombre);
		
		std::cout<< "email: ";
		std::getline(std::cin, email);
		
		std::cout<< "telefono: ";
		std::getline(std::cin, telefono);
		
		Cliente c(id, nombre, email, telefono);
		c.guardarArchivo();
		
		std::cout<< "guardado!!"<< std::endl;
	}
	
	if (opcion == 2){
		std::cout<< "id a buscar: ";
		std::cin>> id;
		
		Cliente encontrado = gestor.buscarCliente(id);
		
		if (encontrado.getID() != 0){
			std::cout << "cliente encontrado\n";
			std::cout<< "id: " <<encontrado.getID()<< std::endl;
			std::cout<< "nombre: " <<encontrado.getNombre()<< std::endl;
			std::cout<< "email: " <<encontrado.getEmail()<< std::endl;
			std::cout<< "telefono: " <<encontrado.getTelefono()<< std::endl;
		} else{
			std::cout<<"no se encontro :(";
		}
	}
	
	return 0;
}
