package main

import (
	"fmt"
	"math/rand"
	"time"
)

var fighters []int
var temp []int

func fightSimulation(i int) {
	if fighters[i] > fighters[len(fighters)-1-i] {
		fighters[len(fighters)-1-i] = -1
	} else {
		fighters[i] = -1
	}
	time.Sleep(100 * time.Millisecond)
}

func chooseWinners() {
	time.Sleep(100 * time.Millisecond)
	temp = temp[0:0]
	for i := 0; i < len(fighters); i++ {
		if fighters[i] != -1 {
			temp = append(temp, fighters[i])
		}
	}
	fighters = temp
}

func main() {
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < 8; i++ {
		fighters = append(fighters, rand.Intn(1000))
	}
	for len(fighters) != 1 {
		for i := 0; i < len(fighters)/2; i++ {
			go fightSimulation(i)
		}
		chooseWinners()
	}
	fmt.Println(fighters[0])
}
