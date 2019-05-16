1) operációsrendszer mint program felhasználja a cpu lehetőségeit
	- minden procihoz más OP-rendszer

2) Az alkalmazások számára tárat cpu időt biztosít

3) Kezeli perifériákat input output

Megszakítások működtetik a programokat.
	rendzsrehívás (Megszakítás)
	végrehajtás
	visszatérés
		kivéve ha
			megtelt memória
			várás egy másik programra
			késleltetés
			hiba
			újraütemezés
			be-kimenet indítás

1) Újrapróbálás
2) Hibajelzés consolra és átlépés
3) Abortálás
4) Kivétel kezelés
5) Diagnisztizálás

--[[10.11
]]

memória
	nyomtatás
	lyukkártya
	mágneslemez
	cserélhető mágneslemez - flopy
	RAM - random acces memory
	hozzáférési idő csökken

	Adatai:
		hozzáférési idő
		méret
		élettartam

	merevlemez
		clinder 
			mágneskorong 
				kétoldalas
				nanométerekkel van az olvasófej felette
				fordulatszám
				szektor
				sáv
	optikai meghajtó
		cd 
		dvd
		blue-ray
	SSD
		solid state disk
		flash memória
		alacsony élettartam
			kopáskiegyenlítés
		gyorsabb hozzáférési idő
		kevesebb áram
		kevesebb hő

Paartíciók:
	Önnáló egység a merevlemezen
		külön kezelhetők
		külön fájlrendszer

fájlrendszer
	tárolja a fájlokat
	és a metaadatokat
		utolsó modosítás
		hozzáférési jog
		kiterjesztés
	fragmentáció
		külső: nem egymás melletti blokkokban van egy fálj
		defragmentáció: töredezetség mentesítés
		belső: blokkon belül van kihasználatlan hely
		blokkméret 1 / 4 / 64
FAT 
	Microfoft
	XP-ig
	Kalsserek 2 - 32 kb
	Bootsektor - fileok
EXT2
	blokk 1 - 8 kb
	superblokk: boot, filerendszer
	Blokkok csoportokban:
	FA rendezés
		Direct
		Indirect
		Double Indirect
	INODE: fizikai címzés
	max 16GB egy file
	linkek
		soft: file tartalmazza egy címét a másik filenak.
		hard: létező Indora mumtat
	swap
		jelnleg nem használt program adatai nem a memóriában, hanem itt tárolódnak.

Hálózat
	Adatok megosztása
	Cél 
		Erőforrás megosztás (nyomtató,fax)
		Nagyobb megbízhatóság (redundancia)
		gazdaságosan növelhető teljesítmény
		elérhetővé válnak a központi adatbázisok
		kommunikációs közeg
	ARPA projekt
	Rétegzett felépítés
		ISO OSI
			7 rétrg 
			alatta felette kummunikál
			alatta lévő szolgáltatásokat veszi igénybe
		Prtotokol
			egy másik hálózatba kötött eszköz azonos rétegével való kummunikáció
		Interfész
			Egymás alatti rétegek kommunikációja
	Fizikai réteg
		UTP kábel: árnyékolatlan csavart kábelek
			más mértékben vannak csavarva
	Adatkapcsolat réteg:
		HUB:
			tovább küldi mindenkinek a hálózaton
		Switch:
			csak annak küldi tovább akinek címezték
	Hálózati réteg:
		IP 32bit: 127.0.0.1

ZH számolás:
	Eltolásos ábrázolás
		3bit -4-es excass
			000 = -4
			111 = 3
	2-es komplemens
		4bit
		8 4 2 1
		0 1 1 0 = 6
		-4 -> -4+1 -> -3 -> 3
		0 0 1 1 = 3 -> invert
		1 1 0 0 = -4
	Lebegőpontos
		Előjel: 1bit
		Mantissza: 4bit: 0,1,1,0
		exponens: 2bit-2: 1,1
		2 1
		1 1 = 3-2 = 1
		1,0110*2^1
	Számrendszer:

	0010|1011 [2] = [16] 2B

	000|101|011 [2] = [8] 53