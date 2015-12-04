#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#define INDEX(r,c,w) (((r+1)*w)+(c+1)) // Borders are blank

typedef enum {ZOMBIE, HUMAN, COP} person_t;

typedef struct {
	bool occupied;
	person_t person;
	
} cell;

cell* grid;
int width;
int height;

double when() {
        struct timeval tp;
        gettimeofday(&tp, NULL);
        return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

bool rand_val(double prob) {
	return rand() < prob * ((double)RAND_MAX + 1.0);
}

void printGrid(cell* grid) {
	int i, j;
	int h = 0;
	int z = 0;
	int c = 0;
	int e = 0;;
	cell cur_cell;
	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++) {
			cur_cell = grid[INDEX(i, j, width)];
			if(cur_cell.occupied) {
				printf("1 ");
				/*switch(cur_cell.person) {
					case HUMAN:
						printf("H "); h++;
						break;
					case ZOMBIE:
						printf("Z "); z++;
						break;
					case COP:
						printf("C "); c++;
						break;
				}*/
			}
			else {
				printf("0 ");// e++;
			}
		}
		printf("\n");
	}
	printf("\n");
	//printf("humans: %i\nzombies: %d\ncops: %d\nempty: %d\ntotal: %d\n", h, z, c, e, h+z+c+e);
}

int main(int argc, char* argv[]) {
	int i, j;
	int numiterations = 1;
	/* Create Grid */
	width  = 20;
	height = 20;
	grid = (cell*)calloc(width+2 * height+2, sizeof(cell)); // We want borders to be blank

	/* Initialize Grid */

	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++) {
			grid[INDEX(i,j,width)].occupied = rand_val(.25) ? true : false;
			if(grid[INDEX(i,j,width)].occupied) {
				grid[INDEX(i,j,width)].person = rand_val(.99) ? HUMAN : ZOMBIE;
			}
		}
	}

	int num_neighbors;
	while(numiterations--) {
		for(i = 0; i < height; i++) {
			for(j = 0; j < width; j++) {
				num_neighbors = grid[INDEX(i-1,j,width)].occupied +
						grid[INDEX(i,j-1,width)].occupied +
						grid[INDEX(i+1,j,width)].occupied +
						grid[INDEX(i,j+1,width)].occupied;
				printf("num_neighbors %d\n", num_neighbors);
				if(num_neighbors < 2)
					grid[INDEX(i,j,width)].occupied = 0;
				if(num_neighbors == 3)
					grid[INDEX(i,j,width)].occupied = 1;
				if(num_neighbors > 3)
					grid[INDEX(i,j,width)].occupied = 0;
					
			}
		}
		printGrid(grid);
	}
	
	printGrid(grid);

	/* Free stuff */
	free(grid);
	return 0;
}
/*
void drawGrid() {
	int draw = 0;
        glRasterPos2f(-1, -1);
        glDrawPixels(width, height, GL_LUMINANCE, GL_FLOAT, grid);
        glFlush();
        glutSwapBuffers();
        glutPostRedisplay();
        draw++;
        if (draw > 50) glutLeaveMainLoop();
        if (!running) glutLeaveMainLoop();
}

void *visualizer(void* args) {
	int i,j;
	int argc = 0;
	char** argv = 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("Grid Filter");
        grid = (float*)malloc(sizeof(float) * width * height);
        for (i = 0; i < height; i++) {
                for (j = 0; j < width; j++) {
                        grid[i*width+j] = 0.75f;
                        //grid[i*width+j] = 0.0f;
                }
        }
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
        glutDisplayFunc(drawGrid);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glutMainLoop();
}
*/
