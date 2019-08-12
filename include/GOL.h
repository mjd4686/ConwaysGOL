#include <SDL2/SDL.h>

//Size of the grid used by the whole program
#define gridsize 70

//Numer of display iterations to wait before updating the Simulation
#define waititerations 100000


class GOL 
{ 
    public: 

    GOL();

    void RenderGrid(SDL_Renderer* renderer);

    void RenderOrgansims(SDL_Renderer* renderer);

    bool ValidNeighbor(int x, int y);

    void UpdateOrganisms();

    void EventsUpdated(SDL_Event event);

    bool SimulationStarted();

    void SetChange(bool value);

    bool GetChange();

    private:

    int camera_x = 0;
    int camera_y = 0;
    int scale = 10;

    bool prevclick = false;
    int prexclick_x = 0;
    int prexclick_y = 0;

    bool change = true;

    bool runsimulation = false;

    bool organisms[gridsize][gridsize];

}; 