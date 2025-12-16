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
	//constructor
	Cliente(int id = 0, std::string nombre = "", std::string email = "", std::string telefono = "");
	
	//getters
	int getID();
	std::string getNombre();
	std::string getEmail();
	std::string getTelefono();
	
	//setters
	void setNombre( std::string nombre);
	void setTelefono( std::string telefono);
	
	//persistencia
	void guardarArchivo();
	std::vector<Cliente> cargarLista();
	Cliente* buscarCliente(int id); 
	
	//utilidad
	void mostrar() ;
};

#endif 
