// videoDriver.c

#include <videoDriver.h>

unsigned int horizontalPixelCount = 1024;
unsigned int verticalPixelCount = 768;
unsigned int numberOfColorBytes = 3;

//Estructura con la informacion que deja el bootLoader
struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode !!!
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen !!!
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

//Puntero a la zona de memoria con la info
struct vbe_mode_info_structure * screenData = (void*)0x5C00;

//Carga el tamaño de la pantalla que haya
void init_VM_Driver() {
	numberOfColorBytes = screenData->bpp / 8;
	verticalPixelCount = screenData->height;
	horizontalPixelCount = screenData->width;
}

void drawPixel(unsigned int x, unsigned int y, int color){
	
    if(x < 0 || x >= horizontalPixelCount || y < 0 || y >= verticalPixelCount)
		return;
	
    char* screen = screenData->framebuffer; 
    unsigned where = (x + y*horizontalPixelCount) * numberOfColorBytes;
    
    screen[where] = color & 255;              // BLUE
    screen[where + 1] = (color >> 8) & 255;   // GREEN
    screen[where + 2] = (color >> 16) & 255;  // RED
}

void copyPixel(unsigned int xSource, unsigned int ySource, unsigned int xDest, unsigned int yDest){
	
    char* screen = screenData->framebuffer; 

    unsigned sourceWhere = (xSource + ySource*horizontalPixelCount) * numberOfColorBytes;
	unsigned destWhere = (xDest + yDest*horizontalPixelCount) * numberOfColorBytes;

    screen[destWhere] = screen[sourceWhere];  			// BLUE
    screen[destWhere + 1] = screen[sourceWhere + 1];   // GREEN
    screen[destWhere + 2] = screen[sourceWhere + 2];  // RED
}

void drawChar(int x, int y, char character, int fontColor, int backgroundColor){
	if(x < 0 || x > horizontalPixelCount - CHAR_WIDTH || y < 0 || y > verticalPixelCount - CHAR_HEIGHT){
		return;
	}

	int aux_x = x;
	int aux_y = y;

	char bitIsPresent;

	unsigned char * toDraw = charBitmap(character);

	for (int i = 0; i < CHAR_HEIGHT; i++){
		for (int j = 0; j < CHAR_WIDTH; j++){
			bitIsPresent = (1 << (CHAR_WIDTH - 1 - j)) & toDraw[i]; //JUGADISIMO pero se le puede restar 1 a j. Confio

			if(bitIsPresent)
				drawPixel(aux_x, aux_y, fontColor);
			else
				drawPixel(aux_x, aux_y, backgroundColor);

				aux_x++;
		}
		aux_x = x;
		aux_y++;
	}
}

int getHorizontalPixelCount(){
	return horizontalPixelCount;
}

int getVerticalPixelCount(){
	return verticalPixelCount;
}