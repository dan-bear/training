#define NUM_OF_CHARS 'z' - 'a' + 1
#define FIRST_CHAR 'a'

char getMostReoccursChar(char array[], int arrayLen){
    //Step1 - fill the histogram.
    int charHistogram[NUM_OF_CHARS] = {0};
    for(int charIdx = 0; charIdx < arrayLen; charIdx++){
        char currentChar = array[charIdx];
        int matchingHistogramIdx = currentChar - FIRST_CHAR;
        charHistogram[matchingHistogramIdx] += 1;
    } 
  
    //Step1 - Find the most reoccurs char using the histogram.
    int maxOccurences = 0;
    int maxOccurencesIdx = 0;
    for(int charIdx = 0; charIdx < NUM_OF_CHARS; charIdx++){
        if(charHistogram[charIdx] > maxOccurences){
            maxOccurences = charHistogram[charIdx];
            maxOccurencesIdx = charIdx;
        }
    }
    // Step3 - from char inndex to char.
    char mostReoccursChar = FIRST_CHAR + maxOccurencesIdx;
    
  return mostReoccursChar;  
}


// A better way to do it is to break the steps to two
// functions.

//declerations. 
/*
int calcMaxOccurencesIdx(int charHistogram[], int histogramLen);
int calcMaxOccurencesIdx(int charHistogram[], int histogramLen);
char fromCharIdxToChar(int charIdx);

char getMostReoccursChar(char array[], int arrayLen){
    int charHistogram[NUM_OF_CHARS] = {0};
    calcHistogram(array, arrayLen, charHistogram);
  
    int maxOccurencesIdx = 
        calcMaxOccurencesIdx(charHistogram, NUM_OF_CHARS);

    char mostReoccursChar = fromCharIdxToChar(maxOccurencesIdx);
    
    return mostReoccursChar;  
}

void calcHistogram(char array[], int arrayLen, int charHistogram[]){
    for(int charIdx = 0; charIdx < arrayLen; charIdx++){
        char currentChar = array[charIdx];
        int matchingHistogramIdx = currentChar - FIRST_CHAR;
        charHistogram[matchingHistogramIdx] += 1;
    }
}

int calcMaxOccurencesIdx(int charHistogram[], int histogramLen){
    int maxOccurences = 0;
    int maxOccurencesIdx = 0;
    for(int charIdx = 0; charIdx < histogramLen; charIdx++){
        if(charHistogram[charIdx] > maxOccurences){
            maxOccurences = charHistogram[charIdx];
            maxOccurencesIdx = charIdx;
        }
    }
  
    return maxOccurencesIdx;
}

char fromCharIdxToChar(int charIdx){
    return FIRST_CHAR + charIdx;
}
*/


