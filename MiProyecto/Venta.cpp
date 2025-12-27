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
}


//agrego producto

bool Venta::AgregarProducto(Producto* producto, int cantidad) {
	
	if (producto == NULL || cantidad <= 0) {
		return false;
	}
	
	DetalleVenta d(producto, cantidad);
	m_detalles.push_back(d);
	
	return true;
}
// quita un producto de la venta buscando por id
bool Venta::QuitarProducto(int IDProducto) {
	
	for (int i = 0; i < m_detalles.size(); i++) {
		
		// compara el id del producto del detalle con el id recibido
		if (m_detalles[i].GetProducto()->GetID() == IDProducto) {
			
			// elimina el detalle de la venta
			m_detalles.erase(m_detalles.begin() + i);
			return true;
		}
	}
	
	return false;
}


//calculo total

void Venta::CalcularTotal() {
	
	m_total = 0;
	
	for(int i = 0; i < m_detalles.size(); i++) {
		m_total += m_detalles[i].GetSubtotal();
	}
}


//confirmo venta

void Venta::ConfirmarVenta() {
	
	CalcularTotal();
	GuardarEnArchivos();
}


// getters

double Venta::Gettotal(){
	return m_total;
}

int Venta::GetID(){
	return m_ID;
}

string Venta::Getfecha(){
	return m_fecha;
}


//guardo en el archivo

void Venta::GuardarEnArchivos() {
	
	ofstream archivo(m_archivoVentas.c_str(), ios::app | ios::binary);
	
	if(archivo){
		archivo.write((char*)&m_ID, sizeof(int));
		
		int idCliente = m_cliente->getID();
		archivo.write((char*)&idCliente, sizeof(int));
		
		archivo.write((char*)&m_total, sizeof(double));
	}
	
	archivo.close();
}


//mostrar ticket

string Venta::MostrarTicket(){
	
	stringstream comprobante;
	
	comprobante<< "venta id: " << m_ID<<endl;
	comprobante<< "cliente: " << m_cliente->getNombre()<<endl;
	comprobante<< "----------------------\n";
	
	for(int i = 0; i < m_detalles.size(); i++){
		comprobante<<m_detalles[i].GetDescripcion()<<endl;
	}
	
	comprobante<<"total: $"<<m_total<<endl;
	
	return comprobante.str();
}
