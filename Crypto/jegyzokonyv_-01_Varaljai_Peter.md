# Adatbiztonság és Kriptográfia 
**Váraljai Péter** *BUGE0Q*

## Jegyzőkönyv 01, 2020.03

### Bevezetés

#### RSA
Az RSA-eljárás nyílt kulcsú (vagyis „aszimmetrikus”) titkosító algoritmus, melyet 1976-ban Ron Rivest, Adi Shamir és Len Adleman fejlesztett ki (és az elnevezést nevük kezdőbetűiből kapta). Ez napjaink egyik leggyakrabban használt titkosítási eljárása. Az eljárás elméleti alapjait a moduláris számelmélet és a prímszámelmélet egyes tételei jelentik. [[1]](https://hu.wikipedia.org/wiki/RSA-elj%C3%A1r%C3%A1s)

#### SHA
A hash függvények (kiejtése: hes, magyarul hasítófüggvények) olyan informatikában használt eljárások, amelyekkel bármilyen hosszúságú adatot adott hosszúságra képezhetünk le. Az így kapott véges adat neve hash/hasító érték. Ezek az algoritmusok az 1980-as évek legvégén az elektronikus aláírás megjelenésével váltak szükségessé. A hasítófüggvények a számítástechnikában, elsősorban a tároló technikában, már az 1950-es évek elején megjelentek. [[2]](https://hu.wikipedia.org/wiki/Kriptogr%C3%A1fiai_hash_f%C3%BCggv%C3%A9ny)

Az SHA (Secure Hash Algorithm) az Egyesült Államok Nemzeti Szabvány és Technológia Hivatala (NIST) által kibocsátott szabványos eljárások összefoglaló elnevezése. (SHA-1, SHA-224, SHA-256, SHA-384 és SHA-512) Az első változatát 1993-ban fejlesztették az NSA felügyelete alatt. Ez 160 bit hosszúságú üzenetkivonatot (message digest) képez amelyet ezt követően a DSA elektronikus aláírás algoritmusban használhatunk. Az SHA-512 hasonló elvek alapján működik mint az SHA-1 de lényegesen nagyobb adat mennyiséget képes kezelni. A bemenete 2128-1 bit hosszúságú lehet. Ezt egyébként, a feldolgozás során 1024 bites blokkokra osztja. A kapott hasító érték összességében 512 bit hosszúságú és 8 db 64 bites blokk alkotja. A bitcoin digitális fizetőeszköz és klónjai SHA-256 algoritmust használnak. [[3]](https://hu.wikipedia.org/wiki/Kriptogr%C3%A1fiai_hash_f%C3%BCggv%C3%A9ny#SHA)

### Előkészületek

A gyakorlatot a [Google Colab](https://colab.research.google.com/) segítségével terveztem elvégezni; a ```pycryptodome``` importálását egyszerűen elvégeztem:

```
!pip install pycryptodome
```

A környezet teszteléseként egy egyszerű RSA kulcs generálást végeztem a ```pycryptodome``` dokumentációja alapján: [[4]](https://pycryptodome.readthedocs.io/en/latest/src/examples.html)

```python
from Crypto.PublicKey import RSA

key = RSA.generate(2048)
private_key = key.export_key()
file_out = open("private.pem", "wb")
file_out.write(private_key)

public_key = key.publickey().export_key()
file_out = open("receiver.pem", "wb")
file_out.write(public_key)
```

### 1. feladat: Kulcskezelés

3 metódust kellet megírni:

#### 1) ```generate_rsa_key(fileName,passphrase=None)```

Ez egy statikus metódus, két bemenettel amiből az egyik opcionális.
Meghívásakor ```fileName``` nevű PEM formátumú fájlokba menti a privát és publikus kulcsokat PEM formátumban. A privát kulcsot az opcionális ```passphrase``` paraméter megadásával lehet titkosítani.

##### Elméleti háttér

+ DER
    + Bináris formában tárolja az adatokat, "hagyományos" szövegszerkesztővel nem lehet megnézni, szerkeszteni.
+ PEM
    + A DER formátumú adatot **Base64** kódolással átalakítja olvasható szöveggé és hozzáfűz egy fejlécet és láblécet, ami egyértelműen jelöli az RSA kulcs kezdetét és végét. Amennyiben titkosítottan tároljuk a privát kulcsot, további sorokkal egészíti ki a fejlécet (Proc-Type, DEK-Info). Ezután egy üres sort emel és csak ez után kezdődik a titkosított kulcs.


##### Kód

```python
    # This static method generates RSA2048 keys, and save them to files.
    #   fileName: the name of the files to store the keys
    #   [passphrase]: The passphrase that encrypts the privatekey
    @staticmethod
    def generate_rsa_key(fileName,passphrase=None):
        # Generate keys
        key = RSA.generate(2048) # WARNING: hardcode!

        # Export the private key to file, optionaly encrypts with passphrase
        priKey = key.export_key(passphrase=passphrase)
        f = open(fileName+"pri.pem", "wb")
        f.write(priKey)
        f.close()

        # Export the public key to file
        pubKey = key.publickey().export_key()
        f = open(fileName+"pub.pem", "wb")
        f.write(pubKey)
        f.close()
        return
```

#### 2) ```load_key(self, fileName, passphrase=None)```

Ez a metódus betölti lementett privát kulcsot tartalmazó PEM fájlból a privát és a hozzá tartozó publikus kulcsot. A ```filename``` paraméter adja meg hogy honnan töltse be, Az opcionális ```passphrase``` paraméter meg akkor szükséges ha a kulcs titkosítva volt tárolva.

##### Kód

```python
    # Load the private key and the corresponding public key, from a file.
    #   fileName: the name of the files where the stored keys is
    #   [passphrase]: The passphrase that decrypts the privatekey
    def load_key(self, fileName, passphrase=None):
        self.priKeyRSA = RSA.import_key(open(fileName+"pri.pem").read(),passphrase=passphrase)
        self.pubKeyRSA = self.priKeyRSA.publickey()
        return
```

#### 3) ```load_public_key(self, fileName)```

Ez a metódus betölt egy publikus kulcsot egy ```fileName``` nevű fájlból, és visszatér vele.

##### Kód

```python
    # Load the public key from a file.
    #   fileName: the name of the files where the stored keys is
    #   return: the publick key
    def load_public_key(self, fileName):
        return RSA.import_key(open(fileName+"pub.pem").read())
```

#### Megjegyzés

+ A kódok eltérnek a megadott sablon által definiálttól, ennek több oka van:
    * Kevesebb változó használat, optimálisabb a kód
    * Felesleges printek nem kellenek
    * A névkonvenció nem egységes, most se lett az, de egy fokkal jobb, csak azokhoz nem nyúltam amik potenciálisan kellenek még majd. #TODO refactor

##### ITKoin konstruktor

Az első feladat után átírtam a konstruktort:

```python
# Constructor of the ITKoin class
    #   fileName: where to save / load the keys
    #   [passphrase]: The passphrase that encrypts the key
    #   [generateKey]: generate and save (False) or load the keys (True) 
    def __init__ (self,fileName,passphrase=None,generateKey=False):
        self.pending_transactions = []
        self.unspent_transactions = []
        self.sender_inputs = []
        self.chain = []
        
        if generateKey: # In case of need, generate new keys
          self.generate_rsa_key(fileName,passphrase)
        self.load_key(fileName,passphrase) # Load from file to memory
```

Így be lehet tölteni már létrehozott RSA kulcsokat, vagy újat generálni; mindezt opcionális titkosítás mellett.

#### Prvát és Publikus kulcs PEM

##### Privát (titkosított)

```
-----BEGIN RSA PRIVATE KEY-----
Proc-Type: 4,ENCRYPTED
DEK-Info: DES-EDE3-CBC,DFF01F68FA3F49DB

//Ss38ASEfIqrPcDEcFUFdXJa5H3H6iq58NI+/68mdPio5NGc0hmcB5m/q8ytbWU
cH3oxTH2M2JZl5N0EseZ5xNImI7GJlQPkIv3aNrv3v/BwYACCo2cuCVXiUEqxpeE
eW/fuOVAsx1N5Jm8bzEPPm1I9EGLoL1/JUUoiB3vxTf93QuXNy2NxgNfc/Otla+Q
mBAaAG+RGFG833LvvMdqXhGgH1v5p9foojhcnlREp+tShhem0N6JJtbJhXVbLUzA
deOZitdKdYiQ9UQDbeVijP2udqQ48Ps0xRTFtp4fa2mg7UZWhPCvSJkU31wb9aWO
mopezpXnXNePYwr02f5tbh/AmbGeh6r605/oiygg+e0eNk+7AfbIOV+D6OIlLr46
PaBnSfVEfoxYXsuUS1pKtZ2diq5mt5vR1TLnM1mUKj1msjLluhUUNk0MoKsf3m5q
5UaeCbSyP5+FSMD1CvaWOwswzquokHeXCtSQJsWCuXwJ7db7vN7JCjvmvEUz764t
z1hqYBncqLeyusl0pjedtDPnEyvgohowvVIS+R3k9ZROLxLo1aufupF5CbH7DEAB
Ozh4/+olNi9QiaPzIkqBQA9JgBvb0q1y/g2GvMgqy4RC/WNucGTueAKAXOp3nXih
DJ/Jq83YFoOMfq6gCsI6KaotbISszCIn0iJtPsEJnTYHGOVavkhAzqtmYlAd625N
EegiydXqw/bLMpfwdtGExyXCeCW4FCzNM0D/5dh5Tl9bHj8Xif10r+Yrl5It2MZt
b0O7q8zrzdZiTcP599MZ/IK6V7pxVl7xzEUve0InlMJOSPd5sXDFp71YavE2uTox
+f+grB4CyTrZ81yrz2hAB9DhMkqxjZM8w8azb5tmiJjqOJDA3wg1DDZtN/6lBZKG
odSshk9PMfcjr0j3/ae5UsMoE2iympYwUJbYVcLf7ye6OSt5CCXN5KIqMG4ilK6V
s6J+19HMgt484Dpp20vnMp2ZXA6pDupp/kysOjX3D/aosLv1mvwkaLJPxhUs7Ypr
2EEX95LavP8Lmab7/uJIwd7Fg5fO7D8hBCp9GMg5yyhYgdxf/O+2NFcngx+tUZ7L
yKOrJQZaXPkkwzt3EtwcxVvLxbTFlT8TyfAqFTSiHella4qRpWKzeQWUrtodfJdi
PJ1J0igfHo53ogi4vqTRbIZnMzn04ba5rcuJGXYzSUw1kpeSL20Jz27SYoQbprE8
+eRWkNnnRpwSXUzMB8g4EK64XmqtJBpliYNMvS0TLHzYtv9V/C5hvcX3h/BaOdig
aEgGpmlw3O6SK/fd0s0Zko8bHFN4eAlSx4VhdpW7u3bw53hjnXukfhE91WcjGQm8
xPx5tEAdDlMIr+n1T5vxXGGgvpAgMuMMDbP3jJ/69mq976UV0c0HELS/msSzsTab
a0qW7S4bi2EQzUPGatTEpgNqzcvbdjAL0Q3IAOktHmWfAq2cdw7m3FkLUiaeP10Q
k3Mll+InF4qxeyRN2fD4fQ8/ehmbllU8RD51HN+AaFhyXyCGVBFYrJhcTSGMSX00
+utB2CPhL47ZReBq8tj+fO5Dih4rndl6IBndLewac757OYg7QyJx6+yOz65nDLTJ
-----END RSA PRIVATE KEY-----
```

##### Publikus

```
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA0VExZtcwWL+4Qeqk2WRx
8OnkWo0nD9BKwO6EfAvHBL3C+4agTbrMhRZZPmADBjdlxDvX4+4oPRbOXjqoJGFD
kwOABZp2WoqjDkdcVif9q+6MuAnoVJh+FcT6EWKhuu4GEy3Apr3rCzW3SgbiG8I+
mCyAfga8VOkIvsPPV30mOShSrezjeZ4LdwgfWrV8wm++zTZ6Ap7bisqLcnIKARsU
e84EkIalRzwMkpaXxPRavS3yAwkFUCQd5wfp15M+0WXrdusHGo2YAhoR0SbuBDTu
0bZsLCoxjuPhMLBEx3hmEjTnt0S+eW0Afcxb173DClz1gRqWQymHiC51sDXV78o4
LQIDAQAB
-----END PUBLIC KEY-----
```

### 2. feladat: Lenyomatolás, aláírás

3 metódust kellet megírni itt is:

#### 1) ```create_hashobject(data)```

A statikus metódus igazából egy csomagoló a **SHA256** köré.
Bemenetként egy Unicode formátumú stringet kap (```data```), amit (hackeléssel) átalakít 8-bites bináris stringé, majd **SHA256** segítségével lenyomatát képzi. Ezzel a hash-objektummal tér vissza.

Hexadecimális kiíratásához a ```hasobj.hexdigest()``` függvényt lehetne használni.

##### Kód:

```python
    # This static method is a wraper around the SHA256.
    #   data: input message (string)
    #   return: SHA256 hash of the data
    @staticmethod
    def create_hashobject(data):  
        return SHA256.new(data=json.dumps(data).encode()) # HAcK: (str->binary)->hash
```

##### json.dumps hackelés

Egy üzenet hasheléséhez minden alkalommal egy hash objektumot kell létrehozzunk a **SHA256** segítségével. Ez azonban csak bináris 8-bites adatokat kezel csak. ```SHA256.new(data=b'message')``` ezt lehet jelölni a string létrehozásakor ```b```-vel előtte, de ez itt nem opció. Ezért a ```json.dumps(data)``` segítségével Unicodeból **stringDump**-ot és a ```stringDump.encode()``` segítségével 8-bites bináris dumpot készítünk. Ezt már "megeszi" az **SHA256**.

#### 2) ```create_signature(self, data)```

Ez egy csomagoló a ```pkcs1_15.new(key).sign(hashObject)``` függvény köré.
A ```data``` paraméterből a korábban megírt ```create_hashobject(data)``` segítségével egy hash-objetumot hoz létre, majd a saját privát kulcsával aláírást készít belőle. Az aláírással tér vissza.

##### Kód:

```python
    # Create a signature for a message
    #   data: input message
    #   return: using our own private key sign the data's hash 
    def create_signature(self, data):
        return pkcs1_15.new(self.priKeyRSA).sign(ITKoin.create_hashobject(data))
```

#### 3) ```verify_signature(self, data, signature, pubKeyRSA)```

Megvizsgálja hogy egy üzenet (```data```) aláírása (```signature```) valóban valós-e, a küldő fél publikus kulcsának segítségével (```pubKeyRSA```).
Ha valós ```True``` értékkel ellenkező esetben ```False``` értékkel tér vissza.

Felhasználja a korábban megírt ```create_hashobject(data)``` hash-objektum készítéshez, és elfedi az eredeti függvény (```pkcs1_15.new(publicKey).verify(hashObject, signature)```) ```raise exeption``` részét.

##### Kód:

```python
    # Verify the signature of a message, using the other party's public key
    #   data: the message
    #   signature: the message's signature
    #   pubKeyRSA: the other party's public key
    #   return: True if the siggnature is correct, False othervise
    def verify_signature(self, data, signature, pubKeyRSA):
        try:
          pkcs1_15.new(pubKeyRSA).verify(ITKoin.create_hashobject(data), signature)
        except ValueError:
          return False
        else:
          return True
```

#### Hash szerepe az aláírás ellenőrzés során

A módszer a következő:

1) Az üzenet feladója kiszámítja az aláírni kívánt üzenet hash értékét
2) A kapott hash értéket titkosítja a privát RSA kulcsával, és az üzenet mellé csatolja
3) A címzett kiszámolja az kapott üzenet hash értékét
4) A címzett a feladó publikus kulcsával dekódolja az üzenethez csatolt aláírást, és összehasonlítja a kiszámolt hash-el.
5) Ha a két érték megegyezik, az üzenet biztosan a publikus kulcs privát párjának birtokosa küldte. Bármilyen módosítás az üzenetben, vagy nem a valós privát kulccsal való titkosítás esetén különböző értéket kapunk.

