#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "geometry.h"
#include "global.h"
#include "quadTree.h"
#include "simulation.h"

void drawCircle(SDL_Renderer* renderer, int xc, int yc, int r) {
    int x = 0, y = r;

    SDL_RenderDrawPoint( renderer, xc+x, yc-y );

    int p = 3 - (2*r);

    for ( x=0 ; x<=y ; x++ )
    {
        if ( p<0 )
        {
            p = ( p + (4*x) + 6 );
        }
        else
        {
            y -= 1;
            p += ( ( 4*(x-y) + 10) );
        }
        SDL_RenderDrawLine ( renderer, xc+x, yc-y, xc-x, yc-y);
        SDL_RenderDrawLine ( renderer, xc+x, yc+y, xc-x, yc+y);
        SDL_RenderDrawLine( renderer, xc+y, yc-x, xc-y, yc-x);
        SDL_RenderDrawLine ( renderer, xc+y, yc+x, xc-y, yc+x);
    }

}

void drawTree(SDL_Renderer* renderer, Quad* quad) {
    /*
    if (quad->id == -1)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    else if (quad->id == 0)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    else if (quad->id == 1)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    else if (quad->id == 2)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    else if (quad->id == 3)
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    else if (quad->id == 4)
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    */
    

    drawCircle(renderer, quad->boundary.x, quad->boundary.y, 10);
    if (!quad->is_divided) return;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, quad->boundary.x, quad->boundary.y, quad->northwest->boundary.x, quad->northwest->boundary.y);
    drawTree(renderer, quad->northwest);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, quad->boundary.x, quad->boundary.y, quad->northeast->boundary.x, quad->northeast->boundary.y);
    drawTree(renderer, quad->northeast);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, quad->boundary.x, quad->boundary.y, quad->southwest->boundary.x, quad->southwest->boundary.y);
    drawTree(renderer, quad->southwest);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, quad->boundary.x, quad->boundary.y, quad->southeast->boundary.x, quad->southeast->boundary.y);
    drawTree(renderer, quad->southeast);
}

void drawSize(Quad* quad, SDL_Renderer* renderer) {
    if (quad->size == 0)
        SDL_SetRenderDrawColor(renderer, 20,20,20, 255);
    else if (quad->size == 5)
        SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
    else if (quad->size == 4)
        SDL_SetRenderDrawColor(renderer, 0,255,0, 255);
    else if (quad->size == 1)
        SDL_SetRenderDrawColor(renderer, 255,0,0, 255);
    else 
        SDL_SetRenderDrawColor(renderer, 0,0,255, 255);

    drawCircle(renderer, quad->boundary.x, quad->boundary.y, 10);

    if ( !quad->is_divided ) return;
    else {
        drawSize(quad->northwest, renderer);
        drawSize(quad->northeast, renderer);
        drawSize(quad->southwest, renderer);
        drawSize(quad->southeast, renderer);
    }
}

void init_system_test() {
    WIDTH = HEIGHT = 800;
    N = 5;
    Nt = 1000;
    masse = 50;

    // Pointer to all particles
    fluid = malloc(N * sizeof(Particle));

    fluid[0].pos.x = 50;
    fluid[0].pos.y = 50; 

    fluid[1].pos.x = 750-10;
    fluid[1].pos.y = 750-10; 

    fluid[2].pos.x = 750+10;
    fluid[2].pos.y = 750+10; 

    fluid[3].pos.x = 750-10;
    fluid[3].pos.y = 750+10; 

    fluid[4].pos.x = 750+10;
    fluid[4].pos.y = 750-10; 

    for(int i=0 ; i<5 ; i++) {
        fluid[i].vel.x = 0;
        fluid[i].vel.y = 0;
    }

}

void compute_acceleration_test(Quad* quad, int i, SDL_Renderer* renderer) {
    if (!quad->is_divided) {
        if (quad->id == i || quad->size==0) return;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, fluid[i].pos.x, fluid[i].pos.y, fluid[quad->id].pos.x, fluid[quad->id].pos.y);
    } 
    else {
        double r2 = pow(quad->boundary.x - fluid[i].pos.x, 2) +
                    pow(quad->boundary.y - fluid[i].pos.y, 2);
        double theta = pow(2*quad->boundary.w,2) / r2;

        if( theta < 0.5 ) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            Point cm = centerOfMass(quad);
            cm.x = cm.x / quad->size;
            cm.y = cm.y / quad->size;

            SDL_RenderDrawLine(renderer, fluid[i].pos.x, fluid[i].pos.y, cm.x, cm.y);
            return;
        }

        compute_acceleration_test(quad->northwest, i, renderer);
        compute_acceleration_test(quad->northeast, i, renderer);
        compute_acceleration_test(quad->southwest, i, renderer);
        compute_acceleration_test(quad->southeast, i, renderer);
    }
}

int main() {
    unsigned char quit = 0;
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_OPENGL, &window, &renderer);

    init_system_test();
    Rect boundary = newRect(WIDTH/2,HEIGHT/2,WIDTH/2,HEIGHT/2);
    Quad* quad;


    while( !quit ) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      quad = newQuad(boundary);
      subdivide(quad);

      for( int i=0 ; i<N ;i++) {
          insertParticle(quad, i);
      }

      compute_acceleration_test(quad, 0, renderer);


      for(int i=0 ; i<N ; i++)
      {
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          drawCircle(renderer, fluid[i].pos.x, fluid[i].pos.y, 3);
      }

      //drawSize(quad, renderer);
      //drawQuad(renderer, quad);

      SDL_RenderPresent(renderer);
      SDL_Delay(100);

      while (SDL_PollEvent(&event))
      if (event.type == SDL_QUIT)
          quit = 1;
      else
          if (event.type == SDL_KEYDOWN)
          if (event.key.keysym.sym == SDLK_q)
              quit = 1;

    }

    // CLEAN
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;


}