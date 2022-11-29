#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 5
#define size 4

//make sure that size is always SIZE-1

/************************************************************************************************************************************************************************************
 * base char array is where cells are represented
 * each cell in base array has a corresponding cell in change int array
 * defualt value of each cell in change array is zero
 * basic logic is that, if the status of a cell in base has to be changed (i.e from dead to alive or vice versa), the value of the corresponding change cell will be set to one.
 * for each element that has the change cell value equal to one, their status is flipped when the next generation is printed
*************************************************************************************************************************************************************************************/

char base[SIZE][SIZE];
int change[SIZE][SIZE];

void assignBase(void);

void initializeBase(void);

//returns a random number between [0, n-1]
int entropy(int n){
    return rand()%n;
}
void printBase(void);

void reset(void);

void apply(void);

void corners(void);

void edges(void);

void interior(void);

int main(void){


    
    srand(time(0));
    assignBase();
    initializeBase();

    printf("Welcome to conway's game of life. The initial seed is randomized, you can control the number of iterations that you want to run. Enter an integer: \n");
    int count;
    scanf("%d",&count);
    printf("\nThe base seeed is: \n");
    printBase();

    int iteration = 1;

    //adjust how long you want the game to run for using this loop
    for(int i = 0; i < count; i++){
        corners();
        edges();
        interior();
        apply();
        printf("\nIternation number %d:", iteration);
        printBase();
        reset();
        iteration++;
    }



    return 0;
}

//initially sets all values to blank

void assignBase(void){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            base[i][j] = ' ';
        }
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            change[i][j] = 0;
        }
    }   

}

//prints it

void printBase(void){
    printf("\n");
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            printf("%c  ", base[i][j]);
        }
        printf("\n");
    }
}

//this makes the random initial seed

void initializeBase(void){

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){

            //50-50 chance of a cell being live
            int cat = entropy(2);
            if(cat==1){base[i][j]='*';}
        }
    }
}

//applies conditions to corners

void corners(void){

    //corner top left
    {
        int count = 0;
        if(base[0][1] == '*'){count+=1;}
        if(base[1][1] == '*'){count+=1;}
        if(base[1][0] == '*'){count+=1;}
        
        if(base[0][0] == ' '){
            //cell becomes alive
            if(count == 3){
                change[0][0] = 1;
            }
        }
        else if(base[0][0] == '*'){
            //cell dies
            if(count<2){
                change[0][0] = 1;
            }
        }

    }

    //corner bottom left
    {
        int count = 0;
        if(base[size-1][0] == '*'){count+=1;}
        if(base[size-1][1] == '*'){count+=1;}
        if(base[size][1] == '*'){count+=1;}
        
        if(base[size][0] == ' '){
            //cell becomes alive
            if(count == 3){
                change[size][0] = 1;
            }
        }
        else if(base[size][0] == '*'){
            //cell dies
            if(count<2){
                change[size][0] = 1;
            }
        }

    }

    //corner top right
    {
        int count = 0;
        if(base[0][size-1] == '*'){count+=1;}
        if(base[1][size-1] == '*'){count+=1;}
        if(base[1][size] == '*'){count+=1;}
        
        if(base[size][0] == ' '){
            //cell becomes alive
            if(count == 3){
                change[0][size] = 1;
            }
        }
        else if(base[size][0] == '*'){
            //cell dies
            if(count<2){
                change[0][size] = 1;
            }
        }

    }
    //corner bottom right
    {
        int count = 0;
        if(base[size][size-1] == '*'){count+=1;}
        if(base[size-1][size-1] == '*'){count+=1;}
        if(base[size-1][size] == '*'){count+=1;}
        
        if(base[size][size] == ' '){
            //cell becomes alive
            if(count == 3){
                change[size][size] = 1;
            }
        }
        else if(base[size][size] == '*'){
            //cell dies
            if(count<2){
                change[size][size] = 1;
            }
        }

    }
}

//applies conditions to edges

