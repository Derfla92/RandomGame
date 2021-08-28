# RandomGame

### Description

This is a random game which is heavily inspired from Rimworld. 



<br>

>### TODO:
>
>- add Multiple player units to control
>- add Attack
>- add Healthsystem
>- add Resources Gathering
>- add Multiplayer(?)

### Installing Msys with SFML and Yaml
1. Följ detta https://www.msys2.org/
    När du kommer till steg 6 så visade den massa "packages" typ. Klicka bara på enter tills du kommer till ":: Proceed with 
   installation"
2. I programmet skriv "pacman -S mingw-w64-x86_64-yaml-cpp"  för att installera yaml.       https://packages.msys2.org/package/mingw-w64-x86_64-yaml-cpp
3. I programmet skriv "pacman -S mingw-w64-x86_64-sfml" för att installera sfml.
https://packages.msys2.org/package/mingw-w64-x86_64-sfml

Den kommer typ installera en ny MinGW. Så när du är klar, så går du in i "miljövariablerna" och byter mingw pathen till den nya. 
Min va "C:\msys64\mingw32\bin".
Starta sedan om VS Code när du bytt path, om du hade den öppen medans du installerade för att de nya "pathsen" ska användas. Sen så borde det funka som vanligt.
