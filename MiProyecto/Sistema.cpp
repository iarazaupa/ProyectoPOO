#include "Sistema.h"
#include <iostream>
#include <vector>

#include "Cliente.h"
#include "Producto.h"
#include "Venta.h"
#include "Stock.h"
#include "DetalleVenta.h"

#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

// ---------------- CONSTRUCTOR ----------------

Sistema::Sistema() {}


// ---------------- LOGIN ----------------


bool Sistema::verificarPassword(string pass) {
	
	char passwordAdmin[20];
	
	ifstream archivo("config.dat", ios::binary);
	
	// Si el archivo no existe, crear la contraseña
	if (!archivo) {
		
		cout << "No existe una contraseña de administrador." << endl;
		cout << "Cree una nueva contraseña: ";
		
		cin >> passwordAdmin;
		
		ofstream crear("config.dat", ios::binary);
		crear.write(reinterpret_cast<char*>(passwordAdmin), sizeof(passwordAdmin));
		crear.close();
		
		archivo.open("config.dat", ios::binary);
	}
	
	archivo.read(reinterpret_cast<char*>(passwordAdmin), sizeof(passwordAdmin));
	archivo.close();
	
	cout << "Ingrese password de administrador: ";
	
	return pass == passwordAdmin;
}

// ---------------- PASSWORD ADMIN ----------------

///Funcion agregar cliente
bool Sistema::agregarCliente (int id, string nombre, string email, string telefono) {
	
	if (m_gestor.existeID(id)) {
		return false;
	} else {
		
		
		Cliente c(id, nombre, email, telefono);
		c.guardarArchivo();
		
		return true;
	}
}


///funcion para buscar cliente
Cliente Sistema::BuscarCliente(int Dni){
	
	Cliente encontrado = m_gestor.buscarCliente(Dni);
	
	if (encontrado.GetID() != 0) {
		
		return encontrado;
		
	}
	else {
		Cliente noEncontrado(0, "", "", "");
		return noEncontrado;
	}
}

///Funcion vender
//Falta hacer
void Sistema::RealizarVenta(int dni) {
	Cliente cliente = BuscarCliente(dni);
	
	if (cliente.GetID()==0) {
		return;
	}
	
	int idVenta = 1;
	Venta v(idVenta, &cliente);
}


///Funcion Listar Clientes
bool Sistema::ListarClientes(vector<Cliente> &clientes) {
	
	Cliente c;
	clientes = c.cargarLista();
	
	return !clientes.empty();
}

///Ver stock
bool Sistema::ListarProductos(vector<Producto> &productos) {
	
	Producto p;
	productos = p.CargarLista();
	
	return !productos.empty();
}

///Funcion Modificar Cliente
bool Sistema::ModificarCliente(int dni, string nombre, string email, string telefono) {
	Cliente cliente = BuscarCliente(dni);
	
	if (cliente.GetID() == 0) {
		return false;
	} 
	return m_gestor.modificarCliente(dni,nombre,email,telefono);
}



// ---------------- MENU NORMAL ----------------

