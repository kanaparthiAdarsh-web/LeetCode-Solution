#include <stdlib.h>
#include <string.h>

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int** dist = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        dist[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++) dist[i][j] = -1;
    }
    
    int* q = (int*)malloc(n * n * sizeof(int));
    int head = 0, tail = 0;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == 1) {
                dist[i][j] = 0;
                q[tail++] = i * n + j;
            }
        }
    }
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while(head < tail) {
        int curr = q[head++];
        int r = curr / n, c = curr % n;
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if(nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q[tail++] = nr * n + nc;
            }
        }
    }
    
    int low = 0, high = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dist[i][j] > high) high = dist[i][j];
        }
    }
    
    int ans = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(dist[0][0] < mid) {
            high = mid - 1;
            continue;
        }
        
        int* bq = (int*)malloc(n * n * sizeof(int));
        int bhead = 0, btail = 0;
        int** visited = (int**)malloc(n * sizeof(int*));
        for(int i = 0; i < n; i++) visited[i] = (int*)calloc(n, sizeof(int));
        
        bq[btail++] = 0;
        visited[0][0] = 1;
        int reachable = 0;
        
        while(bhead < btail) {
            int curr = bq[bhead++];
            int r = curr / n, c = curr % n;
            if(r == n - 1 && c == n - 1) {
                reachable = 1;
                break;
            }
            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i], nc = c + dc[i];
                if(nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc] && dist[nr][nc] >= mid) {
                    visited[nr][nc] = 1;
                    bq[btail++] = nr * n + nc;
                }
            }
        }
        
        for(int i = 0; i < n; i++) free(visited[i]);
        free(visited);
        free(bq);
        
        if(reachable) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    for(int i = 0; i < n; i++) free(dist[i]);
    free(dist);
    free(q);
    return ans;
}