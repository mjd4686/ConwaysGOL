#include <iostream>
#include "GOL.h"

//Constructor
GOL::GOL(){
    //Initalize grid to false
    for(int i=0; i < gridsize; i++){
        for(int j=0; j < gridsize; j++){
            organisms[i][j] = false;
        }
    }
}

//Renders the grid
void GOL::RenderGrid(SDL_Renderer* renderer){
    //reset render window
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    //render grid with panning and zooming taken into account
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    for(int i=0; i <= gridsize; i++){
        for(int j=0; j <= gridsize; j++){
            SDL_RenderDrawLine(renderer, scale*i + camera_x, 0 + camera_y, scale*i + camera_x, scale*gridsize + camera_y);
            SDL_RenderDrawLine(renderer, 0 + camera_x, scale*j + camera_y, scale*gridsize + camera_x, scale*j + camera_y);
        }
    }
}

//Renders the squares of the organisms that are alive
void GOL::RenderOrgansims(SDL_Renderer* renderer){
    for(int i=0; i < gridsize; i++){
        for(int j=0; j < gridsize; j++){
            SDL_Rect temptangle;
            if(organisms[i][j] == true){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
                temptangle.x = scale*i + camera_x;
                temptangle.y = scale*j + camera_y;
                temptangle.w = scale;
                temptangle.h = scale;
                SDL_RenderFillRect(renderer, &temptangle);
            }
        }
    }
}

//See if neighbor is within the grid and alive
bool GOL::ValidNeighbor(int x, int y){
    if((x >= 0) && (x < gridsize) 
    && (y >= 0) && (y < gridsize)){
        if(organisms[x][y] == true){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

//Check the 8 neighbors to see the number of alive neighbors
void GOL::UpdateOrganisms(){
    bool organsims_updated[gridsize][gridsize];
    for(int i=0; i < gridsize; i++){
        for(int j=0; j < gridsize; j++){
            int num_alive_neighbors = 0;
            if(ValidNeighbor(i, j+1)){
                num_alive_neighbors = num_alive_neighbors + 1;
            }
            if(ValidNeighbor(i, j-1)){
                num_alive_neighbors = num_alive_neighbors + 1;
            }
            if(ValidNeighbor(i+1, j)){
                num_alive_neighbors = num_alive_neighbors + 1;
            }
            if(ValidNeighbor(i+1, j+1)){
                num_alive_neighbors = num_alive_neighbors + 1;
            }
            if(ValidNeighbor(i+1, j-1)){
                num_alive_neighbors = num_alive_neighbors + 1;
            }
            if(ValidNeighbor(i-1, j)){
                num_alive_neighbors = num_alive_neighbors + 1;
            }
            if(ValidNeighbor(i-1, j-1)){
                num_alive_neighbors = num_alive_neighbors + 1;
            }
            if(ValidNeighbor(i-1, j+1)){
                num_alive_neighbors = num_alive_neighbors + 1;
            }
            if(organisms[i][j]){
                if(num_alive_neighbors < 2){
                    organsims_updated[i][j] = false;
                }
                if((num_alive_neighbors == 2) || (num_alive_neighbors == 3)){
                    organsims_updated[i][j] = true;
                }
                if(num_alive_neighbors > 3){
                    organsims_updated[i][j] = false;
                }
            }
            else if(num_alive_neighbors == 3){
                organsims_updated[i][j] = true;
            }
            else{
                organsims_updated[i][j] = false;
            }
        }
    }
    memcpy(organisms, organsims_updated, sizeof(bool)*gridsize*gridsize);
}

//Handle updates 
void GOL::EventsUpdated(SDL_Event event){
    //wheel scrolled
    if(event.type == SDL_MOUSEWHEEL)
    {
        if(event.wheel.y > 0) // scroll up
        {
            // Zoom in 
            scale = scale +1;
            camera_x = camera_x - gridsize/2;
            camera_y = camera_y - gridsize/2;
            change = true;
        }
        else if(event.wheel.y < 0) // scroll down
        {
            // Zoom out
            if(scale > 0){
                scale = scale - 1;
            }
            camera_x = camera_x + gridsize/2;
            camera_y = camera_y + gridsize/2;
            change = true;
        }
    }
    //use mouse click and drags to move grid
    if(prevclick){
            camera_x = camera_x + (event.button.x - prexclick_x);
            camera_y = camera_y + (event.button.y - prexclick_y);
            prexclick_x = event.button.x;
            prexclick_y = event.button.y;
            prevclick = true;
            change = true;
    }
    //right click begins, drag grid
    if((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_RIGHT))
    {
        prexclick_x = event.button.x;
        prexclick_y = event.button.y;
        prevclick = true;
    }
    //right click ends, stop dradding
    if((event.type == SDL_MOUSEBUTTONUP) && (event.button.button == SDL_BUTTON_RIGHT)){
        prevclick = false;
    }
    //left click
    if((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)){
        //std::cout << event.button.x << ", " << event.button.y << std::endl;

        //calculate left click in terms of the grid
        int gridx = (event.button.x - camera_x)/scale;
        int gridy = (event.button.y - camera_y)/scale;

        //see if click cooresponds to a valid grid location
        if((gridx >= 0) && (gridx < gridsize) 
        && (gridy >= 0) && (gridy < gridsize)){

            //set grid tile to be rendered and set the graphic as changed
            organisms[gridx][gridy] = true;
            change = true;
        }
        //std::cout << "grid loc:" << (event.button.x - camera_x)/scale << ", " << (event.button.y - camera_y)/scale  << std::endl;
    }
    //start simulation
    if((event.type == SDL_KEYDOWN) && (event.key.keysym.scancode == SDL_SCANCODE_SPACE)){
        std::cout << "Simulation Started" << std::endl;
        runsimulation = true;
    }
}


//Return if the simulation has started
bool GOL::SimulationStarted(){
    return runsimulation;
}

//Set if the display has been changed and needs to be rerendered
void GOL::SetChange(bool value){
    change = value;
}

//Return if there has been a change
bool GOL::GetChange(){
    return change;
}

