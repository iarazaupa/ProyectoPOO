#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <string>
#include <vector>
using namespace std;

class Producto {

private:
	
	int m_ID;
	string m_nombre;
	double m_precio;
	int m_stock;
	string m_archivoProducto;
	string m_categoria;

public:
	Producto(int ID=0, string nombre="", string categoria="", double precio=0, int stock=0);

	int GetID();
	string GetNombre();
	double GetPrecio();
	int GetStock();
	

	void SetNombre(string nombre);
	void SetPrecio(double precio);
	void SetCategoria(string categoria);
	void setStock(int stockNuevo);
	
	//logica de negocios
	void AumentarStock(int cantidad);
	bool DisminuirStock(int cantidad);
	bool HayStock(int cantidad);
	
	string NombreArchivo();
	string GetCategoria();
	
	vector<string> CargarCategorias();
	
	//Archivo
	void GuardarEnArchivo();
	void GuardarDesdeArchivo();
	void GuardarLista(vector<Producto>& productos);
	vector <Producto> CargarLista();
	Producto Mostrar();
	
	void EditarProducto(int id, int opcion);
	bool ExisteProducto(int id);
	
	
};

#endif




