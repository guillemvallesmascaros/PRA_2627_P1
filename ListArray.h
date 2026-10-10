#include "List.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class ListArray : public List<T>{
	private:
		T* arr;
		int max;
		int n;
		static const int MINSIZE = 2;
		void resize(int new_size){
			// Crear array
			T* new_arr = new T[new_size];
			// copiar contenidos del array viejo al nuevo
			for(int i = 0;i<n;i++){
				new_arr[i] = arr[i];
			}
			// liberar recursos de memoria
			delete[] arr;
			// actualizar el puntero
			arr = new_arr;
			// actualizar max
			max = new_size;
		}
	public:
		ListArray(){
			arr = new T[MINSIZE];
			max = MINSIZE;
			n = 0;
		}
		~ListArray() override{
			delete[] arr;
		}
		T operator[](int pos){
			if (pos < 0 || pos >= n){
				throw std::out_of_range("Posicion no valida");
			}
			return arr[pos];
		}
		friend std::ostream&operator<<(std::ostream &out, ListArray<T> &list){
			out << "List => [";
			if (list.n > 0){
				out << "\n";
				for (int i = 0; i < list.n; i++){
					out << "  " << list.arr[i] << "\n";
				}
			}
			out << "]";
			return out;
		}
		void insert(int pos, T e) override{
			if (pos < 0 || pos > n){
				throw std::out_of_range("Posicion no valida");
			}
			// comprobar si esta lleno
			if (n == max){
				resize(max*2);
			}
			// mover los elementos del array
			for(int i = n;i>pos;i--){
				arr[i] = arr[i-1];
			}
			// colocar e en pos
			arr[pos] = e;
			// incrementar el numero de elementos en la lista
			n++;

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
			T elem = arr[pos];
			for(int i=pos;i<n-1;i++){
				arr[i] = arr[i+1];
			}
			n--;
			return elem;
		}
		T get(int pos) override{
			if (pos < 0 || pos >= n){
				throw std::out_of_range("Posicion no valida");
			}
			return arr[pos];
		}
		int search(T e) override{
			for(int i = 0;i<n;i++){
				if(arr[i]==e){
					return i;
				}
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
