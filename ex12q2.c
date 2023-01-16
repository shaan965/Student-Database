#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Node {
    int** game;
    struct Node* next;
};

struct LinkedList{
	struct Node* head;
	int size;
};


struct LinkedList* create_linkedlist(){

	struct LinkedList* toret = malloc(sizeof(struct LinkedList));
	toret -> size = 0;
	toret -> head = NULL;
	return toret;
}

void add_to_linkedlist(struct LinkedList* list, int** game_to_add){
	
	//make a copy from the current status of the game ===
	int** copyof_game_to_add = malloc(9*sizeof(int*));
	for(int i=0; i<9; i++){
		copyof_game_to_add[i] = malloc(9*sizeof(int));
	}
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			copyof_game_to_add[i][j] = game_to_add[i][j]; 
		}
	}

	if(list->head == NULL){
		//it is the first node to be added 
		list -> head = malloc(sizeof(struct Node));
		list -> head -> game = copyof_game_to_add;
		list -> head -> next = NULL;

	}else{
		//it is not the first node 
		struct Node* tail = list->head;
		while(tail->next != NULL){
			tail = tail->next; 
		}
		tail-> next = malloc(sizeof(struct Node));
		tail-> next -> game = copyof_game_to_add;
		tail-> next -> next = NULL;
	}
	list->size ++;
}

int my_log10(int n) {
    if (n < 0) return 1;//numPlaces ((n == INT_MIN) ? INT_MAX: -n);
    if (n < 10) return 1;
    return 1 + my_log10(n / 10);
}

char* int_to_str(int i, int num_digits){
	int numdigits_i = my_log10(i) ;
       	char* str_i = malloc(sizeof(char)*(numdigits_i+1));
	char* toret;
	snprintf(str_i, numdigits_i+1, "%d", i);
	if(num_digits > numdigits_i){
		char* leading_zeros = malloc(sizeof(char)*(num_digits-numdigits_i+1));
		for(int j=0; j<(num_digits-numdigits_i); j++){
			leading_zeros[j] = '0';
		}
		leading_zeros[num_digits-numdigits_i] = '\0';
		toret = malloc(sizeof(char)*(num_digits+1));
		for(int j=0; j<num_digits+1; j++){
			toret[j] = 0;
		}
		strcat(toret, leading_zeros);
		strcat(toret, str_i);
		free(leading_zeros);
		free(str_i);
	}else{
		toret = str_i;
	}
	return toret;	
}

void print_board(int** game){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			printf("%d, ", game[i][j]);
		}
		printf("\n");
	}
}

void print_board_tofile(int** game, char* fname_output){
	
	FILE *fptr;
	fptr = fopen(fname_output,"w");

        for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                        fprintf(fptr, "%d ", game[i][j]);
                }
                fprintf(fptr, "\n");
        }
	fclose(fptr);
}


bool solver(int** game, struct LinkedList* linked_list) {//either solved or not; so binary
	bool flag_complete = true; 
        for(int i=0; i<9; i++){ 
                for(int j=0; j<9; j++){
                        if(game[i][j] == 0){
                                flag_complete = false;
                        }
                }
        }
        if(flag_complete == true){
		add_to_linkedlist(linked_list, game);

                return true;
        }

	
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (game[i][j] == 0) {//if non-existance, then solved
				for (int v = 1; v <= 9; v++) {
					game[i][j] = v;//try digit `v`
					bool conflict = false;
					for (int c = 0; c < 9; c++)
						if (c != j && game[i][c] == v) {
							conflict = true;
							break;
						}
					if (conflict) //`v` is out, no more checking, try `v+1`
						continue;
					for (int r = 0; r < 9; r++)
						if (r != i && game[r][j] == v) {
							conflict = true;
							break;
						}
					if (conflict)
						continue;
					int s = i/3, t = j/3; //the sub-cube indices
					for (int c = 0; c < 3; c++) {
						for (int r = 0; r < 3; r++)
							if ((3*s+r != i || 3*t+c != j) && game[3*s+r][3*t+c] == v) {
								conflict = true;
								break;
							}
						if (conflict)
							break;
					}
					if (conflict)
						continue;
					solver(game, linked_list);
					game[i][j] = 0;
					//if (solver(game, linked_list))	
					//	return true; //I missed this `return` in A1 demo: w/o would revert the game
				}
				game[i][j] = 0;//exhaust all 9 digits, w/o stucked with `9`
				return false; //meaning the prevous entry has a wrong try
			}
		}
	//add_to_linkedlist(linked_list, game);
	return true;
}


int main(int argc, char *argv[]){
	//check whether input arguments are valid
	if(argc < 3){
		printf("This program takes in 2 arguments, like ./ex12q2 input.txt 5, but %d inputs arguments were given.\n", argc-1);
		return -1;
	}
	if(argc > 3){
                printf("Too many arguments to the program. This program take in 2 arguments, like ./ex12q2 input.txt 5, but %d > 2 inputs arguments were given.\n", argc-1);
                return -1;
        }
	FILE *file_input = fopen(argv[1], "r");
	if (file_input == NULL) {
		printf("Could not find the file %s in current directory.\n", argv[1]);
		return -1;
	}
	int k = atoi(argv[2]);
	if(k == 0){
		printf("The input k has to be positive, but the given k is %d.\n", k);
		return -1;
	}
	//read the puzzle ===
	int** game = malloc(9 * sizeof(int*));
	for (int i=0; i<9; i++){
		game[i] = malloc(9 * sizeof(int*));
	}
	for (int i = 0; i < 9; i++) {
		
		for(int j=0; j<9; j++){
			game[i][j] = 0;
			if(fscanf(file_input, "%d", &game[i][j]) != 1){
				printf("invalid value at game[%d][%d].\n", i+1, j+1);
				return -1;
			}
			if((game[i][j]<0) || (game[i][j]>9)){
				printf("Values has to be between 0 and 9, but game[%d][%d] is equal to %d.\n", i+1, j+1, game[i][j]);
				return -1; 
			}
				
		}
	}
        fclose(file_input);	
	

	//solve the game ===
	struct LinkedList* linked_list = create_linkedlist();
        solver(game, linked_list);
	printf("The number of solutions to the puzzle is: %d.\n", linked_list->size);

	
	//write some solutions to output files ===
	int numsolutions_tosave = (k > linked_list->size)? linked_list->size : k;
	int num_digits_fname = my_log10(numsolutions_tosave);
	struct Node* current = linked_list -> head;
	for(int i = 0; i < linked_list->size; i++){
		
		if(i< numsolutions_tosave){
			int** game_i = current -> game;
	        
			char* str_i = int_to_str(i+1, num_digits_fname);
			char* fname_i = malloc(sizeof(char)*(strlen("sol") + strlen(str_i) + strlen(".txt")+1));
			for(int j=0; j<(strlen("sol") + strlen(str_i) + strlen(".txt")); j++)
				fname_i[j] = 0;
			fname_i[strlen("sol") + strlen(str_i) + strlen(".txt")] = 0;
			strcat(fname_i, "sol");
			strcat(fname_i, str_i);
	        	strcat(fname_i, ".txt");
			print_board_tofile(game_i, fname_i);
		        free(str_i);
                	free(fname_i);	
		}

		struct Node* temp = current;
		current = current -> next;
		for(int j=0; j<9; j++)
			free(temp->game[j]);
		free(temp->game);
		free(temp);	
	}	

	free(linked_list);
	for (int i=0; i<9; i++){
                free(game[i]);
        }
	free(game);

		
	return 0;

}
