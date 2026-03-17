/**
 * @file main.cpp
 * @brief Punto de entrada para la simulación de atención a clientes en un banco.
 * @author Santiago Payan Ibarra
 * @author Jose Maria Nuñez Saille
 * @date 16/03/2026
 */

#include "headers/Bank.hpp"
#include <iostream>
#include <new>
#include <vector>
#include <fstream>
#include "headers/Queue.hpp"

using namespace std;

/**
 * @brief Lee una lista de nombres desde un archivo de texto.
 * * Abre un archivo de texto especificado y lee cada línea, almacenándola 
 * en un vector de cadenas. Si el archivo no se puede abrir, imprime un error.
 * * @param nombreArchivo La ruta relativa o absoluta del archivo de texto.
 * @return std::vector<std::string> Un vector que contiene los nombres leídos.
 */
std::vector<std::string> leerNombresDesdeArchivo(const std::string& nombreArchivo) {
    std::vector<std::string> nombres;
    std::ifstream archivo(nombreArchivo);

    // Verificamos que el archivo se abrió correctamente
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            nombres.push_back(linea);
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
 
    return nombres;
}

/**
 * @brief Función principal que ejecuta la simulación del banco.
 * @return Código de salida del programa (0 si fue exitoso).
 */
int main() {
    // Inicializamos la semilla para la generación de números aleatorios
    srand(time(nullptr));
    
    // NOTA: Cambiar este valor para la entrega final.
    // La rúbrica pide un tiempo entre 120 y 240 minutos.
    // int TIEMPO_TOTAL = rand() % (240 - 120 + 1) + 120;
    int TIEMPO_TOTAL = 10; 
 
    // Inicializamos el banco y cargamos los nombres para los clientes
    Bank bank(TIEMPO_TOTAL);
    std::string archivo = "src/nombres.txt";
    std::vector<std::string> names = leerNombresDesdeArchivo(archivo);

    try {
        // Ciclo principal que simula el reloj del banco minuto a minuto
        for (int current_time = 0; current_time < TIEMPO_TOTAL; ++current_time) {
            
            // 1. Posible llegada de un nuevo cliente a la fila
            bank.update(current_time, names[rand() % names.size()]); // Usamos names.size() para evitar desbordamientos
            
            // 2. Iteramos sobre las 3 cajas (módulos) disponibles
            for (int i = 0; i < 3; ++i) {
                // Asignamos un cliente si la caja está libre y hay fila
                bank.assignClientModule(i, current_time);
                
                // Verificamos si el cliente actual en la caja ya terminó su trámite
                bank.verifyAttentionClient(current_time, i);
            }
        }
        
        // Finaliza el tiempo del banco, imprimimos el resumen final
        bank.close();
        
    } catch (const char* &msg) {
        // Atrapa errores lanzados por nuestra pila/cola (ej. underflow)
        std::cout << "Error lógico atrapado: " << msg << std::endl;
        
    } catch (std::bad_alloc& msg) {
        // Atrapa errores críticos de memoria dinámica (ej. falló un new)
        std::cerr << "Error de memoria: " << msg.what() << std::endl;
    }
    
    return 0;
}