/**
 * @file Bank.cpp
 * @brief Implementación de los métodos de la clase Bank.
 * @author Santiago Payan Ibarra
 * @author Jose Maria Nuñez Saille
 * @date 16/03/2026
 */

#include "headers/Bank.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iomanip>

/**
 * @brief Constructor por defecto del módulo (caja)
 * Inicializa los tiempos en cero y el nombre de cliente vacío
 */
Bank::Module::Module() {
    start_time_attention = 0;
    attention_time = 0;
    client = "";
}

/**
 * @brief Constructor de Bank
 * Inicializa las 3 cajas y los arreglos dinámicos necesarios.
 * @param TIME_OPEN_BANK El tiempo total que dura la simulación.
 */
Bank::Bank(int TIME_OPEN_BANK){
    cant_cajas = 3;
    // Arreglo dinámico de colas (una por caja)
    attended_clients = new Queue<Client>[cant_cajas];
    modules = new Module[cant_cajas];
    available_modules = new bool[cant_cajas];
    this->TIME_OPEN_BANK = TIME_OPEN_BANK;

    // Al inicio, todas las cajas están disponibles
    for(int i = 0; i < cant_cajas; ++i) {
        available_modules[i] = false;
    }
}

/**
 * @brief Destructor de Bank
 * Libera la memoria dinámica de los arreglos.
 */
Bank::~Bank() {
    delete [] attended_clients;
    delete [] modules;
    delete [] available_modules;
}

/**
 * @brief Asigna el cliente que está al inicio de la fila a un módulo vacío.
 * @param module_index Índice de la caja (0, 1 o 2).
 * @param current_time Minuto actual de la simulación.
 */
void Bank::assignClientModule(int module_index, int current_time) {
    // Si hay gente esperando y la caja está libre
    if (!waiting_line.isEmpty() && !available_modules[module_index]) {
        // Genera tiempo de atención entre 2 y 8 minutos
        modules[module_index].attention_time = rand() % 7 + 2;
        modules[module_index].client = waiting_line.getFront();
        available_modules[module_index] = true; // Ocupar caja
        modules[module_index].start_time_attention = current_time;
        waiting_line.pop(); // Sacar al cliente de la fila general
    }
    print(current_time);
}

/**
 * @brief Revisa si el cliente actual de una caja ya terminó su tiempo de atención.
 * Si ya terminó, libera la caja y mueve al cliente a la lista de "atendidos".
 * @param current_time Minuto actual de la simulación.
 * @param module_index Índice de la caja (0, 1 o 2).
 */
void Bank::verifyAttentionClient(int current_time, int module_index) {
    if (!available_modules[module_index])
        return; // Caja vacía, nada que hacer
                
    Client client = modules[module_index].client;
    // Revisar si ya pasó el tiempo requerido
    if (current_time - modules[module_index].start_time_attention >=
       modules[module_index].attention_time) {         
        available_modules[module_index] = false; // Liberar caja
        attended_clients[module_index].push(client); // Guardar en historial
        print(current_time);    
    }
}

/**
 * @brief Genera nuevos clientes aleatoriamente y los mete a la fila de espera.
 * @param current_time Minuto actual de la simulación.
 * @param name Nombre aleatorio del nuevo cliente.
 */
void Bank::update(int current_time, Client name) {
    int add_client = rand() % 1 + 1; // Para esta versión, siempre llega uno
    if (current_time % add_client == 0) {
        waiting_line.push(Client(name));
    }
    print(current_time);
           
}

/**
 * @brief Imprime la "pantalla" del banco con las cajas y la fila de espera.
 * @param current_time Minuto actual de la simulación.
 */
void Bank::print(int current_time) {
    clearScreen();

    std::cout << "Duracion: " << TIME_OPEN_BANK << std::endl;
    std::cout << "\n\nTiempo transcurrido: " << current_time << "\n\n" <<std::endl;
    std::cout << std::left << std::setw(20) << "Cajas" << std::setw(20) << "Nombre" << std::setw(20)  << "Tiempo de Espera" << std::endl;

    for (int module_index = 0; module_index < cant_cajas; ++module_index) {
        std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;
        std::cout << std::setfill(' ');
        printBox(module_index);
     }
    
     std::cout << "\nEspera: " << std::endl;

     if (!waiting_line.isEmpty()) {
         waiting_line.print();
     }
    
     // Detiene el programa por 1 segundo para simular el paso del tiempo visualmente
     std::this_thread::sleep_for(std::chrono::seconds(1));
}

/**
 * @brief Cierra el banco y muestra el resumen final.
 * Imprime quiénes fueron atendidos por cada caja y quiénes se quedaron en la fila.
 */
void Bank::close() {
    clearScreen();
    for (int i = 0; i < cant_cajas; ++i) {
        // Si alguien se quedó a medias en la caja cuando cerró el banco, lo consideramos "atendido"
        if(available_modules[i]){ 
            attended_clients[i].push(modules[i].client); 
        }

        if (!attended_clients[i].isEmpty()) {
            std::cout << "\nAtendidos en caja " << i + 1  << ": " << std::endl;
            attended_clients[i].print();
        }
        std::cout << std::endl;
    }
    
    // Los que no alcanzaron caja
    if (!waiting_line.isEmpty()) {
        std::cout << "\n\nEn espera quedaron: " << std::endl;
        waiting_line.print();
    }
}

/**
 * @brief Imprime el estado individual de una caja (ocupada o vacía).
 * @param module_index Índice de la caja a imprimir.
 */
void Bank::printBox(int module_index) {
     if (available_modules[module_index]){
        std::cout << std::left << "En Caja " << module_index + 1 << std::setw(11) << ": " << std::setw(20) << modules[module_index].client << std::setw(20) << " Tiempo de atencion: " << modules[module_index].attention_time << std::endl;
     } else {
         std::cout << std::left << "En Caja " << module_index + 1 << std::setw(10) << ":" << std::setw(20) << " No hay nadie" << std::setw(20) << "Tiempo de atencion: 0" << std::endl;
     }
}

/**
 * @brief Limpia la consola.
 * Usa un comando del sistema específico para Linux/Unix.
 */
void Bank::clearScreen() { 
    system("clear"); 
}