#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

// 1. Definición de la estructura de datos [cite: 29]
struct Nodo {
    string titulo;
    string artista;
    int duracion; // En segundos (entre 30 y 120) [cite: 24]
    Nodo* siguiente;
};

struct ListaCircular {
    // Variables de la lista
    Nodo* cabeza;
    Nodo* cola;
    string nombreLista;
    int idLista;

    // Constructor
    ListaCircular(int id, string nombre) {
        cabeza = nullptr;
        cola = nullptr;
        idLista = id;
        nombreLista = nombre;
    }

    void agregarCancion(string titulo, string artista, int duracion) {
        Nodo* nuevo = new Nodo{titulo, artista, duracion, nullptr};
        if (!cabeza) {
            cabeza = nuevo;
            cola = nuevo;
            nuevo->siguiente = cabeza; 
        } else {
            cola->siguiente = nuevo;
            cola = nuevo;
            cola->siguiente = cabeza; 
        }
    }

    // Lógica para simular el tiempo regresivo [cite: 39]
    void simularReproduccion(Nodo* cancion, int numeroTema) {
        cout << "\nReproduciendo lista [" << idLista << "]: " << nombreLista << "\n"; [cite: 22]
        cout << "Tema " << numeroTema << ". " << cancion->titulo << ". " << cancion->artista 
             << ". Tiempo: " << cancion->duracion << " seg.\n"; [cite: 23]
        
        for (int t = cancion->duracion; t >= 0; t -= 10) {
            cout << "Tiempo restante: " << (t < 0 ? 0 : t) << " seg...\r";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(300)); 
        }
        cout << "Tiempo restante: 0 seg... ¡Completado!       \n";
    }

    // --- 2. Diseño de funciones de reproducción --- [cite: 31]

    // Modo 1: Reproducción secuencial [cite: 33]
    void secuencial() {
        if (!cabeza) return;
        Nodo* actual = cabeza;
        int i = 1;
        cout << "\n--- MODO: SECUENCIAL ---\n";
        do {
            simularReproduccion(actual, i++);
            actual = actual->siguiente;
        } while (actual != cabeza); 
    }

    // Modo 2: Repetición de lista [cite: 34]
    void repetirLista() {
        if (!cabeza) return;
        Nodo* actual = cabeza;
        int i = 1;
        int ciclos = 0;
        cout << "\n--- MODO: REPETICIÓN DE LISTA (Simulando 2 vueltas) ---\n";
        
        while (ciclos < 2) {
            simularReproduccion(actual, i++);
            actual = actual->siguiente;
            if (actual == cabeza) {
                ciclos++;
                if(ciclos < 2) cout << "\n*** Reiniciando la lista desde el principio ***\n"; 
            }
        }
    }

    // Modo 3: Repetición de canción [cite: 35]
    void repetirCancion() {
         if (!cabeza) return;
         cout << "\n--- MODO: REPETICIÓN DE CANCIÓN (Simulando bucle 3 veces) ---\n";
         for (int i = 0; i < 3; i++) {
             simularReproduccion(cabeza, 1); 
         }
    }

    // Modo 4: Aleatorio (shuffle) [cite: 36]
    void aleatorio() {
        if (!cabeza) return;

        int cantidadNodos = 0;
        Nodo* actual = cabeza;
        do {
            cantidadNodos++;
            actual = actual->siguiente;
        } while (actual != cabeza);

        // Arreglo dinámico de punteros
        Nodo** arreglo = new Nodo*[cantidadNodos];
        
        actual = cabeza;
        for (int i = 0; i < cantidadNodos; i++) {
            arreglo[i] = actual;
            actual = actual->siguiente;
        }

        // Librería <random> para mezclar
        random_device rd;  
        mt19937 generador(rd());         //revisar esta función mejor, siento que es un pococ confusa.

        for (int i = cantidadNodos - 1; i > 0; i--) {
            uniform_int_distribution<int> distribucion(0, i); 
            int j = distribucion(generador); 

            Nodo* temporal = arreglo[i];
            arreglo[i] = arreglo[j];
            arreglo[j] = temporal;
        }

        cout << "\n--- MODO: ALEATORIO (SHUFFLE) ---\n";
        for (int i = 0; i < cantidadNodos; i++) {
            simularReproduccion(arreglo[i], i + 1);
        }

        delete[] arreglo; // <-- Esto es para liberar memoria dinámica
    }
};

