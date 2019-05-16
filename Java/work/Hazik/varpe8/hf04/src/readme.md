# Protocol

## Client

- Bármilyen Stringet, address és port nélkül
    - elküldi a Servernek

### ClientEngine

- **pong [args]**
    - **wait4players**
        - tovább küldi a guinak
    - **game [args]**
        - lásd lejjebb

- **setname**
    - beállítja a kliens nevét 
    - küld egy **hello my name is [name]**-et a Clientnek

- **startserver [players] [ship2] [ship3] [ship4] [ship5] [port]**
    - Elindít egy Servert a [port]-on
    - Elküldi a Clientnek a **setserver [players] [ship2] [ship3] [ship4] [ship5]** parancsot

- **startclient [address] [port]**
    - Elindít egy Clienst ami a [adress]:[port] Serverhez próbál csatlakozni.

- **error [args]**
    - tovább küldi a ClientGUI-nak

### ClientGUI
    
- **timeout**
    - kidob a menübe

- **wait4players [max] [cur]**
    - várakozás a játékosokra  [cur]/[max]

- **error [args]**
    - **gameisfull**
        - a szerver elérte a beállított játékosok számát
        - kilép a menübe
    - **setServerInvaildInput [args]**
        - **players**
            - minimu 2 játékos kell
        - **ships** 
            - minimum 1 hajó kell
        - **bound**
            - nem lehet boundolni, vagy az adott portra boundolni
        - **port**
            - hibás port


## Server

- Bármilyen Stringet, addressel és portal
    - elküldi a address:port Clientnek

### ServerEngine

- **ping [name]**
    - válaszol egy **pong [args]**-al

- **hello my name is [name]**
    - Mindenkinek bejelenti: **welcome [name]**


# Game command

### Le:

- (1): size
- (2): player name
- (3)..(2+size): 0 water, 1 foo's ship, 2 foo's destoryed ship, 3 your ship, 4 your destroyed ship

### Fel:
- (1): x
- (2): y


# TODO

Játék implementálásának befelyezése, 
és egy refaktor az enginekre, hogy a Game osztályból hívják a függvényeket amik most a ```else if (Objects.equals(cmd.get(0),"command")) ```blokkok között vannak.
Meg az egyébb TODO-k amik a kódban vannak.