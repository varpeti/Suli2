Teszt rendszer:
    Android 7.0, API 24
    Samsung SM-G920F (Galaxy S6)

LogMacska:
    regex:
        [\\][|][/]

    App indítása:
        I/TestActivity: \|/ onCreate
        I/TestActivity: \|/ onStart
        I/TestActivity: \|/ onResume

    Activity váltás gombal Testről Nextre:
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onStop

    Activity váltás gombal Nextről Testre:
        I/TestActivity: \|/ onCreate
        I/TestActivity: \|/ onStart
        I/TestActivity: \|/ onResume

    Activity váltás fizikai vissza gombal Testről Nextre:
        I/TestActivity: \|/ onStop
        I/TestActivity: \|/ onDestroy

    Activity váltás fizikai vissza gombal Nextről Testre:
        I/TestActivity: \|/ onStart
        I/TestActivity: \|/ onResume

    Kilépés a programbol fizikai vissza gombal:
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onStop
        I/TestActivity: \|/ onDestroy

    Visszalépés a programba a menü fizikai gomb menüből:
        I/TestActivity: \|/ onCreate
        I/TestActivity: \|/ onStart
        I/TestActivity: \|/ onResume

    Program futásának megszakítása a menü fizikai gomb megnyomásával:
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onStop

    Program futásának folytatása:
        I/TestActivity: \|/ onStart
        I/TestActivity: \|/ onResume

    Program futásának megszakítása a telefon zárolása fizikai gombal:
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onStop

    (Program futásának folytatása)
    Program futásának megszakítása a középső fizikai gombal:
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onStop

    (Program futásának folytatása)
    

    Program alvásba helyezése:
        -

    Program indítása a telepített alkalmazásokból:
        I/TestActivity: \|/ onStart
        I/TestActivity: \|/ onResume

    (Program futásának megszakítása a középső fizikai gombal)
    Majd kényszerleállítása:
        -

    (Futtatás)
    (Kilépés a programbol fizikai vissza gombal)
    Program osztott képernyős módba helyezése:
        I/TestActivity: \|/ onDestroy
        I/TestActivity: \|/ onCreate
        I/TestActivity: \|/ onStart
        I/TestActivity: \|/ onResume
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onResume
        I/TestActivity: \|/ onPause

    Visszalépés fizikai vissza gombal:
        I/TestActivity: \|/ onStop
        I/TestActivity: \|/ onDestroy
        I/TestActivity: \|/ onCreate
        I/TestActivity: \|/ onStart
        I/TestActivity: \|/ onResume
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onResume

    Telefon felhívása:
        -

    Telefon hívás fogadása:
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onStop

    Telefon hívás lerakása:
        I/TestActivity: \|/ onStart
        I/TestActivity: \|/ onResume

    Soft Exit ( Intent.ACTION_MAIN ):
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onStop

    Hard Exit ( System.exit(0); ):
        -

    Fin ( finish(); ):
        I/TestActivity: \|/ onPause
        I/TestActivity: \|/ onStop
        I/TestActivity: \|/ onDestroy

Megjegyzések:
    Ha intentel váltok activity-t akkor csak leállítja a futását, de nem destroy-olja, 
    illetve mindig újat hoz létre. 
    Így vissza lehet lépni az előző aktivity-kre a vissza gombal,
    ez már destroy-ol.

    Gombok:
        középső gomb nem destroy-ol
        telefon zárolása nem destroy-ol
        vissza gomb spamelése destoroy-ol
        menü gomb nem, de ha ott kihúzom/bezárom destroy-ol.

    Osztott képernyős mód nagyon idiótán működök.

    Telefon hívás nem hív meg semmit, míg nem foglalkozom vele. 
    Minden más esetben onPause() onStop() hívódik, onDestroy() nem.

    Bezárás alkalmazásból:
        https://stackoverflow.com/questions/3226495/how-to-exit-from-the-application-and-show-the-home-screen
        
        Intent.ACTION_MAIN:
            onPause() onStop() hívódik, onDestroy() nem

        System.exit(0):
            semmi sem hívódik

        finish();
            onPause() onStop() és onDestroy() is hívódik
