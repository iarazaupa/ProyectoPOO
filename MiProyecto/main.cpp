
#include <iostream>
#include <string>
#include "Cliente.h"
#include "Producto.h"
#include "Venta.h"

using namespace std;

// constantes de tipo de usuario
const int SALIR  = 0;
const int NORMAL = 1;
const int ADMIN  = 2;

// declaraciones
int login();
bool verificarPassword();
void menuNormal();
void menuAdmin();
void sistema();


// ---------------- LOGIN ----------------
int login() {
	int opcion;
	
	cout << endl;
	cout << "----- INICIO DE SESION -----" << endl;
	cout << "1 - Usuario normal" << endl;
	cout << "2 - Administrador" << endl;
	cout << "0 - Salir" << endl;
	cout << "Opcion: ";
	cin >> opcion;
	
	if (opcion == ADMIN) {
		if (!verificarPassword()) {
			cout << "Password incorrecta" << endl;
			return -1; // login fallido
		}
	}
	
	return opcion;
}


// ---------------- MENU USUARIO NORMAL ----------------
void menuNormal() {

	int opcion;
	int id;
	string nombre;
	string email;
	string telefono;
	
	Cliente gestor;
	
	
	do {
		cout << endl;
		cout << "----- MENU -----" << endl;
		cout << "1 - Agregar cliente" << endl;
		cout << "2 - Buscar cliente" << endl;
		cout << "3 - Probar venta" << endl;
		cout << "4 - Listar clientes" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		
		// AGREGAR CLIENTE
		if (opcion == 1) {
			
			cout << "id: ";
			cin >> id;
			cin.ignore();
			
			if (gestor.existeID(id)) {
				cout << "Ese ID ya existe" << endl;
			} else {
				cout << "nombre: ";
				getline(cin, nombre);
				
				cout << "email: ";
				getline(cin, email);
				
				cout << "telefono: ";
				getline(cin, telefono);
				
				Cliente c(id, nombre, email, telefono);
				c.guardarArchivo();
				
				cout << "Cliente guardado!!" << endl;
			}
		}
		
		// BUSCAR CLIENTE
		else if (opcion == 2) {
			
			cout << "id a buscar: ";
			cin >> id;
			
			Cliente encontrado = gestor.buscarCliente(id);
			
			if (encontrado.GetID() != 0) {
				cout << "Cliente encontrado" << endl;
				cout << "id: " << encontrado.GetID() << endl;
				cout << "nombre: " << encontrado.getNombre() << endl;
				cout << "email: " << encontrado.getEmail() << endl;
				cout << "telefono: " << encontrado.getTelefono() << endl;
			} else {
				cout << "No se encontro :(" << endl;
			}
		}
		
		// PROBAR VENTA
		else if (opcion == 3) {
			
			cout << "id del cliente para la venta: ";
			cin >> id;
			
			Cliente clienteVenta = gestor.buscarCliente(id);
			
			if (clienteVenta.GetID() == 0) {
				cout << "Cliente no existe" << endl;
			} else {
				Producto producto(100, "producto prueba", 15000, 10);
				
				Venta v(1, &clienteVenta);
				v.AgregarProducto(&producto, 2);
				v.ConfirmarVenta();
				
				cout << v.MostrarTicket();
			}
		}
		
		// LISTAR CLIENTES
		else if (opcion == 4) {
			
			vector<Cliente> lista = gestor.cargarLista();
			
			if (lista.empty()) {
				cout << "No hay clientes cargados" << endl;
			} else {
				cout << "----- LISTA DE CLIENTES -----" << endl;
				for (int i = 0; i < lista.size(); i++) {
					cout << "ID: " << lista[i].GetID()
						<< " | Nombre: " << lista[i].getNombre()
						<< endl;
				}
			}
		}
		
		else if (opcion == 0) {
			cout << "Saliendo del programa..." << endl;
		}
		
		else {
			cout << "Opcion invalida" << endl;
		}
		
	} while (opcion != 0);
	
}


