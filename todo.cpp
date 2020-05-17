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
    return 0;
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
        Node* tail;
        for (int i = 0; currentLine[i] ; i++)
        {
            if (currentLine[i] == ',')
            {
                commaCount += 1;
                char* substr = substring(currentLine, start, i-1);
                if (commaCount == 1)
                {
                    if (start == i)
                    {
                        places[placeCount].province = nullptr;
                        delete [] substr;
                    }
                    else
                    {
                        places[placeCount].province = substr;
                    }
                }
                else if (commaCount == 2)
                {
                    places[placeCount].region = substr;
                }
                else if (commaCount >= 5 && atoi(substr) != 0 && linecount == 0)
                {
                    Node *datastorage = new Node();
                    places[placeCount].headNode = datastorage;
                    datastorage->day = commaCount - 4;
                    datastorage->number = atoi(substr);
                    tail = datastorage;
                    dataCount += 1;
                    linecount += 1;
                    delete [] substr;
                }
                else if (commaCount >= 5 && linecount != 0)
                {
                    Node *datastorage = new Node();
                    datastorage->day = commaCount - 4;
                    datastorage->number = atoi(substr);
                    tail->next = datastorage;
                    tail = datastorage;
                    dataCount += 1;
                    linecount += 1;
                    delete [] substr;
                }
                else
                {
                    delete[] substr;
                }
                start = i+1;
            }
            if ( !currentLine[i+1] )
            {
                Node *datastorage = new Node();
                char* substr = substring(currentLine, start, i);
                datastorage->day = commaCount - 3;
                datastorage->number = atoi(substr);
                tail->next = datastorage;
                tail = datastorage;
                dataCount += 1;
                linecount += 1;
                tail->next = nullptr;
                delete [] substr;
            }
        }
        placeCount += 1;
    }
    return places;
}

int mergeAllProvinces(Place*& places, int placeCount, const char* home){
    home = "Hong Kong"; 
    int originalPlaceCount = placeCount;
    for (int i = 0; i < placeCount; i++)
    {
        if (places[i].province != nullptr && strcmp(places[i].province,home) == 0)
        {
            delete [] places[i].province;
            if (places[i].region != nullptr)
                delete [] places[i].region;
            char* newString = new char[99];
            strcpy(newString, home);
            strcat(newString, "(Home)");
            places[i].region = newString;
            places[i].province = nullptr;
        }
        if (places[i].headNode == nullptr) 
        {
            if (places[i].region != nullptr)
                delete [] places[i].region;
            if (places[i].province != nullptr)
                delete [] places[i].province;
            places[i].region = nullptr;
            places[i].province = nullptr;
        }
    }
    // merge the data and set all already merged provinces's region and province into nullptr
    for (int i = 0; i < originalPlaceCount ; i++)
    {
        for (int j = 0; j<i ; j++)
        {
            if(places[j].region != nullptr 
            && places[i].region != nullptr
            && places[i].headNode != nullptr
            && places[j].headNode != nullptr
            && strcmp(places[i].region,places[j].region) == 0 )
            {
                placeCount -= 1;
                if ( places[i].headNode->next->day == places[j].headNode->next->day)
                {
                    //cout << "merge " << i << " to " << j << endl;
                    if (places[i].region != nullptr)
                        delete [] places[i].region;
                    places[i].region = nullptr;
                    if (places[i].province != nullptr)
                        delete [] places[i].province;
                    places[i].province = nullptr;
                    Node* tailto ;
                    Node* tailfrom ;
                    tailfrom = places[i].headNode;
                    tailto = places[j].headNode;
                    while (tailfrom != nullptr && tailto != nullptr)
                    {
                        tailto->number += tailfrom->number;
                        tailfrom = tailfrom->next;
                        tailto = tailto->next;
                    }
                }
                else if ( places[i].headNode->next->day > places[j].headNode->next->day)
                {
                    //cout << "merge " << i << " to " << j << endl;
                    int difference = places[i].headNode->next->day - places[j].headNode->next->day;
                    if (places[i].region != nullptr)
                        delete [] places[i].region;
                    places[i].region = nullptr;
                    if (places[i].province != nullptr)
                        delete [] places[i].province;
                    places[i].province = nullptr;
                    Node* tailto ;
                    Node* tailfrom;
                    tailfrom = places[i].headNode;
                    tailto = places[j].headNode;
                    for (int k = 0; k < difference && tailto != nullptr; k++)
                    {
                        tailto = tailto->next;
                    }
                    while (tailto != nullptr && tailfrom != nullptr)
                    {
                        tailto->number += tailfrom->number;
                        tailfrom = tailfrom->next;
                        tailto = tailto->next;
                    }
                }
                else if( places[i].headNode->next->day < places[j].headNode->next->day )    //places[i].headNode->next->day < places[j].headNode->next->day
                {
                    //cout << "merge " << j << " to " << i << endl;
                    int difference = places[j].headNode->next->day - places[i].headNode->next->day;
                    if (places[j].region != nullptr)
                        delete [] places[j].region;
                    places[j].region = nullptr;
                    if (places[j].province != nullptr)
                        delete [] places[j].province;
                    places[j].province = nullptr;
                    Node* tailto;
                    Node* tailfrom;
                    tailfrom = places[j].headNode;
                    tailto = places[i].headNode;
                    for (int k = 0; k < difference; k++)
                    {
                        tailto = tailto->next;
                    }
                    while (tailfrom != nullptr && tailto != nullptr)
                    {
                        tailto->number += tailfrom->number;
                        tailfrom = tailfrom->next;
                        tailto = tailto->next;
                    }
                }
            }
        }
    }
    // create a new array that is just big enough to hold the remaining places and copy the old array inside
    Place* mergedplaces = new Place[placeCount];
    int mergedplacesCount = 0;
    for (int i = 0; i < originalPlaceCount ; i++)
    {
        if (places[i].region != nullptr)
        {
            mergedplaces[mergedplacesCount].region = places[i].region;
            mergedplaces[mergedplacesCount].province = nullptr;
            mergedplaces[mergedplacesCount].headNode = places[i].headNode;
            places[i].region = nullptr;
            places[i].headNode = nullptr;
            mergedplacesCount += 1;
        }
    }
    deallocatePlaces(places, originalPlaceCount);
    places = mergedplaces;
    return placeCount;
}

