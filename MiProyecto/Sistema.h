#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "Cliente.h"
using namespace std;

class Sistema {
	
private:
	
	// constantes
	static const int SALIR  = 0;
	static const int NORMAL = 1;
	static const int ADMIN  = 2;
	
	// metodos internos
	//int login();
	///PROPIEDADES DEL LOGIN///
	int m_usuario;
	string m_password;
	Cliente m_gestor;
	
public:
	Sistema();
	
	bool verificarPassword(string pass);
	///Haciendo los metodos del menu normal///
	bool agregarCliente(int id, string nombre, string email, string telefono);
	Cliente BuscarCliente(int Dni);
	
	void menuNormal();
	
	void menuAdmin();
};

#endif



