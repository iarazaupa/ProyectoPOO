#include "Producto.h"
#include <fstream>
#include <sstream>
using namespace std;


Producto::Producto (int ID, string nombre, string categoria, double precio, int stock) {
	m_ID = ID;
	m_nombre = nombre;
	m_categoria = categoria;
	m_precio = precio;
	m_stock = stock;
	
}

int Producto::GetID( ) {
	return m_ID;
}

string Producto::GetNombre ( ) {
	return m_nombre;
}
string Producto::GetCategoria() {
	return m_categoria;
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
	if(cantidad <= m_stock){
		m_stock -= cantidad;
		return true;
	}
	return false;
}


bool Producto::HayStock(int cantidad) {
	return cantidad <= m_stock;
}


void Producto::GuardarEnArchivo() {
	ofstream archivo("productos.txt", ios::app);
	if (archivo.is_open()) {
		archivo << m_ID << ";"
			<< m_nombre << ";"
			<< m_categoria << ";"
			<< m_precio << ";"
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
	//nada todavia no se va a usar
	ofstream archivo("productos.txt");
	if (archivo.is_open()) {
		for (auto &p : productos) {
			archivo << p.m_ID << ";"
				<< p.m_nombre << ";"
				<< p.m_categoria << ";"
				<< p.m_precio << ";"
				<< p.m_stock << endl;
		}
		archivo.close();
	}
}

vector<Producto> Producto::CargarLista() {
	vector<Producto> productos;
	ifstream archivo("productos.txt");
	
	if (archivo.is_open()) {
		string linea;
		
		while (getline(archivo, linea)) {
			int id, stock;
			double precio;
			string nombre;
			string categoria;
			
			size_t p1 = linea.find(';');
			size_t p2 = linea.find(';', p1 + 1);
			size_t p3 = linea.find(';', p2 + 1);
			size_t p4 = linea.find(';', p3 + 1);
			
			if (p1 == string::npos || p2 == string::npos ||
				p3 == string::npos || p4 == string::npos)
				continue;
			
			id = stoi(linea.substr(0, p1));
			nombre = linea.substr(p1 + 1, p2 - p1 - 1);
			
			categoria = linea.substr(p2 + 1, p3 - p2 - 1);
			precio = stod(linea.substr(p3 + 1, p4 - p3 - 1));
			stock = stoi(linea.substr(p4 + 1));
			
			productos.push_back(Producto(id, nombre, categoria, precio, stock));
		}
		
		archivo.close();
	}
	
	return productos;
}




Producto Producto::Mostrar ( ) {
	return *this;
}


vector<string> Producto::CargarCategorias() {
	
	vector<string> categorias;
	
	ifstream archivo("productos.txt");
	
	string linea;
	
	while (getline(archivo, linea)) {
		
		stringstream ss(linea);
		
		string id, nombre, categoria, precio, stock;
		
		getline(ss, id, ';');
		getline(ss, nombre, ';');
		getline(ss, categoria, ';');
		getline(ss, precio, ';');
		getline(ss, stock, ';');
		
		bool existe = false;
		
		for (int i = 0; i < categorias.size(); i++) {
			if (categorias[i] == categoria) {
				existe = true;
				break;
			}
		}
		
		if (!existe) {
			categorias.push_back(categoria);
		}
	}
	
	archivo.close();
	
	return categorias;
}


string Producto::NombreArchivo ( ) {
	return m_archivoProducto;
}


