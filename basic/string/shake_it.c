#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define ABC_SIZE 'z' - 'a' + 1
#define WORD_MAX_LEN 12
#define SONG_MAX_SIZE 50

/* Function Declarations */
void printSong(char* songLyrics[], int songSize);
int readSongLyrics(char* songLyrics[], int songMaxSize, int wordMaxLen);
void releaseMemory(char* songLyrics[], int songSize);
int* findSwiftyWordIndexes(char* songLyrics[], int songSize, int k);
void encryptSwiftyWord(char* songLyrics[],
                  int wordIdxs[],
                  int k,
                  unsigned char taylorCipherKey[ABC_SIZE]);
/// Auxilary functions:
void initStrWithChar(char* str, int strLen, char c);
void copyString(char* src, char* dst);
int calcStrLen(char* str);
bool isSameString(char* str1, char* str2);
int countNumberOfOccurrences(char* word, char** songLyrics, int songSize);
void writeIndexesOfWord(int* wordIndexes,
                        char** songLyric,
                        int songSize,
                        char* word);
void encryptWord(char* word, unsigned char taylorCipherKey[ABC_SIZE]);

// DO NOT TOUCH
void
printSong(char* songLyrics[], int songSize)
{
    for (int i = 0; i < songSize; i++) {
        if (songLyrics[i] != NULL) {
            printf("%s ", songLyrics[i]);
        }
    }
    printf("\n");
}

// DO NOT TOUCH
int
main()
{
    unsigned char taylorCipherKey[ABC_SIZE] = {
        '@', '4', '(', '8', '3', '/', '6', 'H', '!',
        '}', '&', '1', '+', '^', '0', '5', '9', 'R',
        '$', '#', '<', '>', 'w', '*', '~', 'z'
    };

    char* songLyrics[SONG_MAX_SIZE] = { NULL };

    // Get k input
    int k;
    printf("Enter k:\n");
    scanf("%d", &k);

    // Get song lyrics input
    printf("Enter your song lyrics:\n");
    int songSize =
      readSongLyrics(songLyrics, SONG_MAX_SIZE, WORD_MAX_LEN);

    // Find the word that appears k times in the song,
    // and encrypt it using the key
    int* wordIdxs = findSwiftyWordIndexes(songLyrics, songSize, k);
    encryptSwiftyWord(songLyrics, wordIdxs, k, taylorCipherKey);

    // Print the result
    printSong(songLyrics, songSize);

    // Release all dynamically allocated memory
    free(wordIdxs);
    releaseMemory(songLyrics, songSize);

    return 0;
}

/* Your Implementation: */
int readSongLyrics(char* songLyrics[], int songMaxSize, int wordMaxLen)
{
    char* readWordBuffer =
      (char*)malloc((wordMaxLen + 1) * sizeof(char));
    initStrWithChar(readWordBuffer, wordMaxLen + 1, '\0');
    int wordIdx = 0;
    while (scanf(" %s", readWordBuffer) != EOF &&
           wordIdx < songMaxSize) {
        int wordLen = calcStrLen(readWordBuffer);
        char* wordCopy = (char*)malloc((wordLen + 1) * sizeof(char));
        copyString(readWordBuffer, wordCopy);
        songLyrics[wordIdx] = wordCopy;
        /// prepare for next round:
        initStrWithChar(readWordBuffer, wordMaxLen + 1, '\0');
        wordIdx++;
    }

    free(readWordBuffer);
    return wordIdx;
}

int* findSwiftyWordIndexes(char* songLyrics[], int songSize, int k)
{
    int idxOfKRepeatedWord = -1;
    for (int idx = 0; idx < songSize; idx++) {
        int wordOccurrences = countNumberOfOccurrences(
          songLyrics[idx], songLyrics, songSize);
        if (wordOccurrences == k) {
            idxOfKRepeatedWord = idx;
            break;
        }
    }

    int* wordIndexes = (int*)malloc(k * sizeof(int));
    writeIndexesOfWord(wordIndexes,
                       songLyrics,
                       songSize,
                       songLyrics[idxOfKRepeatedWord]);
    return wordIndexes;
}

void encryptSwiftyWord(char* songLyrics[],
                  int wordIdxs[],
                  int k,
                  unsigned char taylorCipherKey[ABC_SIZE])
{
    for (int idx = 0; idx < k; idx++) {
        encryptWord(songLyrics[wordIdxs[idx]], taylorCipherKey);
    }
}

void releaseMemory(char* songLyrics[], int songSize)
{
    for (int idx = 0; idx < songSize; idx++) {
        free(songLyrics[idx]);
    }
}

void encryptWord(char* word, unsigned char taylorCipherKey[ABC_SIZE])
{
    int idx = 0;
    while (word[idx] != '\0') {
        char currentChar = word[idx];
        char encryptedChar = taylorCipherKey[currentChar - 'a'];
        word[idx] = encryptedChar;
        idx++;
    }
}

void writeIndexesOfWord(int* wordIndexes,
                   char** songLyric,
                   int songSize,
                   char* word)
{
    int wordIndexesFrontIdx = 0;
    for (int wordIdx = 0; wordIdx < songSize; wordIdx++) {
        if (isSameString(word, songLyric[wordIdx])) {
            wordIndexes[wordIndexesFrontIdx] = wordIdx;
            wordIndexesFrontIdx++;
        }
    }
}

int countNumberOfOccurrences(char* word, char** songLyrics, int songSize)
{
    int count = 0;
    for (int idx = 0; idx < songSize; idx++) {
        if (isSameString(word, songLyrics[idx])) {
            count += 1;
        }
    }
    return count;
}

bool isSameString(char* str1, char* str2)
{
    int idx = 0;
    while (str1[idx] != '\0' && str2[idx] != '\0') {
        if (str1[idx] != str2[idx]) {
            return false;
        }
        idx++;
    }
    if (str1[idx] == '\0' && str2[idx] == '\0') {
        return true;
    } else {
        return false;
    }
}

void initStrWithChar(char* str, int strLen, char c)
{
    for (int idx = 0; idx < strLen; idx++) {
        str[idx] = c;
    }
}

void copyString(char* src, char* dst)
{
    int idx = 0;
    while (src[idx] != '\0') {
        dst[idx] = src[idx];
        idx++;
    }
    // Save the null terminator in the last position.
    dst[idx] = '\0';
}

int calcStrLen(char* str)
{
    /// Note: the method does not count the null terminator.
    int idx = 0;
    while (str[idx] != '\0') {
        idx++;
    }
    return idx;
}
