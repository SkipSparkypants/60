class HashTable{
  public:
    HashTable(int tableSize);
    void insert(HashTable table, int key, int value);
    void initializeTable();
  private:
    int key;
    int value;
    int tableSize;

};

void HashTable::HashTable(tableSize) : array[20000]
{
  hashTable = array[];
  initializeTable();
}

void HashTable::initializeTable(int tableSize)
{
  for(int i = 0; i < tableSize; i++)
  {
   hashTable[i] = NULL;
  }
  return table;
}

int HashTable::insert(table, key, tableSize)
{
  int hash = key % tableSize;
  if(table[hash]==0)
  {
    table[hash] = key;
  }
   
  else{
    while(table[hash] != 0)
    {
      hash++
    }
    table[hash] == key;
  }
}
