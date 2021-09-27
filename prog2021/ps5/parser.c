#include "parser.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
struct parser* create_parser(){
    struct parser* parser = calloc(1,sizeof(struct parser));
    parser->history = NULL;
    parser->commands = NULL;
    struct command* quit = create_command("KONIEC","Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.","KONIEC",1);
    struct command* sever = create_command("SEVER","Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.","SEVER",1);
    struct command* juh = create_command("JUH","Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.","JUH",1);
    struct command* vychod = create_command("VYCHOD","Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.","VYCHOD",1);
    struct command* zapad = create_command("ZAPAD","Presun do miestnosti nachádzajúcej sa na zapad od aktuálnej. Zmení referenciu aktuálnej miestnosti.","ZAPAD",1);
    struct command* rozhl_sa = create_command("ROZHLIADNI SA","Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.","ROZHLIADNI SA",1);
    struct command* prikazy = create_command("PRIKAZY","Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.","PRIKAZY",1);
    struct command* verzia = create_command("VERZIA","Verzia hry: 1.00a\n Author: Chernov Kostiantyn\n mail: kostiantyn.chernov@student.tuke.sk","VERZIA",1);
    struct command* restart = create_command("RESTART","Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.","RESTART",1);
    struct command* about = create_command("O HRE","Hra o BOJESTVE DOTY","O HRE",1);
    struct command* vezmi = create_command("VEZMI","Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš vziať.)","VEZMI",1);
    struct command* poloz = create_command("POLOZ","Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)","POLOZ",1);
    struct command* inventar = create_command("INVENTAR","Zobrazí obsah hráčovho batohu.","INVENTAR",1);
    struct command* pouzi = create_command("POUZI","Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).","POUZI",1);
    struct command* preskumaj = create_command("PRESKUMAJ","Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš preskúmať.).","PRESKUMAJ",1);
    struct command* nahraj = create_command("NAHRAJ","Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.","NAHRAJ",1);
    struct command* uloz = create_command("ULOZ","Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.","ULOZ",1);
    parser->commands = create_container(parser->commands,COMMAND,quit);
    create_container(parser->commands,COMMAND,sever);
    create_container(parser->commands,COMMAND,juh);
    create_container(parser->commands,COMMAND,vychod);
    create_container(parser->commands,COMMAND,zapad);
    create_container(parser->commands,COMMAND,rozhl_sa);
    create_container(parser->commands,COMMAND,prikazy);
    create_container(parser->commands,COMMAND,verzia);
    create_container(parser->commands,COMMAND,restart);
    create_container(parser->commands,COMMAND,about);
    create_container(parser->commands,COMMAND,vezmi);
    create_container(parser->commands,COMMAND,poloz);
    create_container(parser->commands,COMMAND,inventar);
    create_container(parser->commands,COMMAND,pouzi);
    create_container(parser->commands,COMMAND,preskumaj);
    create_container(parser->commands,COMMAND,nahraj);
    create_container(parser->commands,COMMAND,uloz);

    return parser;
}

struct parser* destroy_parser(struct parser* parser){
    parser->history = destroy_containers(parser->history);
    parser->commands = destroy_containers(parser->commands);
    free(parser);
    return NULL;
}
struct command* parse_input(struct parser* parser, char* input){
    if(parser == NULL){
        return NULL;
    }
    if(input == NULL){
        return NULL;
    }
    if(strlen(input) == 0){
	return NULL;
    }
    int err;
    struct container* ptr = parser->commands;
    for(;ptr!=NULL; ptr=ptr->next){
        err = regexec(&ptr->command->preg, input,0, NULL,REG_ICASE);
        if(!err){
            parser->history= create_container(parser->history,TEXT,input);
            return ptr->command;
        }
    }
    return NULL;
}
