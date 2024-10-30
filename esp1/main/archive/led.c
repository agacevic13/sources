#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <string.h>

//#define PIN 4

typedef struct Person_struct {
    char firstName[20];
    char lastName[20];
    int age;
    void (*DoWork)(char *dataRetrieved)
} Person;


void DoWorkForPerson(char * dataRetrieved)
{
    Person person;
    updatePerson(&person, dataRetrieved);
    printf("person: %s %s is %d years old.\n", person.firstName, person.lastName, person.age);
    
}

void connectAndGetInfo(char *url, void *(DoWork)(char * dataRetrieved)) // once this function call any function that is called translates into DoWork
{
    //connect to wifi
    //connect to endpoint
    //allocate memmory
    char * dataRetrieved = (char *) malloc(1024);
    //fill buffer with data: getRequest(&dataRetrieved)
    //do work and get a person object
    DoWork(dataRetrieved);
    //clean up memory and other resources
    free((void *) dataRetrieved);
}

void updatePerson(Person *person, char * dataRetrieved)
{
    strcpy(person->firstName, "data from dataRetrieved");
    strcpy(person->lastName, "data from dataRetrieved");
    person->DoWork = DoWorkForPerson;
    person->DoWork("some params");
    person->age = 25;
}

void app_main()
{
   connectAndGetInfo("https://getperson.com", DoWorkForPerson); //pointer on what functions to use
}

//  //LED
//     gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
//     uint32_t isOn = 0;
//     while(true)
//     {
//         isOn = !isOn;
//         gpio_set_level(PIN, isOn);
//         vTaskDelay(10 / portTICK_PERIOD_MS);
//     }

    