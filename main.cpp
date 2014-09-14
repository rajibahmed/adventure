/*
 * File:   Main.cpp
 * Author: RAJIB AHMED            - raae10
 * Author: MOHAMMAD ABDUR RAZZAK  - morc10
 *
 * Created on November 15, 2011, 10:52 AM
 */

#include <iostream>
#include "Parser.h"
#include "Player.h"
#include "Element.h"
#include "Node.h"
#include "Socket.h"
#include <cstdlib>
#include <cctype>
#include <signal.h>
using namespace std;

#define HOST "localhost"
#define PORT 3333

int exit_with_error(string msg){
    cout << msg << endl;
    return EXIT_FAILURE;
}



int main() {

    string
    advent_350 ="\n\n\nwelcome to ...\n";
    advent_350 +="  _  __  _ _ ___ _  _ ___ _ _ ___ ___   _____  _\n";
    advent_350+=" / \\|  \\| | | __| \\| |_ _| | | o \\ __| |_ / _// \\  \n";
    advent_350+="| o | o ) V | _|| \\\\ || || U |   / _|  __)\\_ \\ 0 |\n";
    advent_350+="|_n_|__/ \\_/|___|_|\\_||_||___|_|\\\\___| \\__/__/\\_/\n";
    advent_350+="\n               Rajib (raae10) -n- Razzak (morc10)\n";
    cout << advent_350 <<endl;

    Parser game("advent.dat");


    string client_said="";
    Socket server;
    int client_count = 0;

    if(!server.create())    return exit_with_error("Error creating  ");
    if(!server.bind(PORT))  return exit_with_error("Error binding   ");
    if(!server.listen())    return exit_with_error("Error listenting");

    while(true){
      Socket client;
      client.create();
      if(server.accept(client)){
        int pid = fork();
        if( pid > 0 ){


          Player player("Rajib Ahmed", 0 , 1);
          map<string, int>::iterator it;
          string words[3];
          bool show_item= true;


          client.send(advent_350 + "\n");

          for(;;){//game loop

              //this is a socket message
              client.send(game.locations[player.get_current_location()]->get_clue() + "\n");
              player.set_location(game.locations[player.get_current_location()]);



              /*
               * check for items in current player location
               */
              int numer_of_items = player.get_location()->items.size();
              int items_carried = player.carrying.size();

              if(numer_of_items > 0){
                  for (int i = 0; i < numer_of_items; i++) {
                      for(int j=0; j< items_carried ; j++){
                        if(player.carrying[j]->id == player.get_location()->items[i]->id){
                          show_item=false; break;
                        }
                      }
                      if(show_item){
                        client.send("=> " + player.get_location()->items[i]->messages[0] + "\n" ) ;
                      }
                      show_item = true;
                  }
              }

              /*
               * User input handling & formatting
               */
              client.send("~> ") ;//REPL sign :)
              //getline(cin,player.verb);
              client.recv(player.verb);
              player.format_answer();

              //player.carrying.push_back(game.elements[110]);
              //cout << player.carrying[0]->description << endl;

              game.start_idx=0;
              for(int i=0; i<3 ;i++){
                  words[i] = game.tokenizer(player.verb," ");
              }

              !words[0].empty() ? player.verb = words[0] : "";
              !words[1].empty() ? player.noun = words[1] : "";

              if(player.verb == "QUIT"){
                client.close();
                break;
              }
              /*
               * player wants to take Elements
               */
              if(!player.verb.empty() && !player.noun.empty()){
                  it = game.vocabulary.find(player.verb);
                  if(it!=game.vocabulary.end()){
                      if(game.is_action(player.verb) && game.is_object(player.noun)){
                        //cout << "action verb and object sequence" << endl;
                        int element_id = game.vocabulary.find(player.noun)->second;
                        player.carry_item(element_id);
                      }
                  }

              /*
               * player want to only move
               */
              }else if(!player.verb.empty()){
                  it = game.vocabulary.find(player.verb);
                  if(it!=game.vocabulary.end()){
                    if(game.is_motion(player.verb)){

                       player.moves = game.vocabulary.find(player.verb)->second;
                       //cout << player.moves << endl;
                       player.go_to_next_location();

                       if(player.message_id>0){
                          client.send("*=> "+ game.abbr_messages[player.message_id] + "\n");
                          player.message_id=0;
                       }
                    }
                  }else{
                      cout << "dont understand that" << endl;
                  }
              }
          }//game loop
        }//endif fork
      }//client accept
    }//socket while

    return EXIT_SUCCESS;
}
