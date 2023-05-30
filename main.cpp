#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct student {
    string name, lastName, career, email, phoneNo, dni;
    int age, course;
    bool status;
};

struct node {
    string id;
    struct student aspirant;
    node* next;
};

void createNode(node*&);
void add(node*);
void printList(node*);
void printNode(node*, int);
void searchNode(node*);
void modifyNode(node*);
void saveToCSV(node*);
void loadFromCSV(node*&);

const string FILENAME = "data.csv"; // Nombre del archivo CSV

int main() {
    node* ptr = NULL;
    int opt;

    loadFromCSV(ptr); // Cargar datos desde el archivo CSV

    while (true) {
        system("cls");
        opt = 0;
        cout << "1 add\n2 print\n3 get\n4 modify\n";
        cin >> opt;
        switch (opt) {
            case 1:
                system("cls");
                createNode(ptr);
                saveToCSV(ptr); // Guardar datos en el archivo CSV
                break;
            case 2:
                system("cls");
                printList(ptr);
                break;
            case 3:
                system("cls");
                searchNode(ptr);
                break;
            case 4:
                system("cls");
                modifyNode(ptr);
                saveToCSV(ptr); // Guardar datos en el archivo CSV
                break;
        }
    }
    system("pause>nul");
    return 0;
}

void createNode(node*& head) {
    node* ptr = new node();
    add(ptr);
    ptr->next = head;
    head = ptr;
    return;
}

void add(node* head) {
    node* ptr = head;
    cout << "Ingrese id\n";
    cin >> ptr->id; // This will be randomized later
    cout << "\nIngrese nombre\n";
    cin.ignore();
    getline(cin, ptr->aspirant.name);
    transform(ptr->aspirant.name.begin(), ptr->aspirant.name.end(), ptr->aspirant.name.begin(), ::toupper);
    cout << "\nIngrese apellido\n";
    getline(cin, ptr->aspirant.lastName);
    transform(ptr->aspirant.lastName.begin(), ptr->aspirant.lastName.end(), ptr->aspirant.lastName.begin(), ::toupper);
    cout << "\nIngrese carrera\n";
    getline(cin, ptr->aspirant.career);
    transform(ptr->aspirant.career.begin(), ptr->aspirant.career.end(), ptr->aspirant.career.begin(), ::toupper);
    cout << "\nIngrese email\n";
    getline(cin, ptr->aspirant.email);
    cout << "\nIngrese edad\n";
    cin >> ptr->aspirant.age;
    cout << "\nIngrese Semestre\n";
    cin >> ptr->aspirant.course;
    cout << "\nIngrese Numero de telefono\n";
    cin >> ptr->aspirant.phoneNo;
    cout << "\nIngrese cedula\n";
    cin >> ptr->aspirant.dni;
}

void printList(node* head) {
    node* ptr = head;
    int count = 0;
    while (ptr) {
        printNode(ptr, count);
        ptr = ptr->next;
        count++;
    }

    cout << "nullptr";
    system("pause>nul");
}

void printNode(node* head, int count) {
    node* ptr = head;
    cout << "Numero de nodo: " << count << endl;
    cout << "Id: " << ptr->id << "\n";
    cout << "Nombre: " << ptr->aspirant.name << " " << ptr->aspirant.lastName << "\n";
    cout << "Documento De Identidad: " << ptr->aspirant.dni << "\n";
    cout << "Edad: " << ptr->aspirant.age << "\n";
    cout << "Carrera: " << ptr->aspirant.career << "\n";
    cout << "Email: " << ptr->aspirant.email << "\n";
    cout << "Numero de Telefono: " << ptr->aspirant.phoneNo << "\n";
    cout << "Estado: " << (ptr->aspirant.status ? "Inactivo" : "Activo") << "\n\n";
}

void searchNode(node* head) {
    node* ptr = head;
    int count = 0, index = 0;
    string name, lastName, dni, id;
    bool found = false;
    cout << "\t\tBusqueda\n\n0.-ID\n1.- Nombre y Apellido\n2.-Documento de Identidad\n";
    cin >> index;
    while (ptr != NULL) {
        switch (index) {
            case 0:
                cout << "Ingrese el documento de identidad: ";
                cin >> id;
                while (ptr != NULL) {
                    if (id == ptr->id) {
                        printNode(ptr, count);
                        found = true;
                    }
                    count++;
                    ptr = ptr->next;
                }
                break;

            case 1:
                cout << "\nIngrese nombre\n";
                cin.ignore();
                getline(cin, name);
                transform(name.begin(), name.end(), name.begin(), ::toupper);
                cout << "\nIngrese apellido\n";
                getline(cin, lastName);
                transform(lastName.begin(), lastName.end(), lastName.begin(), ::toupper);
                while (ptr != NULL) {
                    if (name == ptr->aspirant.name && lastName == ptr->aspirant.lastName) {
                        printNode(ptr, count);
                        found = true;
                    }
                    count++;
                    ptr = ptr->next;
                }
                break;

            case 2:
                cout << "Ingrese el documento de identidad: ";
                cin >> dni;
                while (ptr != NULL) {
                    if (dni == ptr->aspirant.dni) {
                        printNode(ptr, count);
                        found = true;
                    }
                    count++;
                    ptr = ptr->next;
                }
                break;

            default:
                break;
        }
    }

    if (!found) {
        cout << "\nEstudiante no registrado\n";
    }

    system("pause>nul");
}

void modifyNode(node* head) {
    node* ptr = head;
    int count = 0, index;
    cout << "\nNumero de nodo a modificar: ";
    cin >> index;
    while (ptr != NULL) {
        if (count == index) {
            add(ptr);
        }
        count++;
        ptr = ptr->next;
    }
}

#define FILENAME "data.csv"

void saveToCSV(node* head) {
    ofstream file(FILENAME);
    if (file.is_open()) {
        node* ptr = head;
        while (ptr != NULL) {
            file << ptr->id << ";"
                 << ptr->aspirant.name << ";"
                 << ptr->aspirant.lastName << ";"
                 << ptr->aspirant.career << ";"
                 << ptr->aspirant.email << ";"
                 << ptr->aspirant.age << ";"
                 << ptr->aspirant.course << ";"
                 << ptr->aspirant.phoneNo << ";"
                 << ptr->aspirant.dni << "\n";
            ptr = ptr->next;
        }
        file.close();
        cout << "Datos guardados en " << FILENAME << endl;
    } else {
        cout << "No se pudo abrir el archivo " << FILENAME << endl;
    }
}

void loadFromCSV(node*& head) {
    ifstream file(FILENAME);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            node* ptr = new node();
            istringstream ss(line);
            getline(ss, ptr->id, ';');
            getline(ss, ptr->aspirant.name, ';');
            getline(ss, ptr->aspirant.lastName, ';');
            getline(ss, ptr->aspirant.career, ';');
            getline(ss, ptr->aspirant.email, ';');
            string ageStr;
            getline(ss, ageStr, ';');
            ptr->aspirant.age = atoi(ageStr.c_str());
            string courseStr;
            getline(ss, courseStr, ';');
            ptr->aspirant.course = atoi(courseStr.c_str());
            getline(ss, ptr->aspirant.phoneNo, ';');
            getline(ss, ptr->aspirant.dni, ';');

            ptr->next = head;
            head = ptr;
        }
        file.close();
        cout << "Datos cargados desde " << FILENAME << endl;
    } else {
        cout << "No se pudo abrir el archivo " << FILENAME << endl;
    }
}

