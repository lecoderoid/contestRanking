#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct{
  char name[50];
  double *scores;
  double average;
}Contestant;
void flush(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}
void sort(Contestant *c, unsigned int s){
  for(unsigned int i = 0; i<s; ++i){
    for(unsigned int j = 0; j<(s-1); ++j){
      if(c[j].average < c[j + 1].average){
        Contestant temp = c[j];
        c[j] = c[j + 1];
        c[j + 1] = temp;
      }
    }
  }
}

int main(){
  Contestant *contestants = NULL;
  unsigned int numContestants, numScores;

  printf("Enter number of contestants: ");
  scanf("%d", &numContestants);

  contestants = malloc(numContestants * sizeof(Contestant));
  if(!contestants){
    puts("Can't allocate memory!");
    return 1;
  }
  
  printf("Enter the number of scores: ");
  scanf("%d",&numScores);

  for(unsigned int i = 0; i < numContestants; ++i){
    (contestants + i)->scores = (double*) malloc(numScores * sizeof(double));
    if(!(contestants + i)->scores){
      puts("Can't allocate memory for scores.\n");
      return 1;
    }
  }  
  for(unsigned int i = 0; i < numContestants; ++i){
    flush();
    printf("Enter group/individual name: ");
    if(fgets((contestants + i)->name, sizeof((contestants + i)->name), stdin) == NULL){
      puts("Error reading name");
      return 1;
    }
    
    printf("Enter the scores for %s\n", (contestants+i)->name);
    for(unsigned int j = 0; j < numScores; ++j){
      printf("Judge %d: ", j+1);
      scanf("%lf", &(contestants+i)->scores[j]);
    }
  }
  
  double average = 0.0;
  double sum = 0.0;

  for(unsigned int i  = 0; i < numContestants; ++i){
    printf("\nGroup/Individual name: %s", contestants[i].name);
    for(unsigned j = 0; j < numScores; ++j){
      sum += (contestants + i)->scores[j];
    }
    (contestants + i)->average = sum / numScores;
    printf("\nAverage: %.2f\n", round((contestants + i)->average*10.0)/10.0);
    sum = 0.0;
  }

  sort(contestants, numContestants);
  puts("\n--------------------RANKING---------------------");
  for(unsigned int i = 0; i < numContestants; ++i){
    printf("RANK %d: ",(int)(i+1));
    printf("Group/Individual name: %s | ", contestants[i].name);
    printf("Average: %.1f\n", contestants[i].average);
  }
  puts("");
  //free memory
  for(unsigned int i = 0; i < numContestants; ++i)
    free(contestants[i].scores);
  free(contestants);

  return 0;
}


