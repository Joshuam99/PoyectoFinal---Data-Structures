#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <fstream>
#include <sstream> 
using namespace std;

struct Cuenta
{
	string nombre, apellido;
	int pin, cedula;
	float saldo;
	bool creada = false;
};

struct Transaccion
{
	Cuenta cuenta;
	tm fecha;
	tm hora;
	float monto;
	string detalle;
	long referencia;
};

struct Nodo
{
	Transaccion transaccion;
	Nodo* siguiente;
};

// funciones
long long int numeroReferencia();
void menu();
void insertar(Nodo*&, Transaccion);
void mostrarTransacciones(Nodo*);
void buscarTransaccion(Nodo*);
void EliminarTransaccion(Nodo*);
void menuRetiro(Cuenta&);
void menuDeposito(Cuenta&);
void menuTransferencia(Cuenta&);
void crearComprobante(Transaccion);
//globales
Nodo* lista;
Cuenta cuenta;

int main()
{
	menu();
	return 0;
}

void menu()
{


	//a3000 r 1000


	int opcion;
	cout << "*** Cajero Automatico ***" << endl;
	cout << endl;
	do
	{
		cout << "1. Crear Cuenta" << endl;
		cout << "2. Retirar Dinero" << endl;
		cout << "3. Depositar Dinero" << endl;
		cout << "4. Transferir Dinero" << endl;
		cout << "5. Transacciones" << endl;
		cout << "6. Buscar por detalle" << endl;
		cout << "7. Eliminar transaccion" << endl;
		cout << "8. Salir" << endl;

		cin >> opcion;
		system("cls");
		switch (opcion)
		{

		case 1:
			cin.ignore();
			cout << "1. Nombre" << endl;
			getline(cin, cuenta.nombre);
			cout << "2. Apellido" << endl;
			getline(cin, cuenta.apellido);
			cout << "3. Cedula" << endl;
			cin >> cuenta.cedula;
			cout << "4. PIN" << endl;
			cin >> cuenta.pin;
			cout << "5. Saldo Inicial" << endl;
			cin >> cuenta.saldo;
			cout << endl;
			cout << cuenta.nombre << " su cuenta fue creada exitosamente" << endl;
			cuenta.creada = true;
			system("pause");
			system("cls");

			break;

		case 2:

			menuRetiro(cuenta);

			break;

		case 3:

			menuDeposito(cuenta);
			break;

		case 4:
			menuTransferencia(cuenta);
			break;

		case 5:
			mostrarTransacciones(lista);
			break;

		case 6:
			buscarTransaccion(lista);
			break;
		case 7:
			EliminarTransaccion(lista);
			break;

		case 8:
			cout << "Salio del sistema" << endl;
			break;

		default:
			cout << "Opcion incorrecta" << endl;
			break;
		}

	} while (opcion != 8);
}

long long int numeroReferencia() {
	random_device rd; // random_device crea una fuente de numeros aleatorios basado en el hardware
	mt19937 gen(rd()); // t19937 gen(rd()) crea un generador de numeros
	uniform_int_distribution<int> dist(0, 9); // crea la distribucion de numeros del 0 al 9

	long long int numero = 0; //inicilizamos en numeros que vamos a resolver

	for (int i = 0; i < 10; ++i) {
		numero = numero * 10 + dist(gen);  //generamos 10 numeros y se lo agregamos al numero que vamos a devolver
	}

	return numero; // se retorna el numero
}

void insertar(Nodo*& historial, Transaccion transX) {
	Nodo* nuevoNodo = new Nodo();
	nuevoNodo->transaccion = transX;

	Nodo* aux1 = historial;
	Nodo* aux2 = nullptr;

	while (aux1 != NULL) {
		aux2 = aux1;
		aux1 = aux1->siguiente;
	}

	if (historial == aux1) {
		historial = nuevoNodo;
	}
	else {
		aux2->siguiente = nuevoNodo;
	}
	nuevoNodo->siguiente = aux1;

	// actualizamos el saldo disponible
	nuevoNodo->transaccion.cuenta.saldo = transX.cuenta.saldo;
}


