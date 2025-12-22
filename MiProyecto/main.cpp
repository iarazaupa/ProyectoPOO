#include <iostream>
#include "Cliente.h"
#include "Venta.h"
#include "Producto.h"

using namespace std;

int main() {
	
	int opcion;
	int id;
	string nombre;
	string email;
	string telefono;
	
	Cliente gestor;
	
	cout<< "1 - agregar cliente"<<endl;
	cout<< "2 - buscar cliente"<<endl;
	cout<< "3 - probar venta"<<endl;
	cout<< "opcion: ";
	cin>>opcion;
	

//agrego cliente

	if(opcion == 1){
		
		cout<<"id: ";
		cin>>id;
		cin.ignore();
		
		if(gestor.existeID(id)){
			cout<<"ese id ya existe"<<endl;
			return 0;
		}
		
		cout<<"nombre: ";
		getline(cin, nombre);
		
		cout<<"email: ";
		getline(cin, email);
		
		cout<<"telefono: ";
		getline(cin, telefono);
		
		Cliente c(id, nombre, email, telefono);
		c.guardarArchivo();
		
		cout<<"guardado!!"<<endl;
	}
	
//busco cliente

	if(opcion == 2){
		
		cout<<"id a buscar: ";
		cin>>id;
		
		Cliente encontrado = gestor.buscarCliente(id);
		
		if(encontrado.getID() != 0){
			cout<<"cliente encontrado"<<endl;
			cout<<"id: " <<encontrado.getID()<<endl;
			cout<<"nombre: " <<encontrado.getNombre()<<endl;
			cout<<"email: " <<encontrado.getEmail()<<endl;
			cout<<"telefono: " <<encontrado.getTelefono()<<endl;
		} else{
			cout<<"no se encontro :("<<endl;
		}
	}
	

//pruebo venta
	if(opcion == 3){
		
		cout<<"id del cliente para la venta: ";
		cin>>id;
		
		Cliente clienteVenta = gestor.buscarCliente(id);
		
		if(clienteVenta.getID() == 0){
			cout<<"cliente no existe"<<endl;
			return 0;
		}
		
		//producto de prueba
		Producto producto(100, "producto prueba", 15000);
		
		Venta v(1, &clienteVenta);
		v.AgregarProducto(&producto, 2);
		v.ConfirmarVenta();
		
		cout<<v.MostrarTicket();
	}
	
	return 0;
}
