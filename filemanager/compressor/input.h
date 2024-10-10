#ifndef INPUT_H
#define INPUT_H


#include "miniz.h"
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

void Load(char* filename, uint8* pOutBuff,uLong uncomp_len);
void Save(char* filename, const uint8* pDataToSave);





#endif



