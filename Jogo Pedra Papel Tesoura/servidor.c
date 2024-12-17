#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ctype.h>
#include <time.h>

#define MAX_RODADAS 5

typedef struct {
	int pontuacao_servidor;
	int pontuacao_cliente;
	char jogada_servidor[512];
} Pontuacao;

Pontuacao pontuacao;

void set_color(int text_color, int bg_color) { // Esta funcao permite mudar as cores da interface

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)(bg_color << 4) | text_color);
}

void inicializar_placar(void) {
	pontuacao.pontuacao_servidor = 0;
	pontuacao.pontuacao_cliente = 0;
	strcpy(pontuacao.jogada_servidor, "");
}

void determinaResultado(char* jogada_servidor, char* jogada_cliente) {
    if (strcmp(jogada_servidor, jogada_cliente) == 0) {
    	return;
    } else if ((strcmp(jogada_servidor, "pedra") == 0 && strcmp(jogada_cliente, "tesoura") == 0) ||
               (strcmp(jogada_servidor, "papel") == 0 && strcmp(jogada_cliente, "pedra") == 0) ||
               (strcmp(jogada_servidor, "tesoura") == 0 && strcmp(jogada_cliente, "papel") == 0)) {
    	pontuacao.pontuacao_servidor += 1;
    } else {
        pontuacao.pontuacao_cliente += 1;
    }
    strcpy(pontuacao.jogada_servidor, jogada_servidor);
}

void validar_entrada(char* jogada_servidor) {
	while(1){
        // Recebe a jogada do jogador 1 (servidor)
        printf("\n Escolha pedra, papel ou tesoura(ou 'exit' para sair): ");
        fgets(jogada_servidor, sizeof(jogada_servidor), stdin);
        jogada_servidor[strcspn(jogada_servidor, "\n")] = 0;
        
        int i;
        char temp;
        char string[512];
        
        strcpy(string, "");
        
        for (i = 0; i <= strlen(jogada_servidor); i += 1) {
        	temp = tolower(jogada_servidor[i]);
        	string[i] = temp;
		}
		
		strcpy(jogada_servidor, string);

        if (strcmp(jogada_servidor, "exit") == 0) {
            printf("Encerrando o servidor\n");
            break;
        }
        if (strcmp(jogada_servidor, "pedra") == 0 || strcmp(jogada_servidor, "papel") == 0 ||
            strcmp(jogada_servidor, "tesoura") == 0 || strcmp(jogada_servidor, "exit") == 0) {
            break;  // Sai do loop se a entrada for válida
        } else {
            printf("\n Entrada invalida! Tente novamente.\n");
        }
	}    
}

void imprimir_resultado_final() {
	system("cls");
	set_color(6, 0);
	
	if (pontuacao.pontuacao_servidor > pontuacao.pontuacao_cliente) {
        printf("\n");
        printf("         ##########################          \n");
            printf("         ##########################          \n");
            printf("    #####################################    \n");
            printf("  #########################################  \n");
            printf(" ####      ######################       #### \n");
            printf(" ###       ######################        ### \n");
            printf(" ##        ######################        ### \n");
            printf(" ###     ##########################      ### \n");
            printf(" ###    ############################    #### \n");
            printf("  ###   ### #################### ###    ###  \n");
            printf("  ####   ### ################## ####  ####   \n");
            printf("    ####  ######################### #####    \n");
            printf("     ######## ################ #########     \n");
            printf("       ######  ##############   ######       \n");
            printf("                ############                  \n");
            printf("                  ########                    \n");
            printf("                    ####                      \n");
            printf("                    ####                      \n");
            printf("                    ####                      \n");
            printf("                    ####                      \n");
            printf("                ############                  \n");
            printf("             ##################               \n");
            printf("             ##################               \n");
            printf("             ###            ###               \n");
            printf("             ###  PLAYER 1  ###               \n");
            printf("             ###            ###               \n");
            printf("             ##################               \n");
            printf("             ##################               \n");
            printf("           ######################              \n");
            printf("          ########################              \n");
        } else if (pontuacao.pontuacao_servidor < pontuacao.pontuacao_cliente) {
        	set_color(4, 0);
            printf("\n          _.-\"\"\"-._\n");
    		printf("         /  _   _  \\\n");
    		printf("        /  (9) (9)  \\\n");
    		printf("       /_,         ,_\\\n");
    		printf("       | \\         / |\n");
    		printf(" _     \\  \\._____./  /  __\n");
    		printf(" \\`\\    \\   \\___/   / _|  \\\n");
    		printf("  \\ `\\  /\\         /\\ \\   /\n");
		    printf("   |  `\\/ /`'-----'\\ \\/  / \n");
		    printf("   |_|\\/ /           \\   /  \n");
		    printf("   /    /|           |\\_/   \n");
		    printf("   \\___/ |           | \\    \n");
		    printf("    \\ .  |           |  \\   \n");
		    printf("     \\|  |           |  |   \n");
		    printf("      |  `.         .'  |   \n");
		    printf("      \\    `-.___.-'    /   \n");
		    printf("       `\\       |       /'   \n");
		    printf("         `\\     |     /'     \n");
		    printf("      .-.-.`\\   |   /'.-.-.  \n");
		    printf("     (,(,(,`^   |   ^`,),),)  \n");
		    printf("      '-'-'-----`-----'-'-'   \n");
		    printf("\n");
		    printf("     VV     VV  OO OO OO  CC CC CC   EE EE EE          PP PP    EE EE EE   RR RR     DD DD     EE EE EE  UU    UU \n");
		    printf("     vv     vv  OO    OO  CC         EE                PP   PP  EE         RR   RR   DD    DD  EE        UU    UU \n");
		    printf("      vv   vv   OO    OO  CC         EE EE EE          PP PP    EE EE EE   RR RR     DD    DD  EE EE EE  UU    UU \n");
		    printf("       vv vv    OO    OO  CC         EE                PP       EE         RR   RR   DD    DD  EE        UU    UU \n");
		    printf("        vv      OO OO OO  CC CC CC   EE EE EE          PP       EE EE EE   RR    RR  DD  DD    EE EE EE  UU UU UU \n  ");
        }
        
    set_color(7, 0);
}

