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
	if (cantidad <= m_stock) {
		m_stock -= cantidad;
		return true;
	}
	return false;
}


bool Producto::HayStock (int cantidad) {
	return cantidad <= m_stock;
}


void Producto::GuardarEnArchivo () {
	ofstream archivo("productos.txt", ios::app);
	if (archivo.is_open()) {
		archivo << m_ID << " "
			<< m_nombre << " "
			<< m_precio << " "
			<< m_stock << endl;
		archivo.close();
	}
}

void Producto::GuardarDesdeArchivo () {
	ifstream archivo("productos.txt");
	if (archivo.is_open()) {
		archivo >> m_ID >> m_nombre >> m_precio >> m_stock;
		archivo.close();
	}
}

void Producto::GuardarLista (vector<Producto> & productos) {
	ofstream archivo("productos.txt");
	if (archivo.is_open()) {
		for (auto &p : productos) {
			archivo << p.m_ID << " "
				<< p.m_nombre << " "
				<< p.m_precio << " "
				<< p.m_stock << endl;
		}
		archivo.close();
	}
}

vector<Producto> Producto::CargarLista () {
	vector<Producto> productos;
	ifstream archivo("productos.txt");
	
	if (archivo.is_open()) {
		int id, stock;
		string nombre;
		double precio;
		
		while (archivo >> id >> nombre >> precio >> stock) {
			productos.push_back(Producto(id, nombre, precio, stock));
		}
		archivo.close();
	}
	return productos;
}

Producto Producto::Mostrar ( ) {
	return *this;
}



