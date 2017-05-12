#include "defragmenter.h"

//#include "mynew.h"

//using namespace std;

/*void DiskDrive::print() put in defragrunner.cpp
{
    for(int i = 0; i < capacity; i++)
    {
        cout << i << " " <<  disk[i].fileBlockNum << " " << disk[i].fileID << " " << disk[i].nextBlockID << endl;
    }
}*/
//void print(); put this in defragrunner.h in the diskdrive class

 
  
Defragmenter::Defragmenter(DiskDrive *diskDrive)
{
    diskSize = diskDrive->getCapacity();
    numFiles = diskDrive->getNumFiles();
    int *firstBlock = new int[numFiles];
    short *numBlocks = new short[numFiles];
    int *disk = new int[diskSize];
    short *offSet = new short[diskSize];
    bool *written = new bool[diskSize];
    
    for(int i = 0; i < diskSize; i++)
    {
        disk[i] = 0;
        offSet[i] = 0;
        written[i] = false;
    }
    
    //get first block, number of blocks from directory
    /*for(int i = 0; i < numFiles; i++)
    {
        //numBlocks[i] = diskDrive->directory[i].getSize();
        //firstBlock[i] = diskDrive->directory[i].getFirstBlockID();
        //cout << fileNames[i]  << " " << firstBlock[i] << " " << numBlocks[i] << endl;
    }*/
    
    int count2 = 2;
    int totalBlocks = 1;
    
    for(int i = 0; i < numFiles; i++) //for each file
    {
        numBlocks[i] = diskDrive->directory[i].getSize();
        firstBlock[i] = diskDrive->directory[i].getFirstBlockID();
        int first = firstBlock[i];
        for(int j = 0; j < numBlocks[i]; j++) //for each block
        {
            DiskBlock *temp0;
            temp0 = diskDrive->readDiskBlock(first);
            disk[first] = totalBlocks + int(temp0->getFileBlockNum());
            offSet[first] = totalBlocks + int(temp0->getFileBlockNum()) + 1;
            if(j == numBlocks[i] - 1)
            {
                offSet[first] = 1;
            }
            //cout << "block num: " << disk[first] << endl;
            if(diskDrive->FAT[disk[first]] == false) // if next block empty write to that block
            {
                int next = temp0->getNext();
                temp0->setNext(disk[first] + 1);
                diskDrive->writeDiskBlock(temp0, disk[first]);
                diskDrive->FAT[disk[first]] = true;
                diskDrive->FAT[first] = false;
                written[disk[first]] = true;
                first = next;
                delete temp0;
            }
            else // else do nothing
            {
                first = temp0->getNext();
                delete temp0;
            }
        }
        totalBlocks = totalBlocks + numBlocks[i];
        diskDrive->directory[i].setFirstBlockID(count2); //set first block id in directory
        count2 += numBlocks[i];
    }
    
    delete []numBlocks;
    delete []firstBlock;
    int writeCount = 0;
    int getNext = 0;
    bool recur = false;
    int i = 2;
    while(i < diskSize)
    {
        //if(written[i] == false)
        //{
            if(recur == false)
            {
                if(written[i] == false)
                {
                    //cout << "base case" <<endl;
                    //diskDrive->print();
                    //temp = new DiskBlock;
                    recur = false;
                    DiskBlock *temp2;// = new DiskBlock;
                    temp2 = diskDrive->readDiskBlock(i);  //read data in block i
                    if(diskDrive->FAT[i] == true)//next block has a value
                    {
                        DiskBlock *temp;// = new DiskBlock;
                        temp = diskDrive->readDiskBlock(disk[i]); //save next block data in temp
                        diskDrive->writeDiskBlock(temp,0);
                        delete temp;
                        recur = true;
                    }
                    //cout << "reading: block i " << i << endl;;
                    temp2->setNext(offSet[i]);
                    diskDrive->writeDiskBlock(temp2,disk[i]); //write block i to new block
                    delete temp2;
                    //cout <<"i: " << getNext << " -> " << disk[getNext] << endl;
                    diskDrive->FAT[i] = true;
                    written[i] = true; //next block = true
                    getNext = disk[i]; //equals index of next block to write to
                    ++writeCount;
                    //diskDrive->print();
                    ++i;
                }
                else
                {
                    ++i;
                }
            }
            else
            {//getNextR has already been written to; temp = data from getNextR
                //cout << "next block found" << endl;
                if(written[getNext] == false)
                {
                    //diskDrive->print();
                    recur = false;
                    DiskBlock *temp4;// = new DiskBlock;
                    temp4 = diskDrive->readDiskBlock(0); //read from current
                    if(diskDrive->FAT[disk[getNext]] == true) // if next full
                    {
                        DiskBlock *temp;// = new DiskBlock;
                        temp = diskDrive->readDiskBlock(disk[getNext]); //read next data block
                        diskDrive->writeDiskBlock(temp, 0);
                        delete temp;
                        recur = true;
                    }
                    temp4->setNext(offSet[getNext]);
                    diskDrive->writeDiskBlock(temp4,disk[getNext]); //write from temp to next block  
                    delete temp4;
                    written[getNext] = true;
                    //cout <<"i: " << getNextR << " -> " << disk[getNextR] << endl;
                    if(recur == false) //= 0 so go back to base case
                    {
                        diskDrive->FAT[disk[getNext]] = true;
                        written[disk[getNext]] = true;
                        //delete temp;
                    }
                    getNext = disk[getNext];
                    //diskDrive->printBlock(disk[getNextR]);
                    //cout <<"i: " << getNext << " -> " << disk[getNext] << endl;
                    ++writeCount;
                    //delete temp4;
                    //diskDrive->print();
                }
                else
                {
                    recur = false;
                    //delete temp;
                }
            }
        //}
        if(writeCount == totalBlocks)
        {
            //cout << writeCount << endl;
            break;
        }
    }
    
    for(int i = totalBlocks + 1; i < diskSize; i++) //set empty blocks
    {
        diskDrive->FAT[i] = false;
    }
    
    delete []written;
    delete []disk;
    delete []offSet;
    //diskDrive->print();
    return;
}
