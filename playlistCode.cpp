#include<iostream>
#include<time.h>
#include<string>
#include <algorithm> 
#include <random>    
using namespace std;

// Definicion de las estructuras de datos de cada lista
struct nodo {
    string titulo;
    string artista;
    int duracion;
    nodo* siguiente;
};
// Funcion para insertar canciones al final de la lista
void insertarcancion(nodo* &cabeza, string titulo, string artista, int duracion){
    nodo* nuevoNodo = new nodo();
    nuevoNodo->titulo = titulo;
    nuevoNodo->artista = artista;
    nuevoNodo->duracion = duracion;
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        nuevoNodo->siguiente = cabeza;
    } else {
        nodo* actual = cabeza;
        while (actual->siguiente != cabeza) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
        nuevoNodo->siguiente = cabeza;
    }
}
// Funcion para pausar
void pausaparasegundo(){
    clock_t pausa= clock() + CLOCKS_PER_SEC;
    while (clock() < pausa) {
}
}
// Funcion para reproducir la cancion
void reproducir(nodo* &cancion){
    int tamanobarra=30;

    cout<<"Reproduciendo: "<<cancion->titulo<<" - " <<cancion->artista<<endl;
    // reproduccion regresiva
    for(int t= cancion->duracion; t>=0; --t){
        int cancioncompleta = ((cancion->duracion - t) * tamanobarra) / cancion->duracion;
        string barrallena(cancioncompleta, '-');
        string barraVacia(tamanobarra - cancioncompleta, ' ');
        cout << "\rTiempo restante de la cancion:" << t << "s [" << barrallena << ">" << barraVacia << "]" << flush;
        if (t > 0) {
            pausaparasegundo();
        }
    }
    cout << endl << "Cancion finalizada.\n" << endl;
}
//Funcion para mostrar las canciones de la lista que se seleccione
void mostrarcanciones(nodo* &cabeza) {
    if (cabeza == nullptr) {
        cout << "No hay canciones en la lista" << endl;
        return;
    }
    nodo* actual = cabeza;
    int numero= 1;
     cout<< "\n\tCANCIONES EN LA LISTA\n"<< endl;
    // usamos Do while para dar una vuelta en la lista circular
    do {
        cout <<numero++<<". "<< actual->titulo << " - " << actual->artista << " [" << actual->duracion << "s]" << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}
// Funciones de reproduccion principales
// Reproduccion secuencial
void reproduccionsecuencial(nodo* &cabeza) {
    if (cabeza==nullptr) return;
    nodo* actual = cabeza;
    cout<<"Reproduccion secuencial iniciada"<<endl;
    do {
        reproducir(actual);
        actual = actual->siguiente;
    } while (actual != cabeza);
}
// Repeticion de Lista
void repetirLista(nodo* &cabeza) {
    if (cabeza==nullptr) return;
    nodo* actual = cabeza;
    cout<<"Repetir lista"<<endl;
    //reproducir(actual);
    int cancionesreproducidas=0;
    // Voy a colocar 12 para que reproduzca la lista de 6 canciones 2 veces
    while (cancionesreproducidas < 12) 
    {
        reproducir(actual);
        cancionesreproducidas++;
        actual = actual->siguiente;
      
    }
}
// funcion para repetir cancion
void repetircancion(nodo* &cabeza) {
    if(cabeza==nullptr) return;
     nodo* temp = cabeza;
    cout<< "\nCual cancion quieres repetir?"<< endl;
         int cont = 1, x;
         do{
            cout << cont++ << ". " << temp->titulo << endl;
            temp = temp->siguiente;
         }while(temp != cabeza);
         cout<< "\nIngresa el numero: ";
         do{
            cin>> x;
            if(x>0 && x<7){
                for(int i = 1; i < x; i++){
            temp = temp-> siguiente;
         }
            }else cout<<"\nopción invalida, ingrese otro numero\n";
        
         }while(!(x>0 && x<7));

    cout<<"\nRepetir cancion\n"<<endl;
    for (int i=0; i<2; ++i)
    reproducir(temp);
}
// funcion de aleatorio
void aleatorio(nodo *cabeza) {
     if (cabeza == nullptr) return;
     //para reordenar de forma aleatoria los numeros de la matriz
    int numeros[6] ={1,2,3,4,5,6};
    random_device rd;
    mt19937 g(rd());
    shuffle(numeros, numeros + 6, g);

   
   for (int i = 0; i < 6; ++i) {
        //cada numero de la matriz indica la canción
        nodo* actual = cabeza;
        for (int j = 0; j < numeros[i] ; ++j) {
            actual = actual->siguiente;
        }
        reproducir(actual);
    }
}
int main() {
    //srand(time(0)); // Inicializa la semilla para números aleatorios
    nodo* lista1 = nullptr;
    nodo* lista2 = nullptr;
    nodo* lista3 = nullptr;

    // Agregar canciones a la lista 1



    insertarcancion(lista1, "Rubia Sol Morena Luna", "Caramelos de Cianuro", 3); //120
    insertarcancion(lista1, "Sanitarios", "Caramelos de Cianuro", 3);            //120   
    insertarcancion(lista1, "La Casa", "Caramelos de Cianuro", 3);               //120
    insertarcancion(lista1, "Veronica", "Caramelos de Cianuro", 3);              //120
    insertarcancion(lista1, "Secreto", "Caramelos de Cianuro", 3);               //120
    insertarcancion(lista1, "El Instante Paso", "Caramelos de Cianuro", 3);      //120

    // Agregar canciones a la lista 2
    insertarcancion(lista2, "La dueña del Swing", "Los hermanos Rosario", 3);
    insertarcancion(lista2, "Te Compro Tu Novia", "Ramon Orlando", 3);
    insertarcancion(lista2, "Tu eres Ajena", "Eddy Herrera", 10);
    insertarcancion(lista2, "Tiburon", "Sandy y Papo", 3);
    insertarcancion(lista2, "Una Fotografia", "Bonny Cepeda", 3);
    insertarcancion(lista2, "Tu Sonrisa", "Elvis Crespo", 3);

    // Agregar canciones a la lista 3
    insertarcancion(lista3, "Annihilate", "Metro Bomin", 8);
    insertarcancion(lista3, "Hora Loca", "Rawayana", 3);
    insertarcancion(lista3, "Imitadora", "Romeo Santos", 3);
    insertarcancion(lista3, "Dile", "Don Omar", 5);
    insertarcancion(lista3, "Gasolina", "Daddy Yankee", 3);
    insertarcancion(lista3, "Love Me Again", "John Newman", 3);
// Opciones del menu 
int opcionlista, opcionreproduccion;
char repetirlista, VolverMenuinicial;
nodo* listaSeleccionada = nullptr;
string nombreLista="";
// Menu Inicial de las listas
do {
    cout<<"\n\tSELECCIONE UNA LISTA DE MUSICA:\n"<<endl;
    cout<<"1. Lista 1: Caramelos de Cianuro"<<endl;
    cout<<"2. Lista 2: Merengue"<<endl;
    cout<<"3. Lista 3: Variado"<<endl;
    cout<<"Ingrese el numero de la lista que desea reproducir: ";
    cin>>opcionlista;
    // Asignamos la lista seleccionada segun la opcion del usuario
 do{
    switch (opcionlista) {
        case 1:
            listaSeleccionada = lista1;
            nombreLista="Caramelos de Cianuro";
            break;
        case 2:
            listaSeleccionada = lista2;
            nombreLista="Merengue";
            break;
        case 3:
            listaSeleccionada = lista3;
            nombreLista="Variado";
            break;
        default:
            cout<<"Opcion invalida, por favor seleccione una opcion valida."<<endl;
            VolverMenuinicial='s';
            continue;
    }
    // Menu de opciones de reproduccion
    
        cout<<"\n\tSELECCIONE UN MODO DE REPRODUCCION\n"<<nombreLista<<":"<<endl;
        cout<<"1. Reproduccion Secuencial"<<endl;
        cout<<"2. Repetir Lista"<<endl;
        cout<<"3. Repetir Cancion"<<endl;
        cout<<"4. Reproduccion Aleatoria"<<endl;
        cout<<"5. Mostrar las canciones de la Lista"<<endl;
        cout<<"6. Volver al menu anterior"<<endl;
        cout<<"Ingrese el numero de la opcion de reproduccion: ";
        cin>>opcionreproduccion;

        switch (opcionreproduccion) {
            case 1:
                reproduccionsecuencial(listaSeleccionada);
                break;
            case 2:
                repetirLista(listaSeleccionada);
                break;
            case 3:
                repetircancion(listaSeleccionada);
                break;
            case 4:
                aleatorio(listaSeleccionada);
                break;
            case 5: 
                mostrarcanciones(listaSeleccionada);
                break;
            case 6:
            continue; break;
            default:
                cout<<"Opcion invalida, por favor seleccione una opcion valida."<<endl;
                continue; 
        }
        cout<<"Desea volver al menu de opciones de reproduccion? (s/n): ";
        cin>>repetirlista;
    } while (repetirlista=='s' || repetirlista=='S');

    cout<<"Desea volver al menu inicial de listas? (s/n): ";
    cin>>VolverMenuinicial;

} while (VolverMenuinicial=='s' || VolverMenuinicial=='S');

cout<<"Gracias por usar el reproductor de musica."<<endl;
return 0;
}