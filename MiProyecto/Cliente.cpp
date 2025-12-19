#include "Cliente.h"
#include <fstream>

using namespace std;

// constructor correcto
Cliente::Cliente(int id, string nombre, string email, string telefono) {
	m_ID = id;
	m_nombre = nombre;
	m_email = email;
	m_telefono = telefono;
	m_archivoCliente = "Clientes.dat";
}

// getters
int Cliente::getID() {
	return m_ID;
}

string Cliente::getNombre() {
	return m_nombre;
}

string Cliente::getEmail() {
	return m_email;
}

string Cliente::getTelefono() {
	return m_telefono;
}

// setters
void Cliente::setNombre(string nombre) {
	m_nombre = nombre;
}

void Cliente::setTelefono(string telefono) {
	m_telefono = telefono;
}

// guardar binario
void Cliente::guardarArchivo() {
	ofstream archivo(m_archivoCliente, ios::binary | ios::app);
	
	if (!archivo.is_open()) {
		return;
	}
	
	int largo;
	
	archivo.write((char*)&m_ID, sizeof(int));
	
	largo = m_nombre.size();
	archivo.write((char*)&largo, sizeof(int));
	archivo.write(m_nombre.c_str(), largo);
	
	largo = m_email.size();
	archivo.write((char*)&largo, sizeof(int));
	archivo.write(m_email.c_str(), largo);
	
	largo = m_telefono.size();
	archivo.write((char*)&largo, sizeof(int));
	archivo.write(m_telefono.c_str(), largo);
	
	archivo.close();
}

// cargar lista
vector<Cliente> Cliente::cargarLista() {
	vector<Cliente> lista;
	ifstream archivo("Clientes.dat", ios::binary);
	
	if (!archivo.is_open()) {
		return lista;
	}
	
	while (true) {
		int id;
		int largo;
		string nombre;
		string email;
		string telefono;
		
		if (!archivo.read((char*)&id, sizeof(int))) {
			break;
		}
		
		archivo.read((char*)&largo, sizeof(int));
		if (largo < 0 || largo > 1000) {
			break;
		}
		nombre.resize(largo);
		archivo.read(&nombre[0], largo);
		
		archivo.read((char*)&largo, sizeof(int));
		if (largo < 0 || largo > 1000) {
			break;
		}
		email.resize(largo);
		archivo.read(&email[0], largo);
		
		archivo.read((char*)&largo, sizeof(int));
		if (largo < 0 || largo > 1000) {
			break;
		}
		telefono.resize(largo);
		archivo.read(&telefono[0], largo);
		
		Cliente c(id, nombre, email, telefono);
		lista.push_back(c);
	}
	
	archivo.close();
	return lista;
}

// buscar cliente
Cliente Cliente::buscarCliente(int id) {
	vector<Cliente> lista = cargarLista();
	
	for (int i = 0; i < lista.size(); i++) {
		if (lista[i].getID() == id) {
			return lista[i];
		}
	}
	
	return Cliente();
}

// evitar ids repetidos
bool Cliente::existeID(int id) {
	vector<Cliente> lista = cargarLista();
	
	for (int i = 0; i < lista.size(); i++) {
		if (lista[i].getID() == id) {
			return true;
		}
	}
	
	return false;
}
