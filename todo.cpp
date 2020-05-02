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
        else{}

        if (!headerLine[i+1])
        {
            datelist[listcount-4] = substring(headerLine, start, i);
        }   
    }
    return datelist;
}

int getDay(char** dates, int dateCount, const char* date){
    int dayCount = 1;
    for (int i = 0; i < dateCount; i++)
    {
        if (strcmp(dates[i],date) == 0)
        {
            return dayCount;
        }
        else if (dates[i])
        {
            dayCount += 1;
        }
        else{}

        if (!dates[i+1])
        {
            return 0;
        }
    }
}

Place* getPlaces(char** csvLines, int csvLineCount)
{
    Place* places = new Place[999999];
    int dataCount = 0;
    int placeCount = 0;
    for (int i = 0; i < csvLineCount-1; i++)
    {
        char* currentLine = csvLines[i+1];
        int commaCount = 0;
        int start = 0;
        int linecount = 0;
        Node* tail = new Node();
        for (int i = 0; currentLine[i] ; i++)
        {
            
            Node *datastorage = new Node();
            if (currentLine[i] == ',')
            {
                commaCount += 1;
                if (commaCount == 1)
                {
                    places[placeCount].province = substring(currentLine, start, i-1);
                }
                else if (commaCount == 2)
                {
                    places[placeCount].region = substring(currentLine, start, i-1);
                }
                else if (commaCount >= 5 && atoi(substring(currentLine, start, i-1)) != 0 && linecount == 0)
                {
                    places[placeCount].headNode = datastorage;
                    datastorage->day = commaCount - 4;
                    datastorage->number = atoi(substring(currentLine, start, i-1));
                    tail->next = datastorage;
                    tail = datastorage;
                    dataCount += 1;
                    linecount += 1;
                    
                }
                else if (commaCount >= 5 && linecount != 0)
                {
                    datastorage->day = commaCount - 4;
                    datastorage->number = atoi(substring(currentLine, start, i-1));
                    tail->next = datastorage;
                    tail = datastorage;
                    dataCount += 1;
                    linecount += 1;
                    //cout << dataStorage[dataCount].day << " , " << dataStorage[dataCount].number << endl;                    
                }
                else{}

                start = i+1;
            }
            if (!currentLine[i+1])
            {
                datastorage->day = commaCount - 4;
                datastorage->number = atoi(substring(currentLine, start, i-1));
                tail->next = nullptr;
                tail = nullptr;
                dataCount += 1;
            }
        }
        placeCount += 1;
    }
    return places;
}
/*
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
