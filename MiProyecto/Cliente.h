#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>

using namespace std;

class Cliente {
private:
	int m_ID;
	string m_nombre;
	string m_email;
	string m_telefono;
	string m_archivoCliente;
	
public:
	Cliente(int id = 0, string nombre = "", string email = "", string telefono = "");
	
	int GetID();
	string getNombre();
	string getEmail();
	string getTelefono();
	
	void setID(int id);
	void setNombre(string nombre);
	void setTelefono(string telefono);
	void setEmail(string email);
	
	
	void guardarArchivo();
	vector<Cliente> cargarLista();
	Cliente buscarCliente(int id);
	
	bool existeID(int id);
	bool modificarCliente(int idActual, string nuevoNombre, string nuevoEmail, string nuevoTelefono);
};

#endif
