# ams_function_generator
Repo til Funktions Generator projektet

##Guide:

###Installation:
- Pull repo
- Åben ams_function_generator mappen i VScode
- Den spørger om følgende:
 - Skal den installere Docker: Ja tak
 - Skal den builde/åbne ind i containeren: ja tak
- Når den er færdig med at bygge containeren, så åbner den VScode i kodemiljøet

###Kode:
Du skal ind i mappen source/ for at finde koden.

###Build:
For at build så skal du 2 ting!
1. Åbne en terminal, forbliv i roden (ams_function_generator)
2. Kør kommandoen: cmake .
Dette vil gennemgå evt nye filer som er blevet tilføjet, og skabe makefiles til alt kildekode
3. Kør kommandoen: make
Dette vil compile koden. Den laver så en ams-function-generator.hex fil, dette er vores kode forberedt til Atmega2560.

###Flash Atmega2560:
- Tryk på F1, så skriv og kør følgende: Create New Integrated Terminal
- Dette laver en ny terminal til dig, som er UDENFOR containeren!
- I roden af mappen, kør følgende kommando: ./upload.sh
- Den tager nu den seneste *.hex fil som blev lavet, og uploader den til din atmega2560.
Du burde kunne se enten i terminal, el i et nye powershell terminal vindue, som AvrDude uploader koden til din Atmega2560.
Denne uploader virker KUN med Atmega2560!

###OBS:
Hvis du vil lukke containeren, og arbejde udenfor containeren, så tryk F1, og skriv og kør følgende: Remote: Close Remote Connection
Hvis du er udenfor containeren, og vil genåbne den, så tryk F1, og skriv og kør følgende: Dev Containers: Reopen in Container

###OBS OBS:
Vi bruger desværre ikke WSL, så når du er inde i containeren, og vil slette, skabe, el. flytte filer, så er det pokkers langsomt!
Skal du copy + paste en masse filer ind, så er det nemmere at gå ud af containeren, og gøre det der. Ellers bare vis tålmodighed ;-)

