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
	char m_cateoria;
	string m_archivoProducto;

public:
	Producto(int ID, string nombre, double precio, int stock);
	//getters
	int GetId();
	string GetNombre();
	double GetPrecio();
	int GetStock();
	
	//setters
	void SetNombre(string nombre);
	void SetPrecio(double precio);
	
	//logica de negocios
	void AumentarStock(int cantidad);
	bool DisminuirStock(int cantidad);
	bool HayStock(int cantidad);
	
	//Archivo
	void GuardarEnArchivo();
	void GuardarDesdeArchivo();
	void GuardarLista(vector<Producto>& productos);
	vector <Producto> CargarLista();
	void Mostrar();
	
	
	
	
};

#endif

