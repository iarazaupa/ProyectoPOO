#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>

class Sistema {
	
private:
	
	// constantes
	static const int SALIR  = 0;
	static const int NORMAL = 1;
	static const int ADMIN  = 2;
	
	// metodos internos
	int login();
	bool verificarPassword();
	
	void menuNormal();
	void menuAdmin();
	
public:
	Sistema();
	void Ejecutar();   // antes era sistema()
	
};

#endif