void mostrarTransacciones(Nodo* historial)
{
	Nodo* actual = new Nodo();
	actual = lista;

	cout << "TRANSACCIONES" << endl;
	cout << endl;
	while (actual != NULL) {

		cout << "Numero de referencia : " << actual->transaccion.referencia << endl;
		cout << "Detalle : " << actual->transaccion.detalle << endl;
		actual = actual->siguiente;
	}
	cout << endl;
	system("pause");
	system("cls");
}

void buscarTransaccion(Nodo* lista) {
	Nodo* actual = new Nodo();
	actual = lista;

	string busqueda;
	cout << "BUSCAR POR DETALLE" << endl;
	cin.ignore();
	getline(cin, busqueda);
	cout << endl;

	while (actual != NULL) {

		if (busqueda == actual->transaccion.detalle) {

			cout << "Comprobante" << endl;
			cout << "Retiro : " << actual->transaccion.monto << endl;
			cout << "Fecha " << actual->transaccion.fecha.tm_mday << "/" << (actual->transaccion.fecha.tm_mon + 1) << "/" << (actual->transaccion.fecha.tm_year + 1900) << endl;
			cout << "Monto: " << actual->transaccion.monto << endl;
			cout << "Detalle: " << actual->transaccion.detalle << endl;
			cout << "Numero de referencia: " << actual->transaccion.referencia << endl;

			//opcion



			system("pause");
			system("cls");

			system("pause");
			system("cls");

			char decision;
			cout << "Desea guardar el comprobrante (s/n)";
			cin >> decision;
			if (decision == 'S' || decision == 's') {
				crearComprobante(actual->transaccion);
			}
			system("cls");

		}
		else if (actual->siguiente == NULL) {
			cout << "Transaccion no encontrada";
			system("pause");
			system("cls");
		}

		actual = actual->siguiente;
	}

}

void EliminarTransaccion(Nodo* lista) {
	int opcion;
	if (lista != NULL) {

		cout << "1. Borrar por detalle  2. Borrar por numero de referencia" << endl;
		cin >> opcion;
		string detalle;
		int numeroRef;
		Nodo* auxBorrar = new Nodo();
		Nodo* anterior = new Nodo();

		switch (opcion)
		{
		case 1:

			cout << "Ingrese el detalle";
			cin >> detalle;


			auxBorrar = lista;

			while (auxBorrar != NULL && auxBorrar->transaccion.detalle != detalle) {
				anterior = auxBorrar;
				auxBorrar = auxBorrar->siguiente;
			}

			if (auxBorrar == NULL) {
				cout << "Detalle no encontrado";
				system("pause");
				system("cls");
			}
			else if (anterior == NULL) {
				lista = lista->siguiente;
				delete auxBorrar;
				system("pause");
				system("cls");
			}
			else {
				anterior->siguiente = auxBorrar->siguiente;
				delete auxBorrar;
				cout << "Elemento eliminado";
				system("pause");
				system("cls");
			}
			break;

		case 2:

			cout << "Ingrese el numero de referencia";
			cin >> numeroRef;


			auxBorrar = lista;

			while (auxBorrar != NULL && auxBorrar->transaccion.referencia != numeroRef) {
				anterior = auxBorrar;
				auxBorrar = auxBorrar->siguiente;
			}

			if (auxBorrar == NULL) {
				cout << "Numero de referencia no encontrado";
				system("pause");
				system("cls");
			}
			else if (anterior == NULL) {
				lista = lista->siguiente;
				delete auxBorrar;
				system("pause");
				system("cls");
			}
			else {
				anterior->siguiente = auxBorrar->siguiente;
				delete auxBorrar;
				cout << "Elemento eliminado";
				system("pause");
				system("cls");
			}

			break;

		default:
			break;
		}


	}

}

