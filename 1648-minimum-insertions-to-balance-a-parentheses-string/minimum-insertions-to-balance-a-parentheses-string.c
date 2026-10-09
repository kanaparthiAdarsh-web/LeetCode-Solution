int minInsertions(char* s) {
    int neededRight = 0;
    int missingLeft = 0;
    int missingRight = 0;
    for (int i = 0; s[i] ; i++)
        if (s[i] == '(') {
            if (neededRight % 2 == 1)
                missingRight++,neededRight--;
            neededRight += 2;
        } else {
            neededRight--;
            if (neededRight < 0) 
                missingLeft++,neededRight += 2;
        }
    return neededRight + missingLeft + missingRight;
}