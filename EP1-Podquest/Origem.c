#include <stdlib.h>
#include <stdio.h>

typedef struct podcast {
	int id;
	int numeroEp;

	struct Podcast* prox;
	struct Podcast* prev;
}Podcast;

typedef Podcast* Episodio;

void adicionar();
void remover(int id);
void tocar();
void shuffle();
void proximo();

Episodio criarEp(Episodio inicio);
void criarPlaylist(Episodio inicio);
void mostrar(Episodio inicio);

int main() {
	Episodio inicio = (Episodio)malloc(sizeof(Episodio));
	inicio->prev = NULL;
	inicio->prox = NULL;

	criarPlaylist(inicio, 70);
	mostrar(inicio);

	return 0;
}

/**
* @brief Cria uma playliste com n elementos usando inicio como cabeça
* @param inicio -> nó que representa o inicio da lista
* @param elemento -> quantida de elementos da lista
*/
void criarPlaylist(Episodio inicio, int elementos) {
	for (int i = 0; i < elementos; i++) {
		int num = (rand()+i)/elementos;
		adicionar(inicio, num);
	}
}

/**
* @brief Mostra o conteudo dos elementos da lista
* @param inicio -> nó que representa o inicio da lista
*/
void mostrar(Episodio inicio) {
	Episodio aux = inicio->prox;
	while (aux->prox != NULL) {
		printf_s("%d ",aux->id);
		aux = aux->prox;
	}
}

/**
 * @brief Função que cria um nó generico
 * @param inicio -> nó que representa a cabeça da lista
 * @return Retorna o Episodio generico criado
 */
Episodio criarEp(Episodio inicio) {
	Episodio novo = (Episodio)malloc(sizeof(Episodio));
	novo->prev = NULL;
	novo->prox = NULL;
	return novo;
}

/**
 * @brief Função que adiciona um episodio a Playlsist
 * @param inicio -> nó que representa a cabeça da lista
 * @param id -> numero do ID do episodio
 */
void adicionar(Episodio inicio, int id) {
	Episodio novo = criarEp(inicio);
	novo->id = id;
	if (inicio->prox == NULL) { //se a lista esta vazia
		inicio->prox = novo;
		return;
	}
	novo->prox = inicio->prox;
	inicio->prox = novo;
}

