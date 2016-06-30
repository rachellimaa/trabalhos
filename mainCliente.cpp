#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define PROTOPORT	5193  // n�mero de porta de protocolo default

extern int errno;
char localhost[] = "192.168.0.14"; //nome default host
int main () {


    struct  hostent *ptrh;   // ponteiro para uma entrada de tabela de host
    struct  protoent *ptrp;  // ponteiro para uma entrada de tabela de protocolo
    struct  sockaddr_in sad; //a estrutura para manter um endere�o IP
    int     sd;				   // descritor de socket
    int     port;
    int     count1;
    int     confirm = 0;
    int     k = 0;
    char    *host;              //ponteiro para o nome de host
    int     n;                  // n�mero de caracteres lidos
    char    bufr[1000];          // buffer para dados do servidor
    char    bufs[1000];
    char    buf[1000];
    char    mensagem[100];
    char    criptografia[100];
    char    alfabeto[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char    chave [26] = {'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e'};
    FILE    *arquivo;
#ifdef WIN32
	WSADATA wsaData;
   WSAStartup (0x0101, &wsaData);
#endif
    printf("Bem vindo, Cliente.\n");
    puts("Porta do servidor ?");
    scanf("%d",&port);
    puts("IP do servidor ?");
    scanf("%s",buf);
    memset((char*)&sad,0,sizeof(sad)); //limpa estrutura sockaddr
    sad.sin_family = AF_INET;			  //configura fam�lia para Internet

   //Verifica argumento de linha de comando para porta de protocolo e extrai
   // n�mero de porta se � especificado. Caso contr�rio, usa valor de
   // porta default dado pela constante PROTOPORT

     	port = PROTOPORT;			// usa o n�mero de porta default
    if (port > 0)		{			// teste se o valor � legal
       sad.sin_port = htons((u_short)port);
    }    else {							//imprime mensagem de erro e sai
        fprintf(stderr,"n�mero de porta inv�lida %s\n");
        exit(1);
   }

   // Verifica argumento de host e atribui nome de host

    host = buf;
   // Converte nome de host para endere�o IP equivalente e copia para sad.

    ptrh = gethostbyname(host);
    if (((char *)ptrh) == NULL) {
   		fprintf(stderr, "host inv�lido: %s\n", host);
        exit (1);
   }

    memcpy(&sad.sin_addr,ptrh->h_addr, ptrh->h_length);

   // Mapeia nome do protocolo de transporte TCP para n�mero de protocolo

    if (((int(ptrp = getprotobyname("tcp")))) == 0) {
        fprintf (stderr, "n�o pode mapear \"tcp\" para n�mero de protocolo");
        exit (1);
   }

   // Cria um socket

    sd = socket (PF_INET, SOCK_STREAM, ptrp->p_proto);
    if (sd < 0){
        fprintf(stderr, "a cria��o de socket falhou \n");
        exit (1);
   }

   // Conecta o socket ao servidor especificado

    if (connect(sd, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
        fprintf(stderr, "connect falhou\n");
        exit (1);
        }
    memset(criptografia, 0x0, sizeof(criptografia));
    memset(bufs, 0x0, sizeof(bufs));
    sprintf(mensagem, "eu bebo e sei das coisas\n");
    for (int i=0;i<sizeof(mensagem);i++){
        for (int j=0;j<26;j++){
            if (mensagem[i] == alfabeto[j]){
                criptografia[i] = chave[j];
            }
            else{
                if(mensagem[i] == ' '){
                    criptografia[i] = ' ';
                }
            }
        }
    }
    while (true){
        //Recebe a mensagem do servidor
        memset(bufr, 0x0, sizeof(bufr));
        n= recv(sd, bufr, sizeof(bufr),0);
        //Exibe a mensagem na tela
        printf(">> %s", bufr);
        //Envia uma mensagem ao servidor
        memset(bufs, 0x0, sizeof(bufs));
        sprintf(bufs, "OK\n");
        send(sd, bufs, sizeof(bufs), 0 );
        //Recebe um c�digo do servidor
        memset(bufr, 0x0, sizeof(bufr));
        n= recv(sd, bufr, sizeof(bufr),0);
        //Inicia a autentica��o do login
        if (strcmp (bufr, "0001")==0){
            count1=0;
            while (count1<=3){
                printf("Login: ");
                memset(bufs, 0x0, sizeof(bufs));
                //Envia o login recebido do usu�rio ao servidor
                scanf("%s",&bufs);
                send(sd, bufs, sizeof(bufs), 0 );

                memset(bufr, 0x0, sizeof(bufr));
                n= recv(sd, bufr, sizeof(bufr),0);
                //Verifica��o do login correto
                if (strcmp(bufr, "0002")==0){
                    printf("Login correto.\n\n");
                    count1 = 4;
                }
                else{
                    printf("Login incorreto.\n\n");
                    count1 = count1 + 1;
                }
            }
            memset(bufs, 0x0, sizeof(bufs));
            sprintf(bufs, "Success.\n");
            send(sd, bufs, sizeof(bufs), 0 );
        }
        //In�cio da Autentica��o da senha
        memset(bufr, 0x0, sizeof(bufr));
        n= recv(sd, bufr, sizeof(bufr),0);
        if (strcmp (bufr, "0004")==0){
            count1=0;
            while (count1<=3){
                printf("Senha: ");
                memset(bufs, 0x0, sizeof(bufs));
                //Envia a senha fornecida pelo usu�rio ao servidor
                scanf("%s",&bufs);
                send(sd, bufs, sizeof(bufs), 0 );

                memset(bufr, 0x0, sizeof(bufr));
                n= recv(sd, bufr, sizeof(bufr),0);
                //Verifica��o da senha correta
                if (strcmp(bufr, "0005")==0){
                    printf("Senha correta.\n\n");
                    count1 = 4;
                }
                else{
                    printf("Senha incorreta.\n\n");
                    count1 = count1 + 1;
                }
            }
        }
        printf("Mensagem original: %s\n\nMensagem criptografada: %s\n\n", mensagem, criptografia);
        memset(bufr, 0x0, sizeof(bufr));
        n= recv(sd, bufr, sizeof(bufr),0);
        printf(bufr);
        memset(bufs, 0x0, sizeof(bufs));
        sprintf(bufs, criptografia);
        send(sd, bufs, sizeof(bufs), 0 );
        }
    }

