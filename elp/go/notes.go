// TD1
// Dans $GOPATH/src/, on définit des modules.
// Par exemple : start/
// Dans les modules, on définit des packages.
// Par exemple : hello/

// Réservé aux exécutables !
package main

// go build
// Compile l'exécutable dans le même dossier (src/)

// go install
// Crée l'exécutable dans le dossier bin/

// go clean
// Nettoie tout le dossier src/

// go run hello-world.go
// Compile, exécute et nettoie le programme

// Pour importer un package "start/mymod"
import (
    "fmt"
    "start/mymod"
)

// Dans mymod.go
package mymod

// Si le main est dans start/app-with-mymod
// go install start/mymod start/app-with-mymod

// Déclaration de fonction
func Sum(x int, y int) int {
    return x + y
}

// Déclaration de variable
var trois int = mymod.Sum(1, 2)
var trois = mymod.Sum(1, 2)
trois := mymod.Sum(1, 2) // Déduction auto du type

// Déclaration de tableau
var a []int = []int{0, 1, 2, 3, 4, 5}
a := []int{0, 1, 2, 3, 4, 5}

// Tableaux
b = append(a, 6)
c = make([]int, 5, 10) // Crée tableau vide len(c)=5, cap(c)=10
copy(c, b) // Copie b dans c, en gardant la capacité maximale
a[1:3] // Slice de 1 (inclu) à 3 (non-inclu)
a[:3]
a[5:]

// Maps
ints = make(map[string]int)
delete(ints, "4")
ints["1"] = 1
res, ok := ints["666"]
ints := map[string]int {
    "1":1,
    "2":2,
    "3":3
}

// Structs
type Person struct {
    name string
    email string
    age uint8
}
mrbean := Person{"Mr Bean", "bean@outlook.com", 59}

// Pointeur
var rowan *Person = new(Person)
//ou
rowan := &Person{"Mr Bean", "bean@outlook.com", 59}

// Flow control
if x < 100 {}
if err := file.Chmod(0777); err != nil {}
for i := 0; i < 100; i++ {}
for i := range a {}
for key, value := range ints {}
for c := range "Hello" {}
switch {
case i < 100 && i > 0:
    return i
}
switch b {
case '', ' ', '\n':
    return "White space"
default:
    return "Smth else"
}

// Goroutines
func main() {
    go func() {
        // Smth Smth
    }()
}

// Channels
stop := make(chan int, size) // Création du channel
stop <- 0 // Ds goroutine = Transmission d'une info
stopper := <- stop // Ds main = Consommation de la data

// Select
select {
case next := <- fibs:
    // ...
case <- time.Tick(1*time.Seconds):
    // ...
case <- exit:
    // ...
}
