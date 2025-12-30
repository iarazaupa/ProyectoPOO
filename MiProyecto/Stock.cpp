#include "Stock.h"
#include <iostream>
#include <fstream>

#include <sstream>
using namespace std;

//constructor
Stock::Stock() {
	m_archivoStock = "stock.dat";
}

//agrego un producto al stock
void Stock::AgregarProducto(Producto p){
	productos.push_back(p);
}

// elimino un producto buscando por id
bool Stock::EliminarProducto(int ID){
	
	for(int i = 0; i < productos.size(); i++){
		
		if(productos[i].GetID() == ID){
			productos.erase(productos.begin() + i);
			return true;
		}
	}
	
	return false;
}

//busco un producto por id
Producto* Stock::BuscarProducto(int ID){
	
	for(int i = 0; i < productos.size(); i++){
		
		if (productos[i].GetID() == ID) {
			return &productos[i];
		}
	}
	
	return NULL;
}

// muestra todo el stock
string Stock::MostrarStock(){
	
	stringstream comprobante;
	
	for(int i = 0; i < productos.size(); i++){
		comprobante<< "id: " <<productos[i].GetID()<<endl;
		comprobante<< "nombre: " <<productos[i].GetNombre()<<endl;
		comprobante<< "precio: " <<productos[i].GetPrecio()<<endl;
		comprobante<< "stock: " <<productos[i].GetStock()<<endl;
		
	}
	
	return comprobante.str();
}


//verifico si hay stock suficiente
bool Stock::HayStock(int IDproducto, int cantidad){
	
	Producto* p=BuscarProducto(IDproducto);
	
	if(p == NULL){
		return false;
	}
	
	return p->HayStock(cantidad);
}

//aumento el stock de un producto
bool Stock::AumentarStock(int IDproducto, int cantidad){
	
	Producto* p = BuscarProducto(IDproducto);
	
	if(p == NULL){
		return false;
	}
	
	p->AumentarStock(cantidad);
	return true;
}

//disminuyo el stock de un producto
bool Stock::DisminuirStock(int IDproducto, int cantidad){
	
	Producto* p=BuscarProducto(IDproducto);
	
	if(p == NULL){
		return false;
	}
	
	return p->DisminuirStock(cantidad);
}

//guardo el stock en archivo
void Stock::GuardarStock(){
	
	ofstream archivo(m_archivoStock.c_str(), ios::binary);
	
	if(archivo){
		
		int cantidad = productos.size();
		archivo.write((char*)&cantidad, sizeof(int));
		
		for(int i = 0; i < productos.size(); i++){
			archivo.write((char*)&productos[i], sizeof(Producto));
		}
	}
	
	archivo.close();
}

//cargo el stock desde archivo
void Stock::CargarStock(){	
	ifstream archivo(m_archivoStock.c_str(), ios::binary);
	
	if(!archivo.is_open()){
		return;
	}
	
	int cantidad;
	archivo.read((char*)&cantidad, sizeof(int));
	
	for(int i = 0; i < cantidad; i++){
		Producto p(0, "", 0, 0);
		archivo.read((char*)&p, sizeof(Producto));
		productos.push_back(p);
	}
	
	archivo.close();
}
