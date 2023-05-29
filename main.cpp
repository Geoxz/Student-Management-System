#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

struct student{
    string name, lastName, career, email, phoneNo, dni;
    int age, course;
    bool status;
};

struct node{
    int id;
    struct student aspirant;
    node *next;
};

void createNode(node *&), add(node*), printList(node*), getSpecificNode(node*), modifyNode(node*);

int main(){
    node *ptr = NULL;
    int opt;
    
    while (true){
        system("cls");
        opt = 0;
        cout<<"1 add\n2 print\n3 get\n4 modify\n";
        cin>>opt;
        switch (opt){
        case 1:
            system("cls");
            createNode(ptr);
            break;
        case 2:
            system("cls");
            printList(ptr);
            break;
        case 3:
            system("cls");
            getSpecificNode(ptr);
            break;
        case 4:
            system("cls");
            modifyNode(ptr);
            break;
        }
    }
    system("pause>nul"); 
    return 0;
    }

void createNode(node *&head){
    node *ptr = new node();
    add(ptr);
    ptr -> next = head;
    head = ptr;
    return;
}

void add(node* head){
    node* ptr = head;
    cout<<"Ingrese id\n";
    cin>>ptr->id; //This will be randomized later
    cout<<"\nIngrese nombre\n";
    cin.ignore(); 
    getline(cin, ptr->aspirant.name);
    transform(ptr->aspirant.name.begin(), ptr->aspirant.name.end(), ptr->aspirant.name.begin(), ::toupper);
    cout<<"\nIngrese apellido\n";
//    cin.ignore(); 
    getline(cin, ptr->aspirant.lastName);
    transform(ptr->aspirant.lastName.begin(), ptr->aspirant.lastName.end(), ptr->aspirant.lastName.begin(), ::toupper);
    cout<<"\nIngrese carrera\n";
//    cin.ignore(); 
    getline(cin, ptr->aspirant.career);
    transform(ptr->aspirant.career.begin(), ptr->aspirant.career.end(), ptr->aspirant.career.begin(), ::toupper);
    cout<<"\nIngrese email\n";
//    cin.ignore(); 
    getline(cin, ptr->aspirant.email);
    cout<<"\nIngrese edad\n";
    cin>>ptr->aspirant.age;
    cout<<"\nIngrese Semestre\n";
    cin>>ptr->aspirant.course;
    cout<<"\nIngrese Numero de telefono\n";
    cin>>ptr->aspirant.phoneNo;
    cout<<"\nIngrese cedula\n";
    cin>>ptr->aspirant.dni;
    cout<<endl;
}

void printList(node* head)
{
    node* ptr = head;
    int count=0;
    while (ptr)
    {
        cout<<"Numero de nodo: "<<count<<endl;
        cout<<"Id: "<<ptr->id <<"\n";
        cout<<"Nombre: "<<ptr->aspirant.name<<" "<<ptr->aspirant.lastName<<"\n";
        cout<<"Documento De Identidad: "<<ptr->aspirant.dni<<"\n";
        cout<<"Edad: "<<ptr->aspirant.age << "\n";
        cout<<"Carrera: "<<ptr->aspirant.career<<"\n";
        cout<<"Email: "<<ptr->aspirant.email<<"\n";
        cout<<"Numero de Telefono: "<<ptr->aspirant.phoneNo<<"\n";
        ptr = ptr->next;
        count++;
    }
    cout << "nullptr";
    system("pause>nul"); 
}
 
 void getSpecificNode(node* head){
    node* ptr = head;
    int count = 0, index;
    cout<<"\nNumero de nodo a buscar: ";
    cin>>index;
    while(ptr != NULL){
        if (count == index){
            cout<<ptr->id;
        }
        count++;
        ptr = ptr->next;
    }
    system("pause>nul"); 
 }

 void modifyNode(node* head){
    node* ptr = head;
    int count = 0, index;
    cout<<"\nNumero de nodo a modificar: ";
    cin>>index;
    while(ptr != NULL){
        if (count == index){
            add(ptr);
        }
        count++;
        ptr = ptr->next;
    }
 }