//submit this file ONLY
//if you need to write your own helper functions, write the functions in this file
//again, do NOT include additional libraries and make sure this todo.cpp can be compiled with the unmodified versions of the other given files in our official compilation environment

#include "given.h"
#include "todo.h"

int getDateCount(char* headerLine){
    int count = 0;
    for (int i = 0; headerLine[i]; i++)
    {
    	if(headerLine[i] == ','){
    		count += 1;
    	}
    }
    return count - 3;
}

char** getDates(char *headerLine){

	int size = 9999;
	char **datelist = new char*[size];
	int state = 0;
    int listcount = 0;
    int start = -1;

    for (int i = 0; headerLine[i] ; i++)
    {
        if (state == 0 && headerLine[i] != ',')
        {
            state = 1;
            start = i;
        }
        else if (state == 1 && headerLine[i] == ',')
        {
            state = 0;
            if (listcount >= 4) 
            {
                datelist[listcount-4] = substring(headerLine, start, i-1);
            }
            listcount++;
        }
    }
    return datelist;
}
/*
int getDay(char** dates, int dateCount, const char* date){

}

Place* getPlaces(char** csvLines, int csvLineCount){

}

int mergeAllProvinces(Place*& places, int placeCount, const char* home = "Hong Kong"){

}

void normalizeDays(Place*& places, int& placeCount, int threshold){

}

void changeToNDayGrowth(Place* places, int placeCount, int n){

}

void writeCSV(const char* csvFileName, Place* places, int placeCount){

}

void deallocateCSVLines(char** csvLines, int csvLineCount){

}

void deallocateDates(char** dates, int dateCount){

}

void deallocateLinkedList(Node* headNode){

}

void deallocatePlaces(Place* places, int placeCount){

}
*/
