// Author Alex and Faiyz
#ifndef defragmenterH
  #define defragmenterH

#include "DefragRunner.h"
//#include "mynew.h"
class Defragmenter
{
public:
  Defragmenter(DiskDrive *diskDrive);
  /*DiskBlock *temp0 = NULL;
  DiskBlock *temp = NULL;
  DiskBlock *temp2 = NULL;
  DiskBlock *temp4 = NULL;*/
  int diskSize;
  int numFiles;
  /*bool *written = NULL;
  int *fileNames = NULL;
  int *firstBlock = NULL;
  int *numBlocks = NULL;
  int *disk = NULL;
  int *offSet = NULL;*/
  /*bool *written;
  int *firstBlock;
  int *numBlocks;
  int *disk;
  int *offSet;*/
};
#endif
