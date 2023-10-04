#include <SDL.h>
#include<SDL_mixer.h>
#include<iostream>


int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	if (Mix_OpenAudio(44140, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << Mix_GetError() << std::endl;

	Mix_Music* Track1=Mix_LoadMUS("In The End - Linkin Park.mp3");//more than 1o secs 
	Mix_Music* Track2 = Mix_LoadMUS("Papercut - Linkin Park.mp3");
	Mix_Music* Current=nullptr;
//  Mix_Chunk *sound//this is used to play less than 10 sec long sounds


	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Surface* imageSurface = nullptr;
	window = SDL_CreateWindow("PLAYER",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		500,
		500,
		SDL_WINDOW_RESIZABLE);

	if (window == NULL) {
		std::cout << "error creating window" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}

	surface = SDL_GetWindowSurface(window);
	imageSurface = SDL_LoadBMP("art.bmp");
	if (imageSurface == NULL) {
		std::cout << "image loading error" << SDL_GetError << std::endl;
	}
	else {
		SDL_BlitSurface(imageSurface, NULL, surface, NULL);
		SDL_UpdateWindowSurface(window);
	}
	SDL_Event event;//creating an event
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_p://PLAY	
					if (!Mix_PlayingMusic()) {
						if (Current == nullptr || Current == Track2) {
							Current = Track1;
							Mix_PlayMusic(Current, 0);//start from track 1 always 
						}
					
					
					else if (Mix_PausedMusic())
						Mix_ResumeMusic();
					break;

				case SDLK_s: // STOP
					Mix_HaltMusic();
					break;

				case SDLK_n: // NEXT
					Mix_HaltMusic();
					if (Current == Track1)
						Current = Track2;
						Mix_PlayMusic(Current, 0);
					else if (Current == Track2)
						Current = Track1;
						Mix_PlayMusic(Current, 0);
					break;
				}
			}
		}
	}


	Mix_FreeMusic(Track1);
	Mix_FreeMusic(Track2);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
