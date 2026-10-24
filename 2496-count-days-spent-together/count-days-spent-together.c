int dayOfYear(char* d) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int m = (d[0] - '0') * 10 + (d[1] - '0');
    int day = (d[3] - '0') * 10 + (d[4] - '0');
    int total = day;
    for (int i = 0; i < m - 1; total += days[i],i++);
    return total;
}

int countDaysTogether(char* arriveAlice, char* leaveAlice, char* arriveBob, char* leaveBob) {
    int aa = dayOfYear(arriveAlice);
    int la = dayOfYear(leaveAlice);
    int ab = dayOfYear(arriveBob);
    int lb = dayOfYear(leaveBob);

    int start = aa > ab ? aa : ab;
    int end = la < lb ? la : lb;

    return end >= start ? end - start + 1 : 0;
}