/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica Estructuras de Datos: Estructura DEQUE
Version:0.1

*/
#include <assert.h>

template<typename T>
deque<T>::deque() {
    inicio=0;
    final=0;//si no tine nada
    tama=0;
}//constructor por defecto.


template<typename T>
deque<T>::deque( typename deque<T>::size_type n, const T & t) {

    inicio=0;
    tama=n;
    typename deque<T>::size_type aux1=n/TAM_BLQ;//numero de bloques
    typename deque<T>::size_type aux2=n%TAM_BLQ;//numero de elemmetnos en el ultimo bloque
    if(aux2!=0) {
        aux1++;
        final=aux2;//aqui iba +1
    }
    else {
        final=10;
    }
    vector<T> aux;
    aux.resize(TAM_BLQ,t);
    for(int i=0; i<aux1; i++) {
        L_dq.push_back(aux);
    }
}

template<typename T>
deque<T>::deque( const deque<T> & org) {
    inicio=org.inicio;
    final=org.final;
    tama=org.tama;
    L_dq=org.L_dq;
}

template<typename T>
deque<T>::~deque() {
    tama=0;
    inicio=0;
    final=1;
    clear();
}
template<typename T>
typename deque<T>::size_type deque<T>::size() const {
    return tama;
}


template<typename T>
bool deque<T>::empty() const {
    return size()==0;
}

template<typename T>
T & deque<T>::operator[](typename deque<T>::size_type pos) {
    typename list<vector<T> >::iterator itl=L_dq.begin();
    typename deque<T>::size_type aux1;
    if(pos<(TAM_BLQ-inicio)) { //se encuentra en el primer bloque
        aux1=pos+inicio;//ya que tenemos que emepezar a contar desde inicio.
    }
    else {
        aux1=pos-(TAM_BLQ-inicio);
        typename deque<T>::size_type aux2=aux1/TAM_BLQ;
        aux2++;
        aux1=aux1%TAM_BLQ;
        for(int i=0; i<aux2; i++) {
            itl++;
        }
    }

    return (*itl)[aux1];
}
template<typename T>
const T & deque<T>::operator[](typename deque<T>::size_type pos) const {
    typename list<vector<T> >::const_iterator itl=L_dq.begin();//debe ser un const_iterator porque sino no podria hacer la llamada de begin con un deque constante.
    typename deque<T>::size_type aux1;
    if(pos<TAM_BLQ) { //se encuentra en el primer bloque
        aux1=pos;
    }
    else {
        aux1=pos-(TAM_BLQ-inicio);
        typename deque<T>::size_type aux2=aux1/TAM_BLQ;
        aux2++;
        aux1=aux1%TAM_BLQ;
        for(int i=0; i<aux2; i++) {
            itl++;
        }
    }

    return (*itl)[aux1];
}

template<typename T>
T & deque<T>::at(typename deque<T>::size_type pos) {
    assert((pos>=0) && (pos<tama)) ;
    return operator[](pos);
}
template<typename T>
const T & deque<T>::at(typename deque<T>::size_type pos) const {
    assert((pos>=0) && (pos<tama)) ;
    return operator[](pos);
}

template<typename T>
void deque<T>::push_back(const T & t) {
    if(final==TAM_BLQ || L_dq.empty()) {
        vector<T> aux;//creamos el primer bloque y le resrvamos 10 posiciones.
        aux.resize(TAM_BLQ);
        aux[0]=t;
        L_dq.push_back(aux);
        final=1;
    }
    else {
        typename list<vector<T> >::iterator itl=L_dq.end();
        itl--;
        (*itl)[final]=t;
        final++;
    }
    tama++;
}


template<typename T>
void deque<T>::push_front(const T & t) {
    if(inicio==0) {//problema si deque estaba vacio
        if(L_dq.empty()) {
            inicio=0;
            final=1;
        }
        else inicio=9;
        vector<T> aux;
        aux.resize(TAM_BLQ);
        aux[inicio]=t;
        L_dq.push_front(aux);

    }
    else {
        typename list<vector<T> >::iterator itl=L_dq.begin();
        (*itl)[inicio-1]=t;
        inicio--;
    }
    tama++;
}



