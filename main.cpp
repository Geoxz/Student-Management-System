#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>

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
void searchNode(node*, bool);
void saveToCSV(node*);
void loadFromCSV(node*&);
void showData(node*);
void showPage();
void showDataHeader();
void showPrintData(node*, int);
string generateID(node*);

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int x, int y){
	CursorPosition.X = x; 
	CursorPosition.Y = y; 
	SetConsoleCursorPosition(hConsole,CursorPosition);
}

const string FILENAME = "data.csv"; // Nombre del archivo CSV

int main() {
    node* ptr = NULL;
    int opt;

    loadFromCSV(ptr); // Cargar datos desde el archivo CSV

    while (true) {
        system("cls");
        showPage();
        opt = 0;
        cout << "1. Agregar\n2. Imprimir\n3. Obtener\n4. Modificar\n5. Mostrar datos en consola\n";
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
                searchNode(ptr, 0);
                break;
            case 4:
                system("cls");
                searchNode(ptr, 1);
                saveToCSV(ptr); // Guardar datos en el archivo CSV
                break;
                case 5:
                system("cls");
                showData(ptr);
                break;
            default:
                cout<<"Opcion no valida, intentalo nuevamente\n";
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
    cout << "id: ";
    ptr->id = generateID(ptr);
    cout<<ptr->id;

    cout << "\nIngrese nombre: ";
    cin.ignore();
    getline(cin, ptr->aspirant.name);
    transform(ptr->aspirant.name.begin(), ptr->aspirant.name.end(), ptr->aspirant.name.begin(), ::toupper);

    cout << "\nIngrese apellido: ";
    getline(cin, ptr->aspirant.lastName);
    transform(ptr->aspirant.lastName.begin(), ptr->aspirant.lastName.end(), ptr->aspirant.lastName.begin(), ::toupper);
    
    cout << "\nIngrese carrera: ";
    getline(cin, ptr->aspirant.career);
    transform(ptr->aspirant.career.begin(), ptr->aspirant.career.end(), ptr->aspirant.career.begin(), ::toupper);
    
    cout << "\nIngrese email: ";
    getline(cin, ptr->aspirant.email);
    
    cout << "\nIngrese edad: ";
    cin >> ptr->aspirant.age;
    
    cout << "\nIngrese Semestre: ";
    cin >> ptr->aspirant.course;
    
    cout << "\nIngrese Numero de telefono\n";
    cin >> ptr->aspirant.phoneNo;
    
    cout << "\nIngrese cedula: ";
    cin >> ptr->aspirant.dni;
}

string generateID(node* head){
    node* ptr = head;
    string id;
    int num;

    if (!ptr->id.empty()){
        return ptr->id;
    }

    srand(time(NULL));

    for (int i = 0; i < 4; i++){
        num = 1 + (rand() % 9);
        id += to_string(num);
    }
    return id;
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
    //cout << "Numero de nodo: " << count << endl;
    cout << "ID: " << ptr->id << "\n";
    cout << "Nombre: " << ptr->aspirant.name << " " << ptr->aspirant.lastName << "\n";
    cout << "Edad: " << ptr->aspirant.age << "\n";
    cout << "Documento De Identidad: " << ptr->aspirant.dni << "\n";
    cout << "Carrera: " << ptr->aspirant.career << "\n";
    cout << "Numero de Telefono: " << ptr->aspirant.phoneNo << "\n";
    cout << "Email: " << ptr->aspirant.email << "\n";
    cout << "Estado: " << (ptr->aspirant.status ? "Inactivo" : "Activo") << "\n\n";
}


void searchNode(node* head, bool mod) {
    node* ptr = head;
    int count = 1, index, sType, n;
    string name, lastName, dni, id, career;
    int course, age;
    bool found = false, status;

    cout<<"\t\tBusqueda\n\n";

    if (!mod){
        while (sType > 2 || sType < 1){
            cout<<"Que tipo de busqueda realizara\n1.- Especifica\n2.- General\n";
            cin >> sType;
        }
    } else {
        sType = 1;
    }

    if (sType == 1){
            while (index > 3 || index < 1){
                cout<<"\nIngresa el filtro\n1.- ID\n2.- Nombre\n3.- Documento de identidad\n";
                cin>>index;
            }    
        } else {
            while (index > 3 || index < 1){
                cout<<"\nIngresa el filtro\n1.- Edad\n2.- Carrera\n3.- Carrera y Semestre\n";
                cin>>index;
            } 
        }

    while (ptr != NULL) {
        if (sType == 1){
            switch (index) {

                case 1:
                    cout << "Ingrese el ID: ";
                    cin >> id;
                    while (ptr != NULL) {
                        if (id == ptr->id) {
                            printNode(ptr, count);
                            found = true;
                            if (mod){
                                cout<<"\nDesea Modificarlo\n";
                                cin>>n;
                                if (n == 1){
                                    add(ptr);
                                } else{
                                    return;
                                }
                            }
                        }
                        count++;
                        ptr = ptr->next;
                    }
                    break;

                case 2:
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
                            if (mod){
                                cout<<"\nDesea Modificarlo\n";
                                cin>>n;
                                if (n == 1){
                                    add(ptr);
                                } else{
                                    return;
                                }
                            }
                        }
                        count++;
                        ptr = ptr->next;
                    }
                    break;

                case 3:
                    cout << "Ingrese el documento de identidad: ";
                    cin >> dni;
                    while (ptr != NULL) {
                        if (dni == ptr->aspirant.dni) {
                            printNode(ptr, count);
                            found = true;
                            if (mod){
                                cout<<"\nDesea Modificarlo\n";
                                cin>>n;
                                if (n == 1){
                                    add(ptr);
                                } else{
                                    return;
                                }
                            }
                        }
                        count++;
                        ptr = ptr->next;
                    }
                    break;

                default:
                    break;
            }
        } else {
            switch (index) {
                case 1:
                    cout << "\nIngrese la edad\n";
                    cin>>age;

                    while (ptr != NULL) {
                        if (age == ptr->aspirant.age) {
                            if (!found){
                                system("cls");
                            }
                            showDataHeader();
                            showPrintData(ptr, count);
                            count++;
                            // printNode(ptr, count);
                            found = true;
                        }
                        ptr = ptr->next;
                    }
                    break;

                case 2:
                    cout << "Ingrese el nombre de la carrera: ";
                    cin.ignore();
                    getline(cin, career);
                    transform(career.begin(), career.end(), career.begin(), ::toupper);

                    while (ptr != NULL) {
                        if (career == ptr->aspirant.career) {
                            if (!found){
                                system("cls");
                            }
                            showDataHeader();
                            showPrintData(ptr, count);
                            count++;
                            // printNode(ptr, count);
                            found = true;
                        }
                        ptr = ptr->next;
                    }
                    break;

                case 3:
                    cout << "Ingrese el nombre de la carrera: ";
                    cin.ignore();
                    getline(cin, career);
                    transform(career.begin(), career.end(), career.begin(), ::toupper);

                    cout << "Ingrese el numero del semestre: ";
                    cin>>course;

                    while (ptr != NULL) {
                        if (career == ptr->aspirant.career & course == ptr->aspirant.course){
                            if (!found){
                                system("cls");
                            }
                            showDataHeader();
                            showPrintData(ptr, count);
                            count++;
                            // printNode(ptr, count);
                            found = true;
                        }
                        ptr = ptr->next;
                    }
                    break;

                default:
                    cout<<"Opcion no valida, intente otra vez\n";
                    break;
            }
        }
    }

    if (!found) {
        cout << "\nEstudiante no registrado\n";
    }

    system("pause>nul");
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

