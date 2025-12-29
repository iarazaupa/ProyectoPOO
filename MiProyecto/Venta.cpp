#include "Venta.h"
#include <fstream>
#include <sstream>

using namespace std;

//constructor
Venta::Venta(int ID, Cliente* cliente) {
	m_ID = ID;
	m_cliente = cliente;
	m_total = 0;
	m_archivoVentas = "ventas.dat";
	m_fecha = "";
}

//agrego un producto a la venta
bool Venta::AgregarProducto(Producto* producto, int cantidad){
	if(producto == NULL || cantidad <= 0){
		return false;
	}
	
	DetalleVenta d(producto, cantidad);
	detalles.push_back(d);
	
	return true;
}

// quita un producto de la venta buscando por id

bool Venta::QuitarProducto(int IDProducto) {
	
	for (int i = 0; i < detalles.size(); i++) {
		
		// compara el id del producto del detalle con el id recibido
		if(detalles[i].GetProducto()->	GetID()){
			detalles.erase(detalles.begin() + i);
			return true;
		}
	}
	
	return false;
}

//calculo el total de la venta
void Venta::CalcularTotal() {
	
	m_total = 0;
	
	for(int i = 0; i < detalles.size(); i++){
		
		m_total += detalles[i].CalcularSubtotal();
	}
}

//confirmo la venta
void Venta::ConfirmarVenta() {
	
	CalcularTotal();
	GuardarEnArchivos();
}

//total
double Venta::Gettotal() {
	return m_total;
}

//id
int Venta::GetID() {
	return m_ID;
}

//fecha
string Venta::Getfecha() {
	return m_fecha;
}

//guardo la venta en el archivo
void Venta::GuardarEnArchivos(){
	
	ofstream archivo(m_archivoVentas.c_str(), ios::binary | ios::app);
	
	if(archivo){
		archivo.write((char*)&m_ID, sizeof(int));
		
		int idCliente = m_cliente->getID();
		archivo.write((char*)&idCliente, sizeof(int));
		
		archivo.write((char*)&m_total, sizeof(double));
	}
	
	archivo.close();
}

//cargo ventas desde el archivo
vector<Venta> Venta::CargarVentas(){
	vector<Venta> ventas;
	ifstream archivo(m_archivoVentas.c_str(), ios::binary);
	if(archivo){
		
		while(!archivo.is_open()){
			
			int idVenta;
			int idCliente;
			double total;
			
			archivo.read((char*)&idVenta, sizeof(int));
			archivo.read((char*)&idCliente, sizeof(int));
			archivo.read((char*)&total, sizeof(double));
			
			if(archivo.is_open()){
				break;
			}
			
			Venta v(idVenta, NULL);
			v.m_total = total;
			
			ventas.push_back(v);
		}
	}
	
	archivo.close();
	return ventas;
}

//muestro el ticket de la venta
string Venta::MostrarTicket(){
	
	stringstream comprobante;
	
	comprobante<<"venta id: "<< m_ID<<endl;
	comprobante<<"cliente: "<< m_cliente->getNombre()<<endl;
	comprobante<<"total: $"<< m_total<<endl;
	
	return comprobante.str();
}
