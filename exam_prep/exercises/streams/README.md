# Kompilierung und Ausführung

```bash
# Kompilieren
g++ -std=c++17 -Wall -Wextra -o klausur_aufgabe klausur_aufgabe.cpp

# Ausführen
./klausur_aufgabe
```

# Tipps zur Lösung

## A) Student-Klasse
- Verwenden Sie `int matrikelnummer`, `string name`, `string studiengang`, `int semester`, `vector<double> noten`
- Für Stream-Operatoren: `>>` soll CSV-Format einlesen, `<<` soll formatiert ausgeben
- Für Sortierung: Sortieren Sie nach Durchschnittsnote (beste zuerst)

## B) StudentManager-Klasse
- `vector<Student>` für die Hauptdaten
- `map<string, vector<Student*>>` für schnelle Suche nach Studiengang
- Bei `loadFromFile()`: Zeile für Zeile einlesen, CSV parsen, Fehler abfangen
- Bei `saveToFile()`: Formatierte Ausgabe mit `setprecision()` für Noten

## C) Häufige Fehlerquellen
- Vergessen Sie nicht, Streams nach Fehlern zu prüfen (`stream.fail()`)
- CSV-Parsing: Achten Sie auf Kommas in den Daten
- Exception-Behandlung: Spezifische Exceptions vor allgemeinen fangen
- Memory-Management: Bei Pointern auf Lebensdauer achten

## Beispiel-Ausgabe
```
=== Studentenverwaltung Test ===
Daten geladen: 10 Studenten
Durchschnittsnote aller Studenten: 2.13

Top 3 Studenten:
1. Hoffmann Sarah (Mathematik): 1.33
2. Weber Tom (Informatik): 1.33  
3. Klein Emma (Informatik): 1.67

Informatik-Studenten:
- Mueller Max (Semester 3): 1.67
- Weber Tom (Semester 2): 1.33
- Becker Jan (Semester 6): 3.00
- Klein Emma (Semester 2): 1.67
```

## Bewertungsschema
- **Sehr gut (1.0-1.3)**: Alle Anforderungen erfüllt, elegant implementiert, Bonus-Features
- **Gut (1.7-2.3)**: Alle Hauptanforderungen erfüllt, kleiner Implementierungsfehler
- **Befriedigend (2.7-3.3)**: Grundfunktionalität vorhanden, aber einige Fehler
- **Ausreichend (3.7-4.0)**: Minimale Anforderungen erfüllt, viele Fehler
- **Nicht bestanden (>4.0)**: Wesentliche Teile fehlen oder funktionieren nicht
