#include "Venta.h"
#include <fstream>
#include <sstream>

using namespace std;

// constructor
Venta::Venta(int ID, Cliente* cliente) {
	m_ID = ID;
	m_cliente = cliente;
	m_total = 0;
}

// agrego un producto a la venta
bool Venta::AgregarProducto(Producto* producto, int cantidad) {
	if (producto == NULL || cantidad <= 0) {
		return false;
	}
	
	DetalleVenta d(producto, cantidad);
	detalles.push_back(d);
	
	return true;
}

// quito un producto de la venta buscando por id
bool Venta::QuitarProducto(int IDProducto) {
	
	for (int i = 0; i < detalles.size(); i++) {
		
		// si el id del producto coincide, lo borra
		if (detalles[i].GetProducto()->GetID() == IDProducto) {
			detalles.erase(detalles.begin() + i);
			return true;
		}
	}
	
	return false;
}

// calculo el total de la venta
void Venta::CalcularTotal() {
	m_total = 0;
	
	for (int i = 0; i < detalles.size(); i++) {
		m_total = m_total + detalles[i].CalcularSubtotal();
	}
}

// confirmo la venta
void Venta::ConfirmarVenta() {
	CalcularTotal();
	GuardarEnArchivos();
}

// devuelvo el total
double Venta::Gettotal() {
	return m_total;
}

// devuelvo el id de la venta
int Venta::GetID() {
	return m_ID;
}

// guardo la venta y sus detalles en archivos
void Venta::GuardarEnArchivos() {
	
	// guardo la cabecera de la venta
	ofstream archivoVentas("ventas.dat", ios::binary | ios::app);
	
	if (archivoVentas.is_open()) {
		
		int idCliente = 0;
		
		if (m_cliente != NULL) {
			idCliente = m_cliente->GetID();
		}
		
		archivoVentas.write((char*)&m_ID, sizeof(int));
		archivoVentas.write((char*)&idCliente, sizeof(int));
		
		// ? ARREGLO IMPORTANTE: guardar total como double
		archivoVentas.write((char*)&m_total, sizeof(double));
		
		archivoVentas.close();
	}
	
	// guardo los detalles de la venta
	ofstream archivoDetalles("detallesVenta.dat", ios::binary | ios::app);
	
	if (archivoDetalles.is_open()) {
		
		for (int i = 0; i < detalles.size(); i++) {
			
			int idVenta = m_ID;
			int idProducto = detalles[i].GetProducto()->GetID();
			int cantidad = detalles[i].GetCantidad();
			
			// guardamos precio como double también para que no haya problemas
			double precio = detalles[i].GetProducto()->GetPrecio();
			
			archivoDetalles.write((char*)&idVenta, sizeof(int));
			archivoDetalles.write((char*)&idProducto, sizeof(int));
			archivoDetalles.write((char*)&cantidad, sizeof(int));
			
			// ? también guardamos el precio como double
			archivoDetalles.write((char*)&precio, sizeof(double));
		}
		
		archivoDetalles.close();
	}
}

// muestro el ticket de la venta
string Venta::MostrarTicket() {
	stringstream ticket;
	
	ticket << "venta id: " << m_ID << endl;
	
	if (m_cliente != NULL) {
		ticket << "cliente: " << m_cliente->getNombre() << endl;
	}
	else {
		ticket << "cliente: sin datos" << endl;
	}
	
	for (int i = 0; i < detalles.size(); i++) {
		ticket << detalles[i].Mostrar() << endl;
	}
	
	ticket << "total: $" << m_total << endl;
	
	return ticket.str();
}

// cargo ventas desde el archivo (solo cabecera: idVenta, idCliente, total)
vector<Venta> Venta::CargarVentas() {
	
	vector<Venta> ventas;
	
	// si tu clase tiene m_archivoVentas, perfecto.
	// si no, podés poner "ventas.dat" directo.
	ifstream archivo("ventas.dat", ios::binary);
	
	
	if (!archivo.is_open()) {
		return ventas;
	}
	
	while (true) {
		
		int idVenta;
		int idCliente;
		double total;
		
		archivo.read((char*)&idVenta, sizeof(int));
		if (archivo.eof()) break;
		
		archivo.read((char*)&idCliente, sizeof(int));
		archivo.read((char*)&total, sizeof(double));
		
		Venta v(idVenta, NULL);
		v.m_total = total;
		
		ventas.push_back(v);
	}
	
	archivo.close();
	return ventas;
}

// fecha
string Venta::Getfecha() {
	return m_fecha;
}