Amennyiben a nem az üzenet hash értékét írná alá a feladó, hanem az üzenetet, abban az esetben egy aktív támadó képes lenne generálni olyan aláírást ami megtévesztheti a fogadó felet. Azonban az üzenet lenyomatképzése miatt a legapróbb változtatás is azonnal teljesen más értékhez vezet.

### Tesztelés

Kód írása közben printekkel ellenőriztem a helyes működést, ez azonban nem fenntartható, nem optimális.

Ezért egy ```tests(myCoin)``` függvényt hoztam létre, ahol a ```myCoin``` ```ITKoin``` típusú.

A **tests** letesztel egy üzenetet helyes aláírással, és egyet helytelennel is. Ha minden rendben ment kiírja hogy ```Tests passed!```

#### Kód:

```python
# Test of what we have so far
def tests(myCoin):
  #signature test
  message = "The quick brown fox jumps over the lazy dog"
  assert(myCoin.verify_signature(message,myCoin.create_signature(message),myCoin.pubKeyRSA))
  mA = "LOVE"
  mB = "HATE"
  assert(not myCoin.verify_signature(mA,myCoin.create_signature(mB),myCoin.pubKeyRSA))

  print("Tests passed!")
```

```python
# Create an instance
fileName = "ITC"
verrySecureHardcodedPassphrase = "$d8sa9@&=(III)ns83"
myCoin = ITKoin(fileName,passphrase=verrySecureHardcodedPassphrase,generateKey=True)
# Test it
tests(myCoin)
```

### Források

1) https://hu.wikipedia.org/wiki/RSA-elj%C3%A1r%C3%A1s
2) https://hu.wikipedia.org/wiki/Kriptogr%C3%A1fiai_hash_f%C3%BCggv%C3%A9ny
3) https://hu.wikipedia.org/wiki/Kriptogr%C3%A1fiai_hash_f%C3%BCggv%C3%A9ny#SHA
4) https://pycryptodome.readthedocs.io/en/latest/src/examples.html