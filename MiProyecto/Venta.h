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
	
public:
	//constructor
	Venta(int ID, Cliente* cliente);
	
	//logica principal
	bool AgregarProducto(Producto* producto, int cantidad);
	bool QuitarProducto(int IDProducto);
	void CalcularTotal();
	void ConfirmarVenta();
	
	//getters
	double Gettotal();
	int GetID();
	string Getfecha();
	
	//persistencia
	void GuardarEnArchivos();
	vector<Venta> CargarVentas();
	
	//utilidad
	string MostrarTicket();
};

#endif
