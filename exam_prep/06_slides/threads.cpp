#include <iostream>
#include <thread>
#include <vector>
#include <mutex> // Hinweis: Wird für Teil b) benötigt

// Globale, geteilte Ressource
int g_counter = 0;

// TODO für Teil b): Globalen Mutex hier definieren
std::mutex global_mutex;

// Diese Funktion soll den globalen Zähler 100'000 mal erhöhen
void increment_counter() {
	std::lock_guard<std::mutex> guard(global_mutex);
    for (int i = 0; i < 100000; ++i) {
        // In Teil a) tritt hier das Problem auf.
        // In Teil b) muss dieser Bereich geschützt werden.
        g_counter++;
    }
}

int main() {
    // TODO Teil a) & b): Zwei Threads erstellen und starten,
    // die beide die Funktion increment_counter ausführen.
	std::thread t1(increment_counter);
	std::thread t2(increment_counter);

    // TODO Teil a) & b): Auf das Ende beider Threads warten (join).
	t1.join();
	t2.join();

    std::cout << "Finaler Wert des Zählers: " << g_counter << std::endl;
    std::cout << "Erwarteter Wert: 200000" << std::endl;

    return 0;
}

// a)
// für g_counter wird der wert 200.000 erwartet
// der wert ist deswegen nicht praxisrelevant, weil ich 2 threads habe, die versuchen die gleiche
// funktion auszuführen. in diesem fall ist es so, dass t1 und t2 die increment_counter funktion
// gleichzeitig ausführen. wie genau das ergebnis jedoch zustandekommt weiß ich nicht :(
// 
// b)
// der global mutex beschützt wie ein schlüssel die ressource. wenn ein thread ankommt und
// der schlüssel da ist, kann die rressource manipuliert werden. wenn keiner da ist bedeutet
// das, es ist bereits ein anderer thread am manipulieren, der jetzige thread soll warten, bis
// die ressource freigegeben ist.
// 
// durch den global mutex wird die ressourcenlebenszeit des threads an den mutex und den
// lock_guard gebunden. somit greift das RAII prinzip und die threads werden nach dem scope
// zerstört. dies bringt den vorteil mit sich, dass kein deadlock entsteht, da die ressourcen
// bei z.b. einer exception ordnungsgemäß zerstört werden, oder kein ungültiger pointeraufruf 
// oderso stattfinden kann