// ---------------- MENU ADMIN ----------------
void menuAdmin() {
	int opcion;
	
	Cliente gestorClientes;
	Producto gestorProductos(0, "", 0, 0); // objeto auxiliar
	Venta* ventaAux = nullptr;             // solo estructura
	
	do {
		cout << endl;
		cout << "----- MENU ADMIN -----" << endl;
		cout << "1 - Agregar cliente" << endl;
		cout << "2 - Agregar producto" << endl;
		cout << "3 - Quitar producto" << endl;
		cout << "4 - ver lista de productos" << endl; 
		cout << "5 - Ver ventas" << endl;
		cout << "0 - Cerrar sesion" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		
		switch (opcion) {
			
			// ---------------- AGREGAR CLIENTE ----------------
		case 1: {
			int id;
			string nombre, email, telefono;
			
			cout << "ID cliente: ";
			cin >> id;
			cin.ignore();
			
			if (gestorClientes.existeID(id)) {
				cout << "El ID ya existe" << endl;
				break;
			}
			
			cout << "Nombre: ";
			getline(cin, nombre);
			
			cout << "Email: ";
			getline(cin, email);
			
			cout << "Telefono: ";
			getline(cin, telefono);
			
			Cliente c(id, nombre, email, telefono);
			c.guardarArchivo();
			
			cout << "Cliente agregado correctamente" << endl;
			break;
		}
		
		// ---------------- AGREGAR PRODUCTO ----------------
		case 2: {
			int id, stock;
			string nombre;
			double precio;
			
			cout << "ID producto: ";
			cin >> id;
			cin.ignore();
			
			cout << "Nombre: ";
			getline(cin, nombre);
			
			cout << "Precio: ";
			cin >> precio;
			
			cout << "Stock: ";
			cin >> stock;
			
			Producto p(id, nombre, precio, stock);
			p.GuardarEnArchivo();
			
			cout << "Producto agregado correctamente" << endl;
			break;
		}
		
		// ---------------- QUITAR PRODUCTO ----------------
		case 3: {
			int idProducto;
			
			cout << "ID del producto a quitar: ";
			cin >> idProducto;
			
			// estructura: después se implementa bien
			cout << "Producto eliminado (estructura)" << endl;
			break;
		}
		
		case 4: {
			
			cout<<"lista de productos:"<<endl;
			
			vector<Producto> p = gestorProductos.CargarLista();
			
			if (p.empty()) {
				cout << "No hay productos o no se pudieron leer." << endl;
			}
			
			for(size_t i=0;i<p.size();i++) { 
				cout<<p[i].GetID() << " "<< p[i].GetNombre() << " "<< p[i].GetPrecio()<< " "<< p[i].GetStock() << endl;
			}
			
			break;
		}
		
		// ---------------- VER VENTAS ----------------
		case 5: {
			Venta v(0, nullptr);
			vector<Venta> ventas = v.CargarVentas();
			
			if (ventas.empty()) {
				cout << "No hay ventas registradas" << endl;
			} else {
				cout << "----- LISTA DE VENTAS -----" << endl;
				for (int i = 0; i < ventas.size(); i++) {
					cout << "ID Venta: " << ventas[i].GetID()<< " | Total: $" << ventas[i].Gettotal()<< " | Fecha: " << ventas[i].Getfecha()<< endl;
				}
			}
			break;
		}
		
		case 0:
			cout << "Cerrando sesion admin..." << endl;
			break;
			
		default:
			cout << "Opcion invalida" << endl;
		}
		
	} while (opcion != 0);
}



// ---------------- PASSWORD ADMIN ----------------
bool verificarPassword() {
	string pass;
	const string PASSWORD_ADMIN = "admin123";
	
	cout << "Ingrese password de administrador: ";
	cin >> pass;
	
	return pass == PASSWORD_ADMIN;
}


// ---------------- SISTEMA PRINCIPAL ----------------
void sistema() {
	int tipoUsuario;
	
	do {
		tipoUsuario = login();
		
		if (tipoUsuario == NORMAL) {
			menuNormal();
		}
		else if (tipoUsuario == ADMIN) {
			menuAdmin();
		}
		else if (tipoUsuario == SALIR) {
			cout << "Saliendo del sistema..." << endl;
		}
		else {
			cout << "Intento de login fallido" << endl;
		}
		
	} while (tipoUsuario != SALIR);
}


// ---------------- MAIN ----------------
int main() {
	sistema();
	return 0;
}

