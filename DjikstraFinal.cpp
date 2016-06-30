#include <iostream>
#define INFINITO 1000000

using namespace std;

class PrioridadeLista{
public:
    int tam;
    int *vet;
    int Pai(int);
    void PrioridadeListaInserir(PrioridadeLista &lista, int , int distancia[] , int);
    void imprimirLista(PrioridadeLista *lista);


};

int PrioridadeLista::Pai(int y){

return y/2;

}



void PrioridadeLista::PrioridadeListaInserir(PrioridadeLista &lista, int num, int distancia[], int tam){
     int indice;
        if(lista.tam < tam-1){
            lista.tam++;
            indice=lista.tam;
            while(indice>0 && distancia[lista.vet[Pai(indice)]] > distancia[num]){ //tava ind>1
                lista.vet[indice] = lista.vet[Pai(indice)];
                indice = Pai(indice);
                }
            lista.vet[indice] = num;
        }
}

void PrioridadeLista::imprimirLista(PrioridadeLista *lista){
    for(int i=0; i<=lista->tam; i++)
        cout<<" "<< lista->vet[i];
}


class Vertice{
public:
    int num;
    int peso;
    Vertice *prox;
};

class AdjLista{
public:
    Vertice *listavert;

};

class MinHeap{
public:
    void Heapify(PrioridadeLista &lista, int, int,int distancia[]);
    void MontandoHeap(PrioridadeLista &lista, int distancia[]);
    int remover(PrioridadeLista &lista,int distancia[]);
    void relaxamento(int, int , int, int parent[], int distancia[], int saida[], int *tamSaida, int c[], int,int);
    void MenorCaminhoDijkstra(AdjLista ListaAdj[], int , int , int parent[], int distancia[], int, int saida[], int * tamSaida );
    void MostrarAdjLista(AdjLista ListaAdj[], int);
    void MostrarDistancia(int, int, int distancia[]);
};


void MinHeap::Heapify(PrioridadeLista &lista,  int i, int qtd,int distancia[]){
       int EsqFilho, DirFilho, menor, aux;
    menor = i;
    if(2*i+1 <=qtd){//2
        EsqFilho = 2*i;
        DirFilho = 2*i+1;
        if(distancia[lista.vet[EsqFilho]] < distancia[lista.vet[DirFilho]] && distancia[lista.vet[EsqFilho]] < distancia[lista.vet[i]]){//3
            menor = 2*i;
        }//3.1
        //4
    else{ if(distancia[lista.vet[DirFilho]] < distancia[lista.vet[EsqFilho]] && distancia[lista.vet[DirFilho]] < distancia[lista.vet[i]] ){//5
            menor = 2*i+1;
        }//5.1
    }//4.1
//2.1     //6
    }else{ if(2*i <= qtd){//7
        EsqFilho = 2*i;
        if(distancia[lista.vet[EsqFilho]] < distancia[lista.vet[i] ]){//8
        menor = 2*i;
        }//8.1
    }//7.1

    }//6.1
    if(menor != i){//9
        aux = lista.vet[i];
        lista.vet[i] = lista.vet[menor];
        lista.vet[menor] = aux;
        Heapify(lista, menor, qtd, distancia);
        }


}

void MinHeap::MontandoHeap(PrioridadeLista &lista, int distancia[]){
        for(int i=lista.tam/2 ;i>=0 ; i--)

        Heapify(lista, i, lista.tam,distancia);


}

int MinHeap::remover(PrioridadeLista &lista, int distancia[]){

    if(lista.tam==0)
        cout<<"\nLista vazia!";
    else{
        int menorPrioridade = lista.vet[0];//tava 1
        lista.vet[0] = lista.vet[lista.tam]; // tava 1
        lista.tam--;
        Heapify(lista, 0, lista.tam,distancia);
        return menorPrioridade;

    }
    return 0;
}

void MinHeap::relaxamento(int u, int v, int peso, int parent[], int distancia[], int saida[], int *tamSaida, int c[], int DestVert, int tamC){
    if(distancia[v] > distancia[u] + peso){
        distancia[v] = distancia[u] + peso;
        parent[v] = u;

        }
}

void MinHeap::MenorCaminhoDijkstra(AdjLista ListaAdj[], int tam, int v, int parent[], int distancia[], int DestVert, int saida[], int * tamSaida ){
    int i, w;
    int *C = new int[tam];
    int tamC = 0;


    PrioridadeLista lista;

    lista.vet = new int [tam];
    lista.tam = -1;//tava 0

    distancia[v] = 0;


    PrioridadeLista *c = new PrioridadeLista();
    c->PrioridadeListaInserir(lista, v, distancia, tam);

    for(i=0; i<tam; i++){
       if(i!=v){
            distancia[i] = INFINITO;
            parent[i] = -1;

            c->PrioridadeListaInserir(lista, i, distancia, tam);
        }
    }

        while(lista.tam != 0){
        w = remover(lista, distancia);
        C[tamC] = w;
        tamC++;

        Vertice *x = ListaAdj[w].listavert;
        while(x!=NULL){

        relaxamento(w,x->num, x->peso,parent,distancia, saida, tamSaida, C,DestVert, tamC);
            x = x->prox;

        }

       MontandoHeap(lista,distancia);

    }
/*
            int aux = DestVert;//5
            int saidaV[1000];
            int r=0;
            int aux2=0;

            saidaV[r] = DestVert;//saidaV[0]=5
                r++;//1

            while(parent[aux] != v){//parent[5] != 0
                saidaV[r] = parent[aux];

                r++;

        aux = parent[aux];
        }

             saidaV[r] = v;
             r++;
             aux2=r-1;

        if(distancia[v]<=distancia[DestVert]){
            for(int h=r-1;h>=0;h--){
             if (aux2==r-1){
           cout<<saidaV[h];
                aux2=-10;
             }else{
            cout<<" "<<saidaV[h];
             }
    }
        }else
            for(int h=0;h<0;h++){
             if (aux2==r-1){
              cout<<saidaV[h];
                aux2=-10;
             }else{
             cout<<" "<<saidaV[h];
             }
    }*/

}

