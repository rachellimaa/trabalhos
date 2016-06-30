#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<values.h>
using namespace std;
#define VALOR_INICIAL -1

struct ListaPrior{
   int *vet;
   int tam;
};

struct vertice{
   int num;
   int peso;
   vertice *prox;
};

struct listaadj{
   vertice *listav;
};

int Pai(int x);
void inserirListaPrior(ListaPrior &lista, int num, int dist[], int tam);
void heap_fica(ListaPrior &lista, int i, int qtde, int dist[]);
void constroiheap(ListaPrior &lista, int dist[]);
int remover(ListaPrior &lista, int dist[]);
void relax(int u, int v, int peso, int pai[], int dist[]);
void dijkstra(listaadj Adj[], int tam, int v, int pai[], int dist[]);
void menorCaminho(int verticeOrigem, int verticeDestino,int caminho[], int pai[]);
void menorCaminho2(int verticeOrigem, int verticeDestino,int caminho[], int pai[]);

int main(){

   /** vetor que armazena se vertice for marcado **/
   int *marcado;

   /** antecessor dos vértices no caminoh mínimo **/
   int *pai;

   /** distância mínima em relação à origem **/
   int *dist;

   /** lista de adjacencias entre vertices **/
   listaadj *Adj = NULL;

   /** faça o simples **/
   int *caminho;
   //int tamanhoCaminho=0;

   vertice *novo;

   int numeroVertice, /** número de vértice do grafo == antigo tam **/
   numeroAresta, /** número de aresta do grafo == tamAresta **/
   verticeInicial, /** vertice de origem na aresta == org **/
   verticeFinal, /** vertice destino na aresta == dest **/
   verticeOrigem = 0, /** vertice de origem do caminho minimo == num **/
   verticeDestino = 0, /** vertice de destino do caminho minimo == numDest **/
   distIni =0, distFim =0,
   peso = 0; /** peso da aresta do grafo **/


   cin >> numeroVertice >> numeroAresta;
   fflush(stdin);

   /** alocação de memória **/
   Adj = new listaadj[numeroVertice];
   marcado = new int [numeroVertice];
   pai = new int[numeroVertice];
   dist = new int [numeroVertice];
   caminho = new int[numeroVertice];

   /** incicialização de variáveis **/
   for( int i = 0; i < numeroVertice; i++){
       marcado[i] = 0;
       Adj[i].listav = NULL;
       caminho[i] = 0;
   }

   /** **/
   for(int j = 1; j <= numeroAresta; j++){

      cin >> verticeInicial >> verticeFinal >> peso;
      fflush(stdin);

      /** alocando um nó com o valor do vértice destino para colocar
         na entrada do vertice de origem da lista de adjacencias -->(u,v)
      **/
      novo = new vertice();
      novo->num = verticeFinal;
      novo->peso = peso;

      /** inserindo vertice adjacente a vertice org na lista de adjacencia **/
      novo->prox = Adj[verticeInicial].listav;
      Adj[verticeInicial].listav = novo;


      /** inserindo (v,u) **/
      novo = new vertice();
      novo->num = verticeInicial;
      novo->peso = peso;

      /* inserindo vertice adjacente a vertice org na lista de adjacencia */
      novo->prox = Adj[verticeFinal].listav;
      Adj[verticeFinal].listav = novo;

   } /** fim inicializacao **/

   cin >> verticeOrigem; cin >> verticeDestino;

   for(int i = 0; i < numeroVertice; i++){
       marcado[i] = 0;
       dist[i] = 0;
   }


   //mostrar_Adj(Adj, tam);
   dijkstra(Adj, numeroVertice, verticeOrigem, pai, dist);
   distIni = dist[verticeDestino];
   dijkstra(Adj, numeroVertice, verticeDestino, pai, dist);
   distFim = dist[verticeOrigem];

   if(distIni <= distFim){
        dijkstra(Adj, numeroVertice, verticeOrigem, pai, dist);
        menorCaminho(verticeOrigem, verticeDestino,caminho,pai);
   }else{
        dijkstra(Adj, numeroVertice, verticeDestino, pai, dist);
        menorCaminho2(verticeDestino, verticeOrigem,caminho,pai);
   }

} /** fim main **/

/********************* Pai ******************************/
int Pai(int x){
   return x/2;
}
/********************************************************/

/********************* inserir ListaPrior  ******************************/
void inserirListaPrior(ListaPrior &lista, int num, int dist[], int tam){

   int ind;

   if(lista.tam < (tam-1)){
       lista.tam++;
       ind = lista.tam;

       while(ind > 0 && dist[lista.vet[Pai(ind)]] > dist[num]){
           lista.vet[ind] = lista.vet[Pai(ind)];
           ind = Pai(ind);
       }
       lista.vet[ind] = num;
   }
}
/************************************************************************/