void normalizeDays(Place *& places, int& placeCount, int threshold){
    int originalPlaceCount = placeCount;
    for (int i = 0; i < originalPlaceCount; i++)
    {
        int day = 0;
        Node* ptr;
        ptr = places[i].headNode;
        while (ptr != nullptr)
        {
            if (ptr->number >= threshold)
            {
                day = 1;
                break;
            }
            Node* next = ptr->next;
            delete ptr;
            ptr = next;
        }
        places[i].headNode = ptr;
        {
            Node* current;
            current = places[i].headNode;
            while (current != nullptr)
            {
                current->day = day;
                current = current->next;
                day = day + 1;
            }
        }
    }

    for (int i = 0; i < originalPlaceCount; i++)
    {
        if (places[i].headNode == nullptr)
        {
            placeCount -= 1;
        }
    }

    Place* normplaces = new Place[placeCount];
    int normCount = 0;
    for (int i = 0; i < originalPlaceCount; i++)
    {
        if (places[i].headNode != nullptr)
        {
            normplaces[normCount].region = places[i].region;
            normplaces[normCount].province = places[i].province;
            normplaces[normCount].headNode = places[i].headNode;
            places[i].province = nullptr;
            places[i].region = nullptr;
            places[i].headNode = nullptr;
            normCount += 1;
        }
    }

    deallocatePlaces(places, originalPlaceCount);
    places = normplaces;
}

void changeToNDayGrowth(Place* places, int placeCount, int n){
    for (int i = 0; i < placeCount ; i++)
    {
        Node* copynum = new Node[999];
        Node* head = copynum;
        Node* tail = places[i].headNode;
        while (tail != nullptr)
        {
            head->number = tail->number;
            head->day = tail->day;
            head = head->next = head + 1;
            tail = tail->next;
        }
        head = copynum;
        tail = places[i].headNode;
        for (int j = 0; tail != nullptr && j < n; j++)
        {
            tail = tail->next;
        }
        bool check = false;
        int countail = 0;
        while (tail != nullptr && head != nullptr)
        {
            if (tail->number - head->number != 0 && check == false)
            {
                tail->number = tail->number - head->number;
                tail = tail->next;
                head = head->next;
                countail += 1;
            }
            else if (tail->number - head->number != 0 && check == true)
            {
                tail->number = head->number - tail->number;
                tail->day = head->day;
                tail = tail->next;
                head = head->next;
                countail += 1;
            }
            else
            {
                check = true;
                head = head->next;
            }
        }
        if (check == true)
        {
            tail = places[i].headNode;
            for (int k = 0; k < countail + 4 && tail != nullptr; k++)
            {
                tail = tail -> next;
            }
            deallocateLinkedList(tail->next);
            tail -> next = nullptr;
        }
        delete tail;
        delete [] copynum;
    }
}

void writeCSV(const char* csvFileName, Place* places, int placeCount){
    ifstream ifs(csvFileName);
    if (ifs)
    {
        remove(csvFileName);
    }
    ifs.close();
    ofstream ofs(csvFileName);

    for (int i = 0; i < placeCount; i++)
    {
        Node* ptr;
        ptr = places[i].headNode;
        
        ofs << places[i].region ;
        while (ptr != nullptr)
        {
            ofs << "," << ptr->number;
            ptr = ptr->next;
        }
        ofs << endl;
        delete ptr;
    }
    ofs.close();
}

void deallocateCSVLines(char** csvLines, int csvLineCount){
    for (int i = 0; i < csvLineCount; i++)
    {
        delete [] csvLines[i];
    }
    delete [] csvLines;
}

void deallocateDates(char** dates, int dateCount){
    for (int i = 0; i < dateCount; i++)
    {
        delete [] dates[i];
    }
    delete [] dates;
}

void deallocateLinkedList(Node* headNode){
    while (headNode != nullptr) {
        Node* next = headNode->next;
        delete headNode;
        headNode = next;
    }
}

void deallocatePlaces(Place* places, int placeCount){
    for (int i = 0; i < placeCount; i++)
    {
        deallocateLinkedList(places[i].headNode);
        if (places[i].province != nullptr)
            delete [] places[i].province;
        if (places[i].region != nullptr)
            delete [] places[i].region;
    }
    delete [] places;
}

