#include "Producto.h"


Producto::Producto (int ID, string nombre, double precio, int stock) {
	m_ID = ID;
	m_nombre = nombre;
	m_precio = precio;
	m_stock = stock;
	
}

int Producto::GetId ( ) {
	return m_ID;
}

string Producto::GetNombre ( ) {
	return m_nombre;
}

double Producto::GetPrecio ( ) {
	return m_precio;
}

int Producto::GetStock ( ) {
	return m_stock;
}

void Producto::SetNombre (string nombre) {
	m_nombre = nombre;
}

void Producto::SetPrecio (double precio) {
	m_precio = precio;
}

void Producto::AumentarStock (int cantidad) {
	m_stock +=cantidad;
}

bool Producto::DisminuirStock (int cantidad) {
	m_stock -=cantidad;
}

bool Producto::HayStock (int cantidad) {
	if(cantidad <= m_stock){
		return true;
	}else{
		return false;
	}
}

void Producto::GuardarEnArchivo ( ) {
	//nada todavia no se va a usar
}

void Producto::GuardarDesdeArchivo ( ) {
	//nada todavia no se va a usar
}

void Producto::GuardarLista (vector<Producto> & productos) {
	//nada todavia no se va a usar
}

vector<Producto> Producto::CargarLista ( ) {
	//nada todavia no se va a usar
}

void Producto::Mostrar ( ) {
	//nada todavia no se va a usar
}