template<typename T>//suponemos que no lo llamaremos con el deque vacio
void deque<T>::pop_back( ) { //unicamente movemos fin e ini ya que no podmeos borrar la capacidad del vector con pop_back
    if(final==1) {
        L_dq.pop_back();
        final=10;
    }
    else {
        final--;
    }
    tama--;
}

template<typename T>//suponemos que no lo llamaremos con el deque vacio
void deque<T>::pop_front( ) { //unicamente movemos fin e ini ya que no podmeos borrar la capacidad del vector con pop_back
    if(inicio==9) {
        L_dq.pop_front();
        inicio=0;
        //final=0;¿?
    }
    else {
        inicio++;
    }
    tama--;
}

template<typename T>
void deque<T>::clear( ) {
    tama=0;
    inicio=0;
    final=0;
    L_dq.clear();
}


template<typename T>
deque<T> & deque<T>::operator=(const deque<T> &org) {
    if(this!=&org) {
        inicio=org.inicio;
        final=org.final;
        tama=org.tama;
        L_dq=org.L_dq;
    }
    return *this;
}


template<typename T>
typename deque<T>::iterator deque<T>::begin()  {
    typename deque<T>::iterator sal;
    sal.it_l=L_dq.begin();
    sal.it_v=(*(sal.it_l)).begin();
    sal.it_v+=inicio;
    return sal;
}

template<typename T>
typename deque<T>::iterator deque<T>::end()  {
    typename deque<T>::iterator sal;
    if(final==TAM_BLQ) {
        sal.it_l=L_dq.end();
        sal.it_v=(*(sal.it_l)).begin();
    }
    else {
        sal.it_l=L_dq.end();
        sal.it_l--;//ya que estaria en el bloque anterior al end() de la lista
        sal.it_v=(*(sal.it_l)).begin();
        if(final>0)
            sal.it_v=(sal.it_v)+final;//aqui iba -1
    }

    return sal;
}


template<typename T>
typename deque<T>::const_iterator deque<T>::begin() const {
    typename deque<T>::const_iterator sal;
    sal.it_l=L_dq.begin();
    sal.it_v=(*(sal.it_l)).begin();
    sal.it_v+=inicio;
    return sal;
}

template<typename T>
typename deque<T>::const_iterator deque<T>::end() const {
    typename deque<T>::const_iterator sal;
    if(final==TAM_BLQ) {
        sal.it_l=L_dq.end();
        sal.it_v=(*(sal.it_l)).begin();
    }
    else {
        sal.it_l=L_dq.end();
        sal.it_l--;//ya que estaria en el bloque anterior al end() de la lista
        sal.it_v=(*(sal.it_l)).begin();
        if(final>0)
            sal.it_v=(sal.it_v)+final;//aqui iba -1
    }

    return sal;
}


template<typename T>
void deque<T>::swap(deque<T> & otro) {
    L_dq.swap(otro.L_dq);
    typename deque<T>::size_type aux;
    aux=otro.tama;
    otro.tama=tama;
    tama=aux;
    aux=otro.final;
    otro.final=final;
    final=aux;
    aux=otro.inicio;
    otro.inicio=inicio;
    inicio=aux;
}


