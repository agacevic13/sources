
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <windows.h>
#include "../compressor/input.h"

//char niz[100];
//memcpy(niz, "aslda", strlen("aslda"));

struct sensorData {
    int ID;
    char *room;
    int temp;
};

struct sensorData mySD;

cJSON *simulation = NULL;
cJSON *sensors = NULL;

void initSD(void) {
    simulation = cJSON_CreateObject();   //object
    sensors = cJSON_CreateArray();       //array
    char *buffer = calloc(1000, sizeof(char));
    Load("sensor.json", buffer, 1000);
    //cJSON *sensors = cJSON_Parse(buffer);
    //buffer -> sensors;

    cJSON_AddItemToObject(simulation, "sensors", sensors);  // add array to object


}

void updateSensor(cJSON *sensor,struct sensorData* sd)
{
    cJSON_ReplaceItemInObject(sensor, "room", cJSON_CreateString(sd->room));
    cJSON_ReplaceItemInObject(sensor, "temp", cJSON_CreateNumber(sd->temp));
}

void sendSensorData(const struct sensorData* const sd) 
{
    cJSON *sensor = NULL;
    //cJSON *sensor = cJSON_CreateObject();   // new object for sensor
    //cJSON_AddItemToArray(sensors, sensor);

    cJSON_ArrayForEach(sensor, sensors)
    {
        if (cJSON_GetObjectItem(sensor, "ID")->valueint == sd->ID)
        {
            updateSensor(sensor, (struct sensorData *)sd);
            return;
        }
    }

    cJSON *newsensor = cJSON_CreateObject();   // new object for sensor
    cJSON_AddItemToArray(sensors, newsensor);  // add sensor object to the sensors array

    cJSON_AddNumberToObject(newsensor, "ID", sd->ID);
    cJSON_AddStringToObject(newsensor, "room", sd->room);
    cJSON_AddNumberToObject(newsensor, "temp", sd->temp);
}

void saveSensorData() 
{
    char *jsonString = cJSON_Print(simulation);  
    printf("%s\n", jsonString);  
    Save("sensor.json", jsonString);
    cJSON_free(jsonString); 
}

int main() 
{
    initSD();  

    mySD.ID = 1;
    mySD.room = malloc(100 * sizeof(char));
    memcpy(mySD.room, "Kitchen", strlen("Kitchen"));
    mySD.temp = 23;

    while(1)
    {  
        sendSensorData(&mySD);
        //printSensorData();

        mySD.ID++;
        Sleep(1000); // 1000 ms = 1 second

        if (mySD.ID == 3) 
        {
            mySD.ID = 1;
            //mySD.temp++;
        }
        if (mySD.ID == 2) 
        {
            mySD.room = "Bedroom";
            mySD.temp++;
        }
        if(mySD.temp == 26)
        {
            break;
        }
    }

    saveSensorData();  
    cJSON_Delete(simulation);  
    return 0;
}
