long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
    long long minCost = -1;
    
    int candidates[4];
    candidates[0] = 0;
    candidates[1] = need1 > need2 ? need1 : need2;
    candidates[2] = need1;
    candidates[3] = need2;
    
    for (int i = 0; i < 4; i++) {
        int b = candidates[i];
        if (b < 0) continue;
        if (b > need1 && b > need2 && b > (need1 > need2 ? need1 : need2)) continue;
        
        int rem1 = need1 - b > 0 ? need1 - b : 0;
        int rem2 = need2 - b > 0 ? need2 - b : 0;
        
        long long currentCost = (long long)b * costBoth + (long long)rem1 * cost1 + (long long)rem2 * cost2;
        
        if (minCost == -1 || currentCost < minCost) {
            minCost = currentCost;
        }
    }
    
    int max_need = need1 > need2 ? need1 : need2;
    int rem1 = need1 - max_need > 0 ? need1 - max_need : 0;
    int rem2 = need2 - max_need > 0 ? need2 - max_need : 0;
    long long currentCost = (long long)max_need * costBoth + (long long)rem1 * cost1 + (long long)rem2 * cost2;
    if (minCost == -1 || currentCost < minCost) {
        minCost = currentCost;
    }
    if (costBoth < cost1 + cost2) {
        int b = need1 > need2 ? need1 : need2;
        int rem1 = need1 - b > 0 ? need1 - b : 0;
        int rem2 = need2 - b > 0 ? need2 - b : 0;
        long long c = (long long)b * costBoth + (long long)rem1 * cost1 + (long long)rem2 * cost2;
        if (minCost == -1 || c < minCost) minCost = c;
    } else {
        long long c = (long long)need1 * cost1 + (long long)need2 * cost2;
        if (minCost == -1 || c < minCost) 
            minCost = c;
    }
    
    return minCost;
}