#include <stdio.h>
#include <stdlib.h>
#define image_size 200

struct infoh {
	unsigned int size;               /* Header size in bytes      */
	int height, width;               /* Width and height of image */
	unsigned short int planes;       /* Number of colour planes   */
	unsigned short int bits;         /* Bits per pixel            */
	unsigned int compression;        /* Compression type          */
	unsigned int imagesize;          /* Image size in bytes       */
	int xresolution, yresolution;    /* Pixels per meter          */
	unsigned int ncolours;           /* Number of colours         */
	unsigned int importantcolours;   /* Important colours         */

} pIn, pOut;

struct Pixel {
	unsigned char R, G, B;
};

char  file_name[] = "input.bmp";
FILE *point;
unsigned char pixel[3];

void checkFile() {
    point = fopen(file_name, "rb+");
    if (!point) {
		printf(" please check the file again!\n");
		exit(0);
	}
	else {

        fseek(point, 14, SEEK_SET);
		fread(&pIn, 1, sizeof(infoh), point);

		if (pIn.bits != 24) {
			printf("the file is not a correct bmpfile. please check the file again!\n");
		}
		if (pIn.planes != 1 || pIn.compression != 0) {
			printf("the file is not a correct bmpfile. please check the file again!\n");
		}
	}
}

void readFile(Pixel image[image_size][image_size], int &&width, int &&height) {

	checkFile();
	fseek(point, 14, SEEK_SET);
	fread(&pIn, 1, sizeof(infoh), point); //for width & height
    fseek(point, 54, SEEK_SET); //for pixel

	for (int i = 0, j; i < pIn.width; i++) {
		for (j = 0; j < pIn.height; j++) {
			fread(&pixel, 1, sizeof(pixel), point); //reads a pixel
			image[i][j].B = pixel[0];
			image[i][j].G = pixel[1];
			image[i][j].R = pixel[2];
		}
		char c;
		int temp = j * 3;
		while (temp % 4 != 0) {
			temp++;
			fread(&c, 1, sizeof(char), point);
		}
	}

	fclose(point);

	width = pIn.width;
	height = pIn.height;

}

void writeFile(Pixel image[image_size][image_size]) {

	FILE *point2;
	unsigned char pixel2[3];

    point = fopen(file_name, "rb+");
    point2 = fopen("output.bmp", "wb+");

	char c;
	for (int i = 0; i < 54; i++) {
		fread(&c, 1, sizeof(char), point);
		fwrite(&c, 1, sizeof(char), point2);
	}

	for (int i = 0, j; i < pIn.width; i++) {
		for (j = 0; j < pIn.height; j++) {
			pixel2[0] = image[i][j].B;
			pixel2[1] = image[i][j].G;
			pixel2[2] = image[i][j].R;
			fwrite(&pixel2, 1, sizeof(pixel), point2);
		}

		int temp = j * 3;
		while (temp % 4 != 0) {
			char ch = 0;
			fwrite(&ch, 1, sizeof(char), point2);
			temp++;
		}
	}

	fclose(point);
	fclose(point2);
}
