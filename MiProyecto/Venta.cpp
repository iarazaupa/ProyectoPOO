#include "Venta.h"
#include <fstream>

#include <sstream>
using namespace std;

// onstructor
Venta::Venta(int ID, Cliente* cliente){
	m_ID = ID;
	m_cliente = cliente;
	m_total = 0;
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

//quito un producto de la venta buscando por id
bool Venta::QuitarProducto(int IDProducto){
	
	for(int i = 0; i < detalles.size(); i++){
		
		// si el id del producto coincide, lo borra
		if(detalles[i].GetProducto()->GetID() == IDProducto){
			detalles.erase(detalles.begin() + i);
			return true;
		}
	}
	
	return false;
}

//calculo el total de la venta
void Venta::CalcularTotal(){
	m_total = 0;
	
	for(int i = 0; i < detalles.size(); i++){
		m_total = m_total + detalles[i].CalcularSubtotal();
	}
}

//confirmo la venta
void Venta::ConfirmarVenta(){
	
	CalcularTotal();
	GuardarEnArchivos();
}

//devuelvo el total
double Venta::Gettotal(){
	return m_total;
}

//devuelvo el id de la venta
int Venta::GetID(){
	return m_ID;
}

//guardo la venta y sus detalles en archivos
void Venta::GuardarEnArchivos(){
	
	//guardo la cabecera de la venta
	ofstream archivoVentas("ventas.dat", ios::binary | ios::app);
	
	if(archivoVentas.is_open()){
		
		int idCliente = m_cliente->GetID();
		
		archivoVentas.write((char*)&m_ID, sizeof(int));
		archivoVentas.write((char*)&idCliente, sizeof(int));
		archivoVentas.write((char*)&m_total, sizeof(float));
		
		archivoVentas.close();
	}
	
	// guardo los detalles de la venta
	ofstream archivoDetalles("detallesVenta.dat", ios::binary | ios::app);
	
	if(archivoDetalles.is_open()){
		
		for(int i = 0; i < detalles.size(); i++){
			
			int idVenta = m_ID;
			int idProducto = detalles[i].GetProducto()->GetID();
			int cantidad = detalles[i].GetCantidad();
			float precio = detalles[i].GetProducto()->GetPrecio();
			
			archivoDetalles.write((char*)&idVenta, sizeof(int));
			archivoDetalles.write((char*)&idProducto, sizeof(int));
			archivoDetalles.write((char*)&cantidad, sizeof(int));
			archivoDetalles.write((char*)&precio, sizeof(float));
		}
		
		archivoDetalles.close();
	}
}
//muestro el ticket de la venta
string Venta::MostrarTicket(){
	stringstream ticket;
	
	ticket<<"venta id: "<<m_ID<<endl;
	
	if(m_cliente != NULL){
		ticket<< "cliente: "<<m_cliente->getNombre()<<endl;
	}else{
		ticket<<"cliente: sin datos"<<endl;
	}
	for(int i = 0; i < detalles.size(); i++){
		ticket<<detalles[i].Mostrar()<<endl;
	}
	ticket<< "total: $"<<m_total<<endl;
	
	return ticket.str();
}

//cargo ventas desde el archivo
vector<Venta> Venta::CargarVentas(){
	vector<Venta> ventas;
	ifstream archivo(m_archivoVentas.c_str(), ios::binary);
	if(archivo){
		// guardo los detalles de la venta
	ofstream archivoDetalles("detallesVenta.dat", ios::binary | ios::app);
		
	if(archivoDetalles.is_open()){
			
		while(!archivo.is_open()){
				
			int idVenta;
			int idCliente;
			double total;
				
			archivo.read((char*)&idVenta, sizeof(int));
			archivo.read((char*)&idCliente, sizeof(int));
			archivo.read((char*)&total, sizeof(double));
			for(int i = 0; i < detalles.size(); i++){
					
				if(archivo.is_open()){
					break;
				}
				int idVenta = m_ID;
				int idProducto = detalles[i].GetProducto()->GetID();
				int cantidad = detalles[i].GetCantidad();
				float precio = detalles[i].GetProducto()->GetPrecio();
					
				Venta v(idVenta, NULL);
				v.m_total = total;
					
				ventas.push_back(v);
				archivoDetalles.write((char*)&idVenta, sizeof(int));
				archivoDetalles.write((char*)&idProducto, sizeof(int));
				archivoDetalles.write((char*)&cantidad, sizeof(int));
				archivoDetalles.write((char*)&precio, sizeof(float));
			}
				
			archivoDetalles.close();
		}
			
		archivo.close();
		return ventas;
	}
}
}

//fecha
string Venta::Getfecha() {
	return m_fecha;
}