/********************* heap_fica ***********************************/
void heap_fica(ListaPrior &lista, int i, int qtde, int dist[]){

   int f_esq, f_dir, menor, aux;

   menor = i;

   if(2*i + 1 <= qtde){ /** if 1 **/

      /** o nó que está sendo analisado tem filhos p/ esquerda e direita **/
      f_esq = 2*i;
      f_dir = 2*i+1;

      if( dist[lista.vet[f_esq]] < dist[lista.vet[f_dir]] && dist[lista.vet[f_esq]] < dist[lista.vet[i]] ){ /** if 2 **/
          menor = 2*i;
      }else{

         if( dist[lista.vet[f_dir]] < dist[lista.vet[f_esq]] && dist[lista.vet[f_dir]] < dist[lista.vet[i]]){ /** if 3 **/
             menor = 2*i+1;
         }

      }/** if 2 **/
   }else{

      if(2*i <= qtde){ /** if 4 **/

         /** o nó que está sendo analisado tem filho apenas para a esquerda **/
         f_esq = 2*i;

         if(dist[lista.vet[f_esq]] < dist[lista.vet[i]]){ /** if 5 **/
             menor = 2*i;
         } /** if 5 **/

      }
   } /** if 1 **/

   if(menor != i){
      aux = lista.vet[i];
      lista.vet[i] = lista.vet[menor];
      lista.vet[menor] = aux;
      heap_fica(lista, menor, qtde, dist);
   }
}
/*******************************************************************/

/********************* constroiheap ******************************/
void constroiheap(ListaPrior &lista, int dist[]){
   for( int i = (lista.tam)/2; i >= 0; i--)
     heap_fica(lista,i,lista.tam, dist);
}
/*******************************************************************/

/********************* remover *************************************/
int remover(ListaPrior &lista, int dist[]){
   if(lista.tam == 0)
       cout << "\nLista vazia!";
   else{
       int menor_prior = lista.vet[0];
       lista.vet[0] = lista.vet[lista.tam];
       lista.tam--;
       heap_fica(lista, 0, lista.tam, dist);
       return menor_prior;
   }
   return 0;
}
/*******************************************************************/

/************************ relax  ***********************************/
void relax(int u, int v, int peso, int pai[], int dist[]){

   if(dist[v] > (dist[u] + peso)){

       dist[v] = dist[u] + peso;
       pai[v] = u;
   }
}
//}
/*******************************************************************/

/*************************** Dijkstra ******************************/
void dijkstra(listaadj Adj[], int tam, int v, int pai[], int dist[]){
   //int MAXINT = 100000;
   int i, w;
   int *C = new int[tam];
   int tamC = 0;
   ListaPrior lista;

   lista.vet = new int [tam];
   lista.tam = -1;

   dist[v] = 0;
   inserirListaPrior(lista, v, dist, tam);

   for(i = 0; i < tam; i++){
       if(i != v){
           dist[i] = 10000;
           pai[i] = VALOR_INICIAL;
           inserirListaPrior(lista, i, dist, tam);
       }
   }

   while(lista.tam != 0){
       w = remover(lista, dist);/** eu acho que é esse w **/
       C[tamC] = w;
       tamC++;

       vertice *x = Adj[w].listav;

       while(x != NULL){
          // relax (w,x,peso_wx)
          relax(w,x->num,x->peso, pai, dist);

          // proximo vizinho de w
          x = x->prox;
       }
       constroiheap(lista, dist);
   }
}
/*******************************************************************/

void menorCaminho(int verticeOrigem, int verticeDestino,int caminho[], int pai[]){

   int aux = verticeDestino;
   int aux2 = 0;
   int tamanhoCaminho = 0;
   caminho[tamanhoCaminho] = verticeDestino;
   tamanhoCaminho++;

   while(pai[aux] != verticeOrigem ){
      caminho[tamanhoCaminho] = pai[aux];
      tamanhoCaminho++;
      aux = pai[aux];
   }
   caminho[tamanhoCaminho] = verticeOrigem;
   tamanhoCaminho++;

   aux2 = tamanhoCaminho-1;
   for(int p = tamanhoCaminho-1; p >= 0; p--){

       if(aux2 == tamanhoCaminho-1){
          cout << caminho[p];
          aux2 = -10;
       }else
          cout << " " << caminho[p];

   }
}

void menorCaminho2(int verticeOrigem, int verticeDestino,int caminho[], int pai[]){

   int aux = verticeDestino;
   int aux2 = 0;
   int tamanhoCaminho = 0;
   caminho[tamanhoCaminho] = verticeDestino;
   tamanhoCaminho++;

   while(pai[aux] != verticeOrigem ){
      caminho[tamanhoCaminho] = pai[aux];
      tamanhoCaminho++;
      aux = pai[aux];
   }
   caminho[tamanhoCaminho] = verticeOrigem;
   tamanhoCaminho++;

   aux2 = tamanhoCaminho-1;
   for(int p = 0; p < tamanhoCaminho; p++){

       if(aux2 == tamanhoCaminho-1){
          cout << caminho[p];
          aux2 = -10;
       }else
          cout << " " << caminho[p];

   }
}

