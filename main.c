// ***********************************************************
//DAVINA TITUS
// UIN - 652284919
// PROJECT 04 
// SPRING 2026 UNIVERSITY OF ILLINOIS AT CHICAGO
// CS 211 PROGRAMMING PRACTICUM
/*  

THIS PROGRAM IMPLEMENTS A WORD LADDER GAME AND SOLVER.
A WORD LADDER CONNECTS TWO WORDS BY CHANGING ONE LETTER AT A TIME,
WHERE EACH STEP MUST FORM A VALID DICTIONARY WORD. THE PROGRAM READS
A DICTIONARY FILE, LETS THE USER BUILD A WORD LADDER INTERACTIVELY,
AND THEN USES A BREADTH-FIRST SEARCH ALGORITHM TO FIND THE SHORTEST
POSSIBLE WORD LADDER BETWEEN THE TWO WORDS.

**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;


//------------------- \/\/\/ TOP OF TASK 1 \/\/\/ --------------------

int countWordsOfLength(char* filename, int wordSize) { 
    //---------------------------------------------------------
    // TODO - write countWordsOfLength()    
    //---------------------------------------------------------
    FILE* f = fopen(filename,"r");
    if (f==NULL){
        return -1;
    }

    char word[256];
    int count=0;

    while (fscanf(f,"%s",word)==1){
        if ((int)strlen(word)==wordSize){
            count++;
        }
    }
    fclose(f);
    return count; //modify this line
}

bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    //---------------------------------------------------------
    // TODO - write buildWordArray()    
    //---------------------------------------------------------
    FILE* f = fopen(filename,"r");
    if (f==NULL){
        return false;
    }

    char word[256];
    int idx=0;

    while(fscanf(f,"%s",word) == 1 ){
        if ((int)strlen(word) == wordSize){
            if (idx < numWords) strcpy(words[idx], word);
            idx++;
        }
    }

    fclose(f);
    return idx == numWords; //modify this line
}

int findWord(char** words, char* aWord, int loInd, int hiInd) {
    //---------------------------------------------------------
    // TODO - write findWord()
    //---------------------------------------------------------

    while (loInd <=hiInd){
        int mid = (loInd+hiInd)/2;
        int cmp = strcmp(words[mid],aWord);
        if (cmp==0){
            return mid;
        } else if (cmp <0){
            loInd= mid+1;
        } else {
            hiInd=mid-1;
        }
    }
    return -1; // modify this line
}

void freeWords(char** words, int numWords) {
    //---------------------------------------------------------
    // TODO - write freeWords()
    //---------------------------------------------------------

    for (int i =0; i <numWords;i++){
        free(words[i]);
    }
    free(words);
}

//---------------------- ^^^ END OF TASK 1 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 2 \/\/\/ -------------------

int strCmpCnt(char* str1, char* str2) {
    //---------------------------------------------------------
    // TODO - write strCmpCnt()
    //---------------------------------------------------------

    int count =0;
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int minLen = len1 < len2 ? len1 : len2;
    for (int i =0; i < minLen;i++){
        if (str1[i]!= str2[i]){
            count++;
        }
    }

    if (len1> len2){
        count+=len1-len2;
    } else {
        count+=len2-len1;
    }

    return count; //modify this line
}

int strCmpInd(char* str1, char* str2) {
    //---------------------------------------------------------
    // TODO - write strCmpInd()
    //---------------------------------------------------------

    int i=0;
    while (str1[i]!='\0' && str2[i]!='\0'){
        if (str1[i]!=str2[i]){
            return i;
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') return i;
    return -1; //modify this line
}

//---------------------- ^^^ END OF TASK 2 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 3 \/\/\/ -------------------

void insertWordAtFront(WordNode** ladder, char* newWord) {
    //---------------------------------------------------------
    // TODO - write insertWordAtFront()
    //---------------------------------------------------------

    WordNode* node = (WordNode*)malloc(sizeof(WordNode));
    node->myWord = newWord;
    node->next = *ladder;
    *ladder=node;
}

int getLadderHeight(WordNode* ladder) {
    //---------------------------------------------------------
    // TODO - write getLadderHeight()
    //---------------------------------------------------------

    int count=0;
    WordNode* curr= ladder;
    while(curr!=NULL){
        count++;
        curr=curr->next;
    }
    return count; // modify this line
}

bool checkForValidWord(char** words, int numWords, int wordSize, WordNode* ladder, char* aWord) {
    //---------------------------------------------------------
    // TODO - write checkForValidWord()
    //---------------------------------------------------------
    
    // print statement for various scenarios:
        // user entered "DONE" - valid, top (#1) priority

        if (strcmp(aWord,"DONE")==0){
            printf("Stopping with an incomplete word ladder...\n");
            return true;
        }

        // user entered a word that is too long/short - invalid, priority #2

        if ((int)strlen(aWord)!=wordSize){
            printf("Entered word does NOT have the correct length. Try again...\n");
            return false;
        }
        
        // user entered a word that is not found in the dictionary - invalid, priority #3

        if (findWord(words,aWord,0,numWords-1)<0){
            printf("Entered word NOT in dictionary. Try again...\n");
            return false;
        }
            
        // user entered a word that requires changing more than one-character - invalid, priority #4a
        // user entered a word that requires no character difference (the same word) - invalid, priority #4b

        if (strCmpCnt(ladder->myWord,aWord)!=1){
            printf("Entered word is NOT a one-character change from the previous word. Try again...\n");
            return false;
        }
        
        // user entered a word a valid word - valid, priority #5 (default)
            printf("Entered word is valid and will be added to the word ladder.\n");
    return true; //modify this line
}

bool isLadderComplete(WordNode* ladder, char* finalWord) {
    //---------------------------------------------------------
    // TODO - write isLadderComplete()
    //---------------------------------------------------------

    if (ladder==NULL){
        return false;
    }
    return strcmp(ladder->myWord,finalWord)==0; //modify this line
}

WordNode* copyLadder(WordNode* ladder) {
    //---------------------------------------------------------
    // TODO - write copyLadder()
    //---------------------------------------------------------

    if (ladder==NULL){
        return NULL;
    }

    WordNode* newhd = NULL;
    WordNode* newtail = NULL;
    WordNode* curr= ladder;

    while (curr!=NULL){
        WordNode* node= (WordNode*)malloc(sizeof(WordNode));
        node->myWord=curr->myWord;
        node->next=NULL;

        if (newhd==NULL){
            newhd=node;
            newtail=node;
        } else {
            newtail->next = node;
            newtail=node;
        }

        curr=curr->next;
    }
    return newhd; //modify this line
}

void freeLadder(WordNode* ladder) {
    //---------------------------------------------------------
    // TODO - write freeLadder()
    //---------------------------------------------------------

    WordNode* curr = ladder;
    while (curr!=NULL){
        WordNode* tmp = curr->next;
        free(curr);
        curr=tmp;
    }
}

//---------------------- ^^^ END OF TASK 3 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 4 \/\/\/ -------------------

void displayIncompleteLadder(WordNode* ladder) {
    //-------------------------------------------------------------------
// displayIncompleteLadder() should display the C-strings in the  
//      [ladderWords] array with the first word at the bottom, and 
//      each successive C-string one rung higher on the ladder. 
//      The ladder [height] is the number of words it contains.  
//      To signify the ladder as incomplete, display three lines of  
//      "..." at the top of the ladder. The ladder must be displayed 
//      with an indentation of two whitespaces on every line;
//      Ex: if the start word is "data" and final word is "code" and
//          the incomplete ladder is data->date->gate->gave, then the
//          output display should be as follows (where the quotation  
//          marks are NOT a part of the actual display):
//              "  ..."
//              "  ..."
//              "  ..."
//              "  gave"
//              "  gate"
//              "  date"
//              "  data" 
//-------------------------------------------------------------------
    //---------------------------------------------------------
    // TODO - write displayIncompleteLadder()
    //---------------------------------------------------------

    int height = getLadderHeight(ladder);
    char** wordPtrs = (char**)malloc(height*sizeof(char*));
    WordNode* curr = ladder;
    for (int i=0;i < height;i++){
        wordPtrs[i]=curr->myWord;
        curr=curr->next;
    }

    printf(" ...\n");
    printf(" ...\n");
    printf(" ...\n");

    for (int i=0;i<height;i++){
        printf("  %s\n",wordPtrs[i]);
    }

    free(wordPtrs);
}

void displayCompleteLadder(WordNode* ladder) {
//-------------------------------------------------------------------
// displayCompleteLadder(), should display the C-strings in the  
//      [ladderWords] array with the first word at the bottom, and  
//      each successive C-string one rung higher on the ladder. 
//      The ladder [height] is the number of words it contains.  
//      In between each ladder rung, display the symbol '^' to 
//      signify the character that changes between the two rungs of 
//      the ladder. The ladder should be displayed with an indentation 
//      of two whitespaces to the left of every word;
//
//      HINT: call strCmpInd() here
//
//      Ex: if the start word is "data" and final word is "code" 
//          then the output display for a complete ladder should be  
//          as follows (where the quotation marks are NOT a part of  
//          the actual display):
//              "  code"
//              "    ^ "
//              "  cove"
//              "   ^  "
//              "  cave"
//              "  ^   "
//              "  gave"
//              "    ^ "
//              "  gate"
//              "  ^   "
//              "  date"
//              "     ^"
//              "  data" 
//-------------------------------------------------------------------
    //---------------------------------------------------------
    // TODO - write displayCompleteLadder()
    //---------------------------------------------------------

    int height= getLadderHeight(ladder);
    char** wordPtrs = (char**)malloc(height*sizeof(char*));
    WordNode* curr = ladder;

    for (int i=0;i<height;i++){
        wordPtrs[i]=curr->myWord;
        curr=curr->next;
    }

    int wordSize=(int)strlen(wordPtrs[0]);

    for (int i=0;i<height;i++){
        printf("  %s\n", wordPtrs[i]);

        if (i<height-1){
            int diffIdx = strCmpInd(wordPtrs[i],wordPtrs[i+1]);
            printf("  ");
            for (int j = 0; j < diffIdx; j++) printf(" ");
            printf("^");
            for (int j = diffIdx + 1; j < wordSize; j++) printf(" ");
            printf("\n");
        }
    }
    free(wordPtrs);
}

//---------------------- ^^^ END OF TASK 4 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 5 \/\/\/ -------------------

void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    //---------------------------------------------------------
    // TODO - write insertLadderAtBack()
    //---------------------------------------------------------

    LadderNode* node = (LadderNode*)malloc(sizeof(LadderNode));
    node->topWord= newLadder;
    node->next=NULL;
    if (*list==NULL){
        *list=node;
        return;
    }

    LadderNode* curr= *list;
    while (curr->next!=NULL){
        curr=curr->next;
    }
    curr->next = node;
}

WordNode* popLadderFromFront(LadderNode** list) {
    //---------------------------------------------------------
    // TODO - write popLadderFromFront()
    //---------------------------------------------------------

    if (*list==NULL){
        return NULL;
    }

    LadderNode* front = *list;
    WordNode* ladder=front->topWord;
    *list = front->next; //modify this line
    free(front);
    return ladder; //modify this line
}

void freeLadderList(LadderNode* myList) {
    //---------------------------------------------------------
    // TODO - write freeLadderList()
    //---------------------------------------------------------

    LadderNode* curr= myList;
    while (curr!=NULL){
        LadderNode* tmp=curr->next;
        freeLadder(curr->topWord);
        free(curr);
        curr=tmp;
    }
}

//---------------------- ^^^ END OF TASK 5 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 6 \/\/\/ -------------------

WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {
    //---------------------------------------------------------
    // TODO - write findShortestWordLadder()
    //---------------------------------------------------------

    LadderNode* myList=NULL;

    int startidx = findWord(words,startWord,0,numWords-1);
    if (startidx < 0) return NULL;
    WordNode* myLadder=NULL;
    insertWordAtFront(&myLadder,words[startidx]);
    usedWord[startidx]=true;
    insertLadderAtBack(&myList,myLadder);

    char neighbor[100];

    while (myList!=NULL){
        myLadder=popLadderFromFront(&myList);
        char* topWord=myLadder->myWord;

        for (int i=0; i< wordSize;i++){
            for (int ch='a';ch<='z';ch++){
                if (ch==(int)topWord[i]){
                    continue;
                }

                strcpy(neighbor,topWord);
                neighbor[i]=(char)ch;

                int idx = findWord(words,neighbor,0,numWords-1);
                if (idx<0) continue;

                if (usedWord[idx]) continue;

                usedWord[idx]=true;

                if (strcmp(words[idx],finalWord)==0){
                    insertWordAtFront(&myLadder,words[idx]);
                    freeLadderList(myList);
                    return myLadder;
                }

                WordNode* diffLadder = copyLadder(myLadder);
                insertWordAtFront(&diffLadder,words[idx]);
                insertLadderAtBack(&myList,diffLadder);
            }
        }
        freeLadder(myLadder);
    }  
    return NULL; //modify this line
}

//---------------------- ^^^ END OF TASK 5 ^^^ ----------------------


//------------------- \/\/\/ TOP OF OTHERS \/\/\/ -------------------


// randomly set a word from the dictionary word array
void setWordRand(char** words, int numWords, int wordSize, char* aWord) {
    printf("  Picking a random word for you...\n");
    strcpy(aWord,words[rand()%numWords]);
    printf("  Your word is: %s\n",aWord);
}

// interactive user-input to set a word;
//  ensures the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    if (strcmp(aWord,"RAND") != 0) printf("  Enter a %d-letter word (enter RAND for a random word): ", wordSize);
    int count = 0;
    while (!valid) {
        if (strcmp(aWord,"RAND") != 0) scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word (enter RAND for a random word): ", wordSize);
            }
        } else if (strcmp(aWord,"RAND") != 0) {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word (enter RAND for a random word): ", wordSize);
        }
        if (!valid && (count >= 5 || strcmp(aWord,"RAND") == 0)) { //too many tries, picking random word
            setWordRand(words, numWords, wordSize, aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}

//---------------------- ^^^ END OF OTHERS ^^^ ----------------------



//-----------------------------------------------------
// The primary application is mostly fully-develop as
//  provided in main(); changes in main() should be
//  limited to updates made for the game play task(s)
//  and testing-related purposes (such as command-line
//  arguments for "TESTING MODE" to call a test case 
//  master function, or something similar)
//-----------------------------------------------------
int main(int argc, char* argv[]) {

    printf("\n");
    printf("--------------------------------------------\n");
    printf("Welcome to the CS 211 Word Ladder Generator!\n");
    printf("--------------------------------------------\n\n");
    

    //-------------- \/\/\/ TOP OF PROGRAM SETTINGS \/\/\/ --------------
    //--- COMMAND-LINE ARGUMENTS AND/OR INTERACTIVE USER-INPUT \/\/\/ ---

    
    // default values for program parameters that may be set with
    //  command-line arguments
    int wordSize = -2114430;
    char dict[100] = "notAfile";
    char startWord[30] = "notAword";
    char finalWord[30] = "notValid";
    bool playMode = false;
    
    printf("\nProcessing command-line arguments...\n");

    //-------------------------------------------------------------------
    // command-line arguments:
    //  [-n wordLen] = sets word length for word ladder;
    //                 if wordLen is not a valid input
    //                 (cannot be less than 2 or greater than 20),
    //                 or missing from command-line arguments,
    //                 then let user set it using interactive user input
    // [-d dictFile] = sets dictionary file;
    //                 if dictFile is invalid (file not found) or
    //                 missing from command-line arguments, then let
    //                 user set it using interactive user input
    // [-s startWord] = sets the starting word;
    //                  if startWord is invalid
    //                  (not in dictionary or incorrect length) or
    //                  missing from command-line arguments, then let
    //                  user set it using interactive user input
    // [-f finalWord] = sets the final word;
    //                  if finalWord is invalid
    //                  (not in dictionary or incorrect length) or
    //                  missing from command-line arguments, then let
    //                  user set it using interactive user input
    // [-p playModeSwitch] = turns playMode ON if playModeSwitch is "ON"
    //                       or leaves playMode OFF if playModeSwitch is
    //                       anything else, including "OFF"
    //-------------------------------------------------------------------

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i],"-n") == 0 && argc > i+1) {
            wordSize = atoi(argv[i+1]);
            ++i;
        } else if (strcmp(argv[i],"-d") == 0 && argc > i+1) {
            strcpy(dict, argv[i+1]);
            ++i;
        } else if (strcmp(argv[i],"-s") == 0 && argc > i+1) {
            strcpy(startWord, argv[i+1]);
            ++i;
        } else if (strcmp(argv[i],"-f") == 0 && argc > i+1) {
            strcpy(finalWord, argv[i+1]);
            ++i;
        } else if (strcmp(argv[i],"-p") == 0 && argc > i+1) {
            playMode = (strcmp(argv[i+1],"ON") == 0);
            ++i;
        }
    }
    
    srand((int)time(0));
    
    // set word length using interactive user-input
    //  if wordSize == -2114430, it was NOT set with command-line args
    while (wordSize < 2 || wordSize > 20) {
        if (wordSize != -2114430) printf("Invalid word size for the ladder: %d\n", wordSize);
        printf("Enter the word size for the ladder: ");
        scanf("%d",&wordSize);
        printf("\n");
    }

    printf("This program is a word ladder building game and a solver that\n");
    printf("finds the shortest possible ");
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input to set the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize];
    //  if dict == "notAfile", it was NOT set with command-line args
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        if (strcmp(dict, "notAfile") != 0) {
            printf("  Dictionary %s not found...\n",dict);
        }
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i]
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize);
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n\n");

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array,
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    // start/final words may have already been set using command-line arguments
    // the start/final word can also be set to "RAND" resulting in a random
    //  assignment from any element of the words array
    if (strcmp(startWord,"RAND")==0) {
        printf("Setting the start word randomly...\n");
        setWordRand(words, numWords, wordSize, startWord);
    } else if (findWord(words, startWord,0, numWords-1) < 0 || strlen(startWord) != wordSize) {
        if (strcmp(startWord,"notAword")==0) {
            printf("Setting the start %d-letter word... \n", wordSize);
        } else {
            printf("Invalid start word %s. Resetting the start %d-letter word... \n", startWord, wordSize);
        }
        setWord(words, numWords, wordSize, startWord);
    }
    //printf("\n");
    
    if (strcmp(finalWord,"RAND")==0) {
        printf("Setting the final word randomly...\n");
        setWordRand(words, numWords, wordSize, finalWord);
    } else if (findWord(words, finalWord,0, numWords-1) < 0 || strlen(finalWord) != wordSize) {
        if (strcmp(finalWord,"notValid")==0) {
            printf("Setting the final %d-letter word... \n", wordSize);
        } else {
            printf("Invalid final word %s. Resetting the final %d-letter word... \n", finalWord, wordSize);
        }
        setWord(words, numWords, wordSize, finalWord);
    }
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");
    
    //----------------- ^^^ END OF PROGRAM SETTINGS ^^^ -----------------
    
    
    //-------------- \/\/\/ TOP OF GAME PLAY SECTION \/\/\/ --------------
    
    if (!playMode) {
        printf("\n");
        printf("---------------------------------------------\n");
        printf("No Word Ladder Builder Game; Play Mode is OFF\n");
        printf("---------------------------------------------\n");
        printf("\n");
    } else {
        printf("\n");
        printf("-----------------------------------------------\n");
        printf("Welcome to the CS 211 Word Ladder Builder Game!\n");
        printf("-----------------------------------------------\n");
        printf("\n");

        printf("Your goal is to make a word ladder between two ");
        printf("%d-letter words: \n  %s -> %s\n\n",wordSize, startWord,finalWord);
        
        WordNode* userLadder = NULL;
        int ladderHeight = 0; // initially, the ladder is empty
        int startInd = findWord(words, startWord, 0, numWords-1);
        insertWordAtFront(&userLadder, words[startInd]);
        ladderHeight++; // Now, the ladder has a start word
            
        char aWord[30] = "XYZ";
        printf("\n");
        
        // Let the user build a word ladder interactively & iteratively.
        // First, check that ladder is not too long AND not complete.
        //-------------------------------------------------------------------
        // TODO - PART OF Task 4 (GAME PLAY): modify the while loop condition
        //          such that the word ladder building process continues only
        //          if BOTH of the following conditions are met:
        //              1. the user is NOT attempting to stop the word ladder
        //                 building process, which occurs if the entered word
        //                 [aWord] from the last iteration is "DONE"
        //              2. the ladder is still incomplete; i.e. the last word
        //                 added to ladder is not the final word;
        //                 note: this should use a call to isLadderComplete()
        //-------------------------------------------------------------------
        while ( strcmp(aWord,"DONE") != 0 && !isLadderComplete(userLadder, finalWord)) {   // modify this line
            printf("The goal is to reach the final word: %s\n",finalWord);
            printf("The ladder is currently: \n");
            displayIncompleteLadder(userLadder);
            printf("Current ladder height: %d\n",ladderHeight);
            printf("Enter the next word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");
            
            // Make sure the entered word is valid for the next ladder rung;
            // if not, repeatedly allow user to enter another word until one is valid
            while (!checkForValidWord(words, numWords, wordSize, userLadder, aWord)) {
                printf("Enter another word (or DONE to stop): ");
                scanf("%s",aWord);
                printf("\n");
            }

            // add the entered word to the ladder (unless it is "DONE")
            if (strcmp(aWord,"DONE") != 0) {
                int currInd = findWord(words, aWord, 0, numWords-1);
                insertWordAtFront(&userLadder, words[currInd]);
                ladderHeight++;
            }
            printf("\n");
        }

        // Check if the built word ladder is complete and
        // display the word ladder appropriately.
        if (isLadderComplete(userLadder, finalWord)) {
            printf("Word Ladder complete!\n\n");
            displayCompleteLadder(userLadder);
            printf("\nWord Ladder height = %d\n\n", ladderHeight);
            printf("Can you find a shorter Word Ladder next time??? \n");
        } else {
            printf("The final Word Ladder is incomplete:\n");
            displayIncompleteLadder(userLadder);
            printf("Word Ladder height = %d\n\n", ladderHeight);
            printf("Can you complete the Word Ladder next time??? \n");
        }
        freeLadder(userLadder);
    }
    
    //----------------- ^^^ END OF GAME PLAY SECTION ^^^ -----------------
    
    
    //-------------- \/\/\/ TOP OF WORD LADDER SOLVER \/\/\/ --------------
    
    printf("\n\n");
    printf("-----------------------------------------\n");
    printf("Welcome to the CS 211 Word Ladder Solver!\n");
    printf("-----------------------------------------\n");
    printf("\n");
    

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // OPTIONAL EXTENTION TO FIND LONGEST WORD LADDER:
    //  program must end with finding the shortest word ladder
    //  (& the associated print statements); if you choose to
    //  extend your program to find the longest word ladder,
    //  put the long word ladder algorithm (& the associated
    //  print statements) BEFORE the short word ladder algorithm
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    
    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);
    } else {
        printf("Shortest Word Ladder found!\n\n");
        displayCompleteLadder(myLadder);
        //printLadder(myLadder);
    }
    printf("\nWord Ladder height = %d\n\n",getLadderHeight(myLadder));

    //----------------- ^^^ END OF WORD LADDER SOLVER ^^^ -----------------
    
    
    //-------------- \/\/\/ TOP OF CLEAN-UP \/\/\/ --------------
    
    // TODO - Part of ALL Tasks:
    //      free all heap-allocated memory to avoid potential
    //      memory leaks. Since the word length for the word
    //      ladder is variable (i.e. set by a command-line
    //      argument or interactive user-input) any array
    //      whose size depends on the word length should be
    //      dynamically heap-allocated, and thus, must be
    //      tracked and freed before program termination.
    //      A big part of the memory management & freeing
    //      is handled by the following functions, but
    //      you may have introduced additional heap-memory
    //      allocations, especially as part of the game play.
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    //----------------- ^^^ END OF CLEAN-UP ^^^ -----------------

    
    return 0;
}