void menuRetiro(Cuenta& cuenta) {
	if (cuenta.creada == false) {
		cout << "Usted debe crear una cuenta" << endl;
		system("pause");
		system("cls");
	}
	else {
		int confirmPin;
		cout << "Digite su PIN :";
		cin >> confirmPin;
		system("cls");
		if (confirmPin == cuenta.pin)
		{
			string detalle;
			float monto;

			cout << "RETIROS" << endl;
			cout << "Saldo actual :" << cuenta.saldo << endl;
			cout << "Monto a retirar" << endl;
			cin >> monto;
			cin.ignore();
			cout << "Detalle" << endl;
			getline(cin, detalle);
			system("cls");

			if (monto > cuenta.saldo) {
				cout << "Fondos insuficientes" << endl;
			}
			else {

				long numeroRef = numeroReferencia();
				time_t now = time(nullptr);
				tm fecha, localTime;
				localtime_s(&fecha, &now);
				localtime_s(&localTime, &now);

				Transaccion transaccion;
				transaccion.cuenta = cuenta;
				transaccion.fecha = fecha;
				transaccion.hora = localTime;
				transaccion.monto = monto;
				transaccion.detalle = detalle;
				transaccion.referencia = numeroRef;
				cuenta.saldo = cuenta.saldo - monto;
				transaccion.cuenta.saldo = transaccion.cuenta.saldo - monto;

				cout << "Comprobante" << endl;
				cout << "Retiro : " << transaccion.monto << endl;
				cout << "Saldo restante: " << cuenta.saldo << endl;
				cout << "Fecha " << fecha.tm_mday << "/" << (fecha.tm_mon + 1) << "/" << (fecha.tm_year + 1900) << endl;

				// Formatear y mostrar la hora
				char horaFormateada[9]; // Espacio para HH:MM:SS + '\0'
				strftime(horaFormateada, sizeof(horaFormateada), "%H:%M:%S", &transaccion.hora);
				cout << "Hora: " << horaFormateada << endl;

				cout << "Monto: " << transaccion.monto << endl;
				cout << "Detalle: " << transaccion.detalle << endl;
				cout << "Numero de referencia: " << transaccion.referencia << endl;

				insertar(lista, transaccion);
				system("pause");
				system("cls");

				char decision;
				cout << "Desea guardar el comprobrante (s/n)";
				cin >> decision;
				if (decision == 'S' || decision == 's') {
					crearComprobante(transaccion);
				}
				system("cls");

			}



		}
		else {
			cout << "PIN incorrecto" << endl;
			system("pause");
			system("cls");
		}
	}


}

void menuDeposito(Cuenta& cuenta) {
	if (cuenta.creada == false) {
		cout << "Usted debe crear una cuenta" << endl;
		system("pause");
		system("cls");
	}
	else {
		int confirmPin;
		cout << "Digite su PIN :";
		cin >> confirmPin;
		system("cls");
		if (confirmPin == cuenta.pin)
		{
			float deposito;
			string detalle;
			cout << "Depositos" << endl;
			cout << endl;
			cout << "Monto a depositar : ";
			cin >> deposito;
			cout << "Detalle : ";
			cin >> detalle;

			long numeroRef = numeroReferencia();
			time_t now = time(nullptr);
			tm fecha, localTime;
			localtime_s(&fecha, &now);
			localtime_s(&localTime, &now);

			Transaccion transaccion;
			transaccion.cuenta = cuenta;
			transaccion.fecha = fecha;
			transaccion.hora = localTime;
			transaccion.monto = deposito;
			transaccion.detalle = detalle;
			transaccion.cuenta.saldo = transaccion.cuenta.saldo + deposito;
			cuenta.saldo = cuenta.saldo + deposito;
			transaccion.referencia = numeroRef;


			system("cls");
			cout << "Comprobante" << endl;
			cout << endl;
			cout << "Deposito : " << transaccion.monto << endl;
			cout << "Saldo Actual : " << cuenta.saldo << endl;
			cout << "Fecha " << fecha.tm_mday << "/" << (fecha.tm_mon + 1) << "/" << (fecha.tm_year + 1900) << endl;
			char horaFormateada[9];
			strftime(horaFormateada, sizeof(horaFormateada), "%H:%M:%S", &transaccion.hora);
			cout << "Hora: " << horaFormateada << endl;
			cout << "Detalle : " << transaccion.detalle << endl;
			cout << "Numero de referencia : " << transaccion.referencia << endl;
			insertar(lista, transaccion);
			system("pause");
			system("cls");

			char decision;
			cout << "Desea guardar el comprobrante (s/n)";
			cin >> decision;
			if (decision == 'S' || decision == 's') {
				crearComprobante(transaccion);
			}
		}
		else {
			cout << "PIN incorrecto" << endl;
			system("pause");
			system("cls");
		}

	}

}