void Sistema::menuNormal() {
	
	int opcion;
	int id;
	string nombre;
	string email;
	string telefono;
	
	Cliente gestor;
	Producto gestorProductos(0, "", "", 0, 0);
	
	do {
		
		cout << endl;
		cout << "----- MENU -----" << endl;
		cout << "1 - Agregar cliente" << endl;
		cout << "2 - Buscar cliente" << endl;
		cout << "3 - Vender" << endl;
		cout << "4 - Listar clientes" << endl;
		cout << "5 - Ver stock" << endl;
		cout << "6 - Modificar Datos del cliente" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		
		// ---------------- AGREGAR CLIENTE ----------------
		
		
		// ---------------- BUSCAR CLIENTE ----------------
		if (opcion == 0) {
			
			cout << "DNI a buscar: ";
			
			//validacion de que es un numero
			while (!(cin >> id)) {
				cout << "Error: ingrese un DNI valido (solo numeros): ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
			
			cin.ignore();
			
			Cliente encontrado = gestor.buscarCliente(id);
			
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
		
		// ---------------- VENTA ----------------
		
		else if (opcion == 3) {
			
			int idCliente;
			cout << "DNI del cliente para la venta: ";
			
			//validar que es un numero
			while (!(cin >> idCliente)) {
				cout << "Error: ingrese un DNI valido (solo numeros): ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
			
			cin.ignore();
			
			Cliente clienteVenta = gestor.buscarCliente(idCliente);
			
			if (clienteVenta.GetID() == 0) {
				cout << "Cliente no existe" << endl;
			}
			else {
				
				vector<Producto> listaProductos = gestorProductos.CargarLista();
				
				if (listaProductos.empty()) {
					cout << "No hay productos cargados para vender." << endl;
				}
				else {
					
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
						
						// AGREGAR PRODUCTO
						if (opcionVenta == 1) {
							vector<string> categorias = gestorProductos.CargarCategorias();
							
							cout << endl;
							cout << "----- CATEGORIAS -----" << endl;
							
							for (int i = 0; i < categorias.size(); i++) {
								cout << i + 1 << " - " << categorias[i] << endl;
							}
							
							cout << "0 - Volver" << endl;
							
							int opCategoria;
							string categoriaElegida;
							
							cout << "Opcion: ";
							cin >> opCategoria;
							cin.ignore();
							
							if (opCategoria == 0) {
								continue;
							}
							
							if (opCategoria >= 1 && opCategoria <= categorias.size()) {
								
								categoriaElegida = categorias[opCategoria - 1];
								
							}
							else {
								
								cout << "Opcion invalida." << endl;
								continue;
								
							}
							
							cout << endl;
							cout << "----- LISTA DE PRODUCTOS -----" << endl;
							
							bool hay = false;
							
							for (int i = 0; i < listaProductos.size(); i++) {
								
								if (listaProductos[i].GetCategoria() == categoriaElegida) {
									
									hay = true;
									
									cout << "ID: " << listaProductos[i].GetID()
										<< " | Nombre: " << listaProductos[i].GetNombre()
										<< " | Precio: $" << listaProductos[i].GetPrecio()
										<< " | Stock: " << listaProductos[i].GetStock()
										<< endl;
								}
							}
							
							if (!hay) {
								cout << "No hay productos en esa categoria." << endl;
								continue;
							}
							
							int idProducto;
							int cantidad;
							
							cout << "ID del producto: ";
							cin >> idProducto;
							
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
								else {
									
									int cantidadEnCarrito = 0;
									vector<DetalleVenta> detallesActuales = v.GetDetalles();
									
									for (int j = 0; j < detallesActuales.size(); j++) {
										
										if (detallesActuales[j].GetProducto()->GetID() == idProducto) {
											cantidadEnCarrito = detallesActuales[j].GetCantidad();
											break;
										}
									}
									
									if ((cantidad + cantidadEnCarrito) > productoSeleccionado->GetStock()) {
										
										cout << "No hay stock suficiente" << endl;
										cout << "(Stock total: " << productoSeleccionado->GetStock() << ")" << endl;
										
									}
									else {
										
										v.AgregarProducto(productoSeleccionado, cantidad);
										cout << "Producto agregado a la venta." << endl;
									}
								}
							}
						}

						// QUITAR PRODUCTO
						else if (opcionVenta == 2) {
							
							int idProducto;
							int cantidad;
							
							cout << "ID del producto a quitar: ";
							cin >> idProducto;
							
							cout << "Cantidad: ";
							cin >> cantidad;
							
							if (v.QuitarProducto(idProducto, cantidad)) {
								cout << "Producto quitado." << endl;
							}
							else {
								cout << "No se encontro ese producto en la venta." << endl;
							}
						}
						
						// CONFIRMAR
						else if (opcionVenta == 3) {
							
							v.ConfirmarVenta();
							
							cout << endl;
							cout << "VENTA CONFIRMADA!!" << endl;
							cout << "------------------------" << endl;
							cout << v.MostrarTicket();
							cout << "------------------------" << endl;
							
							opcionVenta = 0;
						}
						
						else if (opcionVenta == 4) {
							
							v.CalcularTotal();
							
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
			}
			else {
				cout << "----- LISTA DE CLIENTES -----" << endl;
				
				for (int i = 0; i < lista.size(); i++) {
					cout << "DNI: " << lista[i].GetID()
						<< " | Nombre: " << lista[i].getNombre()
						<< " | Telefono: " << lista[i].getTelefono() << endl;
				}
			}
		}
		
		// VER STOCK
		else if (opcion == 5) {
			
			cout << "Lista de productos:" << endl;
			
			vector<Producto> p = gestorProductos.CargarLista();
			
			if (p.empty()) {
				cout << "No hay productos o no se pudieron leer." << endl;
			}
			cout << fixed << setprecision(2);
			for (int i = 0; i < p.size(); i++) {
				
				cout << p[i].GetID() << " "
					<< p[i].GetNombre() << " "
					<< p[i].GetCategoria() << " "
					<< p[i].GetPrecio() << " "
					<< p[i].GetStock() << endl;
			}
		}
		
		// ---------------- MODIFICAR CLIENTE ----------------
		
		else if (opcion == 6) {
			
			int idModificar;
			
			int nuevoID;
			string nuevoNombre;
			string nuevoEmail;
			string nuevoTelefono;
			int respuesta;
			bool huboCambios = false;
			
			cout << "DNI del cliente a modificar: ";
			cin >> idModificar;
			cin.ignore();
			
			Cliente clienteActual = gestor.buscarCliente(idModificar);
			
			if (clienteActual.GetID() == 0) {
				cout << "No existe un cliente con ese DNI" << endl;
			}
			else {
				
				cout << endl;
				cout << "Datos actuales del cliente:" << endl;
				cout << "DNI: " << clienteActual.GetID() << endl;
				cout << "Nombre: " << clienteActual.getNombre() << endl;
				cout << "Email: " << clienteActual.getEmail() << endl;
				cout << "Telefono: " << clienteActual.getTelefono() << endl;
				
				// valores actuales por defecto
				nuevoID = clienteActual.GetID();
				nuevoNombre = clienteActual.getNombre();
				nuevoEmail = clienteActual.getEmail();
				nuevoTelefono = clienteActual.getTelefono();
				
				//AGERGANDO PARA PODER MODIFICAR EL DNI Y EL NOMBRE
				
				cout << "Modificar nombre? (1 = si / 0 = no): ";
				cin >> respuesta;
				cin.ignore();
				
				if (respuesta == 1) {
					cout << "Nuevo nombre: ";
					getline(cin, nuevoNombre);
					huboCambios = true;
				}
				
				
				cout << endl;
				cout << "Modificar email? (1 = si / 0 = no): ";
				cin >> respuesta;
				cin.ignore();
				
				if (respuesta == 1) {
					cout << "Nuevo email: ";
					getline(cin, nuevoEmail);
					huboCambios = true;
				}
				
				cout << "Modificar telefono? (1 = si / 0 = no): ";
				cin >> respuesta;
				cin.ignore();
				
				if (respuesta == 1) {
					cout << "Nuevo telefono: ";
					getline(cin, nuevoTelefono);
					huboCambios = true;
				}
				
				
				//ACA CONSULTA SI HUBO CAMBIOS, SI ES QUE SI, LOS GUARDA
				if (huboCambios) {
					
					if (gestor.modificarCliente(idModificar,nuevoNombre, nuevoEmail, nuevoTelefono)) {
						cout << endl;
						cout << "Cliente modificado correctamente" << endl;
					}
					else {
						cout << "Error al modificar cliente" << endl;
					}
				}
				else {
					cout << endl;
					cout << "Perfecto, no realizaste cambios" << endl;
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


/// ---------------- MENU ADMIN ----------------

void Sistema::menuAdmin() {
	
	int opcion;
	
	Cliente gestorClientes;
	Producto gestorProductos(0, "", "", 0, 0);
	
	do {
		
		cout << endl;
		cout << "----- MENU ADMIN -----" << endl;
		cout << "1 - Agregar cliente" << endl;
		cout << "2 - Agregar producto" << endl;
		cout << "3 - Quitar producto" << endl;
		cout << "4 - Ver lista de productos" << endl;
		cout << "5 - Ver ventas" << endl;
		cout << "6 - Ver lista de clientes" << endl;
		cout << "7 - Ver productos con stock bajo" << endl;
		cout << "8 - Cantidad de ventas por mes" << endl;
		cout << "9 - Eliminar categoria" << endl;
		cout << "10 - Editar producto" << endl;
		cout << "0 - Cerrar sesion" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		
		switch (opcion) {
			
		//Agregar cliente
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
		
		case 2: {
			
			int id, stock;
			string nombre;
			string categoria;
			double precio;
			
			cout << "ID producto: ";
			cin >> id;
			cin.ignore();
			
			cout << "Nombre: ";
			getline(cin, nombre);
			
			// Cargar categorías existentes
			vector<string> categorias = gestorProductos.CargarCategorias();
			
			cout << endl;
			cout << "Categoria:" << endl;
			
			for (int i = 0; i < categorias.size(); i++) {
				cout << i + 1 << " - " << categorias[i] << endl;
			}
			
			cout << categorias.size() + 1 << " - Nueva categoria" << endl;
			
			int opCategoria;
			
			cout << "Opcion: ";
			cin >> opCategoria;
			cin.ignore();
			
			if (opCategoria >= 1 && opCategoria <= categorias.size()) {
				
				categoria = categorias[opCategoria - 1];
				
			}
			else if (opCategoria == categorias.size() + 1) {
				
				cout << "Ingrese el nombre de la nueva categoria: ";
				getline(cin, categoria);
				
			}
			else {
				
				cout << "Categoria invalida." << endl;
				break;
				
			}
			
			cout << "Precio: ";
			cout << fixed << setprecision(2);
			cin >> precio;
			
			cout << "Stock: ";
			cin >> stock;
			// Prueba
			
			Producto p(id, nombre, categoria, precio, stock);
			
			p.GuardarEnArchivo();
			
			cout << "Producto agregado correctamente." << endl;
			break;
		}
		
		//Quitar producto
		case 3: {
			
			int idProducto;
			
			cout << "ID del producto a quitar: ";
			cin >> idProducto;
			
			Stock stock;
			stock.CargarStock();
			
			if (stock.EliminarProducto(idProducto)) {
				stock.GuardarStock();
				cout << "Producto eliminado correctamente." << endl;
			}
			else {
				cout << "No se encontro ningun producto con ese ID." << endl;
			}
			
			break;
		}
		
		//Ver lista de productos
		case 4: {
			
			vector<Producto> productos = gestorProductos.CargarLista();
			
			if (productos.empty()) {
				cout << "No hay productos registrados" << endl;
			}
			else {
				
				cout << "----- LISTA DE PRODUCTOS -----" << endl;
				
				for (int i = 0; i < productos.size(); i++) {
					
					cout << "ID: " << productos[i].GetID()
						<< " | Nombre: " << productos[i].GetNombre()
						<< " | Categoria: " << productos[i].GetCategoria()
						<< " | Precio: $" << productos[i].GetPrecio()
						<< " | Stock: " << productos[i].GetStock()
						<< endl;
				}
			}
			
			break;
		}
		
		//Ver ventas
		case 5: {
			
			Venta v(0, nullptr);
			vector<Venta> ventas = v.CargarVentas();
			
			if (ventas.empty()) {
				cout << "No hay ventas registradas" << endl;
			}
			else {
				
				cout << "----- LISTA DE VENTAS -----" << endl;
				
				for (int i = 0; i < ventas.size(); i++) {
					
					cout << "ID Venta: " << ventas[i].GetID();
					
					vector<string> nombres = ventas[i].GetNombresProductos();
					vector<int> cantidades = ventas[i].GetCantidadesProductos();
					
					if (nombres.empty()) {
						cout << " | No hay productos";
					}
					else {
						for (int j = 0; j < nombres.size(); j++) {
							cout << " | Producto: " << nombres[j]
								<< " | Cantidad: " << cantidades[j];
						}
					}
					
					cout << " | Total: $" << ventas[i].Gettotal()
									  << " | Fecha: " << ventas[i].Getfecha()
									  << endl;
				}
			}
			
			break;
		}
		
		//Ver lista de clientes
		case 6: {
			
			vector<Cliente> lista = gestorClientes.cargarLista();
			
			if (lista.empty()) {
				cout << "No hay clientes cargados" << endl;
			}
			else {
				
				for (int i = 0; i < lista.size(); i++) {
					
					cout << "DNI: " << lista[i].GetID()
						<< " | Nombre: " << lista[i].getNombre()
						<< " | Telefono: " << lista[i].getTelefono() <<endl;
				}
			}
			
			break;
		}
		
		//Ver productos con stock bajo
		case 7: {
			
			Stock stock;
			
			stock.CargarStock();
			stock.VerificarStockBajo();
			
			break;
		}
		
		//Cantidad de ventas por mes
		case 8: {
			Venta v(0, nullptr);
			vector<Venta> ventas = v.CargarVentas();
			
			if (ventas.empty()) {
				cout << "No hay ventas registradas" << endl;
			} else {
				int contadorMeses[12] = {0};
				double totalDineroMeses[12] = {0.0};
				
				for (auto& venta : ventas) {
					string fechaStr = venta.Getfecha();
					
					if (fechaStr.length() >= 6) {
						string mesStr = fechaStr.substr(3,2);
						int mes = stoi(mesStr);
						if (mes >=1 && mes <= 12) {
							contadorMeses[mes-1]++;
							totalDineroMeses[mes-1] += venta.Gettotal();
						}
					}
				};
			
				const string nombreMeses[12] = {"Enero", "Febrero", "Marzo", "Abril",
					"Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre",
					"Diciembre"};
			
				cout << "--- Cantidad de Ventas por Mes ---" << endl;
				bool mostrarMensajeVacio = true;
				for(int i=0;i<12;i++) { 
					if(contadorMeses[i] > 0) {
						cout << nombreMeses[i] << ": " << contadorMeses[i] << " venta(s) | " << totalDineroMeses[i] << endl;
						mostrarMensajeVacio = false;
					}
				}
			
				if (mostrarMensajeVacio) {
					cout << "No se encontraron ventas con meses validos" << endl;
				}
			}
			break;
		}
		
		case 9: {
			vector<string> categorias = gestorProductos.CargarCategorias();
			
			if (categorias.empty()) {
				cout << "No hay categorias registradas." << endl;
				break;
			}
			
			cout << endl << "----- ELIMINAR CATEGORIA -----" << endl;
			for (int i = 0; i < categorias.size(); i++) {
				cout << i + 1 << " - " << categorias[i] << endl;
			}
			cout << "0 - Cancelar" << endl;
			
			int opCategoria;
			cout << "Opcion a eliminar: ";
			cin >> opCategoria;
			cin.ignore();
			
			if (opCategoria == 0) {
				break;
			}
			
			if (opCategoria >= 1 && opCategoria <= categorias.size()) {
				string categoriaEliminar = categorias[opCategoria - 1];
				
				cout << "Seguro que desea eliminar la categoria '" << categoriaEliminar 
					<< "'? Los productos pasaran a 'Sin categoria'. (1 = si / 0 = no): ";
				
				int confirmar;
				cin >> confirmar;
				cin.ignore();
				
				if (confirmar == 1) {
					Stock stock;
					stock.CargarStock(); // Cargamos el archivo en el vector de memoria
					
					int cantidad = stock.EliminarCategoria(categoriaEliminar); 
					
					if (cantidad > 0) {
						stock.GuardarStock(); // Sobrescribimos el archivo con los datos del vector actualizado
						cout << "Categoria eliminada. Se modificaron " << cantidad << " productos." << endl;
					} else {
						cout << "No habia productos con esa categoria." << endl;
					}
				} else {
					cout << "Eliminacion cancelada." << endl;
				}
				
			} else {
				cout << "Opcion invalida." << endl;
			}
			
			break;
		}
		
		case 10: {
			
			int id;
			cout << "Ingrese el ID del producto a editar: ";
			cin >> id;
			cin.ignore();
			
			if (!gestorProductos.ExisteProducto(id)) {
				cout << "El producto no existe." << endl;
				break;
			}
			
			int opcionEditar;
			
			cout << endl;
			cout << "¿Que desea modificar?" << endl;
			cout << "1 - Nombre" << endl;
			cout << "2 - Categoria" << endl;
			cout << "3 - Precio" << endl;
			cout << "4 - Stock" << endl;
			cout << "5 - Todo" << endl;
			cout << "Opcion: ";
			cin >> opcionEditar;
			cin.ignore();
			
			gestorProductos.EditarProducto(id, opcionEditar);
			
			cout << "Producto editado correctamente." << endl;
			
			break;
		}
		
		
		//Cerrar sesion
		case 0:
			cout << "Cerrando sesion admin..." << endl;
			break;
			
		default:
			cout << "Opcion invalida" << endl;
		}
		
		
	} while (opcion != 0);
}


// ---------------- EJECUTAR SISTEMA ----------------

