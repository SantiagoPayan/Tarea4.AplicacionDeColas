#include <iostream>

// Constructor
template <typename T> 
Queue<T>::Queue() : _size(0), found(nullptr) {}

// Destructor
template <typename T> 
Queue<T>::~Queue() { clear(); }

// Constructor de copias
template <typename T>
Queue<T>::Queue(const Queue<T> &s) : found(nullptr), _size(0) {
    *this = s; // Llama al operador de asignación
}

// Operador de Asignación (¡Corregido!)
template <typename T> 
Queue<T> &Queue<T>::operator=(const Queue<T> &q) {
    if (this == &q) return *this;
    clear();
    if (!q.isEmpty()) {
        // En una cola circular, el frente es found->next
        Element *now = q.found->next; 
        for (int i = 0; i < q._size; ++i) {
            push(now->value);
            now = now->next;
        }
    }
    return *this;
}

// push (Agregar al fondo)
template <typename T> 
void Queue<T>::push(T value) {
    try {
        Element* new_;
        if (!isEmpty()) {
            new_ = new Element(value, found->next); // El nuevo apunta al frente
            found->next = new_; // El fondo viejo apunta al nuevo
        } else {
            new_ = new Element(value);
        }
        found = new_; // El nuevo es el fondo oficial
        ++_size;
        if(_size == 1) found->next = found; // Si es el único, se apunta a sí mismo
    } catch (std::bad_alloc &) {
        throw "Error: it's not possible to push the value onto the queue.";
    }
}

// pop (Eliminar del frente)
template <typename T> 
void Queue<T>::pop() {
    if (isEmpty()) throw "Error: The queue is empty.";
    
    Element *aux = found->next; // Guardamos el frente
    if (_size == 1) {
        found = nullptr; // Si solo había uno, la cola queda vacía
    } else {
        found->next = aux->next; // El fondo ahora apunta al segundo elemento
    }
    
    delete aux; // Borramos el viejo frente
    --_size;
}

// clear (Vaciar)
template <typename T> 
void Queue<T>::clear() {
    while (!isEmpty()) pop();
}

// getFront (Frente)
template <typename T> 
T Queue<T>::getFront() const {
    if (isEmpty()) throw "Error: The queue is empty.";
    return found->next->value;
}

// getFound (Fondo)
template <typename T> 
T Queue<T>::getFound() const {
    if (isEmpty()) throw "Error: The queue is empty.";
    return found->value;
}

// size
template <typename T> 
int Queue<T>::size() const { return _size; }

// isEmpty
template <typename T> 
bool Queue<T>::isEmpty() const { return _size == 0; }

// print
template <typename T> 
void Queue<T>::print() const {
    if (isEmpty()) return; // Quité el throw para que no crashee al imprimir colas vacías
    
    Element *aux = found->next; // Empezamos desde el frente
    for (int i = 0; i < _size; ++i) {
        std::cout << aux->value << std::endl;
        aux = aux->next;
    }
}

// Constructor del Nodo (Element)
template <typename T>
Queue<T>::Element::Element(T v, Queue<T>::Element *next_) : value(v), next(next_) {}