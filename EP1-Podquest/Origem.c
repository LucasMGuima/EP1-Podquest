#include <stdlib.h>
#include <stdio.h>

typedef struct episodio {
	int id;
	int numeroEp;

	struct Episodio* prox;
	struct Episodio* prev;
}Episodio;

typedef struct listaEp {
	struct Episodio* inicio;
	struct Episodio* ultimo;
}ListaEp;

typedef struct podcast{
	//nome do podcast vai ser uma string futuramente
	int nome;

	struct Podcast* prox;
	struct Podcast* prev;

	//lista contendo os episodios do podcast
	struct ListaEp* listEpisodios;
}Podcast;

typedef struct listPodcast {
	struct Podcast* inicio;
	struct Podcast* ultimo;
}ListaPodcast;

typedef struct playlist {
	struct ListaPodcast* listPodcast;
}Playlist;

typedef Episodio* Ep;
typedef Podcast* Podcst;
typedef Playlist* Plylist;

void adicionarEP(Plylist playlist, Podcst podcast);
void adicionarPodcast(Plylist playlist);
void remover(int id);
void tocar();
void shuffle();
void proximo();
void mostrar(Plylist playlist);

Ep criarEp();
Plylist criarPlaylist();

int main() {
	Plylist playlist = criarPlaylist();

	return 0;
}

/**
* @brief Cria uma playliste vazia
* @return Playlist vazia
*/
Plylist criarPlaylist() {
	Plylist playlist = (Plylist)malloc(sizeof(Plylist));
	ListaPodcast* auxLista = (ListaPodcast*)malloc(sizeof(ListaPodcast));
	auxLista->inicio = NULL;
	auxLista->ultimo = NULL;
	playlist->listPodcast = auxLista;
	return playlist;
}

/**
* @brief Mostra o conteudo dos elementos da lista, se estiver vazia escreve na tela que a playlist está vazia
* @param Playlist -> Lista que representa a playlist
*/
void mostrar(Plylist playlist) {
	//playlist esta fazia
	if (playlist->listPodcast == NULL) {
		printf_s("A Playlist está vazia");
		return;
	}

	//imprime todos os episdodios de todos os podcasts contidos na playlist
	ListaPodcast* auxListPodCst = playlist->listPodcast;
	for (Podcst auxPodcast = playlist->listPodcast; auxPodcast != auxListPodCst->ultimo; auxPodcast = auxPodcast->prox) {
		ListaEp* auxListaEp = auxPodcast->listEpisodios;
		Ep auxEp = auxListaEp->inicio;
		
		printf("Podcast: %d \n", auxPodcast->nome);
		
		//O podcast so tem um episodio
		if (auxEp == auxListaEp->ultimo) {
			printf_s("Ep. %d | ", auxEp->id);
			printf("\n");
			auxEp = auxListaEp->ultimo;
		}

		for (; auxEp != auxListaEp->ultimo; auxEp = auxEp->prox) {
			printf_s("Ep. %d | ", auxEp->id);
		}
		printf("\n");
	}
}

/**
 * @brief Função que cria um nó generico
 * @param inicio -> nó que representa a cabeça da lista
 * @return Retorna o Episodio generico criado
 */
Ep criarEp() {
	Ep novo = (Ep)malloc(sizeof(Ep));
	novo->prev = NULL;
	novo->prox = NULL;
	return novo;
}

/**
 * @brief Função que adiciona um episodio a Playlsist
 * @param Playlist -> Lista que representa a playlist
 * @param Podcast -> Pocast a qual o episodio criado faz parte
 */
void adicionarEP(Plylist playlist, Podcst podcast) {
	Ep novo = criarEp();
	novo->id = rand();
	
	//Adciona ao podcast
	ListaEp* auxListaEp = podcast->listEpisodios;
	if (auxListaEp->inicio != NULL) novo->prox = auxListaEp->inicio;
	if (auxListaEp->ultimo == NULL) auxListaEp->ultimo = novo;
	auxListaEp->inicio = novo;
}

/**
* @brief Função para adicionar um podcasta a playlist
* @param Playlist -> Playlist onde o podcast sera incerido
*/
void adicionarPodcast(Plylist playlist) {

}

