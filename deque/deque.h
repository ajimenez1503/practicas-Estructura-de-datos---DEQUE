/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica Estructuras de Datos: Estructura DEQUE
Version:0.1

*/
#ifndef __deque_H
#define __deque_H

#include <assert.h>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

/** deque<T>

deque<T>:: deque, size, capacity, empty, operator[], at, push_back, push_front, resize, operator=, insert, erase,

deque<T>::iterator::  iterator,operator*, operator++, operator-- operator=, operator==, operator!=

deque<T>::const_iterator:: const_iterator,operator*, operator++, operator-- operator=, operator==, operator!=

Descripción

Un deque es un contenedor que permite el acceso aleatorio (mediante valores enteros) a los elementos, inserción y borrado en tiempo constante si se realiza al final y comienzo del deque. Sin embargo, la inserción y el borrado son de orden lineal si se realizan en posiciones intermedias del deque. Si sólo necesitamos añadir/borrar elementos por el final es preferible utilizar el vector. 

 Al contrario que los vectores, un deque no garantiza que los elementos se almacenen en posiciones contiguas de memoria, sino que estos se almacenan en bloques de tamaño fijo.

Ambos, vectores y deques, proporcionan una interfaz muy similar y pueden utilizarse para resolver los mismos problemas, pero internamente son muy diferentes. Mientras que los vectores almacenan la informacion  de forma contigua,  tienendose  que redimensionar  todo el vector cuando crece su tamaño, los elementos en un deque se pueden almacenan en diferentes en bloques, manteniendo el deque la informacion necesaria para permitir el acceso directo a cualquiera de sus elementos en orden constante. Por tanto tienen una representacion interna mas compleja que el vector, lo que le permite crecer de forma más eficiente bajo ciertas circunstancias, particularmente cuando se consideran secuencias muy grandes de elementos, donde realojarlos todos tiene un elevado coste para el vector.
En cualquier caso, la interfaz de un deque permite acceder a los elementos secuencialmente. 

La eficiencia de las operaciones de un deque son:

    Acceso Aleatorio - O(1). En nuestra implementacíon será  un poco más lento
    Inserción y borrado al principio y al final - O(1), análisis amortizado
    Inserción y borrado en cualquier otra posición - lineal O(n) 
El número de elementos en el deque puede variar dinámicamente; la gestión de la memoria es automática. 
 
**/


template<typename T>
class deque {
 public:
  typedef unsigned int size_type;
  typedef T value_type;
  class iterator;
  class const_iterator;

/**
     @brief Constructor por defecto
     
  */
  deque();
 /**
     @brief Constructor primitivo 
@param[in] n número de elementos en el deque
@param[in] t elemento a insertar, por defecto T()

Crea un deque con n elementos con el valor t
     
  */
  deque( size_type n, const T & t = T()  );

/**
     @brief Constructor de copia.
     
     @param[in] org deque que se copia
     
     Crea un deque  duplicado exacto de org.
  */
  deque( const deque<T> & org);

   
/**
     @brief Destructor.
     Destruye el receptor liberando los recursos que ocupaba.
  */
  ~deque();

/** @brief tamaño
    Devuelve el numero de elementos en el deque
*/
  size_type size() const;


/** @brief vacia
   Chequea si el deque esta vacio (size()==0)
*/
  bool empty() const;
/** @brief acceso directo
  @param[in] pos posicion del deque
@return Devuelve una referencia al elemento n-esimo del deque
*/
  T & operator[](size_type pos);
/** @brief acceso directo
  @param[in] pos posicion del deque
@return Devuelve una referencia cosntnte al elemento n-esimo del deque
*/
  const T & operator[ ](size_type pos) const;

/** @brief acceso directo seguro, chequea que la posición sea correcta
  @param[in] pos posicion del deque
@return Devuelve una referencia al elemento n-esimo del deque
*/
  T & at(size_type pos);
/** @brief acceso directo seguro, chequea que la posición sea correcta
  @param[in] pos posicion del deque
@return Devuelve una referencia cosntnte al elemento n-esimo del deque
*/
  const T & at(size_type pos) const;

/** @brief insertar final
  @param[in] t elemento a insertar del deque

Añade el elemento t al final del deque
*/
  void push_back(const T & t);

/** @brief insertar inicio
  @param[in] t elemento a insertar del deque

Añade el elemento t al final del deque
*/
  void push_front(const T & t);

/** @brief borrar inicio
 
Elimina el elemento   al inicio del deque
*/
  void pop_front( );

/** @brief borrar final
 
Elimina el elemento   al final del deque
*/
  void pop_back();//esta mal no se le pasan argumentos.
/** @brief elimiar todos los elementos 
 
Elimina todos los elementos del contenedor.
*/
  void clear( );
/**
 @brief Modificar el tamaño 
@param[in] n número de elementos en el deque
@param[in] t elemento a insertar, por defecto T()

Si el numero de elementos es menor que n, se añaden al final copias de t, hasta alcanzar un tamaño n. Si el numero de elementos es mayor que n, el deque se reduce a los primeros n elementos. 
*/
  void resize( size_type n, const T & t = T() );

/** @brief operador de asignacion
@param[org] el deque a asignar.
*/
  deque<T> & operator=( const deque<T> & org);
  
  // ITERADOR SOBRE VECTORES
  class iterator {
        public:
               iterator();
               iterator( const deque<T>::iterator & it);
               T & operator*();
               iterator & operator++();
 	       iterator & operator--();
               iterator & operator=(const deque<T>::iterator & it);
               bool operator==(const deque<T>::iterator & it) const;
               bool operator!=(const deque<T>::iterator & it) const;
        private:
               friend class deque;
               typename list<vector<T> >::iterator it_l;
               typename vector<T>::iterator it_v;
               };
   class const_iterator {
        public:
               const_iterator();
               const_iterator( const deque<T>::const_iterator & it);
               const T & operator*();
               const_iterator & operator++();
	       const_iterator & operator--();
               const_iterator & operator=(const deque<T>::const_iterator & it);
               bool operator==(const deque<T>::const_iterator & it) const;
               bool operator!=(const deque<T>::const_iterator & it) const;
        private:
               friend class deque;
               typename list<vector<T> >::const_iterator it_l;
               typename vector<T>::const_iterator it_v;
               };
/**
 @brief inicio del deque
*/
   iterator begin();
/**
 @brief fin del deque,

devuelve la posición siguiente al último elemento
*/
   iterator end();
/**
 @brief inicio del deque
*/
   const_iterator begin() const;
/**
 @brief fin del deque,

devuelve la posición siguiente al último elemento
*/
   const_iterator end() const;
/**
 @brief Insertar elemento
@param[in] pos posicion a insertar
@param[in] T elemento a insertar

Inserta el elemento t justo antes de pos, desplaza el resto de los elementos una posición hacia el final del deque
*/
   iterator insert(typename deque<T>::iterator & pos, const T & t);
/**
 @brief borrado de elementos
@param[in] pos posicion a borrar


Borra el elemento de la posición pos, desplaza los siguientes elementos una posición hacia el inicio del deque
*/
   iterator erase(typename deque<T>::iterator & pos);
   
/** @brief intercambia el contenido de dos deques

Intercambia el contenido entre *this y otro, No implica borrado o copia de elementos
*/
void swap(deque<T> & otro);

 private:
  #define TAM_BLQ 10
  list<vector<T> > L_dq;
  typename vector<T>::size_type inicio;  // Inicio de los datos
  typename vector<T>::size_type final;   // fin de los datos
  size_type tama;
  
  void cheq_rep( ) const;
  

};

#include "deque.hxx"
#endif
