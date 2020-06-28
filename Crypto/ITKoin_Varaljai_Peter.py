from base64 import b64encode, b64decode
from Crypto.Signature import pkcs1_15
from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256
import json

# Hardcode mentesség
privatTag = '_privat.pem'
publicTag = '_public.pem'
idTag     = '.id'

class ITKoin:
    def __init__ (self):

        # Fájlokba tároljuk a dolgokat azt szimulálva mintha kívülröl érkezne
        # Blokklánc lista
        self.chainFileName = 'chain.txt'
        # Várakozó tranzakciók
        self.pendingTransactionsFileName = 'pending.txt'
        # Saját kulcsaink
        self.myPrivateKeyFileName = 'itk_01'

        # Tárolók 
        # Blokk lánc lista
        self.chain = []
        # Feldolgozásra váró tranzakciók
        self.pendingTransactions = []
        # El nem költött tranzakciók listája (összes)
        self.unspentOutputs = []
        # El nem költött tranzakciók listája (saját)
        self.myUnspentOutputs = []

        # Inicalizálás
        # A felhasználói lista
        self.theITKoinUsers = ['itk_01', 'itk_02']
        # A kezdő összeg amit mindenki megkap induláskor
        self.initialOffering = 1000
        # Nehézség
        self.numOfZeros = 4
        
    # RSA kulcsokat generál majd fájlokba menti
    #   Bemenet: fileName, [passphrase]
    #   Kimenet: 3 fájl
    #       1 privát kulcsot tartalamzó file fileName+fileTag néven PEM formátumban
    #       1 publikus kulcsot tartalamzó file fileName+fileTag néven PEM formátumban
    #       1 az ID-t tartalmazó file fileName+fileTag néven ASCII formátumban
    def generateRSAKey(self, fileName,passphrase=None):

        # Generate RSA
        key = RSA.generate(2048) 

        # A privát kulcsot (amiből kiszámolható a publikus is) elmentjük egy fájlba, PEM formátumban
        f = open(fileName + privatTag, 'wb')
        f.write(key.export_key(passphrase=passphrase))
        f.close()

        # A publikus kulcsot elemntjük egy fájlba
        f = open(fileName + publicTag, 'wb')
        f.write(key.publickey().export_key())
        f.close()

        
        # A publikus kulcsot ASCII karakterekké alakítjuk, lehasseljük, bináris stringé alakítjuk majd kiírjuk az id fájlba
        f = open(fileName + idTag, 'wb')
        f.write(self.createHashHexValue(key.publickey().export_key().decode('ascii')).encode('ascii'))
        f.close()

        return

    # Betölti a privát kulcsunkat majd eltárolja a privát kulcsot, az abból számolt a publikus kulcsot és az abból számolt az ID-t.
    #   Bemenet: [passphrase]
    #   Kimenet: nincs
    def loadMyData(self,passphrase=None):
        file = open(self.myPrivateKeyFileName+privatTag, 'r')
        self.myPrivatKey = RSA.import_key(file.read(),passphrase=passphrase)
        file.close()

        self.myPublicKey = self.myPrivatKey.publickey()

        file = open(self.myPrivateKeyFileName+idTag, 'r')
        self.myID = file.read()
        file.close()
        return
     
    # Betölti a fileName által hivatkozott publikus kulcsot
    #   Bemenet: fileName
    #       a fileName-el kezdődő publikus kulcs
    #   Kimenet: Publikus RSA kulcs 
    @staticmethod
    def loadPublicKey(fileName):
        return RSA.import_key(open(fileName+publicTag).read())

    # Betölti a fileName által hivatkozott ID-t
    #   Bemenet: fileName
    #       a fileName-el kezdődő ID fájl
    #   Kimenet: ID [string]
    @staticmethod
    def loadID(fileName):
        return open(fileName+idTag, 'r').read()

    # Képzi és vissza adja egy string SHA256-os lenyomatát.
    #   Bemenet: data
    #   Kimenet: SHA256-os lenyomat objektum
    @staticmethod
    def createHashObject(data):
        return SHA256.new(json.dumps(data).encode())

    # Képzi és vissza adja egy string SHA256-os lenyomatát.
    #   Bemenet: data
    #   Kimenet: SHA256-os lenyomat hexadecimális stringként
    @staticmethod
    def createHashHexValue(data):
        return ITKoin.createHashObject(data).hexdigest()

    # Aláírást készít egy üzenethez a saját privátkulcsunk segítségével
    #   Bemenet: data
    #   Kimenet: Aláírás
    def createSignature(self, data):
        return b64encode( pkcs1_15.new(self.myPrivatKey).sign(self.createHashObject(data)) ).decode()

    # Ellenőrzi az aláírás helyességét egy adaton
    #   Bemenet:
    #       data - az üzenet
    #       signature - az aláírás
    #       publicKey - a küldő fél publikus RSA kulcsa
    #   Kimenet: igaz ha valódi az aláírás, hamis különben
    def verifySignature(self, data, signature, publicKey):
        try:
          pkcs1_15.new(publicKey).verify(self.createHashObject(data), b64decode(signature.encode()) )
        except ValueError:
          return False
        else:
          return True

    # Kidumpolja json formátumba az adatot egy fájlba
    #   Bemenet: 
    #       data - adat
    #       fileName - fájl neve
    #   Kimenet: nincs
    @staticmethod
    def saveData(data, fileName):
        with open(fileName, 'w') as f:
            json.dump(data, f)
        return

    # Beolvassa a json formátú adatot az adott fájlból
    #   Bemenet: fileName - fájl neve
    #   Kimenet: adat
    @staticmethod
    def loadData(fileName):
        with open(fileName) as f:
            return json.load(f)
        

    # Lementi a blokkláncot
    #   Előkövetelmény: chain
    #   Végeredmény: chainFileName
    def saveChain(self):
        self.saveData(self.chain, self.chainFileName)
        return

    # Lementi a várakozó tranzakciókat
    #   Előkövetelmény: pendingTransactions
    #   Kimenet: pendingTransactionsFileName
    def savePendingTransactions(self):
        self.saveData(self.pendingTransactions, self.pendingTransactionsFileName)
        return

    # Beolvassa a blokkláncot, és ellenőrzi annak helyességét
    #   Előkövetelmény: chainFileName
    #   Végeredmény: chain
    def loadChain(self):
        self.chain = ITKoin.loadData(self.chainFileName)
        self.validateChain()
        return

    # Beolvassa a várakozó tranzakciókat, megvizsgálja őket, és eldobálja a nem érvényeseket
    #   Előkövetelmény: pendingTransactionsFileName
    #   Végeredmény: pendingTransactions
    def loadPendingTransactions(self):
        self.findUnspentOutputs() # Az unspentOutputok között keresi majd a hivatkozott outputokat.

        self.pendingTransactions = self.loadData(self.pendingTransactionsFileName)
        validatedPendingTransactions = []
        while len(self.pendingTransactions) != 0:
            transaction = self.pendingTransactions.pop()
            if self.validateTransaction(transaction):
                validatedPendingTransactions.append(transaction)
        self.pendingTransactions = validatedPendingTransactions
        return

    # Ellenőrzi egy tranzakció helyességét
    #   Bemenet: 
    #     transaction - a tranzakció
    #   Kimenet: igaz/hamis - 
    def validateTransaction(self, transaction):
        sumOfInputs = 0
        for input in transaction['inputs']:
            data = {'txid':input['txid'],'csaposhi':input['csaposhi']}
            # Aláírások ellenőrzés
            if (not self.verifySignature(data, input['signature'], RSA.import_key(input['publicKey']))):
                print(data,input['signature'],RSA.import_key(input['publicKey']))
                return False
            # Input hivatkozások ellenőrzése
            if data not in self.myUnspentOutputs:
                print(data,self.myUnspentOutputs)
                return False
            sumOfInputs += input["csaposhi"]
        
        
        sumOfOutputs = 0
        for output in transaction['outputs']:
            sumOfOutputs += output['csaposhi']
            # Minden output nagyobb mint 0
            if (output['csaposhi']<=0):
                return False

        # Outputok összege megegyezik-e az inputok összegével
        if sumOfInputs != sumOfOutputs:
            return False

        return True

    # Ellenőrzi a blokkláncot
    #   Előkövetelmény: chain
    #   Végeredmény: Figyelmeztet ha nem helyes a blokklánc
    def validateChain(self):
        lastBlock = self.chain[0]
        ci = 1 # Az első blokk kivétel, nem ellenőrizzük
        
        # Végigmegyünk az összes blokkokon páronként
        while ci < len(self.chain):
            block = self.chain[ci]

            # Megvizsgáljuk hogy tényleg egybe van-e fűzve a blokklánc
            if self.createHashHexValue(lastBlock['blockHeader']) != block['blockHeader']['previousBlockHeaderHash']:
                return False

            # Megvizsgáljuk hogy az aktuális blokk hash értéke elég 0-ával kezdődik-e.
            if not self.PoW(self.createHashHexValue(block)):
                return False
            
            lastBlock = block
            ci += 1
        # Az utolsó blockot is megvizsgáljuk még, hogy érvényes e a PoW érték.
        if not self.PoW(self.createHashHexValue(self.chain[-1])):
            return False

        return True



    # Megkersi és elmenti az összes elköltetlen outputot, a sajátunkat külön tárolva.
    #   Előkövetelmény: chain, myID
    #   Végeredmény: unspentOutputs, myUnspentOutputs
    def findUnspentOutputs(self):
        self.unspentOutputs = []
        self.myUnspentOutputs = []
        #Első blokk
        for transaction in self.chain[0]['transactions']:
            for output in transaction['outputs']:
                self.unspentOutputs.append({'txid':transaction['txid'], 'csaposhi': output['csaposhi']})
                if output['recipient']==self.myID:
                    self.myUnspentOutputs.append({'txid':transaction['txid'], 'csaposhi': output['csaposhi']})
        #Többi blokk
        for block in self.chain[1:]: 
            for transaction in block['transactions']: # Blokk összes tranzakciója
                for output in transaction['outputs']: # Összes output - belerakjuk ha létezik
                    self.unspentOutputs.append({'txid':transaction['txid'], 'csaposhi': output['csaposhi']})
                    if output['recipient'] == self.myID:
                        self.myUnspentOutputs.append({'txid':transaction['txid'], 'csaposhi': output['csaposhi']})
                for input in transaction['inputs']: # Összes input - kiszedjük ha felhasználtuk
                    inp = {'txid':input['txid'], 'csaposhi': input['csaposhi']}
                    self.unspentOutputs.remove(inp) # Hibát dob ha nincs benne a hivatkozott output.
                    if inp in self.myUnspentOutputs:
                        self.myUnspentOutputs.remove(inp)
        return

    # Ellenőrzi hogy a hex string elegendő 0-val kezdődik-e.
    #   Bemenet: hex
    #   kimenet: igen/nem
    def PoW(self,hex):
        return (hex[:self.numOfZeros] == ("0" * (self.numOfZeros+1))[:self.numOfZeros] )

    # Az összes fel nem használt tranzakciót belerakja egy blokkba, és "kibányássza"
    #   Előkövetelmény: chain, pendingTransactions
    #   Végeredmény: chain, pendingTransactions
    def mine(self):

        if len(self.chain) == 0:
            # Az első blokknak speciális az előző blokk lenyomat értéke
            previousBlockHeaderHash = 'ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff'
        else:
            # Az új blokk előző blokk lenyomat értéke
            previousBlockHeaderHash = self.createHashHexValue(self.chain[-1]['blockHeader'])

        nonce = 0

        # Blokk header létrehozás
        blockHeader = {
            'nonce': nonce,
            'previousBlockHeaderHash': previousBlockHeaderHash,
            'transactionsHash' : self.createHashHexValue(self.pendingTransactions),
        }

        # Addig növeli a nonce értékét amíg a a blockHeaderHash értéke megfelelő számú 0-val kezdődik.
        while True:
            if self.PoW(self.createHashHexValue(blockHeader)):
                break
            blockHeader['nonce'] += 1

        # Létrehozza a blokkot a header és az összes várakozó tranzakciót felhasználva
        block = {
            'blockHeader': blockHeader,
            'transactions': self.pendingTransactions
        }

        self.chain.append(block) # berakja a blokkba
        self.saveChain() # lementi ("kihírdei")
        self.pendingTransactions = [] # Kitörli a felhasznált tranzakciókat a várakozó listából
        self.savePendingTransactions() # lementi ("kihírdei")
        return

    # Létrehozza az első blokkot, ahol kiossza a kezdő összegeket
    #   Előkövetelmény: theITKoinUsers
    #   Végeredmény: chain    
    def generateFirstBlock(self):
        self.pendingTransactions = []
        while len(self.theITKoinUsers) > 0:
            recipient = self.loadID(self.theITKoinUsers.pop())
            transaction = {'inputs': [],'outputs': [{'csaposhi': self.initialOffering,'recipient': recipient}] }
            transaction['txid'] = self.createHashHexValue(transaction) # a tranzakció lenyomata az ID
            self.pendingTransactions.append(transaction) # Belerakjuk a várakozó tranzakciók listájába
        self.mine() # Majd kibányásszuk.
        return

    # Létrehoz egy új tranzakciót a saját nevünkben
    #   Bemenet: 
    #       csaposhi - összeg
    #       recipient - kedvezményezett
    #   Kimenet: nincs
    def newTransaction(self, csaposhi, recipient):
        summa = 0
        inputs=[]

        # Amíg summa nem éri el az utalni kívánt összeget, elköltetlen outputokat keres és hozzáadja a felhasználni kívánt összegekhez
        try:
          while (summa < csaposhi):
              nextOutput = self.myUnspentOutputs.pop() #pop will raise an error when no unspent tranzaction left
              inputs.append(nextOutput)
              summa += nextOutput['csaposhi']
        except Exception as e:
          print("Not enough csaposhi!")
          return

        # Aláírja az összes inputot csatolja a publikus kulcsát
        for input in inputs:
            input['signature'] = self.createSignature(input)
            input['publicKey'] = self.myPublicKey.export_key().decode('ascii') # a publikus kulcsunk PEM formátumba

        # Outputok létrehozása (utalás, visszajáró)
        outputs = [{'csaposhi': csaposhi,'recipient': recipient}]
        if summa > csaposhi: # Visszajáró?
            outputs.append({'csaposhi': summa-csaposhi,'recipient': self.myID})

        transaction = {'inputs': inputs,'outputs': outputs}
        transaction['txid'] = self.createHashHexValue(transaction) # a tranzakció lenyomata az ID
        self.pendingTransactions.append(transaction) # Hozzáadjuk a várakozó tranzakciókhoz
        self.savePendingTransactions() # lementi ("kihírdei")
        return