void cargarListas(ListaCircular& l1, ListaCircular& l2, ListaCircular& l3) {
    // Lista 1: Variado (6 pistas) [cite: 15]
    l1.agregarCancion("Mi niña bonita", "Chino y Nacho", 45); 
    l1.agregarCancion("Bohemian Rhapsody", "Queen", 120);
    l1.agregarCancion("Despacito", "Luis Fonsi", 60);
    l1.agregarCancion("Shape of You", "Ed Sheeran", 90);
    l1.agregarCancion("Blinding Lights", "The Weeknd", 80);
    l1.agregarCancion("Levitating", "Dua Lipa", 50);

    // Lista 2: Pop (6 pistas) [cite: 16]
    l2.agregarCancion("Thriller", "Michael Jackson", 100);
    l2.agregarCancion("Toxic", "Britney Spears", 60);
    l2.agregarCancion("Bad Romance", "Lady Gaga", 90);
    l2.agregarCancion("Watermelon Sugar", "Harry Styles", 55);
    l2.agregarCancion("Anti-Hero", "Taylor Swift", 70);
    l2.agregarCancion("Uptown Funk", "Bruno Mars", 110);

    // Lista 3: Tu cantante favorito (6 pistas OST CoD MW) [cite: 17]
    l3.agregarCancion("Piccadilly Circus", "Sarah Schachner", 120);
    l3.agregarCancion("Into the Furnace", "Sarah Schachner", 90);
    l3.agregarCancion("Rooftop", "Sarah Schachner", 80);
    l3.agregarCancion("Highway", "Sarah Schachner", 110);
    l3.agregarCancion("Safehouse", "Sarah Schachner", 45);
    l3.agregarCancion("Old Comrades", "Sarah Schachner", 60);
}

int main() {
    ListaCircular listaVariado(1, "Variado");
    ListaCircular listaPop(2, "Pop");
    ListaCircular listaFavorito(3, "OST Modern Warfare (Sarah Schachner)");

    cargarListas(listaVariado, listaPop, listaFavorito);

    int opcLista = 0;
    bool continuar = true;

    while (continuar) {
        cout << "\n========================================\n";
        cout << "       LISTAS DE REPRODUCCIÓN\n"; [cite: 14]
        cout << "========================================\n";
        cout << "Lista [1] Variado\n"; [cite: 15]
        cout << "Lista [2] Pop\n"; [cite: 16]
        cout << "Lista [3] OST Modern Warfare\n"; [cite: 17]
        cout << "Lista [4] Salir\n";
        cout << "Seleccione una lista a reproducir: "; [cite: 18]
        cin >> opcLista;

        if (opcLista == 4) break;
        if (opcLista < 1 || opcLista > 3) {
            cout << "Opción inválida. Intente de nuevo.\n";
            continue;
        }

        ListaCircular* listaActual;
        if (opcLista == 1) listaActual = &listaVariado;
        else if (opcLista == 2) listaActual = &listaPop;
        else listaActual = &listaFavorito;

        bool enSubMenu = true;
        while (enSubMenu) {
            int opcModo = 0;
            cout << "\n--- MODOS DE REPRODUCCIÓN ---\n";
            cout << "1. Reproducción secuencial\n";
            cout << "2. Repetición de lista\n";
            cout << "3. Repetición de canción\n";
            cout << "4. Aleatorio (shuffle)\n";
            cout << "Seleccione el modo: ";
            cin >> opcModo;

            switch (opcModo) {
                case 1: listaActual->secuencial(); break;
                case 2: listaActual->repetirLista(); break;
                case 3: listaActual->repetirCancion(); break;
                case 4: listaActual->aleatorio(); break;
                default: cout << "Modo inválido.\n"; continue;
            }

            char resp;
            cout << "\n¿Deseas volver a reproducir esta lista? si es sí (s), en qué modo, si es no (n), volver al menú inicial: "; [cite: 26]
            cin >> resp;

            if (tolower(resp) == 'n') {
                enSubMenu = false; 
            } 
        }
    }
    
    cout << "\n¡Gracias por usar el reproductor!\n";
    return 0;
}