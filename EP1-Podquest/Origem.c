#include <stdlib.h>
#include <stdio.h>

typedef struct episodio {
	int id;

	struct Episodio* prox;
	struct Episodio* prev;
}Episodio;

typedef struct listaEp {
	struct Episodio* inicio;
	struct Episodio* ultimo;
}ListaEp;

typedef struct podcast{
	int id;
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
	int tamanho;

	struct ListaPodcast* listPodcast;
}Playlist;

typedef struct epAtual{
	struct Episodio* episodio;
	struct Podcast* podcast;
}EpAtual;

typedef Episodio* Ep;
typedef Podcast* Podcst;
typedef Playlist* Plylist;
typedef EpAtual* EpisoidoAtual;

void adicionarEP(Plylist playlist);
void adicionarPodcast(Plylist playlist);
void remover(Plylist playlist);
void tocar(EpisoidoAtual EpAtual, Plylist playlist);
void shuffle();
void proximo();
void mostrar(Plylist playlist);

void Menu(Plylist playlist);

Ep criarEp();
Plylist criarPlaylist();

int main() {
	Plylist playlist = criarPlaylist();
	Menu(playlist);
	return 0;
}

/*
*	@brief Escreve o menu de opções na tela
*/
void Menu(Plylist playlist) {
	int op = -1;
	EpisoidoAtual EpAtual = (EpisoidoAtual)malloc(sizeof(EpisoidoAtual));
	EpAtual->episodio = NULL;
	EpAtual->podcast = NULL;

	while (op != 0) {
		printf("------PODQUEST-------\n");
		printf("1. Add Podcast\n");
		printf("2. Add Episodio\n");
		printf("3. Remover Episodio\n");
		printf("4. Mostrar Playlist\n");
		printf("5. Tocar\n");
		printf("0. Fechar\n");
		printf("---------------------\n");
		printf("Entre com o numero da opcao: ");
		scanf_s("%d", &op);

		//Swith da opção
		switch (op)
		{
			//Adciona um podcast
			case 1:
				adicionarPodcast(playlist);
				break;
			//Adicona um ep
			case 2:
				adicionarEP(playlist);
				break;
			//Remove um ep
			case 3:
				remover(playlist);
				break;
			//Mostra todas os Podcasts e seus épisodios
			case 4:
				mostrar(playlist);
				break;
			case 5:
				tocar(EpAtual, playlist);
				break;
		}

	}
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
	playlist->tamanho = 0;
	return playlist;
}

/**
* @brief Mostra o conteudo dos elementos da lista, se estiver vazia escreve na tela que a playlist está vazia
* @param Playlist -> Lista que representa a playlist
*/
void mostrar(Plylist playlist) {
	//imprime todos os episdodios de todos os podcasts contidos na playlist
	ListaPodcast* auxListPodCst = playlist->listPodcast;

	//playlist esta fazia
	if (auxListPodCst->inicio == NULL) {
		printf_s("A Playlist esta vazia \n");
		return;
	}

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
			auxEp = auxListaEp->ultimo;
		}

		for (; auxEp != NULL; auxEp = auxEp->prox) {
			printf_s("Ep. %d | ", auxEp->id);
		}
		printf("\n");
		return;
	}

	for (Podcst auxPodcast = auxListPodCst->inicio; auxPodcast != NULL; auxPodcast = auxPodcast->prox) {
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
				auxEp = auxListaEp->ultimo;
			}

			for (; auxEp != NULL; auxEp = auxEp->prox) {
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

	printf("Entre com o numero do novo ep:");
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
	int idPodcast;
	printf("Entre com o id do podcast a adicionar: ");
	scanf_s("%d", &idPodcast);

	//corre pela lista até achar o podcast correto
	Podcst auxPodast = NULL;
	ListaPodcast* auxListaPodcast = playlist->listPodcast;
	for (Podcst podcast = auxListaPodcast->inicio; podcast != NULL; podcast = podcast->prox) {
		if (podcast->id == idPodcast) {
			auxPodast = podcast;
			break;
		}
	}

	if (auxPodast == NULL) {
		printf_s("Não foi pocivel achar o podcast de id %d", idPodcast);
		return;
	}

	//Adciona ao podcast
	ListaEp* auxListaEp = auxPodast->listEpisodios;
	if (auxListaEp->inicio != NULL) {
		Ep aux = auxListaEp->inicio;
		aux->prev = novo;
		novo->prox = aux;
	}
	if (auxListaEp->ultimo == NULL) {
		auxListaEp->ultimo = novo;
	}
	auxListaEp->inicio = novo;
}

