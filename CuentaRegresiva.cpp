#include <iostream>
#include <ctime>
#include <thread> // Para pausar un poco el procesador
#include <chrono>

void iniciarTemporizador(int min, int seg) {
    // Calculamos cuántos segundos totales queremos contar
    int segundosTotales = (min * 60) + seg;

    // Obtenemos el tiempo actual y le sumamos la duración
    time_t tiempoInicial = time(0);
    time_t tiempoFinal = tiempoInicial + segundosTotales;

    while (true) {
        time_t ahora = time(0);
        double segundosRestantes = difftime(tiempoFinal, ahora);

        if (segundosRestantes <= 0) {
            std::cout << "\rTiempo cumplido!          " << std::endl;
            break;
        }

        // Convertir segundos restantes a formato MM:SS
        int m = (int)segundosRestantes / 60;
        int s = (int)segundosRestantes % 60;

        // Imprimir el tiempo. El '\r' regresa el cursor al inicio de la línea
        std::cout << "\rTiempo restante: " 
                  << (m < 10 ? "0" : "") << m << ":" 
                  << (s < 10 ? "0" : "") << s << "   " << std::flush;

        // Pausar un poco para no saturar el CPU (100ms)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    int m, s;
    std::cout << "Minutos: "; std::cin >> m;
    std::cout << "Segundos: "; std::cin >> s;

    iniciarTemporizador(m, s);

    return 0;
}
