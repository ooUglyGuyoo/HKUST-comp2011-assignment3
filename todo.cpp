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
        else{}
    }
}

Place* getPlaces(char** csvLines, int csvLineCount)
{
    Place* places = new Place[csvLineCount];
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
                    if (start == i)
                    {
                        places[placeCount].province = nullptr;
                    }
                    else
                    {
                        places[placeCount].province = substring(currentLine, start, i-1);
                    }
                    
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
                }
                else{}
                start = i+1;
            }
            if ( !currentLine[i+1] )
            {
                datastorage->day = commaCount - 3;
                datastorage->number = atoi(substring(currentLine, start, i));
                tail->next = datastorage;
                tail = datastorage;
                dataCount += 1;
                linecount += 1;
                datastorage->next = nullptr;
                tail->next = nullptr;
                tail = nullptr;
            }
        }
        placeCount += 1;
    }
    return places;
}

int mergeAllProvinces(Place*& places, int placeCount, const char* home){
    home = "Hong Kong";
    // merge the data and set all already merged provinces's region and province into nullptr
    for (int i = 0; &places[i] ; i++)
    {
        for (int j = 0; j<i ; j++)
        {
            if(places[j].province != nullptr && places[j].region != nullptr && strcmp(places[i].region,places[j].region) == 0)
            {
                placeCount -= 1; cout << "placecount - 1" << endl;
                if (places[i].headNode->next->day == places[j].headNode->next->day)
                {
                    cout << "copy " << i << " to " << j << endl;
                    cout << "places[i].headNode->next->day == places[j].headNode->next->day" << endl;
                    places[i].region = nullptr;
                    places[i].province = nullptr;
                    Node* tailto = new Node();
                    Node* tailfrom = new Node();
                    tailfrom = places[i].headNode;
                    tailto = places[j].headNode;
                    while (tailto->next != nullptr)
                    {
                        tailfrom = tailfrom->next;
                        tailto = tailto->next;
                        tailto->number += tailfrom->next->number;
                    }
                    tailfrom->next = nullptr;
                    tailto->next = nullptr;
                    tailfrom = nullptr;
                    tailto = nullptr;
                }
                else if (places[i].headNode->next->day > places[j].headNode->next->day)
                {
                    cout << "copy " << i << " to " << j << endl;
                    cout << "places[i].headNode->next->day > places[j].headNode->next->day" << endl;
                    int difference = places[j].headNode->next->day - places[i].headNode->next->day;
                    places[i].region = nullptr;
                    places[i].province = nullptr;
                    Node* tailto = new Node();
                    Node* tailfrom = new Node();
                    tailfrom = places[i].headNode;
                    tailto = places[j].headNode;
                    for (int k = 0; k <= difference; k++)
                    {
                        tailto = tailto->next;
                    }
                    while (tailto->next != nullptr)
                    {
                        tailfrom = tailfrom->next;
                        tailto = tailto->next;
                        tailto->number += tailfrom->next->number;
                    }
                    tailfrom->next = nullptr;
                    tailto->next = nullptr;
                    tailfrom = nullptr;
                    tailto = nullptr;
                }
                else    //places[i].headNode->next->day < places[j].headNode->next->day
                {
                    cout << "copy " << j << " to " << i << endl;
                    cout << "places[i].headNode->next->day < places[j].headNode->next->day" << endl;
                    int difference = places[i].headNode->next->day - places[j].headNode->next->day;
                    places[j].region = nullptr;
                    places[j].province = nullptr;
                    Node* tailto = new Node();
                    Node* tailfrom = new Node();
                    tailfrom = places[j].headNode;
                    tailto = places[i].headNode;
                    for (int k = 0; k <= difference; k++)
                    {
                        tailto = tailto->next;
                    }
                    while (tailto->next != nullptr)
                    {
                        tailfrom = tailfrom->next;
                        tailto = tailto->next;
                        tailto->number += tailfrom->next->number;
                    }
                    tailfrom->next = nullptr;
                    tailto->next = nullptr;
                    tailfrom = nullptr;
                    tailto = nullptr;
                }
            }
        }
    }
    // create a new array that is just big enough to hold the remaining places and copy the old array inside
    Place* mergedplaces = new Place[placeCount];
    int mergedplacesCount = 0;
    for (int i = 0; &places[i]; i++)
    {
        if (places[i].region != nullptr)
        {
            mergedplaces[mergedplacesCount].region = places[i].region;
            mergedplaces[mergedplacesCount].province = nullptr;
            mergedplaces[mergedplacesCount].headNode = places[i].headNode;
            mergedplacesCount += 1;
        }
    }
    //delete the old array
    delete [] places;
    //
    for (int i = 0; &places[i]; i++)
    {
        if (places[i].region != nullptr)
        {
            places[i].region = mergedplaces[i].region;
            places[i].headNode = mergedplaces[i].headNode;
        }
    }

    return placeCount;
}

void normalizeDays(Place *& places, int& placeCount, int threshold){

    cout << places[3].province << endl;
    for (int i = 0; &places[i]; i++)
    {
        int daycount = 0;
        Node* node = new Node[placeCount];
        node->next = places[i].headNode;
        node = node->next;
        cout << "check for loop" << endl;
        while (node->next != nullptr)
        {
            node = node->next;
            cout << "check while loop" << endl;
            if (node->number >= threshold && daycount == 0)
            {
                cout << "check if" << endl;
                places[i].headNode = node;
                daycount += 1;
                node->day = daycount;
            }
            else if (daycount > 0)
            {
                cout << "check else if" << endl;
                daycount += 1;
                node->day = daycount;
            }
        }
        cout << places[i].province << endl;
    }
}
/*
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
