#include "Cliente.h"
#include <fstream>
#include <iostream> 
#include <string>

//constructor
Cliente::Cliente(int id, std::string nombre, std::string email, std::string telefono) {
	m_ID = id;
	m_nombre = nombre;
	m_email = email;
	m_telefono = telefono;
	m_archivoCliente = "Clientes.txt";
}

//getters
int Cliente::getID() {
	return m_ID;
}

std::string Cliente::getNombre() {
	return m_nombre;
}

std::string Cliente::getEmail() {
	return m_email;
}

std::string Cliente::getTelefono() {
	return m_telefono;
}

//setters
void Cliente::setNombre( std::string nombre) {
	m_nombre = nombre;
}

void Cliente::setTelefono( std::string telefono) {
	m_telefono = telefono;
}

//guardar cliente en el archivo
void Cliente::guardarArchivo() {
	std::ofstream archivo;
	archivo.open(m_archivoCliente, std::ios::app);
	
	if (!archivo.is_open()) {
		throw std::runtime_error("no se pudo abrir el archivo");
	}
	
	archivo << std::to_string(m_ID) << ";";
	archivo << m_nombre << ";";
	archivo << m_email << ";";
	archivo << m_telefono << ";";  
	
	archivo.close();
}

//cargar todos los clientes desde el archivo
std::vector<Cliente> Cliente::cargarLista() {
	std::vector<Cliente> lista;
	std::ifstream archivo;
	archivo.open(m_archivoCliente);
	
	if (!archivo.is_open()) {
		throw std::runtime_error("no se pudo abrir el archivo");
	}
	
	std::string linea;
	while (std::getline(archivo, linea)) {
		std::string idStr, nombre, email, telefono;
		int pos;
		
		//id
		pos = linea.find(';');
		idStr = linea.substr(0, pos);
		linea.erase(0, pos + 1);
		
		//nombre
		pos = linea.find(';');
		nombre = linea.substr(0, pos);
		linea.erase(0, pos + 1);
		
		//email
		pos = linea.find(';');
		email = linea.substr(0, pos);
		linea.erase(0, pos + 1);
		
		//teléfono 
		pos = linea.find(';');
		telefono = linea.substr(0, pos);
		
		
		int id = std::stoi(idStr);
		
		Cliente c(id, nombre, email, telefono);
		lista.push_back(c);
	}
	
	archivo.close();
	return lista;
}

//mostrar cliente
void Cliente::mostrar() {
	std::cout << "ID: " << m_ID << std::endl;
	std::cout << "Nombre: " << m_nombre << std::endl;
	std::cout << "Email: " << m_email << std::endl;
	std::cout << "Telefono: " << m_telefono << std::endl;
}

//buscar cliente por ID
Cliente* Cliente::buscarCliente(int id) {
	std::vector<Cliente> lista = cargarLista();
	
	for (int i = 0; i < lista.size(); i++) {
		if (lista[i].getID() == id) {
			return new Cliente(lista[i].getID(), lista[i].getNombre(), lista[i].getEmail(), lista[i].getTelefono());
		}
	}
	return nullptr;
}
