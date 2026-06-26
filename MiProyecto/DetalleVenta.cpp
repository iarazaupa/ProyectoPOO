#include "DetalleVenta.h"
#include <sstream>
#include <iomanip>


DetalleVenta::DetalleVenta (Producto * producto, int cantidad) {
	m_producto = producto;
	m_cantidad = cantidad;
	
}

Producto* DetalleVenta::GetProducto ( ) {
	return m_producto;
}

int DetalleVenta::GetCantidad ( ) {
	return m_cantidad;
}

double DetalleVenta::CalcularSubtotal () {
	if (m_producto == nullptr)
		return 0.0;
	return m_producto->GetPrecio() * m_cantidad;
}


string DetalleVenta::Mostrar() {
	if (m_producto == nullptr)
		return "Detalle de venta sin producto";
	
	stringstream ss;
	
	ss << fixed << setprecision(0);
	
	ss << "Producto: " << m_producto->GetNombre() << "\n";
	ss << "Cantidad: " << m_cantidad << "\n";
	ss << "Precio unitario: $" << m_producto->GetPrecio() << "\n";
	ss << "Subtotal: $" << CalcularSubtotal();
	
	return ss.str();
}


bool DetalleVenta::DisminuirCantidad(int cantidad) {
	if (cantidad <= m_cantidad) {
		m_cantidad -= cantidad;
		return true;
	}
	
	return false;
}

void DetalleVenta::SetCantidad (int cantidad) {
	m_cantidad = cantidad;
}


