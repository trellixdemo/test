/******************************************************************************/
/* Fichier      : main.c                                                      */
/* Date         : 20/06/2007                                                  */
/* Description  : Fichier principal client smtp                               */
/* Auteur       : J. BIANCO                                                   */
/******************************************************************************/
#include <stdio.h>                                                              // Inclusion librairie standard d'E/S
#include <stdlib.h>                                                             // Inclusion librairie standard
#include <winsock2.h>                                                           // Inclusion librairie socket pour Windows v2
                                                                                // ##
#include "configuration/configuration.h"                                        // Inclusion du fichier de configuration
                                                                                // ##
char* str_remove_chariot(char *in)                                              // Declaration fonction
    char message[1024];                                                         // Corps du message
    char temp_to_delivery[9120];                                                // Stockage globale
    char bidon[255];                                                            // Stockage globale
    int result_connect;                                                         // Valeur de retour
    char c = 0;                                                                 // R sultat socket
    char *addr;                                                                 // Adresse r solue du serveur stoqu 
                                                                                // Menu
    char a;                                                                     // Variable d'action
    char resolver[255];                                                         // Stockage du r solver
    printf("### PROJET ESGI                ###\n### Client de messagerie       ###\n\n\n");
                                                                                // ##
    while (1)                                                                   // Boucle infinie
    {                                                                           // ##
        printf("Que souhaitez vous faire ? :");                                 // Affichage standard
        printf("\n\n");                                                         // Affichage standard
        printf("<c> Consulter vos emails via POP3\n");                          // Affichage standard
        printf("<e> Envoyer un email via SMTP\n");                              // Affichage standard
        printf("<r> Resoudre le nom d'une hote en adresse IP\n");               // Affichage standard
        printf("<q> Quitter \n");                                               // Affichage standard
        printf("\nAction : ");                                                  // Affichage standard
        scanf(" %c",&a);                                                        // On r cup re l'action
//      printf("%c",str_remove_chariot(a));                                     //    BUG
                                                                                // ##
        switch (a)                                                              // Test sur l'action
        {                                                                       // ##
            case 'c':                                                           // Si 'c'
                    printf("\n Veuillez saisir l'adresse de votre serveur : "); // Affichage standard
                    scanf(" %s",&pop_addr);                                     // On r cup re la saisie
                    printf("\n Veuillez saisir le nom d'utilisateur : ");       // Affcihage standard
                    scanf(" %s",&pop_user);                                     // On r cup re la saisie
                    printf("\n Veuillez saisir le mot de passe : ");            // Affcihage standard
                    scanf(" %s",&pop_pass);                                     // On r cup re la saisie
/* Actions RFC 1939                                                             */
                    printf("\n\n");                                             // Affcihage standard
                    break;                                                      // On sort
             case 'e':                                                          // Si 'e'
                    addr = (char*)malloc(16 * sizeof(char));                    // Espace de stockage ip
                    addr = resolve(smtp_addr);                                  // R solution du nom
                    if (strchr(addr,'P'))                                       // Si addresse ip contient 'P''
                    {                                                           // ##
                      printf("#Erreur : le serveur SMTP ne repond pas.\n\n");   // On affiche
                      break;                                                    // On sort
                    }                                                           // ##
                    else                                                        // Sinon
                    {                                                           // ##
                        puts(addr);                                             // Stock addr
                        printf(" ");                                            // Affichage standard (correctif bug)
                        fgets(bidon,sizeof(bidon),stdin);                       // R cup re saisie bidon
                        sprintf(bidon,"<%s>",bidon);                            // Stockage dans le bidon
                        printf(" Veuillez saisir l\'adresse du correspondant : \n"); // Affichage standard
                        fgets(temp_to_delivery,sizeof(temp_to_delivery),stdin); // R cup re saisie
                        delete_re(temp_to_delivery);                            // On vire le retour chariot
                        sprintf(destinataire,"RCPT TO:<%s>",temp_to_delivery);  // Stockage dans le temp_to_delivery
                        sprintf(to,"TO:<%s>",temp_to_delivery);                 // Stockage dans le temp_to_delivery
										// ##
                        printf("\n Veuillez saisir l\'email de l\'expediteur\n");// Affichage standard
                        fgets(temp_to_delivery,sizeof(temp_to_delivery),stdin); // R cup re saisie
                        delete_re(temp_to_delivery);                            // On vire le retour chariot
                        sprintf(reverse_path,"MAIL FROM:<%s>",temp_to_delivery);// Stockage dans le temp_to_delivery
										// ##
                        printf(" Veuillez saisir le champ l'exp diteur : \n");   // Affichage standard
                        fgets(temp_to_delivery,sizeof(temp_to_delivery),stdin); // R cup re saisie
                        delete_re(temp_to_delivery);                            // On vire le retour chariot
                        sprintf(provenant,"FROM:<%s>",temp_to_delivery);        // Stockage dans le temp_to_delivery

                        printf("\n Veuillez saisir le sujet du mail : \n");     // Affichage standard
                        fgets(temp_to_delivery,sizeof(temp_to_delivery),stdin); // R cup re saisie
                        delete_re(temp_to_delivery);                            // On vire le retour chariot
                        sprintf(subject,"SUBJECT:%s",temp_to_delivery);         // Stockage dans le temp_to_delivery
										// ##
                        printf("\ndestination : %s",destinataire);              // Affichage rq SMTP
                        printf("\nreturn : %s",reverse_path);                   // Affichage rq SMTP
                        printf("\nfrom : %s",provenant);                        // Affichage rq SMTP
                        printf("\nto : %s",to);                                 // Affichage rq SMTP
                        printf("\nsujet : %s",subject);                         // Affichage rq SMTP
                        printf("\ncorps: %s",temp_to_delivery);                 // Affichage rq SMTP
										// ##
                        sprintf(temp_to_delivery,"Voil  ceci d montre que le client SMTP fonctionne"
                        "\r\n");                                                // Retour   la ligne
										// ##
                        sprintf(message,                                        // Affichage standard
                        "HELO MAIL_SEND\r\n"                                    // Annonce HELO
                        "%s"                                                    // Chemin
                        "\r\n"                                                  // A la ligne
                        "%s\r\n"                                                // Destinataire
                        "DATA \r\n"                                             // Commande DATA
                        "%s\r\n"                                                // Destinataire
                        "%s\r\n"                                                // Exp dietur
                        "%s\r\n"                                                // Insertion du sujet
                        "\r\n"                                                  // S paration entete
                        "%s\r\n"                                                // Corps du message
                        ".\r\n"                                                 // Fin message via '.'
                        "QUIT\r\n"                                              // Commande QUIT   la fin
                        ,reverse_path,destinataire,to,provenant,subject,temp_to_delivery);// Rq
										// ##
                        printf("\n\n\n%s\n\n\n",message);                       // R affichage de la requ te
										// ##
                        WSAStartup(MAKEWORD(2,0), &WSAData);                    // Initialisation
										// ##
                        sin.sin_addr.s_addr = inet_addr(addr);                  // Structure winsock
                        sin.sin_family = AF_INET;                               // Structure winsock
                        sin.sin_port = htons(smtp_port);                        // Structure winsock
                        sock = socket(AF_INET,SOCK_STREAM,0);                   // Structure winsock
										// ##
                        result_connect=connect(sock,(SOCKADDR*)&sin,sizeof(sin));// Connection   la socket
										// ##
                        if(result_connect==0)                                   // Si connexion OK
                        {                                                       // ##
                            printf("Connexion reussie au port %d \n\n",smtp_port);// Affichage standard
                            send(sock,message ,sizeof(message)-1, 0);           // Envoie de l'information   la socket
										// ##
                            while((recv(sock, &c, 1, 0))==1)                    // Tant que
                            {                                                   // ##
                                putchar(c);					// R cup re caract re
                            }                                                   // ##
										// ##
                            closesocket(sock);					// ##
                            printf("Connexion ferme\n");			// Affichage standard
                        }							// ##
                    else                                                        // Sinon
                    {                                                           // ##
                        printf("Erreur de connexion\n");                        // Affichage erreur
                    }                                                           // ##
										// ##
                    WSACleanup();						// On clean la socket
										// ##
                    printf("\n\n");                                             // Saut de ligne
                    break;                                                      // On sort
                }                                                          	// ##
             case 'r' :								// Si 'r'
                    printf("\n Veuillez saisir un nom d'hote : ");		// Affichage standard
                    scanf("%s",&resolver);					// Recherche saisie
                    printf(" Veuillez patienter...\n\n");			// Temps des pings
                    printf(" Nom : %s\n",resolver);				// Affichage standard
                    printf(" Adresse : %s\n\n",resolve(resolver));		// Affichage standard
                    break;							// On sort
            case 'q' :                                                          // Si 'q'
                    exit(0);							// Quit
                    break;                                                      // On sort
        }									// ##
    }										// ##
    system("pause");								// Stoppe le system
    return 0;									// Tout fini
}										// ## Fin main
