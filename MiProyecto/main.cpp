#include<iostream>
using namespace std;

#include "Producto.h"

int main (int argc, char *argv[]) {
	Producto mateDeAlgarrobo(0, "mate de algarrobo", 16.00, 4);
	
	cout<<"el mate:"<<mateDeAlgarrobo.GetNombre()<<"cuesta"<<mateDeAlgarrobo.GetPrecio()<<"y hay:"<<mateDeAlgarrobo.GetStock()<<"unidades";
	
	
	return 0;
}