template<typename T>
void deque<T>::resize( typename deque<T>::size_type  n, const T & t) {
    int aux;
    typename list<vector<T> >::iterator itl;
    if(tama<n) {
        aux=n-tama;
        if(TAM_BLQ-final!=0 && !(L_dq.empty()) ) {
            itl=L_dq.end();
            itl--;//accedemos al ultimo vector.
            while(/*aux>(TAM_BLQ-final)*/final<TAM_BLQ && aux>0) {//¿?no estoy seguro si >=  o >
                (*itl)[final]=t;
                final++;//modificamos la variable fin.
                aux--;//disminuimos lo que debemos añadir.
            }
        }
        if(aux>0) {
            int aux2=aux/TAM_BLQ;
            aux2++;
            for(int i=0; i<aux2; i++) {
                vector<T> v;
                v.resize(TAM_BLQ,t);
                L_dq.push_back(v);
            }
            aux2=aux%TAM_BLQ;
            final=aux2;// +1?¿ igualamos fin a una posicion mas del ultimo elemento añadido en el uñltimo bloque.
        }
    }
    else {
        aux=tama-n;
        int aux2=aux/TAM_BLQ;
        if(aux2>0) { //habríaque quitar bloques
            itl=L_dq.end();
            itl--;//accedemos al ultimo vector.
            for(int i=0; i<aux2; i++) {
                (*itl).clear();
                itl=L_dq.erase(itl);
                itl--;
            }
        }
        if(aux>0) {
            if(inicio==0) {
                final=final-(aux%TAM_BLQ);
            }
            else {
                aux2=(final-(aux%TAM_BLQ));
                if(aux2<0) { //si deque tiene dos bloques
                    cout<<"aa"<<endl;
                    itl=L_dq.end();
                    itl--;//accedemos al ultimo vector.
                    (*itl).clear();
                    itl=L_dq.erase(itl);//eliminamos el ultimo bloque
                    final=TAM_BLQ+aux2;//+ ya qeu aux2 es negativo
                }
                else {
                    final=inicio+(n%TAM_BLQ);

                }

            }
        }
    }
    tama=n;
}
template<typename T>
typename deque<T>::iterator deque<T>::insert(typename deque<T>::iterator & pos, const T & t) {

    typename deque<T>::iterator it1;
    typename deque<T>::iterator it2;
    T aux;

    bool principio= false;//para comprobar si el bloque donde esta pos, esta mas cerca del principio o del final.
    typename list<vector<T> >::iterator itl=L_dq.begin();//iterador a la lista
    typename deque<T>::iterator it(pos);
    int contador=0,tamalista=(tama/TAM_BLQ)+1;//numero aproximado de bloques
    while(it.it_l!=itl) {
        contador++;
        ++itl;
    }
    if(tamalista-contador>=contador)//mas cerca del principio
        principio=true;

    if(principio) {
        push_front(t);//incrmenta tamaño e inicio
        it1=begin();
        it2=it1;
        ++it2;//representa el elemento siguiente a it1
        while(it2!=pos) {
            aux=*it1;//
            *it1=*it2;//swap
            *it2=aux;//
            ++it1;
            ++it2;
        }
    }
    else {
        push_back(t);//incrmenta tamaño y final
        it1=end();
        --it1;//it representa el elemento añadido.
        it2=it1;
        while(it1!=pos) {
            --it2;//it2 represneta el elemento anterior a it1
            aux=*it1;//
            *it1=*it2;//swap
            *it2=aux;//
            --it1;
        }
    }
    return it1;
}


template<typename T>
typename deque<T>::iterator deque<T>::erase(typename deque<T>::iterator & pos) {
    typename deque<T>::iterator it1;
    typename deque<T>::iterator it2;
    T aux;
    it1=pos;
    it2=it1;

    bool principio= false;//para comprobar si el bloque donde esta pos, esta mas cerca del principio o del final.
    typename list<vector<T> >::iterator itl=L_dq.begin();//iterador a la lista
    typename deque<T>::iterator it(pos);
    int contador=0,tamalista=(tama/TAM_BLQ)+1;//numero aproximado de bloques
    while(it.it_l!=itl) {
        contador++;
        ++itl;
    }
    if(tamalista-contador>=contador)//mas cerca del principio
        principio=true;


    if(principio) {
        while(it1!=begin()) {
            --it2;
            aux=*it1;//
            *it1=*it2;//swap
            *it2=aux;//
            --it1;
        }
        pop_front();//modifica tamaño e inicio
    }

    else {
        ++it2;//representa el elemento siguiente a it1
        while(it2!=end()) {
            aux=*it1;//
            *it1=*it2;//swap
            *it2=aux;//
            ++it1;
            ++it2;
        }
        pop_back();//incrmenta tamaño e inicio
    }
    it1=pos;
    return ++it1;



}
template<typename T>
void deque<T>::cheq_rep( ) const { 
     assert(inicio>=0 && inicio<=9 && final>=0 && final<=10);
		
     typename list<vector<T> >::iterator itl=L_dq.begin();
     for(itl=L_dq.begin();itl!=L_dq.end();itl++){
	assert((*itl).size()==10);	
     }

}


