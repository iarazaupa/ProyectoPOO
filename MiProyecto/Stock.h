#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include <string>
#include "Producto.h"

using namespace std;

class Stock {
	
private:
	vector<Producto> productos;    
	string m_archivoStock;          
	
public:
	//constructor
	Stock();
	
	//crud
	void AgregarProducto(Producto p);
	bool EliminarProducto(int ID);
	Producto* BuscarProducto(int ID);
	
	//consulta
	string MostrarStock();
	bool HayStock(int IDproducto, int cantidad);
	
	//movimientos de stock
	bool AumentarStock(int IDproducto, int cantidad);
	bool DisminuirStock(int IDproducto, int cantidad);
	
	//persistencia
	void GuardarStock();
	void CargarStock();
};

#endif