void showData(node* head) {
    system("cls");
    node* ptr = head;
    int line = 0;
    showDataHeader();
    while (ptr != NULL) {
        line++;
        showPrintData(ptr, line);
        ptr = ptr->next;
    }
    cout<<endl;
    system("pause");        
}

void showDataHeader(){
    gotoXY(0,0);
    cout<<"ID";
    gotoXY(7,0);
    cout<<"Nombre";
    gotoXY(30,0);
    cout<<"Carrera";
    gotoXY(55,0);
    cout<<"Semestre";
    gotoXY(70,0);
    cout<<"Estado";
}

void showPrintData(node* ptr, int line){
    gotoXY(0,line);
    cout<<ptr->id;
    gotoXY(7,line);
    cout<<ptr->aspirant.name;
    gotoXY(30,line);
    cout<<ptr->aspirant.career;
    gotoXY(55,line);
    cout<<ptr->aspirant.course;
    gotoXY(70,line);
    cout<<(ptr->aspirant.status ? "Inactivo" : "Activo");
    cout<<endl;
}

void showPage() {
    cout << "\t\t********************************************" << endl;
    cout << "\t\t*                                          *" << endl;
    cout << "\t\t*                 BIENVENIDO               *" << endl;
    cout << "\t\t*                 AL SISTEMA               *" << endl;
    cout << "\t\t*                DE GESTION DE             *" << endl;
    cout << "\t\t*                 ESTUDIANTES              *" << endl;
    cout << "\t\t*                                          *" << endl;
    cout << "\t\t********************************************" << endl;
    cout << endl;
    cout << "       A        -->   A -> B -> D -> E -> G -> C -> F -> H" << endl;
    cout << "      / \\                                           " << endl;
    cout << "     B   C                                          " << endl;
    cout << "    / \\   \\                                         " << endl;
    cout << "   D   E   F                                        " << endl;
    cout << "      /     \\                                       " << endl;
    cout << "     G       H                                      " << endl;
    cout << endl;
}