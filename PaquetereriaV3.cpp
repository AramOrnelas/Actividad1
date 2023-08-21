#include <iostream>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <vector>

using namespace std;

class Paquete {
	public:
		int id;
		float peso;
		string origen;
		string destino;

		Paquete(int _id, float _peso, const string& _origen, const string& _destino): id(_id), peso(_peso), origen(_origen), destino(_destino) {}
};
class Nodo {
	public:
		Paquete paquete;
		Nodo* siguiente;

		Nodo(const Paquete& _paquete): paquete(_paquete), siguiente(nullptr) {}
};

class Lista {

	public:
		Nodo* inicio;
		Lista():inicio(nullptr) {}

		void AgregarInicio(const Paquete& paquete) {
			Nodo* nuevoNodo= new Nodo(paquete);
			nuevoNodo->siguiente=inicio;
			inicio=nuevoNodo;
		}

		void MostrarTodo() {
			Nodo* actual=inicio;
			if(inicio!=nullptr) {

				while(actual!=nullptr) {
					cout<<"ID: "<<actual->paquete.id<<endl;
					cout<<"Peso: "<<actual->paquete.peso<<endl;
					cout<<"Origen: "<<actual->paquete.origen<<endl;
					cout<<"Destino: "<<actual->paquete.destino<<endl;
					cout<<endl;
					actual=actual->siguiente;
				}
			} else {
				cout<<"No hay paquete que mostrar"<<endl;
			}
			system("pause");

		}

		void EliminarInicio() {
			if(inicio!=nullptr) {
				Nodo* temp=inicio;
				inicio= inicio->siguiente;
				delete temp;
				cout<<"Paquete eliminado con exito"<<endl;
			} else {
				cout<<"No hay Paquetes para eliminar"<<endl;

			}
			system("pause");
		}

		void EliminarTodo() {
			Nodo* actual=inicio;
			while(actual!=nullptr) {
				Nodo* temp=actual;
				actual=actual->siguiente;
				delete temp;
			}
			inicio=nullptr;

		}

		void Guardar(const string& NomArchivo) {
			ofstream archivo(NomArchivo);
			if(archivo.is_open()) {
				Nodo* actual=inicio;
				while(actual!=nullptr) {
					archivo<<actual->paquete.id<<endl;
					archivo<<actual->paquete.peso<<endl;
					archivo<<actual->paquete.origen<<endl;
					archivo<<actual->paquete.destino<<endl;
					actual=actual->siguiente;
				}
				archivo.close();
				EliminarTodo();
				cout<<"Datos guardados, se a eliminado la sesion actual"<<endl;
			} else {
				cout<<"No se a logrado Guardar"<<endl;
			}
			system("pause");
		}

		void Cargar(const string& NomArchivo) {
			ifstream archivo(NomArchivo);
			if(archivo.is_open()) {
				int id;
				float peso;
				string origen,destino;
				while(archivo>>id>>peso) {
					archivo.ignore();
					getline(archivo,origen);
					getline(archivo,destino);
					Paquete paquete(id,peso,origen,destino);
					AgregarInicio(paquete);

				}
				archivo.close();
				cout<<"Archivo cargado con exito"<<endl;

			} else {
				cout<<"No se logor encontrar el archivo"<<endl;
			}
		}


		void InvertirLista() {
			Nodo* prev = nullptr;
			Nodo* current = inicio;
			Nodo* next = nullptr;

			while (current != nullptr) {
				next = current->siguiente;
				current->siguiente = prev;
				prev = current;
				current = next;
			}

			inicio = prev;
		}
		
		void CargarEnOrden(const string& NomArchivo) {
			ifstream archivo(NomArchivo);
			if (archivo.is_open()) {
				vector<Paquete> paquetes; 
				int id;
				float peso;
				string origen, destino;
				while (archivo >> id >> peso) {
					archivo.ignore();
					getline(archivo, origen);
					getline(archivo, destino);
					Paquete paquete(id, peso, origen, destino);
					paquetes.push_back(paquete);
				}
				archivo.close();

				Lista listaTemporal;
				for (const Paquete& paquete : paquetes) {
					listaTemporal.AgregarInicio(paquete);
				}

				
				Nodo* tempInicio = listaTemporal.inicio;
				while (tempInicio != nullptr) {
					AgregarInicio(tempInicio->paquete);
					tempInicio = tempInicio->siguiente;
				}

				cout << "Archivo cargado en orden con éxito" << endl;
			} else {
				cout << "No se logró encontrar el archivo" << endl;
			}
		}







};

int main() {


	Lista lista;
	Paquete paquete(0,0,"","");
	int id,opc;
	float peso;
	string origen;
	string destino;
	string archivo;
	do {
		system("cls");
		cout<<"****Bienveneido a PAQUETERIAS AMAZUN****"<<endl;
		cout<<"1)Agregar al inicio"<<endl;
		cout<<"2)Eliminar inicio"<<endl;
		cout<<"3)Mostrar"<<endl;
		cout<<"4)Guardar"<<endl;
		cout<<"5)Cargar"<<endl;
		cout<<"6)Salir"<<endl;
		cin>>opc;
		cin.ignore();

		switch(opc) {

			case 1:
				cout<<"id"<<endl;
				cin>>id;
				cout<<"peso"<<endl;
				cin>>peso;
				cin.ignore();
				cout<<"origen"<<endl;
				getline(cin,origen);
				cout<<"destino"<<endl;
				getline(cin,destino);
				cin.ignore();

				paquete=Paquete(id,peso,origen,destino);
				lista.AgregarInicio(paquete);
				cout<<"Paquete agregado con exito"<<endl;
				system("pause");

				break;

			case 2:
				lista.EliminarInicio();
				break;
			case 3:
				lista.MostrarTodo();

				break;
			case 4:
				cout<<"Nombre para el archivo"<<endl;
				getline(cin,archivo);
				cin.ignore();
				lista.Guardar(archivo);
				break;
			case 5:
				cout<<"Nombre de archivo a cargar"<<endl;
				getline(cin,archivo);
				cin.ignore();
				lista.CargarEnOrden(archivo);
				break;
			case 6:

				break;

		}
	} while(opc!=6);
	return 0;

}