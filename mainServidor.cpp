#include <windows.h>
#include <winsock.h>
#include <string.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define PROTOPORT       5193            /* default protocol port number */
#define QLEN            6               /* size of request queue        */

const int TAM_BUFFER = 1000;
int     visits      =   0;              /* counts client connections    */

main()

{
        struct  protoent *ptrp;  /* pointer to a protocol table entry   */
        struct  sockaddr_in sad; /* structure to hold server's address  */
        struct  sockaddr_in cad; /* structure to hold client's address  */
        int     sd, sd2;         /* socket descriptors                  */
        int     port, count1;            /* protocol port number                */
        int     alen,n,pontarq,tbuf, j;            /* length of address                   */
        char    bufr[TAM_BUFFER];           /* buffer for string the server sends  */
        char    linha[TAM_BUFFER];
        char    bufs[TAM_BUFFER];
        FILE    *arquivo;
        char    ch[TAM_BUFFER];
        char    mensagem[100];
        char    alfabeto[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        char    chave[26] = {'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e'};

#ifdef WIN32
        WSADATA wsaData;
        WSAStartup(0x0101, &wsaData);
#endif
        memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure */
        sad.sin_family = AF_INET;         /* set family to Internet     */
        sad.sin_addr.s_addr = INADDR_ANY; /* set the local IP address   */

        port = PROTOPORT;       /* use default port number      */
        if (port > 0)                   /* test for illegal value       */
                sad.sin_port = htons((u_short)port);
        else {                          /* print error message and exit */
                fprintf(stderr,"Numero de porta invalido \n");
                exit(1);
        }

        /* Map TCP transport protocol name to protocol number */

        if ( ((int)(ptrp = getprotobyname("tcp"))) == 0) {
                fprintf(stderr, "Nao foi possivel mapear o numero do protocolo");
                exit(1);
        }

        /* Create a socket */

        sd = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
        if (sd < 0) {
                fprintf(stderr, "Falha na criacao do socket\n");
                exit(1);
        }

        /* Bind a local address to the socket */

        if (bind(sd, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
                fprintf(stderr,"bind failed\n");
                exit(1);
        }

        printf("Bem vindo ao Servidor\n");

        if (listen(sd, QLEN) < 0) {
                fprintf(stderr,"Esculta falhou\n");
                exit(1);
        }
    while(true){
        alen = sizeof(cad);
        sd2=accept(sd, (struct sockaddr *)&cad, &alen) ;

        memset(bufs, 0x0, sizeof(bufs));
        sprintf(bufs,"Bem-vindo ao servidor Bombril.\n");
        send(sd2,bufs,strlen(bufs),0);

        memset(bufr, 0x0, sizeof(bufr));
        n= recv(sd2, bufr, sizeof(bufr),0);

        memset(bufs, 0x0, sizeof(bufs));
        sprintf(bufs,"0001");
        //Tudo OK
        send(sd2,bufs,strlen(bufs),0);

        memset(bufr, 0x0, sizeof(bufr));
        n= recv(sd2, bufr, sizeof(bufr),0);

        count1=0;
        while (count1<=3){
            if (strcmp (bufr,"le")==0){
                memset(bufs, 0x0, sizeof(bufs));
                sprintf(bufs, "0002");
                send(sd2,bufs,strlen(bufs),0);
                count1 = 4;
            }
            else{
                memset(bufs, 0x0, sizeof(bufs));
                sprintf(bufs, "0003");
                send(sd2,bufs,strlen(bufs),0);
                memset(bufr, 0x0, sizeof(bufr));
                count1 = count1 + 1;
                n= recv(sd2, bufr, sizeof(bufr),0);
            }
        }
        memset(bufr, 0x0, sizeof(bufr));
        n= recv(sd2, bufr, sizeof(bufr),0);

        memset(bufs, 0x0, sizeof(bufs));
        sprintf(bufs,"0004");
        send(sd2,bufs,strlen(bufs),0);

        memset(bufr, 0x0, sizeof(bufr));
        n= recv(sd2, bufr, sizeof(bufr),0);
        count1=0;
        while (count1<=3){
            if (strcmp (bufr,"lety")==0){
                memset(bufs, 0x0, sizeof(bufs));
                sprintf(bufs, "0005");
                send(sd2,bufs,strlen(bufs),0);
                count1 = 4;
            }
            else{
                memset(bufs, 0x0, sizeof(bufs));
                sprintf(bufs, "0006");
                send(sd2,bufs,strlen(bufs),0);
                count1 = count1 + 1;
                n= recv(sd2, bufr, sizeof(bufr),0);
            }
        }
        memset(bufs, 0x0, sizeof(bufs));
        sprintf(bufs,"OK\n");
        send(sd2,bufs,strlen(bufs),0);

        memset(bufr, 0x0, sizeof(bufr));
        n= recv(sd2, bufr, sizeof(bufr),0);
        printf("Mensagem recebida: %s\n\n", bufr);
        for (int i = 0;i<sizeof(bufr);i++){
            j = 0;
            while (j<26){
                if (bufr[i] == chave[j]){
                    bufr[i] = alfabeto[j];
                    j = 25;
                }
                else{
                    if (bufr[i] == ' '){
                        bufr[i] = ' ';
                    }
                }
                j = j + 1;
            }
        }
            printf("Mensagem recebida: %s", bufr);
        }
//        memset(bufr, 0x0, sizeof(bufr));
//        n= recv(sd2, bufr, sizeof(bufr),0);
//        printf("\n%s\n",bufr);
//        while (strcmp (bufr, "5555") != 0){
//            if (strcmp(bufr, "1111") == 0){
//                memset(bufs, 0x0, sizeof(bufs));
//                printf("Abrindo o paint\n");
//                system("mspaint");
//            }
//            else if (strcmp (bufr, "2222") == 0){
//                memset(bufs, 0x0, sizeof(bufs));
//                printf("Abrindo Video\n");
//                system("teste.mp4");
//            }
//            else if (strcmp(bufr, "3333") == 0){
//                memset(bufs, 0x0, sizeof(bufs));
//                printf("Abrindo driver CD/DVD\n");
//                system("nircmd.exe cdrom open D:");
//            }
//
//            else if (strcmp (bufr, "4444") == 0){
//                memset(bufs, 0x0, sizeof(bufs));
//                printf("Enviando lista de arquivos \n");
//                arquivo = fopen ("diretorio.txt", "r");
//
//                while(fgets(linha, TAM_BUFFER, arquivo)){
//                    strcat(bufs, linha);
//                }
//                fclose(arquivo);
//
//                send (sd2, bufs, sizeof(bufs),0);
//            }
//            else if (strcmp(bufr, "apostilas.txt") == 0){
//                printf("Enviando arquivo apostilas.txt\n");
//                memset(bufs, 0x0, sizeof(bufs));
//                printf("Enviando diretorio\n");
//                arquivo = fopen ("apostilas.txt", "r");
//
//                while(fgets(linha, TAM_BUFFER, arquivo)){
//                    strcat(bufs, linha);
//                }
//                send (sd2, bufs, sizeof(bufs),0);
//                printf("\nArquivo transferido com sucesso.\n");
//                fclose(arquivo);
//            }
//            else if (strcmp(bufr, "lista.txt") == 0){
//                printf("Enviando arquivo lista.txt\n");
//                memset(bufs, 0x0, sizeof(bufs));
//                printf("Enviando diretorio\n");
//                arquivo = fopen ("lista.txt", "r");
//
//                while(fgets(linha, TAM_BUFFER, arquivo)){
//                    strcat(bufs, linha);
//                }
//                send (sd2, bufs, sizeof(bufs),0);
//                printf("\nArquivo transferido com sucesso.\n");
//                fclose(arquivo);
//            }
//            else if (strcmp(bufr, "redes.txt") == 0){
//                printf("Enviando arquivo redes.txt\n");
//                memset(bufs, 0x0, sizeof(bufs));
//                printf("Enviando diretorio\n");
//                arquivo = fopen ("redes.txt", "r");
//
//                while(fgets(linha, TAM_BUFFER, arquivo)){
//                    strcat(bufs, linha);
//                }
//                send (sd2, bufs, sizeof(bufs),0);
//                printf("\nArquivo transferido com sucesso.\n");
//                fclose(arquivo);
//            }
//            memset(bufr, 0x0, sizeof(bufr));
//            n= recv(sd2, bufr, sizeof(bufr),0);
//            }
//            sprintf(bufs, "Desconectado\n");
//            send(sd2,bufs,strlen(bufs),0);
//

        closesocket(sd2);
    }
