#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "Cliente.h"
#include "Producto.h"
#include "Venta.h"
#include "Stock.h"

using namespace std;

class Sistema {
	
private:
	
	// constantes
	static const int SALIR  = 0;
	static const int NORMAL = 1;
	static const int ADMIN  = 2;
	

	vector<Producto> m_listaProductos;
	// metodos internos
	//int login();
	///PROPIEDADES DEL LOGIN///
	int m_usuario;
	string m_password;
	Cliente m_gestor;
	Producto m_gestorProducto;
	Venta m_venta;
	Stock m_stock;
	
public:
	Sistema();
	
	bool verificarPassword(string pass);
	
	///Haciendo los metodos del menu normal///
	bool agregarCliente(int id, string nombre, string email, string telefono);
	Cliente BuscarCliente(int Dni);
	bool ListarClientes(vector<Cliente> &clientes);
	bool ListarProductos(vector<Producto> &productos);
	
	
	// Obtener categorías disponibles
	vector<string> ObtenerCategorias();
	// Validar la opción elegida y devolver la categoría correspondiente
	bool ObtenerCategoriaSeleccionada(const vector<string>& categorias, int opcion, string& categoria);
	// Obtener productos de una categoría
	vector<Producto*> ObtenerProductosPorCategoria(string categoria);
	// Buscar producto por ID
	Producto* BuscarProducto(int idProducto);
	// Verificar si el producto encontrado pertenece a la categoría elegida
	bool ProductoPerteneceCategoria(Producto* producto,string categoria);
	// Verificar si la cantidad ingresada es válida
	bool CantidadValida(int cantidad);
	// Obtener cantidad de ese producto que ya está dentro de la venta
	int ObtenerCantidadProductoEnVenta(Venta& venta,int idProducto);
	// Verificar que haya stock suficiente
	bool HayStockDisponible(Venta& venta,Producto* producto,int cantidad);
	// Agregar producto a la venta
	bool AgregarProductoAVenta(Venta& venta,Producto* producto,int cantidad);
	// Quitar producto de la venta
	bool QuitarProductoDeVenta(Venta& venta,int idProducto,int cantidad);
	// Confirmar la venta
	bool ConfirmarVenta(Venta& venta);
	// Obtener ticket
	string ObtenerTicket(Venta& venta);
	// Obtener total
	double ObtenerTotalVenta(Venta& venta);
	
	void ActualizarProductos();
	
	bool ModificarCliente(int dni, string nombre, string email, string telefono);
	/*void RealizarVenta(int dni);*/
	
	bool verificarDniVenta(int dni);
	
	///Metodos del Menu ADMIN
	
	//Agregar Producto
	bool AgregarProductoAdmin(int id, int stock, string nombre, string categoria, double precio);
	
	//Quitar Producto
	bool QuitarProductoAdmin(int idProducto);
	
	//Ver Ventas
	vector<Venta> VerVentas();
	///cant de ventas por mes
	
	
	//Ver Stock Bajo
	vector<Producto> StockBajo();
	
	
	///Menus anteriores
	void menuNormal();
	
	void menuAdmin();
};

#endif