/**
* @brief Função para adicionar um podcasta a playlist
* @param Playlist -> Playlist onde o podcast sera incerido
*/
void adicionarPodcast(Plylist playlist) {
	Podcst novo = (Podcst)malloc(sizeof(Podcast));
	novo->prox = NULL;
	novo->prev = NULL;
	
	//seta o id do Podcast de acordo com o tamanho da lista
	novo->id = playlist->tamanho;
	playlist->tamanho += 1;

	printf("Entre com o nome do Podcast:");
	scanf_s("%s", &novo->nome, 10);

	ListaEp* eps = (ListaEp*)malloc(sizeof(ListaEp));
	eps->inicio = NULL;
	eps->ultimo = NULL;

	novo->listEpisodios = eps;

	ListaPodcast* listaPodcast = playlist->listPodcast;

	printf_s("%s foi adicionado com id [%d]. \n", novo->nome, novo->id);
	//se a lista estiver vazia
	if (listaPodcast->inicio == NULL) {
		listaPodcast->inicio = novo;
		listaPodcast->ultimo = novo;		
		return;
	}

	Podcst auxIni = listaPodcast->inicio;
	auxIni->prev = novo;
	novo->prox = auxIni;
	listaPodcast->inicio = novo;
}

/*
*	@brief Remove um epísodio de um podcast especifico.
*	@param Playlist -> Playlist contem os Podcasts
*/
void remover(Plylist playlist) {
	int idPocast;
	int numEp;

	//Entra com os dados necessarios
	printf("Entre com o id do Podcast: ");
	scanf_s("%d", &idPocast);
	
	printf("Entre com o numero do Ep a ser removido: ");
	scanf_s("%d", &numEp);


	//percorre a playlist atras do podcast
	ListaPodcast* auxLista = playlist->listPodcast;

	//checa se a Playlist está vazia
	if (playlist->tamanho <= 0) {
		printf("A Playlist está vazia.\n");
		return;
	}

	for (Podcst podcast = auxLista->inicio; podcast != NULL; podcast = podcast->prox) {
		//é o podcast que procuramos
		if (podcast->id == idPocast) {
			//percorre o lista de episodios atras doq queremos remover
			ListaEp* auxListaEp = podcast->listEpisodios;

			//checa se a Lista de Episodio está vazia.
			if (auxListaEp->inicio == NULL) {
				printf("A lista de episodios está vazia.\n");
				return;
			}

			for (Ep episodio = auxListaEp->inicio; episodio != NULL; episodio = episodio->prox) {
				//é o episodio que procuramos
				if (episodio->id == numEp) {
					//remove o peisodio
					printf_s("Episódio %d do podcast %s removido!.\n", numEp, podcast->nome);
					//se o episodio é o unico da lista
					if (episodio->prox == NULL && episodio->prev == NULL) {
						auxListaEp->inicio = NULL;
						auxListaEp->ultimo = NULL;
						break;
					}

					//se o episodio é o ulimo da lista
					if (episodio == auxListaEp->ultimo) {
						Ep auxPrev = episodio->prev;
						auxPrev->prox = NULL;
						auxListaEp->ultimo = auxPrev;
						break;
					}

					Ep auxPrev = episodio->prev;
					Ep auxProx = episodio->prox;

					auxPrev->prox = auxProx;
					auxProx->prev = auxPrev;
					break;
				}
			}
			break;
		}
	}
}

/*
*	@brief Emprime na tela o episodio atual e a qual podcast pertence.
*	@param EpAtual -> Struct que guarda as informações do episodio atual
*	@param Playlist -> Playlist contem os Podcasts
*/
void tocar(EpisoidoAtual EpAtual, Plylist playlist) {
	ListaPodcast* podcasts = playlist->listPodcast;
	//se estiver nulo pega o primeiro elemento do primeiro podcast
	if (EpAtual->episodio == NULL) {
		//pega o primeiro podcasta da lista
		EpAtual->podcast = podcasts->inicio;

		//pega o primeiro episodio do podcast
		Podcast* auxPodcast = podcasts->inicio;
		ListaEp* auxListEp = auxPodcast->listEpisodios;
		Episodio* auxEpisodio = auxListEp->inicio;
		EpAtual->episodio = auxEpisodio;
	}

	//imprime na tela o podcasta q está tocando
	if (EpAtual->episodio != NULL) {
		Episodio* auxEp = EpAtual->episodio;
		Podcast* auxPodcast = EpAtual->podcast;
		printf_s("Estou no Ep. %d do Podcast: %s\na", auxEp->id, auxPodcast->nome);
	}
}


