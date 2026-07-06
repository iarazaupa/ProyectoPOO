#include "Stock.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// constructor
Stock::Stock() {
	// antes era stock.dat (binario)
	// ahora lo hacemos compatible con tu sistema real:
	m_archivoStock = "productos.txt";
}

// agrego un producto al stock
void Stock::AgregarProducto(Producto p) {
	productos.push_back(p);
}

// elimino un producto buscando por id
bool Stock::EliminarProducto(int ID) {
	
	for (int i = 0; i < productos.size(); i++) {
		
		if (productos[i].GetID() == ID) {
			productos.erase(productos.begin() + i);
			return true;
		}
	}
	
	return false;
}

// busco un producto por id
Producto* Stock::BuscarProducto(int ID) {
	
	for (int i = 0; i < productos.size(); i++) {
		
		if (productos[i].GetID() == ID) {
			return &productos[i];
		}
	}
	
	return NULL;
}

// muestra todo el stock
string Stock::MostrarStock() {
	
	stringstream comprobante;
	
	for (int i = 0; i < productos.size(); i++) {
		comprobante << "id: " << productos[i].GetID() << endl;
		comprobante << "nombre: " << productos[i].GetNombre() << endl;
		comprobante << "categoria: " << productos[i].GetCategoria() << endl;
		comprobante << "precio: " << productos[i].GetPrecio() << endl;
		comprobante << "stock: " << productos[i].GetStock() << endl;
		comprobante << endl;
	}
	
	return comprobante.str();
}

// verifico si hay stock suficiente
bool Stock::HayStock(int IDproducto, int cantidad) {
	
	Producto* p = BuscarProducto(IDproducto);
	
	if (p == NULL) {
		return false;
	}
	
	return p->HayStock(cantidad);
}

// aumento el stock de un producto
bool Stock::AumentarStock(int IDproducto, int cantidad) {
	
	Producto* p = BuscarProducto(IDproducto);
	
	if (p == NULL) {
		return false;
	}
	
	p->AumentarStock(cantidad);
	return true;
}

// disminuyo el stock de un producto
bool Stock::DisminuirStock(int IDproducto, int cantidad) {
	
	Producto* p = BuscarProducto(IDproducto);
	
	if (p == NULL) {
		return false;
	}
	
	return p->DisminuirStock(cantidad);
}

// guardo el stock en archivo (formato: id;nombre;precio;stock)
void Stock::GuardarStock() {
	
	ofstream archivo(m_archivoStock.c_str());
	
	if (!archivo.is_open()) {
		return;
	}
	
	for (int i = 0; i < productos.size(); i++) {
		
		archivo << productos[i].GetID() << ";"
			<< productos[i].GetNombre() << ";"
			<< productos[i].GetCategoria() << ";"
			<< productos[i].GetPrecio() << ";"
			<< productos[i].GetStock() << endl;
	}
	
	archivo.close();
}

// cargo el stock desde archivo (formato: id;nombre;precio;stock)
void Stock::CargarStock() {
	
	productos.clear();
	
	ifstream archivo(m_archivoStock.c_str());
	
	if (!archivo.is_open()) {
		return;
	}
	
	string linea;
	
	while (getline(archivo, linea)) {
		
		if (linea.empty()) continue;
		
		size_t p1 = linea.find(';');
		size_t p2 = linea.find(';', p1 + 1);
		size_t p3 = linea.find(';', p2 + 1);
		size_t p4 = linea.find(';', p3 + 1);
		
		if (p1 == string::npos || p2 == string::npos ||
			p3 == string::npos || p4 == string::npos) {
			continue;
		}
		
		int id = stoi(linea.substr(0, p1));
		string nombre = linea.substr(p1 + 1, p2 - p1 - 1);
		string categoria = linea.substr(p2 + 1, p3 - p2 - 1);
		double precio = stod(linea.substr(p3 + 1, p4 - p3 - 1));
		int stock = stoi(linea.substr(p4 + 1));
		
		productos.push_back(Producto(id, nombre, categoria, precio, stock));
	}
	
	archivo.close();
}

// verifica qué productos tienen stock bajo y los muestra por pantalla
void Stock::VerificarStockBajo() {
	
	const int STOCK_MINIMO = 1;
	bool hay = false;
	
	cout << "----- PRODUCTOS CON STOCK BAJO -----" << endl;
	
	for (int i = 0; i < productos.size(); i++) {
		
		if (productos[i].GetStock() <= STOCK_MINIMO) {
			
			hay = true;
			
			cout << "ID: " << productos[i].GetID()
				<< " | Nombre: " << productos[i].GetNombre()
				<< " | Categoria: " << productos[i].GetCategoria()
				<< " | Stock: " << productos[i].GetStock()
				<< endl;
		}
	}
	
	if (!hay) {
		cout << "No hay productos con stock bajo." << endl;
	}
}


int Stock::EliminarCategoria(string categoriaVieja) {
	int modificados = 0;
	
	// Iteramos sobre el vector de productos
	for (int i = 0; i < productos.size(); i++) {
		if (productos[i].GetCategoria() == categoriaVieja) {
			productos[i].SetCategoria("Sin categoria");
			modificados++;
		}
	}
	
	return modificados;
}
