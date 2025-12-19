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
	
	int getID();
	string getNombre();
	string getEmail();
	string getTelefono();
	
	void setNombre(string nombre);
	void setTelefono(string telefono);
	
	void guardarArchivo();
	vector<Cliente> cargarLista();
	Cliente buscarCliente(int id);
	
	bool existeID(int id);
};

#endif
