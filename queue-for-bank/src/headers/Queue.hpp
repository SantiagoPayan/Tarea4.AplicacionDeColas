/**
 * \file Queue.hpp
 * \brief Implementacíon de colas
 * \author Carlos Enrique Mancillas Duran
 * \author Braulio Alessandro S&aacute;nchez Berm&uacute;dez
 * \date 16/03/2024
 */
#include <iostream>
#ifndef QUEUE_HPP
#define QUEUE_HPP

/** \class Queue
 *
 * Esta clase template ofrece una implementaci&oacute;n de cola con operaciones
para agregar,
 * eliminar elementos, y consultar el tope de la cola, entre otras.
 *
 * \tparam T Tipo de elementos almacenados en la cola.
 *
 *
 *
*
 */
template <typename T = int> class Queue {
public:
  /**
   * \brief Constructor por defecto que inicializa una cola vac&iacute;a.
   */
  explicit Queue();

  /**
   * \brief Constructor de copia.
   * \param p Otra cola de la cual se copiar&aacute;n los elementos.
   */
  Queue(const Queue &p);

  /**
   * \brief Sobrecarga del operador de asignaci&oacute;n.
   * \param p Otra cola de la cual se copiar&aacute;n los elementos.
   * \exception const <b>char *</b> La cola copia no puede ser creado.
   *
   * \return Referencia a la cola actual.
   */
  Queue &operator=(const Queue &p);

  /**
   * \brief Destructor que libera la memoria de la cola.
   */
  ~Queue();

  /**
   * \brief Agrega un nuevo elemento al fondo de la cola.
   * \param valor El valor a agregar.
   */
  void push(T valor);

  /**
   * \brief Elimina el elemento al principio de la cola.
   */
  void pop();

  /**
   * \brief Obtiene el valor del inicio de la cola sin eliminarlo.
   *
   * \exception const <b>char *</b> La cola está vacía.

   * \return El valor en el tope de la cola.
   */
  T getFront() const;

  /**
   * \brief Obtiene el valor del fondo de la cola sin eliminarlo.
   *
   * \exception const <b>char *</b> La cola está vacía.

   * \return El valor en el tope de la cola.
   */
  T getFound() const;
  /**
   * \brief Vac&iacute;a la cola eliminando todos sus elementos.
   *
   * \exception const <b>char *</b> La pial está vacía.

   */
  void clear();

  /**
   * \brief Obtiene el tamaño actual de la cola, es decir, el n&uacute;mero de
   * elementos.
   * \return El n&uacute;mero de elementos en la cola.
   */
  int size() const;

  /**
   * \brief Verifica si la cola est&aacute; vac&iacute;a.
   * \return Verdadero si la cola est&aacute; vac&iacute;a, falso de lo
   * contrario.
   */
  bool isEmpty() const;

  /**
   * \brief Imprime todos los elementos de la cola, utilizado para pruebas.
   */
  void print() const;

private:
    int _size;

    struct Element {
        Element(T v, Element *next_ = nullptr);
        T value;
        Element *next;
    }* found;
};

#include "../templates/Queue.tpp"

#endif // QUEUE_HPP
