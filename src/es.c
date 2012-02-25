#include "es.h"
#include "mm.h"
#include "const.h"
#include <stdlib.h>
#include <SDL/SDL.h>

SDL_Surface *screen, *image;  //surfaces fixes
SDL_Surface *img;             //surface changeante
SDL_Rect dst;                 //rectangles
SDL_Event event;              //evenements

//initialisation SDL
void SDL_init()
{
  SDL_Init(SDL_INIT_VIDEO) == -1;
  atexit(SDL_Quit);
  screen = SDL_SetVideoMode(300, 525, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 96, 96, 96));

  image = SDL_LoadBMP(BACK);
  dst.w = image->w;
  dst.h = image->h;
  dst.x = 0;
  dst.y = 0;
  SDL_BlitSurface(image, NULL, screen, &dst);
  SDL_Flip(screen);

  image = SDL_LoadBMP(GRILLE);
    SDL_SetColorKey(image, SDL_SRCCOLORKEY,
  SDL_MapRGB(image->format, 255, 0, 255));
  dst.w = image->w;
  dst.h = image->h;
  SDL_BlitSurface(image, NULL, screen, &dst);
  SDL_Flip(screen);

  SDL_FreeSurface(image);

  case_affiche(11, TOURS + 1, 0);
  case_affiche(11, TOURS + 1, 1);
  case_affiche(11, TOURS + 1, 2);
  case_affiche(11, TOURS + 1, 3);

  SDL_WM_SetCaption(APP_NAME, NULL);
}

//traduction en couleur
void couleur(int ball, char img_file[FS_MAX])
{
  switch(ball)
  {
    case 0: strcpy(img_file, CUR);break;
    case 1: strcpy(img_file, C1); break;
    case 2: strcpy(img_file, C2); break;
    case 3: strcpy(img_file, C3); break;
    case 4: strcpy(img_file, C4); break;
    case 5: strcpy(img_file, C5); break;
    case 6: strcpy(img_file, C6); break;
    case 7: strcpy(img_file, C_OK); break;
    case 8: strcpy(img_file, C_IN); break;
    case 9: strcpy(img_file, GAGNE); break;
    case 10: strcpy(img_file, PERDU); break;
    case 11: strcpy(img_file, C_INT); break;
  }
}

//affichage d'une balle
void case_affiche(int nimg, int tour, int pos)
{
  char img_file[FS_MAX];

  couleur(nimg, img_file);
  img = SDL_LoadBMP(img_file);

  SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format, 255, 0, 255));
  dst.w = img->w;
  dst.h = img->h;
  dst.x = 15 + (pos * 30) + 2;
  dst.y = (tour - 1) * 30 + (15 * tour) + 2;
  if (tour == TOURS + 1) dst.y += 15;
  SDL_BlitSurface(img, NULL, screen, &dst);
  SDL_Flip(screen);

  char titre[256];
  strcpy(titre, APP_NAME);
  strcat(titre, MSG_BASE);
  SDL_WM_SetCaption(titre, NULL);
}

//affichage du message de fin
void msg_end(int gagne, int tour, combinaison comb)
{
  if (gagne)
  {
    case_affiche(comb[0], TOURS + 1, 0);
    case_affiche(comb[1], TOURS + 1, 1);
    case_affiche(comb[2], TOURS + 1, 2);
    case_affiche(comb[3], TOURS + 1, 3);
    case_affiche(9, TOURS + 1, NB_POSITIONS + 1);
  }
  else
  {
    case_affiche(comb[0], TOURS + 1, 0);
    case_affiche(comb[1], TOURS + 1, 1);
    case_affiche(comb[2], TOURS + 1, 2);
    case_affiche(comb[3], TOURS + 1, 3);
    case_affiche(10, TOURS + 1, NB_POSITIONS + 1);
  }
}

//saisie d'une combinaison
void comb_saisie(combinaison *comb, int tour)
{
  int done = 0;
  int pos = 0;	//position sur la combinaison

  case_affiche((*comb)[0], tour, 0);
  case_affiche((*comb)[1], tour, 1);
  case_affiche((*comb)[2], tour, 2);
  case_affiche((*comb)[3], tour, 3);
  case_affiche(0, tour, pos);

  while(!done)
    {
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        //actions de touches
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_UP)
            (*comb)[pos]++;
          if(event.key.keysym.sym == SDLK_DOWN)
            (*comb)[pos]--;
          if(event.key.keysym.sym == SDLK_LEFT)
            pos--;
          if(event.key.keysym.sym == SDLK_RIGHT)
            pos++;
          if(event.key.keysym.sym == SDLK_RETURN)
            done = 1;
          if(event.key.keysym.sym == SDLK_ESCAPE)
            exit(EXIT_SUCCESS);

          //controle sur nouvelle position
          if (pos > NB_POSITIONS - 1)
            pos = 0;
          if (pos < 0)
            pos = NB_POSITIONS - 1;

          //controle sur nouvelle couleur
          if ((*comb)[pos] > NB_COULEURS)
            (*comb)[pos] = 1;
          if ((*comb)[pos] < 1)
            (*comb)[pos] = NB_COULEURS;

          //affichage
          case_affiche((*comb)[0], tour, 0);
          case_affiche((*comb)[1], tour, 1);
          case_affiche((*comb)[2], tour, 2);
          case_affiche((*comb)[3], tour, 3);
          if (!done) case_affiche(0, tour, pos);
          break;
      }
    }
  }
}

//affichage des caractères bon ou mal placée
void diag_affiche(int tour, int ok, int in)
{
  int pos = 0;

  while (ok > 0)
  {
    case_affiche(7, tour, pos + NB_POSITIONS + 1);
    pos++;
    ok--;
  }

  while (in > 0)
  {
    case_affiche(8, tour, pos + NB_POSITIONS + 1);
    pos++;
    in--;
  }
}

//pause
int final_pause()
{
  int done = 0;
  char titre[256];
  strcpy(titre, APP_NAME);
  strcat(titre, MSG_END);
  SDL_WM_SetCaption(titre, NULL);
  while(!done)
    {
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_ESCAPE)
            done = 1;
          if(event.key.keysym.sym == SDLK_F2)
            done = 2;
          break;
      }
    }
  }
  return done;
}
