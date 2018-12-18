package main

import (
	"fmt"
	"time"
)

func nombresImpairs(c chan int) {
	// fonction à completer
	// cette fonction doit renvoyer sur le canal c
	// le numero suivant de la suite
	// chaque 300 milliseconds
	tick := time.Tick(300 * time.Millisecond)
	var i int = 1
	for {
		c <- i
		i += 2
		<- tick
	}
}
func main() {
	endSignal := time.After(10000 * time.Millisecond)
	n := make(chan int)
	go nombresImpairs(n)
	for {
		select {
		case numero := <-n:
			fmt.Print(numero)
		case <-endSignal:
			fmt.Println("BINGO!")
			return
		default:
			fmt.Print(".")
			time.Sleep(50 * time.Millisecond)
		}
	}
}
