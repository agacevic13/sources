#include <stdio.h> 
#include "cJSON.h"

struct sensorData
{
    int ID;
    char *room;
    int temp;
};
struct sensorData mySD;

cJSON *simulation = NULL;
cJSON *sensors = NULL;
cJSON *sensor = NULL;
cJSON *ID = NULL;
cJSON *room = NULL;
cJSON *temp = NULL;

void initSD(void)
{
    sensors = cJSON_CreateObject();
}

void sendSensorData(const struct sensorData* const sd)
{
    cJSON *simulation =cJSON_CreateObject();

    sensors =cJSON_CreateArray();
    cJSON_AddItemToObject(simulation, "sensors", sensors);
    
    sensor = cJSON_CreateObject();
    cJSON_AddItemToArray(sensors, sensor);
    ID = cJSON_CreateNumber(sd->ID);
    cJSON_AddItemToObject(sensor, "ID", ID);

    room = cJSON_CreateString(sd->room);
    cJSON_AddItemToObject(sensor, "room", room);

    temp = cJSON_CreateNumber(sd->temp);
    cJSON_AddItemToObject(sensor, "temp", temp);

    
    char *jsonString = cJSON_Print(simulation);
    printf("%s\n", jsonString);

}

#if 0
void writeSensorData()
{
    FILE *fp = fopen("sensorData.json", "w");
    if(fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    
    fputs(jsonString, fp);
    fclose;

}
#endif


#include <windows.h>

int main()
{
    initSD();
    
    mySD.ID = 1;
    mySD.room = "Kitchen";
    mySD.temp = 23;

    while(1)
    {
        sendSensorData(&mySD);
        mySD.ID++;
        Sleep(1000); // ms
        if (mySD.ID == 3)
        {
            mySD.ID = 1;
            mySD.temp+=3;
            
        }
        if(mySD.ID == 2)
        {
            mySD.room = "Bedroom";
            mySD.temp ++;
        }
        if (mySD.temp > 30) 
        {
            break;
        }
        
#if 0
        if(mySD.ID == 1)
        {
            
        }
#endif
            
    }
}



#if 0
int createfile() { 
// create a cJSON object 
cJSON *json = cJSON_CreateObject(); 
cJSON_AddStringToObject(json, "name", "John Doe"); 
cJSON_AddNumberToObject(json, "age", 30); 
cJSON_AddStringToObject(json, "email", "john.doe@example.com"); 

// convert the cJSON object to a JSON string 
char *json_str = cJSON_Print(json); 

// write the JSON string to a file 
FILE *fp = fopen("data.json", "w"); 
if (fp == NULL) { 
	printf("Error: Unable to open the file.\n"); 
	return 1; 
} 
printf("%s\n", json_str); 
fputs(json_str, fp); 
fclose(fp);
// free the JSON string and cJSON object 
cJSON_free(json_str); 
cJSON_Delete(json); 
return 0; 
}
#endif
