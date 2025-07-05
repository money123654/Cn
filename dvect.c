#include <stdio.h>

#define MAX_NODES 10
#define INFINITY 9999

void printRoutingTable(int costMatrix[MAX_NODES][MAX_NODES], int numNodes) {
    printf("\nRouting Table:\n");
    printf("Router | ");
    for (int i = 0; i < numNodes; i++) {
        printf("To %-6d", i);
    }
    printf("\n");
    printf("-------|");
    for (int i = 0; i < numNodes; i++) {
        printf("---------");
    }
    printf("\n");

    for (int i = 0; i < numNodes; i++) {
        printf("   %-4d | ", i);
        for (int j = 0; j < numNodes; j++) {
            if (costMatrix[i][j] == INFINITY)
                printf("INF     ");
            else
                printf("%-8d", costMatrix[i][j]);
        }
        printf("\n");
    }
}

void distanceVectorRouting(int costMatrix[MAX_NODES][MAX_NODES], int numNodes) {
    int distance[MAX_NODES][MAX_NODES], nextHop[MAX_NODES][MAX_NODES];

    // Initialize distance and nextHop matrices
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            distance[i][j] = costMatrix[i][j];
            if (costMatrix[i][j] != INFINITY && i != j)
                nextHop[i][j] = j;
            else
                nextHop[i][j] = -1;
        }
    }

    // Update distance and nextHop matrices
    for (int k = 0; k < numNodes; k++) {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    nextHop[i][j] = nextHop[i][k];
                }
            }
        }
    }

    // Print the routing tables for each router
    for (int i = 0; i < numNodes; i++) {
        printf("\nRouting table for Router %d:\n", i);
        printf("Destination | Next Hop | Distance\n");
        printf("------------|----------|---------\n");
        for (int j = 0; j < numNodes; j++) {
            if (i != j) {
                printf("     %-8d|     %-6d|     %-7d\n", j, nextHop[i][j], distance[i][j]);
            }
        }
    }
}

int main() {
    int numNodes, costMatrix[MAX_NODES][MAX_NODES];

    printf("Enter the number of routers: ");
    scanf("%d", &numNodes);

    printf("Enter the cost matrix (enter 9999 for no direct link):\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &costMatrix[i][j]);
            if (i == j) {
                costMatrix[i][j] = 0;
            } else if (costMatrix[i][j] == 0) {
                costMatrix[i][j] = INFINITY;
            }
        }
    }

    printf("\nInitial Cost Matrix:");
    printRoutingTable(costMatrix, numNodes);

    distanceVectorRouting(costMatrix, numNodes);

    return 0;
}
