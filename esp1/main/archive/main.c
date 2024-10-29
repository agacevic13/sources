#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string.h>

struct Person {
  char firstName[20];
  char lastName[20];
  void (*doWork)(char *dataRetrieved);
  int age;
};

void updatePerson(struct Person *person, char *dataRetrieved) {
  strcpy(person->firstName, "data from dataRetrieved");
  strcpy(person->lastName, "Fisher");
  person->doWork = DoWorkForPerson;
  person->doWork("some params");
  person->age = 35;
}

void connectAndGetInfo(char *url, void (*doWork)(char *dataRetrieved)) {
  // connect to wirelesw
  // connect to endpoint
  // allocate memory

  char *dataRetrieved = (char *)malloc(1024);
  // fill buffer with data: getRequest(&dataRetrieved)
  // do work and get a person object
  doWork(dataRetrieved);
  // clean up memory and other resources
  free((void *)dataRetrieved);
}

void DoWorkForPerson(char *dataRetrieved) {
  struct Person person;
  updatePerson(&person, dataRetrieved);
  printfprintf("Person: %s %s is %d years old\n", person.firstName,
               person.lastName, person.age);
}

void app_main(void) {
  connectAndGetInfo("http://getperson.com", DoWorkForPerson);
}