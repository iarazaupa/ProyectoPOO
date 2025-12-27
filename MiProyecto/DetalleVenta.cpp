#include "DetalleVenta.h"


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


string DetalleVenta::Mostrar () {
	if (m_producto == nullptr)
		return "Detalle de venta sin producto";
	
	string resultado = "Producto: " + m_producto->GetNombre() + "\n";
	resultado += "Cantidad: " + to_string(m_cantidad) + "\n";
	resultado += "Precio unitario: $" + to_string(m_producto->GetPrecio()) + "\n";
	resultado += "Subtotal: $" + to_string(CalcularSubtotal());
	
	return resultado;
}

