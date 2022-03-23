#include <stdlib.h>
#include <stdio.h>

typedef struct podcast {
	int id;
	int numeroEp;

	struct Podcast* prox;
	struct Podcast* prev;
}Podcast;

typedef Podcast* Episodio;

typedef struct lista {
	struct Episodio* inicio;
	struct Episodio* ultimo;
}Lista;

typedef Lista* Playlist;

void adicionar(Playlist playlist);
void remover(int id);
void tocar();
void shuffle();
void proximo();

Episodio criarEp(Episodio inicio);
Playlist criarPlaylist();
void mostrar(Playlist playlist);

int main() {
	Playlist playlist = criarPlaylist();
	adicionar(playlist);
	adicionar(playlist);
	adicionar(playlist);
	mostrar(playlist);

	return 0;
}

/**
* @brief Cria uma playliste vazia
* @return Playlist vazia
*/
Playlist criarPlaylist() {
	Playlist playlist = (Playlist)malloc(sizeof(Playlist));
	playlist->inicio = NULL;
	playlist->ultimo = NULL;
	return playlist;
}

/**
* @brief Mostra o conteudo dos elementos da lista, se estiver vazia escreve na tela que a playlist está vazia
* @param Playlist -> Lista que representa a playlist
*/
void mostrar(Playlist playlist) {
	//playlist esta fazia
	if (playlist->inicio == NULL) {
		printf_s("A Playlist está vazia");
		return;
	}

	Episodio aux = playlist->inicio;
	//a lista so tem um elemento
	if (aux->prox == NULL) {
		printf_s("%d |", aux->id);
		return;
	}

	//a lista tem mais de um elemento
	do {
		printf_s("%d |",aux->id);
		aux = aux->prox;
	} while (aux != NULL);
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
 * @param Playlist -> Lista que representa a playlist
 */
void adicionar(Playlist playlist) {
	Episodio novo = criarEp(playlist->inicio);
	novo->id = rand();
	if (playlist->inicio == NULL) { //se a lista esta vazia
		playlist->inicio = novo;
		return;
	}
	novo->prox = playlist->inicio;
	playlist->inicio = novo;
}

