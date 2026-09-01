
#define MAX_Q 1048576 

struct State {
    int x, y, mask, e, steps;
};

int minMoves(char** classroom, int classroomSize, int energy) {
    int m = classroomSize;
    int n = strlen(classroom[0]);
    int sx = -1, sy = -1;
    int litterCount = 0;
    int litterId[20][20];
    
    memset(litterId, -1, sizeof(litterId));

    for (int i = 0; i < m; i++) 
        for (int j = 0; j < n; j++)
            if (classroom[i][j] == 'S') {
                sx = i;
                sy = j;
            } else 
                if (classroom[i][j] == 'L')
                    litterId[i][j] = litterCount++;

    int fullMask = (1 << litterCount) - 1;
    if (fullMask == 0) return 0;

    int bestEnergy[20][20][1024];
    memset(bestEnergy, -1, sizeof(bestEnergy));

    struct State* queue = (struct State*)malloc(sizeof(struct State) * MAX_Q);
    int head = 0, tail = 0;

    queue[tail & (MAX_Q - 1)] = (struct State){sx, sy, 0, energy, 0};
    tail++;
    bestEnergy[sx][sy][0] = energy;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (head < tail) {
        struct State curr = queue[head & (MAX_Q - 1)];
        head++;

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n && classroom[nx][ny] != 'X') {
                int ne = curr.e - 1;
                
                if (ne < 0) 
                    continue;

                if (classroom[nx][ny] == 'R')
                    ne = energy;

                int nmask = curr.mask;
                if (classroom[nx][ny] == 'L')
                    nmask |= (1 << litterId[nx][ny]);

                if (nmask == fullMask) {
                    free(queue);
                    return curr.steps + 1;
                }

                if (ne > bestEnergy[nx][ny][nmask]) {
                    bestEnergy[nx][ny][nmask] = ne;
                    queue[tail & (MAX_Q - 1)] = (struct State){nx, ny, nmask, ne, curr.steps + 1};
                    tail++;
                }
            }
        }
    }

    free(queue);
    return -1;
}