void edges(void){
    //top edge
    for(int i = 1; i <  size; i++){
        int count = 0;
        if(base[0][i-1] == '*'){count++;}
        if(base[1][i-1] == '*'){count++;}
        if(base[1][i] == '*'){count++;}
        if(base[1][i+1] == '*'){count++;}
        if(base[0][i+1] == '*'){count++;}

        //cell dies
        if(base[0][i] == '*'){
            //overpopulation
            if(count > 3){
                change[0][i] = 1;
            }
            //underpopulation
            if(count < 2){
                change[0][i] = 1;
            }
        }
        //cell becomes alive
        if(base[0][i] == ' '){
            if(count == 3){
                change[0][i] = 1;
            }
        }
    }
    //left edge
    for(int i = 1; i <  size; i++){
        int count = 0;
        if(base[i-1][0] == '*'){count++;}
        if(base[i-1][1] == '*'){count++;}
        if(base[i][1] == '*'){count++;}
        if(base[i+1][1] == '*'){count++;}
        if(base[i+1][0] == '*'){count++;}

        //cell dies
        if(base[i][0] == '*'){
            //overpopulation
            if(count > 3){
                change[i][0] = 1;
            }
            //underpopulation
            if(count < 2){
                change[i][0] = 1;
            }
        }
        //cell becomes alive
        if(base[i][0] == ' '){
            if(count == 3){
                change[i][0] = 1;
            }
        }
    }
    
    //bottom edge

    for(int i = 1; i <  size; i++){
        int count = 0;
        if(base[size][i-1] == '*'){count++;}
        if(base[size-1][i-1] == '*'){count++;}
        if(base[size-1][i] == '*'){count++;}
        if(base[size-1][i+1] == '*'){count++;}
        if(base[size][i+1] == '*'){count++;}

        //cell dies
        if(base[size][i] == '*'){
            //overpopulation
            if(count > 3){
                change[size][i] = 1;
            }
            //underpopulation
            if(count < 2){
                change[size][i] = 1;
            }
        }
        //cell becomes alive
        if(base[0][i] == ' '){
            if(count == 3){
                change[size][i] = 1;
            }
        }
    }

    //right edge
    for(int i = 1; i <  size; i++){
        int count = 0;
        if(base[i-1][size] == '*'){count++;}
        if(base[i-1][size-1] == '*'){count++;}
        if(base[i][size-1] == '*'){count++;}
        if(base[i+1][size-1] == '*'){count++;}
        if(base[i+1][size] == '*'){count++;}

        //cell dies
        if(base[i][size] == '*'){
            //overpopulation
            if(count > 3){
                change[i][size] = 1;
            }
            //underpopulation
            if(count < 2){
                change[i][size] = 1;
            }
        }
        //cell becomes alive
        if(base[i][size] == ' '){
            if(count == 3){
                change[i][size] = 1;
            }
        }
    }


}

//applies conditions to cells with 8 cells bordering them


void interior(void){
    for(int i = 1; i < size; i++){
        for(int j = 1; j < size; j++){
            int count = 0;
            if(base[i-1][j-1] == '*'){count++;}
            if(base[i-1][j] == '*'){count++;}
            if(base[i-1][j+1] == '*'){count++;}
            if(base[i][j-1] == '*'){count++;}
            if(base[i][j+1] == '*'){count++;}
            if(base[i+1][j-1] == '*'){count++;}
            if(base[i+1][j] == '*'){count++;}
            if(base[i+1][j+1] == '*'){count++;}

            //cell dies
            if(base[i][j] == '*'){
                //overpopulation
                if(count > 3){
                    change[i][j] = 1;
                }
                //underpopulation
                if(count < 2){
                    change[i][j] = 1;
                }
            }
            //cell becomes alive
            if(base[i][j] == ' '){
                if(count == 3){
                    change[i][j] = 1;
                }
            }

        }
    }
}


//resets the table for the next generation

void reset(void){

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            change[i][j] = 0;
        }
    }

}

//applies changes

void apply(void){


    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(change[i][j]==1){
                if(base[i][j]==' '){base[i][j] ='*';}
                else{base[i][j] = ' ';}
            }
        }
    }
   
}