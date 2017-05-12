class HashTable{
  public:
    HashTable(tableSize);
    void insert(int key, int value);
    void initializeTable();   
    void probe(tableSize, key, hash)
  private:
    int key;
    int value;
    int tableSize;
      
};

HashTable::HashTable(tableSize) : array[20000]
{
  hashTable = array[];
  for(int a = 0; a < tableSize; a++){
    hashTable[a] == 0;
  }
}

/*void HashTable::initializeTable(int tableSize)
{
  for(int i = 0; i < tableSize; i++)
  {
   hashTable[i] = 0;
  }
  return table;
}*/

HashTable::insert(HashTable hashTable, int key, int tableSize)
{
  int hash = key % tableSize;
  for(int a = 0; a < tableSize; a++){ 
    while(hashTable[hash]!=0){
      hash += a * a
    }  
  }

  hashTable[hash] = key;
}

