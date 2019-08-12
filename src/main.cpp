#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GOL.h"




int main(int argc, const char* argv[]){
    //init SDL
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {

        //Create window and renderer
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        //Counter used to wait waititerations before updating the simulation
        int count = 0;

        //initalize the game of life class
        GOL instance;

        //Init window and renderer
        if (SDL_CreateWindowAndRenderer(800, 800, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            //Display loop
            while (!done) {
                SDL_Event event;

                //See if anything has happened (mouse click, mouse drag, space click)
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                    //Change display based off events
                    instance.EventsUpdated(event);
                }

                //Only re-render if there has been a change 
                if(instance.GetChange()){
                    instance.RenderGrid(renderer);
                    instance.RenderOrgansims(renderer);

                    //Render the graphic
                    SDL_RenderPresent(renderer);
                }
                //Set change to false after rendering
                instance.SetChange(false);

                //Update organisms locations based off Conway's Game of Life rules
                if(instance.SimulationStarted() && (count > waititerations)){
                        instance.UpdateOrganisms();
                        instance.SetChange(true);
                        count = 0;
                }
                count = count + 1; 
            }
        }

        //clean up
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;

    return EXIT_SUCCESS;
}