#include "Sistema.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	
	Sistema sistema;
	
	
	int opcion;
	
	do{
		cout << endl;
		cout << "----- INICIO DE SESION -----" << endl;
		cout << "1 - Usuario normal" << endl;
		cout << "2 - Administrador" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
	

	
		if(opcion == 1){

			sistema.menuNormal();
		
		
		
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