void menuTransferencia(Cuenta& cuenta) {
	if (cuenta.creada == false) {
		cout << "Usted debe crear una cuenta" << endl;
		system("pause");
		system("cls");
	}
	else {
		int confirmPin;
		cout << "Digite su PIN :";
		cin >> confirmPin;
		system("cls");
		if (confirmPin == cuenta.pin) {
			float transferencia;
			int numCuenta;
			string detalle;
			cout << "Transferencias" << endl;
			cout << endl;
			cout << "Monto a transferir : ";
			cin >> transferencia;
			cout << "Numero de cuenta : ";
			cin >> numCuenta;
			cout << "Detalle : ";
			cin >> detalle;

			if (transferencia > cuenta.saldo) {
				system("cls");
				cout << "Fondos insuficientes" << endl;
				system("pause");
				system("cls");
			}
			else {
				long numeroRef = numeroReferencia();
				time_t now = time(nullptr);
				tm fecha, localTime;
				localtime_s(&fecha, &now);
				localtime_s(&localTime, &now);

				Transaccion transaccion;
				transaccion.cuenta = cuenta;
				transaccion.fecha = fecha;
				transaccion.hora = localTime;
				transaccion.monto = transferencia;
				transaccion.detalle = detalle;
				transaccion.cuenta.saldo = transaccion.cuenta.saldo - transferencia;
				cuenta.saldo = cuenta.saldo - transferencia;
				transaccion.referencia = numeroRef;

				system("cls");
				cout << "Comprobante" << endl;
				cout << endl;
				cout << "Transferencia : " << transaccion.monto << endl;
				cout << "Numero de cuenta : " << numCuenta << endl;
				cout << "Fecha " << fecha.tm_mday << "/" << (fecha.tm_mon + 1) << "/" << (fecha.tm_year + 1900) << endl;
				char horaFormateada[9];
				strftime(horaFormateada, sizeof(horaFormateada), "%H:%M:%S", &transaccion.hora);
				cout << "Hora: " << horaFormateada << endl;
				cout << "Detalle : " << transaccion.detalle << endl;
				cout << "Numero de referencia : " << transaccion.referencia << endl;
				insertar(lista, transaccion);
				system("pause");
				system("cls");

				char decision;
				cout << "Desea guardar el comprobrante (s/n)";
				cin >> decision;
				if (decision == 'S' || decision == 's') {
					crearComprobante(transaccion);
				}
				system("cls");

			}



		}
		else {
			cout << "PIN incorrecto" << endl;
			system("pause");
			system("cls");

		}
	}


}

void crearComprobante(Transaccion transaccion) {
	stringstream ss;
	ss << "Comp" << transaccion.referencia << ".txt"; // Generar nombre del archivo

	string nombreArchivo = ss.str();

	ofstream archivoComprobante(nombreArchivo);
	if (archivoComprobante.is_open()) {
		archivoComprobante << "*** Comprobante ***" << endl;
		archivoComprobante << "Nombre : " << transaccion.cuenta.nombre << " " << transaccion.cuenta.apellido << endl;
		archivoComprobante << "Numero de referencia: " << transaccion.referencia << endl;
		archivoComprobante << "Monto: " << transaccion.monto << endl;
		archivoComprobante << "Fecha: " << transaccion.fecha.tm_mday << "/" << (transaccion.fecha.tm_mon + 1) << "/" << (transaccion.fecha.tm_year + 1900) << endl;
		archivoComprobante << "Detalle: " << transaccion.detalle << endl;
		archivoComprobante.close();
		cout << "Comprobante guardado exitosamente como '" << nombreArchivo << "'" << endl;
	}
	else {
		cout << "Error al abrir el archivo" << endl;
	}
}