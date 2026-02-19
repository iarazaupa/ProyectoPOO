#include "Venta.h"
#include <fstream>
#include <sstream>
#include "Stock.h"
#include <ctime>


#include <iostream>
using namespace std;

// constructor
Venta::Venta(int ID, Cliente* cliente) {
	m_ID = ID;
	m_cliente = cliente;
	m_total = 0;
}

// obtengo la fecha actual del sistema
string Venta::ObtenerFechaActual() {
	
	time_t ahora = time(0);
	tm* tiempo = localtime(&ahora);
	
	stringstream ss;
	
	ss << tiempo->tm_mday << "/"
		<< tiempo->tm_mon + 1 << "/"
		<< tiempo->tm_year + 1900;
	
	return ss.str();
}


// agrego un producto a la venta
bool Venta::AgregarProducto(Producto* producto, int cantidad) {
	
	if (producto == NULL || cantidad <= 0) {
		return false;
	}
	
	int idNuevo = producto->GetID();
	
	// Si ya existe ese producto en la venta, sumamos cantidad
	for (int i = 0; i < detalles.size(); i++) {
		
		if (detalles[i].GetProducto()->GetID() == idNuevo) {
			
			int cantidadActual = detalles[i].GetCantidad();
			detalles[i].SetCantidad(cantidadActual + cantidad);
			
			return true;
		}
	}
	
	// Si no existe, lo agregamos como nuevo detalle
	DetalleVenta d(producto, cantidad);
	detalles.push_back(d);
	
	return true;
}


// quito un producto de la venta buscando por id
bool Venta::QuitarProducto(int IDProducto,int cantidad) {
	
	for (int i = 0; i < detalles.size(); i++) {
		
		// si el id del producto coincide, lo borra
		if (detalles[i].GetProducto()->GetID() == IDProducto) {
			
			if(detalles[i].DisminuirCantidad(cantidad)){
				if(detalles[i].GetCantidad() == 0){
					
					detalles.erase(detalles.begin() + i);
					return true;
					
				}
				
				return true;
			}
			
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
void Venta::ConfirmarVenta() {
	
	// 1) calcular total
	CalcularTotal();
	
	// 2) guardar fecha actual
	m_fecha = ObtenerFechaActual();
	
	// 3) guardar venta y detalles
	GuardarEnArchivos();
	
	// 4) DESCONTAR STOCK REAL (productos.txt)
	Stock stock;
	stock.CargarStock();
	
	for (int i = 0; i < detalles.size(); i++) {
		
		int idProducto = detalles[i].GetProducto()->GetID();
		int cantidad = detalles[i].GetCantidad();
		
		bool ok = stock.DisminuirStock(idProducto, cantidad);
		
		if (!ok) {
			cout<< "ERROR: no se pudo descontar stock del producto ID "<< idProducto << endl;
		}
	}
	
	stock.GuardarStock();
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
		
		// guardo total
		archivoVentas.write((char*)&m_total, sizeof(double));
		
		// ---------- NUEVO: guardar fecha ----------
		int largoFecha = m_fecha.size();
		archivoVentas.write((char*)&largoFecha, sizeof(int));
		archivoVentas.write(m_fecha.c_str(), largoFecha);
		
		archivoVentas.close();
	}
	
	
	// guardo los detalles de la venta
	ofstream archivoDetalles("detallesVenta.dat", ios::binary | ios::app);
	
	if (archivoDetalles.is_open()) {
		
		for (int i = 0; i < detalles.size(); i++) {
			
			int idVenta = m_ID;
			int idProducto = detalles[i].GetProducto()->GetID();
			int cantidad = detalles[i].GetCantidad();
			double precio = detalles[i].GetProducto()->GetPrecio();
			
			archivoDetalles.write((char*)&idVenta, sizeof(int));
			archivoDetalles.write((char*)&idProducto, sizeof(int));
			archivoDetalles.write((char*)&cantidad, sizeof(int));
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
		
		// ---------- NUEVO: leer fecha ----------
		int largoFecha;
		archivo.read((char*)&largoFecha, sizeof(int));
		
		char* buffer = new char[largoFecha + 1];
		archivo.read(buffer, largoFecha);
		buffer[largoFecha] = '\0';
		
		string fecha(buffer);
		delete[] buffer;
		// ----------------------------------------
		
		Venta v(idVenta, NULL);
		v.m_total = total;
		v.m_fecha = fecha;
		
		ventas.push_back(v);
	}
	
	archivo.close();
	return ventas;
}


// fecha
string Venta::Getfecha() {
	return m_fecha;
}
