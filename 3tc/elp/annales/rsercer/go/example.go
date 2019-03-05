package main

import (
	"fmt"
	"time"
)

// fonction qui affiche la séquence de nombres naturels
// à un interval de 1000 milliseconds chaque nombre.

func main() {
	numberTick := time.Tick(1000 * time.Millisecond)
	for i := 0; i < 20; i++ {
		<-numberTick
		fmt.Println(i)
	}
}
