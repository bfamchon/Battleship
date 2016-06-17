#ifndef PACKET_TYPE_HPP_
#define PACKET_TYPE_HPP_

#pragma once

#include "SFML/System.hpp"

typedef sf::Uint8 PacketType;
const PacketType INITIAL_NAME_DATA=0;
const PacketType GENERAL_MSG=1;
const PacketType NONE = 3;

const PacketType SERVEUR_MSG=10;
const PacketType DISCONNECT = SERVEUR_MSG+1;
const PacketType SHUTDOWN_SERVEUR = SERVEUR_MSG+2;
const PacketType SEND_USER_WAIT = SERVEUR_MSG+3;
const PacketType GET_USER_WAIT = SERVEUR_MSG+4;
const PacketType SEND_LISTE_ATTENTE = SERVEUR_MSG+5;
const PacketType SERVEUR_FULL = SERVEUR_MSG+6;

const PacketType JEU_MSG=50;
const PacketType START_PLAY = JEU_MSG+1;
const PacketType STOP_PLAY = JEU_MSG+2;
const PacketType SEND_FLOTTE = JEU_MSG+3;
const PacketType MAJ_FLOTTE = JEU_MSG+4;
const PacketType SEND_COUP = JEU_MSG+5;
const PacketType GET_COUP = JEU_MSG+6;
const PacketType SEND_RESPONSE_COUP = JEU_MSG+7;
const PacketType SEND_WINNER = JEU_MSG+8;
  
#endif