void MinHeap::MostrarAdjLista(AdjLista ListaAdj[], int tam){
    Vertice *v;
    for(int i=0; i<tam;i++){
       v=ListaAdj[i].listavert;
       cout<<"\nEntrada "<<i<<" ";
       while(v != NULL){
            cout<<"(" << i << "," << v->num << ")" <<" ";//<< v->peso<<" ";
            v = v->prox;

       }

    }
}

void MinHeap::MostrarDistancia(int tam, int orig, int distancia[]){

    cout<< "\nDistancia da origem " << orig << " para os demais vertices\n";

     for(int i=0; i< tam; i++)

        cout<<"\n Vertice " << i << " - " << distancia[i];


}


int main(){

    int *marcado;
    int *parent;
    int *distancia;


    AdjLista *ListaAdj;
    Vertice *novo;

    int *saida;
    int tamSaida;

    int tam, org, dest, OrigemVert=0, peso=0, arestaa, cont=0;

    cin>> tam >> arestaa;
   // fflush(stdin);

        ListaAdj = new AdjLista[tam];
        marcado = new int [tam];

        parent = new int[tam];
        distancia = new int [tam];

        saida = new int[tam];

        for(int i=0; i<tam; i++){

        ListaAdj[i].listavert = NULL;
        marcado[i] = 0;
        saida[i]=0;
    }

    while(cont!=arestaa){

  //      cout<< "\n VerticeOrigem - VerticeDestino - Peso da aresta: ";
    cin>> org >> dest >> peso;
    //fflush(stdin);
        cont++;


        novo = new Vertice();
        novo->num = dest;
        novo->peso = peso;
        novo->prox = ListaAdj[org].listavert;
        ListaAdj[org].listavert = novo;

     //A volta do anzol
        novo= new Vertice();
        novo->num = org;
        novo->peso=peso;

        novo->prox = ListaAdj[dest].listavert;
        ListaAdj[dest].listavert = novo;

    }

    int DestVert=0;
                cin>> OrigemVert >> DestVert;
               // fflush(stdin);

                 for(int i=0; i< tam; i++){
                    marcado[i] = 0;
                    distancia[i] = 0;
                }

                MinHeap *mini = new MinHeap();
              //  mini->MostrarAdjLista(ListaAdj, tam);
                 // cout<<endl;
                //  cout<<endl;

                int distancia1, distancia2;

            mini->MenorCaminhoDijkstra(ListaAdj, tam, OrigemVert, parent, distancia, DestVert, saida, &tamSaida);
            distancia1 = distancia[DestVert];

            mini->MenorCaminhoDijkstra(ListaAdj, tam, DestVert, parent, distancia, OrigemVert, saida, &tamSaida);
            distancia2 = distancia[OrigemVert];

            if(distancia1<=distancia2){

                mini->MenorCaminhoDijkstra(ListaAdj, tam, OrigemVert, parent, distancia, DestVert, saida, &tamSaida);

                 int aux = DestVert;//5
                 int saidaV[1000];
                 int r=0;
                 int aux2=0;

                 saidaV[r] = DestVert;//saidaV[0]=5
                 r++;//1

                 while(parent[aux] != OrigemVert){//parent[5] != 0
                    saidaV[r] = parent[aux];
                    r++;
                    aux = parent[aux];
                 }

                 saidaV[r] = OrigemVert;
                 r++;
                 aux2=r-1;

                for(int h=r-1;h>=0;h--){
                   if (aux2==r-1){
                      cout<<saidaV[h];
                      aux2=-10;
                   }else{
                      cout<<" "<<saidaV[h];
                   }
                }



                //cout << "dist[" << DestVert <<"] = " << distancia[DestVert] << endl;
                }else{
                        mini->MenorCaminhoDijkstra(ListaAdj, tam, DestVert, parent, distancia, OrigemVert, saida, &tamSaida);
                int aux = OrigemVert;//5
                 int saidaV[1000];
                 int r=0;
                 int aux2=0;

                 saidaV[r] = OrigemVert;//saidaV[0]=5
                 r++;//1

                 while(parent[aux] != DestVert){//parent[5] != 0
                    saidaV[r] = parent[aux];
                    r++;
                    aux = parent[aux];
                 }

                 saidaV[r] = DestVert;
                 r++;
                 aux2=0;

                for(int h=0;h<r;h++){
                   if (aux2==0){
                      cout<<saidaV[h];
                      aux2=-10;
                   }else{
                      cout<<" "<<saidaV[h];
                   }
                }


                }}
