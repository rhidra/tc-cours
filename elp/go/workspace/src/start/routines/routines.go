

package main

import "fmt"

func main() {

  c := make(chan int, 10)
  for i := 0; i < 8; i++ {
    fmt.Println("Lancement de la goroutine ", i)
    go func() {
      fmt.Println("i= ", i)
      c<- i
      c<- i * 10
    }()
  }

  for {
    fmt.Println(<-c)
  }
}


