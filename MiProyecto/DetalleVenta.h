#ifndef DETALLEVENTA_H
#define DETALLEVENTA_H

class DetalleVenta {
private:
	Producto* m_producto;
	int m_cantidad;
	
public:
	DetalleVenta(Producto* producto, int cantidad);
	Producto* GetProducto();
	int GetCantidad();
	double CalcularSubtotal();
	string Mostrar();
	

};

#endif


