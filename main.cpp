#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct student{
    string name, career, email, status;
    int age, dni, course, phoneNo;

};

struct node{
    int id;
    struct student aspirant;
    node *next;
};

void add(node *&), printList(node*), getSpecificNode(node*), modifyNode(node*);

int main(){
    node *ptr = NULL;
    for (size_t i = 0; i < 3; i++)
    {
        add(ptr);
    }
    printList(ptr);
    getSpecificNode(ptr);
    modifyNode(ptr);
    printList(ptr);
    system("pause>nul");
}

void add(node *&head){
    node *new_node = new node();
    cout<<"Ingrese id\n";
    cin>>new_node->id;
    cout<<"\nIngrese nombre\n";
    cin.ignore(); 
    getline(cin, new_node->aspirant.name);
    cout<<"\nIngrese edad\n";
    cin>>new_node->aspirant.age;
    new_node -> next = head;
    head = new_node;
    system("cls");
}

void printList(node* head)
{
    node* ptr = head;
    int count=0;
    while (ptr)
    {
        cout<<"Numero de nodo: "<<count<<endl;
        cout <<"Id: "<<ptr->id <<"\n";
        cout <<"Nombre: "<<ptr->aspirant.name << "\n";
        cout <<"Edad: "<<ptr->aspirant.age << "\n\n";
        ptr = ptr->next;
        count++;
    }
    cout << "nullptr";
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
 }

 void modifyNode(node* head){
    node* ptr = head;
    int count = 0, index;
    cout<<"\nNumero de nodo a modificar: ";
    cin>>index;
    while(ptr != NULL){
        if (count == index){
            cout<<"Ingrese id\n";
            cin>>ptr->id;
            cout<<"\nIngrese nombre\n";
            cin.ignore(); 
            getline(cin, ptr->aspirant.name);
            cout<<"\nIngrese edad\n";
            cin>>ptr->aspirant.age;
        }
        count++;
        ptr = ptr->next;
    }
 }