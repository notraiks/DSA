#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
typedef char String[MAX];

typedef struct {
    int priority;      
    String trafficMovement; 
    String lane;         
    int time;             
} trafficPriority;

void display(trafficPriority tp);

int main(void) {
    trafficPriority list[8] = {
        {1, "straight", "main", 50},   
        {2, "left", "main", 20},    
        {3, "right", "main", 10},    
		{4, "pedestrian", "main", 30},             
        {5, "straight", "diversion", 50}, 
        {6, "left", "diversion", 20},    
        {7, "right", "diversion", 10},     
        {8, "pedestrian", "diversion", 30}, 
    };

    FILE *fp;
    fp = fopen("traffic.dat", "wb");
    
    if (fp != NULL) {
        fwrite(list, sizeof(trafficPriority), 6, fp);
        fclose(fp); 
    } else {
        printf("Error opening file.\n");
    }
    
    int x;
    for (x = 0; x < 8; ++x) {
        display(list[x]);
        printf("\n");
    }
    
    return 0;
}

void display(trafficPriority tp) {
    printf("%-10d | %-10s | %-10s | %d", tp.priority, tp.trafficMovement, tp.lane, tp.time);
}

