#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>

class Cliente {
private:
	int m_ID;
	std::string m_nombre;
	std::string m_email;
	std::string m_telefono;
	std::string m_archivoCliente;
	
public:
	Cliente(int id = 0, std::string nombre = "", std::string email = "", std::string telefono = "");
	
	int getID();
	std::string getNombre();
	std::string getEmail();
	std::string getTelefono();
	
	void setNombre(std::string nombre);
	void setTelefono(std::string telefono);
	
	void guardarArchivo();
	std::vector<Cliente> cargarLista();
	Cliente* buscarCliente(int id);
	
	// mostrar 
	std::string mostrar(); 
};

#endif
