
#include <iostream>
#include <string>
#include "Cliente.h"
#include "Producto.h"
#include "Venta.h"
#include "Stock.h"

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
		cout << "3 - vender" << endl;
		cout << "4 - Listar clientes" << endl;
		cout << "5 - Ver stock" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		
		// AGREGAR CLIENTE
		if (opcion == 1) {
			
			cout << "DNI: ";
			cin >> id;
			cin.ignore();
			
			if (gestor.existeID(id)) {
				cout << "Ese DNI ya existe" << endl;
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
			
			cout << "DNI a buscar: ";
			cin >> id;
			
			Cliente encontrado = gestor.buscarCliente(id);
			
			if (encontrado.GetID() != 0) {
				cout << "Cliente encontrado" << endl;
				cout << "DNI: " << encontrado.GetID() << endl;
				cout << "nombre: " << encontrado.getNombre() << endl;
				cout << "email: " << encontrado.getEmail() << endl;
				cout << "telefono: " << encontrado.getTelefono() << endl;
			} else {
				cout << "No se encontro :(" << endl;
			}
		}
		
		// PROBAR VENTA
		else if (opcion == 3) {
			
			int idCliente;
			cout << "DNI del cliente para la venta: ";
			cin >> idCliente;
			
			Cliente clienteVenta = gestor.buscarCliente(idCliente);
			
			if (clienteVenta.GetID() == 0) {
				cout << "Cliente no existe" << endl;
			} 
			else {
				
				Producto gestorProductos(0, "", 0, 0);
				vector<Producto> listaProductos = gestorProductos.CargarLista();
				
				if (listaProductos.empty()) {
					cout << "No hay productos cargados para vender." << endl;
				} 
				else {
					
					// ID de venta simple (por ahora)
					int idVenta = 1;
					
					Venta v(idVenta, &clienteVenta);
					
					int opcionVenta;
					do {
						cout << endl;
						cout << "----- MENU VENTA -----" << endl;
						cout << "1 - Agregar producto" << endl;
						cout << "2 - Quitar producto" << endl;
						cout << "3 - Confirmar venta" << endl;
						cout << "4 - Ver ticket actual" << endl;
						cout << "0 - Cancelar" << endl;
						cout << "Opcion: ";
						cin >> opcionVenta;
						
						// ---------------- AGREGAR PRODUCTO ----------------
						if (opcionVenta == 1) {
							
							cout << endl;
							cout << "----- LISTA DE PRODUCTOS -----" << endl;
							
							for (int i = 0; i < listaProductos.size(); i++) {
								cout << "ID: " << listaProductos[i].GetID()
									<< " | Nombre: " << listaProductos[i].GetNombre()
									<< " | Precio: $" << listaProductos[i].GetPrecio()
									<< " | Stock: " << listaProductos[i].GetStock()
									<< endl;
							}
							
							int idProducto;
							int cantidad;
							
							cout << endl;
							cout << "ID del producto: ";
							cin >> idProducto;
							
							// buscar producto en la lista
							Producto* productoSeleccionado = NULL;
							
							for (int i = 0; i < listaProductos.size(); i++) {
								if (listaProductos[i].GetID() == idProducto) {
									productoSeleccionado = &listaProductos[i];
									break;
								}
							}
							
							if (productoSeleccionado == NULL) {
								cout << "Producto no encontrado." << endl;
							} 
							else {
								cout << "Cantidad: ";
								cin >> cantidad;
								
								if (cantidad <= 0) {
									cout << "Cantidad invalida." << endl;
								}
								else if (cantidad > productoSeleccionado->GetStock()) {
									cout << "No hay stock suficiente." << endl;
								}
								else {
									v.AgregarProducto(productoSeleccionado, cantidad);
									cout << "Producto agregado a la venta." << endl;
								}
							}
						}
						
						// ---------------- QUITAR PRODUCTO ----------------
						else if (opcionVenta == 2) {
							int idProducto;
							
					
							
							int cantidad;
							
							cout << "ID del producto a quitar: ";
							cin >> idProducto;
							
							
							///ingresa la cantidad del producto que desea quitar 
							cout<<"cantidad: "<<endl;
							cin>>cantidad;
							
							
							if (v.QuitarProducto(idProducto, cantidad)) {
								cout << "Producto quitado." << endl;
							} else {
								cout << "No se encontro ese producto en la venta." << endl;
							}
						}
						
						// ---------------- CONFIRMAR VENTA ----------------
						else if (opcionVenta == 3) {
							
							v.ConfirmarVenta();
							
							cout << endl;
							cout << "VENTA CONFIRMADA!!" << endl;
							cout << "------------------------" << endl;
							cout << v.MostrarTicket();
							cout << "------------------------" << endl;
							
							opcionVenta = 0; // salir del menu venta
						}
						// ---------------- VER TICKET ACTUAL ----------------
						else if (opcionVenta == 4) {
							
							v.CalcularTotal(); // para que el total se vea actualizado
							
							cout << endl;
							cout << "----- TICKET ACTUAL -----" << endl;
							cout << v.MostrarTicket();
							cout << "-------------------------" << endl;
						}
						
						else if (opcionVenta == 0) {
							cout << "Venta cancelada." << endl;
						}
						else {
							cout << "Opcion invalida." << endl;
						}
						
					} while (opcionVenta != 0);
				}
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
					cout << "DNI: " << lista[i].GetID()
						<< " | Nombre: " << lista[i].getNombre()
						<< endl;
				}
			}
		}
		//  Ver Stock
		else if (opcion == 5) {
			
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
			
			cout << "DNI cliente: ";
			cin >> id;
			cin.ignore();
			
			if (gestorClientes.existeID(id)) {
				cout << "El DNI ya existe" << endl;
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
			
			Stock stock;
			stock.CargarStock();
			
			if (stock.EliminarProducto(idProducto)) {
				stock.GuardarStock();
				cout << "Producto eliminado correctamente." << endl;
			} else {
				cout << "No se encontro ningun producto con ese ID." << endl;
			}
			
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

