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
	char nome[10];

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

void adicionarEP(Plylist playlist);
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
	adicionarPodcast(playlist);
	adicionarPodcast(playlist);
	adicionarPodcast(playlist);
	mostrar(playlist);
	adicionarEP(playlist);
	mostrar(playlist);

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
		printf_s("A Playlist está vazia \n");
		return;
	}

	//imprime todos os episdodios de todos os podcasts contidos na playlist
	ListaPodcast* auxListPodCst = playlist->listPodcast;

	//checa se so existe um podcast na playlist
	if (auxListPodCst->inicio == auxListPodCst->ultimo) {
		Podcst auxPodcast = auxListPodCst->inicio;
		ListaEp* auxListaEp = auxPodcast->listEpisodios;

		if (auxListaEp->inicio == NULL) {
			printf("Podcast: %s esta vazio \n", auxPodcast->nome);
			return;
		}

		Ep auxEp = auxListaEp->inicio;

		printf("Podcast: %s \n", auxPodcast->nome);

		//O podcast so tem um episodio
		if (auxEp == auxListaEp->ultimo) {
			printf_s("Ep. %d | ", auxEp->id);
			printf("\n");
			auxEp = auxListaEp->ultimo;
		}

		for (; auxEp != auxListaEp->ultimo; auxEp = auxEp->prox) {
			printf_s("Ep. %d | ", auxEp->id);
		}
		return;
	}

	for (Podcst auxPodcast = auxListPodCst->inicio; auxPodcast != NULL; auxPodcast = auxPodcast->prox) {
		if (auxPodcast == NULL) return;
		ListaEp* auxListaEp = auxPodcast->listEpisodios;
		
		//checa se o podcast está vazio, se sim avisa
		if (auxListaEp->inicio == NULL) {
			printf("Podcast: %s esta vazio \n", auxPodcast->nome);
		}
		else {
			Ep auxEp = auxListaEp->inicio;

			printf("Podcast: %s \n", auxPodcast->nome);

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
}

/**
 * @brief Função que cria um nó generico
 * @param inicio -> nó que representa a cabeça da lista
 * @return Retorna o Episodio generico criado
 */
Ep criarEp() {
	Ep novo = (Ep)malloc(sizeof(Ep));

	printf("Entre com o id do novo ep:");
	scanf_s("%d", &novo->id);

	novo->prev = NULL;
	novo->prox = NULL;
	return novo;
}

/**
 * @brief Função que adiciona um episodio a Playlsist
 * @param Playlist -> Lista que representa a playlist
 * @param Podcast -> Pocast a qual o episodio criado faz parte
 */
void adicionarEP(Plylist playlist) {
	Ep novo = criarEp();
	
	//a qual podcasta dicionar
	ListaPodcast* auxListaPodcast = playlist->listPodcast;
	//corre pela lista até achar o podcast correto
	Podcst auxPodast = auxListaPodcast->inicio;

	//Adciona ao podcast
	ListaEp* auxListaEp = auxPodast->listEpisodios;
	if (auxListaEp->inicio != NULL) novo->prox = auxListaEp->inicio;
	if (auxListaEp->ultimo == NULL) auxListaEp->ultimo = novo;
	auxListaEp->inicio = novo;
}

/**
* @brief Função para adicionar um podcasta a playlist
* @param Playlist -> Playlist onde o podcast sera incerido
*/
void adicionarPodcast(Plylist playlist) {
	Podcst novo = (Podcst)malloc(sizeof(Podcast));

	printf("Entre com o nome do Podcast:");
	scanf_s("%s", &novo->nome, 10);

	ListaEp* eps = (ListaEp*)malloc(sizeof(ListaEp));
	eps->inicio = NULL;
	eps->ultimo = NULL;

	novo->listEpisodios = eps;

	ListaPodcast* listaPodcast = playlist->listPodcast;

	//se a lista estiver vazia
	if (listaPodcast->inicio == NULL) {
		listaPodcast->inicio = novo;
		listaPodcast->ultimo = novo;
		return;
	}

	novo->prox = listaPodcast->inicio;
	listaPodcast->inicio = novo;
}