void teste_mostrar_score(void) {
	int x;
	for(x=0;x<120;x++){
		Sleep(1);
		printf(">");
	}
	printf("\n");
	printf("\n                  |++++++++++++++++++++++++++++++++|               |++++++++++++++++++++++++++++++++|");
    printf("\n                  |     PONTUACAO SERVIDOR : 0%d    |               |      PONTUACAO CLIENTE : 0%d    |", pontuacao.pontuacao_servidor, pontuacao.pontuacao_cliente);
    printf("\n                  |++++++++++++++++++++++++++++++++|               |++++++++++++++++++++++++++++++++|\n\n");
    for(x=0;x<120;x++){
		Sleep(1);
		printf(">");
	}

}


int main() {
    WSADATA winsocketsDados;
    if (WSAStartup(MAKEWORD(2, 2), &winsocketsDados) != 0) {
        printf("Falha ao inicializar o Winsock\n");
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Erro ao criar o socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(51171);

    if (bind(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Erro ao associar o socket: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
        printf("Erro ao colocar o socket em estado de escuta: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
     printf("\n                                 ||-----------------BEM VINDO JOGADOR 1-------------------||\n");
     printf("\n                                                    Esperando jogador 2...\n");

    // Aceitar conexão do jogador 2
    SOCKET clientSocket2;
    struct sockaddr_in clientAddr2;
    int clientAddrLen2 = sizeof(clientAddr2);
    clientSocket2 = accept(sock, (struct sockaddr*)&clientAddr2, &clientAddrLen2);
    if (clientSocket2 == INVALID_SOCKET) {
        printf("Erro ao aceitar conexao do jogador 2: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
     printf("\n                                                   Jogador 2 conectado                                                 \n");
     
    inicializar_placar();
    send(clientSocket2, (char*)&pontuacao, sizeof(Pontuacao), 0);

    char jogada_servidor[512], jogada_cliente[512];
    int bytesReceived2;
    char resultado[512];
    int sair = 0;

    // Recebe jogadas
    while (pontuacao.pontuacao_servidor < (MAX_RODADAS / 2) + 1 && pontuacao.pontuacao_cliente < (MAX_RODADAS / 2) + 1) {
    	system("cls");
    	teste_mostrar_score();
    	fflush(stdin);
        printf("\n\n < Aguardando a jogada do jogador 2.. >\n");
        // Recebe a jogada do jogador 2 (cliente)
        bytesReceived2 = recv(clientSocket2, jogada_cliente, sizeof(jogada_cliente), 0);
        if (bytesReceived2 == SOCKET_ERROR || bytesReceived2 == 0) {
            printf("Erro ao receber dados do jogador 2 ou conexão encerrada\n");
            break;
        }
        
        jogada_cliente[bytesReceived2] = '\0';
        
        validar_entrada(jogada_servidor);
        
        if (strcmp("exit", jogada_servidor) == 0) {
        	closesocket(clientSocket2);
    		closesocket(sock);
   			WSACleanup();
        	return 0;
		}
        
        determinaResultado(jogada_servidor, jogada_cliente);
        
		send(clientSocket2, (char*)&pontuacao, sizeof(Pontuacao), 0);
		
		if (pontuacao.pontuacao_servidor >= 3 || pontuacao.pontuacao_cliente >= 3) {
			imprimir_resultado_final();
			system("pause");
        	return 0; // Encerra o jogo se algum jogador atingiu 3 pontos
    	}
    }
    
    closesocket(clientSocket2);
    closesocket(sock);
    WSACleanup();
    
    return 0;
}
