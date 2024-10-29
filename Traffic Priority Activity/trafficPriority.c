#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
typedef char String[15];

typedef struct {
    int priority;      
    String trafficMovement; 
    String lane;         
    int time;             
}Traffic;

typedef struct {
    Traffic data[MAX];
    int lastIndex;
}Heap;

//Priority Levels:
//    0 - Straight   : Main Lane
//    1 - Straight   : Diversion Lane
//    2 - Left       : Main Lane
//    3 - Left       : Diversion Lane
//    4 - Right      : Main Lane
//    5 - Right      : Diversion Lane
//    6 - Pedestrian : Main Lane
//    7 - Pedestrian : Diversion Lane
	
void display(Traffic list[]);
void initHeap(Heap *pQ);
void priorityEnq(Heap *pQ, Traffic t);
int totalTime(Heap *pQ);
void displayPQ(Heap *pQ);

int main(void) {
    Heap pQ;
    initHeap(&pQ);
	
    // Populate and save to traffic.dat
    Traffic list[5] = {
        {6, "pedestrian", "main", 5},   
        {4, "right", "main", 9},    
        {0, "straight", "main", 20},    
		{5, "right", "diversion", 31},             
        {1, "straight", "diversion", 60} 
    };

    FILE *fp;
    fp = fopen("traffic.dat", "wb");
    
    if (fp != NULL) {
        fwrite(list, sizeof(Traffic), 5, fp);
        fclose(fp); 
    } else {
        printf("Error opening file.\n");
    }
    
    // Display traffic scenario
    display(list);
    
    // Enqueue by priority number.
    int x;
    for (x = 0; x < MAX; x++) {
        priorityEnq(&pQ, list[x]);
    }
    
    displayPQ(&pQ);
	
    int res = totalTime(&pQ);
    printf("\nThe time before main lane pedestrian can cross: %d\n", res);

    FILE *fpResults = fopen("traffic_result.dat", "a");
    if (fpResults != NULL) {
        fprintf(fpResults, "The time before main lane pedestrian can cross is: %d\n", res);
        fclose(fpResults);
    } else {
        printf("Error opening results file.\n");
    }
	
    return 0;
}

void display(Traffic list[]) {
    int x;
    printf("Traffic Scenario: ");
    printf("\n----------------------------------------\n");
    printf("%-13s | %-13s | %-10s\n", "Direction", "Lane", "Time");
    printf("----------------------------------------\n");
    
    for (x = 0; x < MAX; ++x) {
        printf("%-13s | %-13s | %d\n", list[x].trafficMovement, list[x].lane, list[x].time);
    }
    
    printf("----------------------------------------\n");
}

void initHeap(Heap *pQ) {
    int x;
    for (x = 0; x < MAX; x++) {
        pQ->data[x].priority = -1;
    }
    pQ->lastIndex = -1;
}

void priorityEnq(Heap *pQ, Traffic t) {
    if (pQ->lastIndex < MAX - 1) {
        pQ->data[++pQ->lastIndex] = t;

        int child = pQ->lastIndex;
        int parent = (child - 1) / 2;
        while (child > 0 && pQ->data[child].priority < pQ->data[parent].priority) {
            Traffic temp = pQ->data[child];
            pQ->data[child] = pQ->data[parent];
            pQ->data[parent] = temp;

            child = parent;
            parent = (child - 1) / 2;
        }
    }
}

int totalTime(Heap *pQ) {
    int result = 0, x;
    for (x = 0; x <= pQ->lastIndex; x++) {
        if (pQ->data[x].priority == 6) { 
            break;  
        }
        result += pQ->data[x].time;  
    }
    return result; 
}

void displayPQ(Heap *pQ) {
    int x;
    printf("\nPriority Queue:\n");
    printf("-------------------------------------------------\n");
    printf("%-8s | %-13s | %-12s | %s\n", "Priority", "Direction", "Lane", "Time");
    printf("-------------------------------------------------\n");
    for (x = 0; x <= pQ->lastIndex; x++) {
        printf("%-8d | %-13s | %-12s | %d\n", pQ->data[x].priority, pQ->data[x].trafficMovement, pQ->data[x].lane, pQ->data[x].time);
    }
    printf("-------------------------------------------------\n");
}

