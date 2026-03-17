/**
 * \file Bank.hpp
 * \brief Implementacion de la clase Banco
 * \author Braulio Alessandro Sánchez Bermúdez
 * \author Carlos Enrique Mancillas Duran
 * \date 16/03/2024
 * */

#ifndef BANK_HPP
#define BANK_HPP
#include "Queue.hpp"

/**
 * \typedef std::string Client
 * \brief Define Client como un alias para std::string, utilizado para representar los nombres de los clientes en el banco.
 */
typedef std::string Client;

/**
 * \typedef std::string Client
 * \brief Define Client como un alias para std::string, utilizado para representar los nombres de los clientes en el banco.
 */
class Bank {
private:
    int cant_cajas;
    struct Module {
    public:
        Module();
        int start_time_attention;
        int attention_time;
        Client client;
    };

    int add_rand_client;
    int client_name_rand;

    bool* available_modules;
    Queue<Client>* attended_clients;
    Queue<Client> waiting_line;
    Module *modules;
    int TIME_OPEN_BANK;

    void printBox(int module_index);
    void print(int current_time);
    void clearScreen();
    
public:
    /**
     * \brief Constructor por defecto que inicializa un objeto de clase Bank.
     * \param int El tiempo en el que esta abierto el banco.
     */
    Bank(int time_open_bank);

    /**
     * \brief Destructor que libera la memoria del objeto Bank.
     */
    ~Bank();

    /**
     * \brief Assigna cliente a modulo disponible.
     * \param module_index Checa que modulo (0,1,2) esta disponible
     * \param current_time Asigna el tiempo en el que empezo la atención al cliente
     */
    void assignClientModule(int module_index, int current_time);

    /**
     * \brief Imprime los clientes que fueron atendidos en cada queja y los que quedaron en la lista
     de espera.
     */
    void close();

    /**
     * \brief Metodo que agrega a la lista de espera el nombre del cliente.
     * \param current_time Tiempo actual en la que la persona llega al banco.
     * \param client Cliente (nombre de la persona).
     */
    void update(int current_time, Client client);

    /**
     * \brief Verifica si la caja o mdulo esta disponible.
     * \param int Tiempo transcurrido.
     * \param int Número de caja.
     */
    void verifyAttentionClient(int current_time, int module_attention);
};

#endif
