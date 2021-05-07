

# Komunikacja międzyprocesowa
Aplikacja wykorzystująca pamięć współdzieloną do komunikacji między procesami aktorów w procesie przemysłowym.

## Spis treści
- [Informacje ogólne](#informacje-ogólne)
- [Technologie](#technologie)
- [Uruchamianie programu](#uruchamianie-programu)
- [Dodatkowe informacje](#dodatkowe-informacje)
- [Status projektu](#status-projektu)

## Informacje ogólne 
Program pokazuje komunikację międzyprocesową za pomocą shared memory wykorzystując do tego uproszczoną symulację huty szkła. Komunikacja przebiega pomiędzy procesami czujników a procesem systemu sterowania.

## Technologie
Projekt został napisany przy użyciu
- C

## Uruchamianie programu
Program został napisany i można go skompilować i uruchomić na Linux Ubuntu.

## Korzystanie z aplikacji
Program otwiera pulpit operatora pozwalający zalogować się jako użytkownik i rozpocząć pracę lub zalogować się jako admin i zarządzać użytkownikami. Po zalogowaniu jako operator otwiera się dziewięć kolejnych niezależnych procesów którymi można sterować. System sterowania automatycznie reaguje w zależności od tego co użytkownik wprowadził na czujnikach.

## Dodatkowe informacje
W pliku doc.docx znajduje się dokumentacja dotycząca procesu.

## Status projektu
Zakończony.





