typedef struct {
    int weight;
    int index;
} Server;

typedef struct {
    long long free_time;
    int weight;
    int index;
} BusyServer;

void swapServer(Server* a, Server* b) {
    Server temp = *a;
    *a = *b;
    *b = temp;
}

void swapBusy(BusyServer* a, BusyServer* b) {
    BusyServer temp = *a;
    *a = *b;
    *b = temp;
}

void pushAvailable(Server* heap, int* size, int weight, int index) {
    int curr = (*size)++;
    heap[curr] = (Server){weight, index};
    while (curr > 0) {
        int parent = (curr - 1) / 2;
        if (heap[parent].weight > heap[curr].weight || 
            (heap[parent].weight == heap[curr].weight && heap[parent].index > heap[curr].index)) {
            swapServer(&heap[parent], &heap[curr]);
            curr = parent;
        } else 
            break;
    }
}

Server popAvailable(Server* heap, int* size) {
    Server root = heap[0];
    heap[0] = heap[--(*size)];
    int curr = 0;
    while (2 * curr + 1 < *size) {
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int smallest = curr;

        if (heap[left].weight < heap[smallest].weight || 
            (heap[left].weight == heap[smallest].weight && heap[left].index < heap[smallest].index))
            smallest = left;
        
        if (right < *size && (heap[right].weight < heap[smallest].weight || 
            (heap[right].weight == heap[smallest].weight && heap[right].index < heap[smallest].index)))
            smallest = right;
        

        if (smallest != curr) {
            swapServer(&heap[curr], &heap[smallest]);
            curr = smallest;
        } else
            break;
        
    }
    return root;
}

void pushBusy(BusyServer* heap, int* size, long long free_time, int weight, int index) {
    int curr = (*size)++;
    heap[curr] = (BusyServer){free_time, weight, index};
    while (curr > 0) {
        int parent = (curr - 1) / 2;
        if (heap[parent].free_time > heap[curr].free_time || 
            (heap[parent].free_time == heap[curr].free_time && heap[parent].weight > heap[curr].weight) ||
            (heap[parent].free_time == heap[curr].free_time && heap[parent].weight == heap[curr].weight && heap[parent].index > heap[curr].index)) {
            swapBusy(&heap[parent], &heap[curr]);
            curr = parent;
        } else
            break;
    }
}

BusyServer popBusy(BusyServer* heap, int* size) {
    BusyServer root = heap[0];
    heap[0] = heap[--(*size)];
    int curr = 0;
    while (2 * curr + 1 < *size) {
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int smallest = curr;

        if (heap[left].free_time < heap[smallest].free_time || 
            (heap[left].free_time == heap[smallest].free_time && heap[left].weight < heap[smallest].weight) ||
            (heap[left].free_time == heap[smallest].free_time && heap[left].weight == heap[smallest].weight && heap[left].index < heap[smallest].index))
            smallest = left;
        
        if (right < *size && (heap[right].free_time < heap[smallest].free_time || 
            (heap[right].free_time == heap[smallest].free_time && heap[right].weight < heap[smallest].weight) ||
            (heap[right].free_time == heap[smallest].free_time && heap[right].weight == heap[smallest].weight && heap[right].index < heap[smallest].index)))
            smallest = right;
        

        if (smallest != curr) {
            swapBusy(&heap[curr], &heap[smallest]);
            curr = smallest;
        } else 
            break;
    }
    return root;
}

int* assignTasks(int* servers, int serversSize, int* tasks, int tasksSize, int* returnSize) {
    *returnSize = tasksSize;
    int* ans = (int*)malloc(tasksSize * sizeof(int));

    Server* availHeap = (Server*)malloc(serversSize * sizeof(Server));
    int availSize = 0;

    BusyServer* busyHeap = (BusyServer*)malloc(serversSize * sizeof(BusyServer));
    int busySize = 0;

    for (int i = 0; i < serversSize; i++)
        pushAvailable(availHeap, &availSize, servers[i], i);

    long long current_time = 0;

    for (int j = 0; j < tasksSize; j++) {
        if (current_time < j)
            current_time = j;

        while (busySize > 0 && busyHeap[0].free_time <= current_time) {
            BusyServer b = popBusy(busyHeap, &busySize);
            pushAvailable(availHeap, &availSize, b.weight, b.index);
        }

        if (availSize == 0) {
            current_time = busyHeap[0].free_time;
            while (busySize > 0 && busyHeap[0].free_time <= current_time) {
                BusyServer b = popBusy(busyHeap, &busySize);
                pushAvailable(availHeap, &availSize, b.weight, b.index);
            }
        }

        Server s = popAvailable(availHeap, &availSize);
        ans[j] = s.index;
        pushBusy(busyHeap, &busySize, current_time + tasks[j], s.weight, s.index);
    }

    free(availHeap);
    free(busyHeap);

    return ans;
}