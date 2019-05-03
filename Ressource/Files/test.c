#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
#include <SFML/Graphics/Export.h>
#include <SFML/System/Time.h>
#include <SFML/Window/Keyboard.h>
#include <stdlib.h>
#include <stdio.h>
int windows()
{
	sfVideoMode mode = {800,600,150};
	sfRenderWindow* window;
	sfTexture* visor;
	sfTexture* texture;
	sfTexture* background;
	sfSprite *Visor;
	sfSprite* sprite_background;
	sfSprite* sprite;
	sfMusic* music;
	sfMusic* sound;
	sfEvent event;
	sfClock *clock;
	sfTime time;
	sfIntRect rect;
	float second;
	sfVector2f position;
	sfVector2f pos_visor;
	sfVector2f origin;
	/* Create the main window */
	window = sfRenderWindow_create(mode, "Duck Hunt", sfResize | sfClose, NULL);
	if (!window)
		return (0);
	/* Load a sprite to display */
	visor = sfTexture_createFromFile("Ressource/Texture/visor.png",NULL);
	texture = sfTexture_createFromFile("Ressource/Texture/sprite.png.png", NULL);
	background = sfTexture_createFromFile("Ressource/Texture/background.png", NULL);
	if (!texture)
		return(0);
	Visor = sfSprite_create();
	sprite_background = sfSprite_create();
	sprite = sfSprite_create();

	sfSprite_setTexture(Visor,visor,sfTrue);
	sfSprite_setTexture(sprite_background, background, sfTrue);
	sfSprite_setTexture(sprite, texture, sfTrue);


	clock = sfClock_create();

	
	/*	 Load a music to play */				
	music = sfMusic_createFromFile("Ressource/Sound/musique.ogg");
	sound = sfMusic_createFromFile("Ressource/Sound/coin_effect.ogg");

	if (!music) 
		return(0); 
/* /\*   Play the music *\/ */
	sfMusic_play(music); 
	/* Start the game loop */
	sfRenderWindow_setMouseCursorVisible(window,sfFalse);
	position.x = -10;
	position.y = rand() % 580;

	origin.x = 22;
	origin.y = 22;
	
	sfSprite_setOrigin(Visor,origin);
	while (sfRenderWindow_isOpen(window))
	{
		pos_visor.x = sfMouse_getPositionRenderWindow(window).x;
		pos_visor.y = sfMouse_getPositionRenderWindow(window).y;

	        sfSprite_setPosition(Visor,pos_visor); 
		
		sfRenderWindow_drawSprite(window,sprite_background,NULL);
		time = sfClock_getElapsedTime(clock);
		second = time.microseconds / 100000.0;
		sfSprite_setTextureRect(sprite, rect);


		sfSprite_setPosition(sprite,position);

		if (position.x > 800) {
			position.x = -30;
			position.y = rand() % 580;
		}
		
		position.x += 0.7;
		
		 if (second > 0.0 && second < 1) {  
		  	rect.top = 0; 
		  	rect.left = 0;  
		  	rect.width = 35;  
		  	rect.height = 37;  
			
		 }  
		 if (second > 1 && second < 2) {  
		 	rect.top = 0;  
		 	rect.left = 36;  
		 	rect.width = 49; 
		 	rect.height = 37;  
	       
		 }  
		 if (second > 2  && second < 3) {  
		 	rect.top = 0;  
		 	rect.left = 49;  
		 	rect.width = 39;  
		 	rect.height = 37;  
		 } 

			 if (second > 3  && second < 4) {
		 	rect.top = 0; 
		 	rect.left = 39; 
		 	rect.width = 48; 
		 	rect.height = 37; 
		 } 
				
		 if (second > 4) {  
		 	sfClock_restart(clock);  
		 } 		 

		
		/* Process events */
		while (sfRenderWindow_pollEvent(window, &event)) {
			
			/* Close window : exit */
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
			if (event.type == sfEvtMouseButtonPressed) {
				if (pos_visor.x >= position.x && pos_visor.x <= position.x + 50
				    && pos_visor.y >= position.y && pos_visor.y <= position.y + 50) {
					sfMusic_play(sound);
					position.x = -45;
					position.y = rand() % 500;
				}
			}
		}
		/* Draw the sprite */
		sfRenderWindow_drawSprite(window, Visor,NULL);
		sfRenderWindow_drawSprite(window, sprite, NULL);
				
		
		/* Update the window */
		
		sfRenderWindow_display(window);
	}
/* Cleanup resources */
	sfMusic_destroy(music);
	sfSprite_destroy(sprite_background);
	sfTexture_destroy(background);
	sfSprite_destroy(sprite);
	sfTexture_destroy(texture);
	sfTexture_destroy(visor);
	sfSprite_destroy(Visor);
	sfRenderWindow_destroy(window);
	return(0);
}

int main()
{
	
	windows();
	return(0);
		
}
