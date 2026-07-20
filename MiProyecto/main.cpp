#include "Sistema.h"
#include <iostream>
#include <string>
#include "Cliente.h"
#include "Producto.h"
using namespace std;

int main() {
	
	Sistema sistema;
	
	int opcion;
	
	do{
		
		int Dni;
		string nombre;
		string email;
		string telefono;
		
		//No se pa q sirve
//		Cliente gestor;
//		Producto gestorProductos(0, "", "", 0, 0);
		
		cout << endl;
		cout << "----- INICIO DE SESION -----" << endl;
		cout << "1 - Usuario normal" << endl;
		cout << "2 - Administrador" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
	
		if(opcion == 1){
			int opcionMenu;
			
			do {
/*			sistema.menuNormal();*/
				cout << endl;
				cout << "----- MENU -----" << endl;
				cout << "1 - Agregar cliente" << endl;
				cout << "2 - Buscar cliente" << endl;
				cout << "3 No completado - Vender" << endl;
				cout << "4 - Listar clientes" << endl;
				cout << "5 - Ver stock" << endl;
				cout << "6 - Modificar Datos del cliente" << endl;
				cout << "0 - Salir" << endl;
				cout << "Opcion: ";
				cin>>opcionMenu;
			
				switch (opcionMenu) {
				case 1: {
					///Agregar Cliente
					bool clienteAgg = false;
					
					while (!clienteAgg) {
						cout << "DNI: ";
						
						// Validación de que es un número
						while (!(cin >> Dni)) {
							cout << "Error: ingrese un DNI valido (solo numeros): ";
							cin.clear();
							cin.ignore(10000, '\n');
						}
						
						cin.ignore(); // limpiar el salto de línea
						
						cout << "Nombre: ";
						getline(cin, nombre);
						
						cout << "Email: ";
						getline(cin, email);
						
						cout << "Telefono: ";
						getline(cin, telefono);
						
						clienteAgg = sistema.agregarCliente(Dni, nombre, email, telefono);
						
						if (!clienteAgg) {
							cout << "Error: ya existe un cliente con ese DNI. Intente nuevamente.\n\n";
						}
					}
					cout << "Usuario agregado correctamente.\n";
				}
				break;
				case 2: {
					///Buscar Cliente 
					cout << "DNI a buscar: ";
					
					//validacion de que es un numero
					while (!(cin >> Dni)) {
						cout << "Error: ingrese un DNI valido (solo numeros): ";
						cin.clear();
						cin.ignore(10000, '\n');
					}
					
					cin.ignore();
					
					Cliente encontrado = sistema.BuscarCliente(Dni);
					
					if (encontrado.GetID() != 0) {
						
						cout << "Cliente encontrado" << endl;
						cout << "DNI: " << encontrado.GetID() << endl;
						cout << "Nombre: " << encontrado.getNombre() << endl;
						cout << "Email: " << encontrado.getEmail() << endl;
						cout << "Telefono: " << encontrado.getTelefono() << endl;
					}
					else {
						cout << "No se encontro :(" << endl;
					}
				}
				break;
				
				///realizar venta
				case 3:
				{
					int dni;
					
					cout << "DNI del cliente: ";
					cin >> dni;
					
					
					// Buscar cliente
					Cliente cliente = sistema.BuscarCliente(dni);
					
					
					if(cliente.GetID() == 0)
					{
						cout << "Cliente inexistente." << endl;
						break;
					}
					
					
					// Crear venta
					int idVenta = 1;
					
					Venta venta(idVenta, &cliente);
					
					
					
					int opcionVenta;
					do
					{
						
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
						
						if(opcionVenta == 1)
						{
							
							vector<string> categorias = sistema.ObtenerCategorias();
							cout << endl;
							cout << "----- CATEGORIAS -----" << endl;
							
							for(int i = 0; i < categorias.size(); i++)
							{
								cout << i+1 << " - "
									<< categorias[i]
									<< endl;
							}
							int opCategoria;
							
							cout << "Seleccione categoria: ";
							cin >> opCategoria;
							
							string categoria;
							
							if(!sistema.ObtenerCategoriaSeleccionada(categorias,opCategoria,categoria))
							{
								cout << "Categoria invalida." << endl;
								break;
							}
							vector<Producto*> productos = sistema.ObtenerProductosPorCategoria(categoria);
							cout << endl;
							cout << "----- PRODUCTOS -----" << endl;
							
							for(int i=0;i<productos.size();i++)
							{
								
								cout << "ID: "
									<< productos[i]->GetID()
									<< " | "
									<< productos[i]->GetNombre()
									<< " | Precio: $"
									<< productos[i]->GetPrecio()
									<< " | Stock: "
									<< productos[i]->GetStock()
									<< endl;
								
							}
							
							int idProducto;
							
							cout << "ID producto: ";
							cin >> idProducto;
							
							Producto* producto = sistema.BuscarProducto(idProducto);
							
							if(producto == NULL)
							{
								cout << "Producto no encontrado." << endl;
								break;
							}
							
							int cantidad;
							
							cout << "Cantidad: ";
							cin >> cantidad;
							if(sistema.AgregarProductoAVenta(venta,producto, cantidad))
							{
								cout << "Producto agregado correctamente."
									<< endl;
							}
							else
							{
								cout << "No se pudo agregar el producto."
									<< endl;
							}
							
						}
							
						// ---------------- QUITAR PRODUCTO ----------------
						
						
						else if(opcionVenta == 2)
						{
							
							int idProducto;
							int cantidad;
							
							
							cout << "ID producto a quitar: ";
							cin >> idProducto;
							
							
							cout << "Cantidad: ";
							cin >> cantidad;
							
							if(sistema.QuitarProductoDeVenta(venta,idProducto,cantidad))
							{
								cout << "Producto quitado." << endl;
							}else
							{
								cout << "No se encontro el producto."
									<< endl;
							}
							
						}
						
						// ---------------- CONFIRMAR ----------------
						
						
						else if(opcionVenta == 3)
						{
							
							
							if(sistema.ConfirmarVenta(venta))
							{
								
								cout << endl;
								cout << "VENTA CONFIRMADA" << endl;
								cout << "------------------" << endl;
								
								
								cout << sistema.ObtenerTicket(venta);
								
								
								cout << "------------------" << endl;
								
							}
							
							
							opcionVenta = 0;
							
						}
						
						// ---------------- TICKET ACTUAL ----------------
						
						
						else if(opcionVenta == 4)
						{
							
							cout << endl;
							cout << "----- TICKET -----"
								<< endl;
							
							
							cout << sistema.ObtenerTicket(venta);
							
							
							cout << endl;
							
						}
						
						
						
						
						else if(opcionVenta == 0)
						{
							cout << "Venta cancelada." << endl;
						}
						
						
						else
						{
							cout << "Opcion invalida." << endl;
						}
						
						
						
					}while(opcionVenta != 0);
					
					
					break;
				}
				case 4: {
					///Listar Clientes
					vector<Cliente> clientes;
					if (sistema.ListarClientes(clientes)) {
						for (int i = 0; i < clientes.size(); i++) {
							cout << "DNI: " << clientes[i].GetID()
								<< " | Nombre: " << clientes[i].getNombre()
								<< " | Telefono: " << clientes[i].getTelefono() << endl;
						}
					} else {
						cout << "No hay clientes registrados" << endl;
					}
				}
				break;
				case 5: {
					///Ver Stock
					vector<Producto> productos;
					if (sistema.ListarProductos(productos)) {
						
						for (int i = 0; i < productos.size(); i++) {
							cout << productos[i].GetID() << " "
								<< productos[i].GetNombre() << " "
								<< productos[i].GetCategoria() << " "
								<< productos[i].GetPrecio() << " "
								<< productos[i].GetStock() << endl;
						}
					} else {
						cout << "No hay productos" << endl;
					}
				}
				break;
				case 6: {
					///Modificar Cliente
					int idModificar;
					string nuevoNombre;
					string nuevoEmail;
					string nuevoTelefono;
					int respuesta;
					
					cout << "DNI del cliente a modificar: ";
					cin >> idModificar;
					cin.ignore();
					
					Cliente clienteActual = sistema.BuscarCliente(idModificar);
					
					if (clienteActual.GetID() == 0) {
						cout << "No existe un cliente con ese DNI" << endl;
					}
					else {
						// Mostrar datos
						cout << "DNI: " << clienteActual.GetID() << endl;
						cout << "Nombre: " << clienteActual.getNombre() << endl;
						cout << "Email: " << clienteActual.getEmail() << endl;
						cout << "Telefono: " << clienteActual.getTelefono() << endl;
						cout << endl;
						
						nuevoNombre = clienteActual.getNombre();
						nuevoEmail = clienteActual.getEmail();
						nuevoTelefono = clienteActual.getTelefono();
						
						bool huboCambios = false;
						
						cout << "Modificar nombre? (1=si / 0=no): ";
						cin >> respuesta;
						cin.ignore();
						
						if (respuesta == 1) {
							cout << "Nuevo nombre: ";
							getline(cin, nuevoNombre);
							huboCambios = true;
						}
						
						cout << "Modificar email? (1=si / 0=no): ";
						cin >> respuesta;
						cin.ignore();
						
						if (respuesta == 1) {
							cout << "Nuevo email: ";
							getline(cin, nuevoEmail);
							huboCambios = true;
						}
						
						cout << "Modificar telefono? (1=si / 0=no): ";
						cin >> respuesta;
						cin.ignore();
						
						if (respuesta == 1) {
							cout << "Nuevo telefono: ";
							getline(cin, nuevoTelefono);
							huboCambios = true;
						}
						
						if (huboCambios) {
							
							if (sistema.ModificarCliente(idModificar,
														 nuevoNombre,
														 nuevoEmail,
														 nuevoTelefono))
								cout << "Cliente modificado correctamente";
							else
								cout << "Error al modificar";
						}
					}
				}
				break;
				default:
				break;
				}
			} while (opcionMenu != 0);
		} else if (opcion == 2) {
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
