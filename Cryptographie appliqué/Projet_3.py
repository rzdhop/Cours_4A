import rsa
import sqlite3

class Generator:
    def __init__(self):
        self.bddName = "KeyStore.sqlite"
        self.bdd = self._initBDD()
        self.bddCursor = self.bdd.cursor()
        
    def _initBDD(self, database:str = None) -> sqlite3.Connection:
        database = self.bddName if database is None else database
        bdd =  sqlite3.connect(database, check_same_thread=False)
        cursor = bdd.cursor()
        cursor.execute("""CREATE TABLE IF NOT EXISTS Keys (
            id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT,
            modulus varchar(3000) NOT NULL, 
            exponant varchar(10) NOT NULL,
            bitsize INT NOT NULL)
        """)
        bdd.commit()
        return bdd
    
    @staticmethod
    def massKeyGen(KeyGen:'Generator', numOfKey:int, bitsize:list = [128, 256, 512, 1024, 2048]):
        for size in bitsize:
            print(f"Printing {size}bit keys...", end="\n")
            for keyIndex in range(numOfKey):
                print(f" Generating... {int((keyIndex / numOfKey)*100)}%", end="\r")
                KeyGen.InsertKey(KeyGen.genKey(size))
    
    def CheckDuplicate(self) -> list:
        """
        Return list of Tuple
        
        [  (<modulus>, <iteration>, <bisize>), ...  ]
        """
        duplicates = []
        duplicateFinderPayload = """
        SELECT modulus, COUNT(modulus), bitsize
            FROM Keys
        GROUP BY modulus, bitsize
            HAVING COUNT(modulus) > 1"""
        
        for row in self.bddCursor.execute(duplicateFinderPayload).fetchall():    
            duplicates.append((row[0], row[1], row[2]))
        
        if len(duplicates):
            print("Duplicate has been found !")
            for duplicate in duplicates:
                print(f"\tModulus : {duplicate[0]} | Iteration : {duplicate[1]} | BitSize : {duplicate[2]}")
        
        self.bdd.commit()
        return duplicates
    
    def InsertKey(self, key:tuple):
        (modulus, exponant, bitsize) = key
        self.bddCursor.execute(f"""INSERT INTO Keys (modulus,exponant,bitsize) VALUES (
                            "{str(modulus)}", 
                            "{str(exponant)}", 
                            "{str(bitsize)}")
        """)
        self.bdd.commit()
        
    def close(self):
        self.bddCursor.close()
        self.bdd.close()
    
    @staticmethod
    def genKey(bitsize:int) -> tuple:
        (pubkey, privkey) = rsa.newkeys(bitsize)
        modulus = pubkey.n
        exponant = pubkey.e
        return  (modulus, exponant, bitsize)


if __name__ == "__main__":
    KeyGen = Generator()
    Generator.massKeyGen(KeyGen, 500000)
    
    KeyGen.close()
    
    
    