//-------------------------------------------------------------------------------------------------
//metodos iterator

template<typename T>
deque<T>::iterator::iterator() {//constructor por defecto
}


template<typename T>
deque<T>::iterator::iterator(const typename deque<T>::iterator & it) {//constructor de copia
    it_v=it.it_v;
    it_l=it.it_l;
}

template<typename T>
T & deque<T>::iterator::operator*() {
    return *it_v;
}
template<typename T>
typename deque<T>::iterator & deque<T>::iterator::operator++() {
    typename vector<T>::iterator itv((*this).it_v);
    if((++itv)==(*it_l).end()) { //si es el final del vector
        it_l++;
        it_v=(*it_l).begin();
    }
    else {
        it_v++;
    }
    return *this;
}


template<typename T>
typename deque<T>::iterator & deque<T>::iterator::operator--() {
    if(it_v==(*it_l).begin()) { //si esta al principio dedel vector
        it_l--;
        it_v=(*it_l).end();
        it_v--;
    }
    else {
        it_v--;
    }

    return *this;
}


template<typename T>
typename deque<T>::iterator & deque<T>::iterator::operator=(const typename deque<T>::iterator &it) {
    if(this!=&it) {
        it_v = it.it_v;
        it_l = it.it_l;
    }
    return *this;
}


template<typename T>
bool deque<T>::iterator::operator==(const typename deque<T>::iterator &it) const  {
    return (it_v==it.it_v  &&  it_l==it.it_l) ;
}

template<typename T>
bool deque<T>::iterator::operator!=(const typename deque<T>::iterator &it) const {
    return (it_v!=it.it_v  ||  it_l!=it.it_l) ;
}




//-------------------------------------------------------------------------------------------------
//metodos const_iterator

template<typename T>
deque<T>::const_iterator::const_iterator() {//constructor por defecto
}


template<typename T>
deque<T>::const_iterator::const_iterator(const typename deque<T>::const_iterator & it) {//constructor de copia
    it_v=it.it_v;
    it_l=it.it_l;
}

template<typename T>
const T & deque<T>::const_iterator::operator*() {
    return *it_v;
}
template<typename T>
typename deque<T>::const_iterator & deque<T>::const_iterator::operator++() {
    typename vector<T>::const_iterator itv((*this).it_v);
    if((++itv)==(*it_l).end()) { //si es el final del vector
        it_l++;
        it_v=(*it_l).begin();
    }
    else {
        it_v++;
    }
    return *this;
}


template<typename T>
typename deque<T>::const_iterator & deque<T>::const_iterator::operator--() {
    if(it_v==(*it_l).begin()) { //si esta al principio dedel vector
        it_l--;
        it_v=(*it_l).end();
        it_v--;
    }
    else {
        it_v--;
    }

    return *this;
}


template<typename T>
typename deque<T>::const_iterator & deque<T>::const_iterator::operator=(const typename deque<T>::const_iterator &it) {
    if(this!=&it) {
        it_v = it.it_v;
        it_l = it.it_l;
    }
    return *this;
}


template<typename T>
bool deque<T>::const_iterator::operator==(const typename deque<T>::const_iterator &it) const  {
    return (it_v==it.it_v  &&  it_l==it.it_l) ;
}

template<typename T>
bool deque<T>::const_iterator::operator!=(const typename deque<T>::const_iterator &it) const {
    return (it_v!=it.it_v  ||  it_l!=it.it_l) ;
}




