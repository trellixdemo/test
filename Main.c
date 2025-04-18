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
										// 