def simulateCommunication(myCoin):
    myCoin.loadChain()
    myCoin.loadPendingTransactions()


myCoin = ITKoin()

# Init
print("Init")
for user in myCoin.theITKoinUsers: # Felhasznáálók létrehozása: RSA kulcsok és ID-k generálása.
    myCoin.generateRSAKey(user)
myCoin.loadMyData() # Saját adataim betöltése (kulcsok, ID)
myCoin.generateFirstBlock() # Első blokk legenerálása és a láncba fűzése
simulateCommunication(myCoin)
print("Elköltetlen outputjaink:")
print(myCoin.myUnspentOutputs)

# Új Tranzakció
print("\nÚj tranzakció")
myCoin.newTransaction(12,myCoin.loadID("itk_02"))
simulateCommunication(myCoin)
print("A várakozó tranzakciók:")
print(myCoin.pendingTransactions)

# Bányászás
print("\nBányászás")
myCoin.mine()
simulateCommunication(myCoin)
print("Elköltetlen outputjaink:")
print(myCoin.myUnspentOutputs)

# Új Tranzakció
print("\nÚj tranzakció")
myCoin.newTransaction(989,myCoin.loadID("itk_01")) # Nincs elég fedezet {-1}
simulateCommunication(myCoin)
myCoin.newTransaction(100,myCoin.loadID("itk_01")) # Elküldjük magunknak = felváltjuk kisebbre {100, 888}
simulateCommunication(myCoin)
myCoin.newTransaction(-999,myCoin.loadID("itk_02")) # Visszajáró +999-lesz, a -999-re meg nem fog soha a hivatkozni itk_02 | de ellenőrizzük ezért ez nem fog soha bekerülni!
simulateCommunication(myCoin)
print("A várakozó tranzakciók:")
print(myCoin.pendingTransactions)

# Bányászás
print("\nBányászás")
myCoin.mine()
simulateCommunication(myCoin)
print("Elköltetlen outputjaink:")
print(myCoin.myUnspentOutputs)

# Chain
print("\nBlokklánc")
simulateCommunication(myCoin)
print(myCoin.chain)