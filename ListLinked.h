#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
	    Node<T>* first;
	    int n;
    public:
	    ListLinked(){
		    first = nullptr;
		    n = 0;
	    }
	    ~ListLinked(){
		    while(first != nullptr){
		    Node<T>* aux = first->next;
		    delete first;
		    first = aux;
		    }
	    }
	    T operator[](int pos){
		    if (pos < 0 || pos > n-1){
			    throw std::out_of_range("Posicion no valida");
		    }
		    int i = 0;
		    Node<T>* aux = first;
		    while(i!=pos){
			    aux = aux->next;
			    i++;
		    }
		    return aux->data;
	    }
	    friend std::ostream& operator<<(std::ostream &out, ListLinked &list){
		    out << "List => [";
		    if (list.n > 0){
			    out << "\n";
			    Node<T>* aux = list.first;
			    while (aux != nullptr){
				    out << "  " << aux->data << "\n";
				    aux = aux->next;
			    }
		    }
		    out << "]";
		    return out;
	    }
	void insert(int pos, T e) override{
		if (pos < 0 || pos > n){
			throw std::out_of_range("Posicion no valida");
		}
		int i = 0;
		//iterar hasta la posicion
		if(pos==0){
			Node<T>* nuevo = new Node<T>(e,first);
			first = nuevo;
			n++;
		}
		else{
			Node<T>* prev = first;
		    	while(i!=pos-1){
			    	prev = prev->next;
			    	i++;
				}
				Node<T>* nuevo = new Node<T>(e,prev->next);
			prev->next = nuevo;
			n++;
		}
	}
	void append(T e) override{
		insert(n,e);
	}
	void prepend(T e) override{
		insert(0,e);
	}
	T remove(int pos) override{
		if (pos < 0 || pos >= n){
			throw std::out_of_range("Posicion no valida");
		}
		int i = 0;
		//iterar hasta la posicion
		if(pos==0){
			T dato = first->data;
			Node<T>* post = first->next;
			delete first;
			first = post;
			n--;
			return dato;
		}
		else{
			Node<T>* prev = first;
		    	while(i!=pos-1){
			    	prev = prev->next;
			    	i++;
				}
			Node<T>* to_delete = prev->next;
			T dato = to_delete->data;
			prev->next = to_delete->next;
			delete to_delete;
			n--;
			return dato;
		}
	}
	T get(int pos) override{
		if (pos < 0 || pos > n-1){
			throw std::out_of_range("Posicion no valida");
		}
		Node<T>* aux = first;
		int i = 0;
		while(i!=pos){
			aux = aux->next;
			i++;
		}
		return aux->data;
	}
	int search(T e) override{
		Node<T>* aux = first;
		int i = 0;
		while(i<n && n!=0){
			if(aux->data==e){
				return i;
			}
			aux = aux->next;
			i++;
		}
		return -1;
	}
	bool empty() override{
		if(n==0){
			return true;
		}
		else{
			return false;
		}
	}
	int size() override{
		return n;
	}
};

#endif // LIST_LINKED_H
