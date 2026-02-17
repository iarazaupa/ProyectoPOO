#ifndef DETALLEVENTA_H
#define DETALLEVENTA_H
#include "Producto.h"

class DetalleVenta {
private:
	Producto* m_producto;
	int m_cantidad;
	
public:
	DetalleVenta(Producto* producto, int cantidad);
	Producto* GetProducto();
	int GetCantidad();
	bool DisminuirCantidad(int cantidad);
	double CalcularSubtotal();
	string Mostrar();
	

};

#endif





