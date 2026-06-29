#ifndef VENTA_H
#define VENTA_H

#include <string>
#include <vector>
#include "Cliente.h"
#include "Producto.h"
#include "DetalleVenta.h"

using namespace std;

class Venta {
	
private:
	int m_ID;                           
	Cliente* m_cliente;                 
	vector<DetalleVenta> detalles;   
	double m_total;                     
	string m_fecha;                     
	string m_archivoVentas;
	vector<string> m_nombresProductos;
	vector<int> m_cantidadesProductos;
	
public:
	//constructor
	Venta(int ID, Cliente* cliente);
	
	//logica principal
	bool AgregarProducto(Producto* producto, int cantidad);
	bool QuitarProducto(int IDProducto,int cantidad);
	void CalcularTotal();
	void ConfirmarVenta();
	
	double Gettotal();
	int GetID();
	vector<DetalleVenta> GetDetalles();
	string Getfecha();
	string ObtenerFechaActual();
	
	vector<string> GetNombresProductos();
	vector<int> GetCantidadesProductos();
	void GuardarEnArchivos();
	vector<Venta> CargarVentas();
	

	string MostrarTicket();
};

#endif
