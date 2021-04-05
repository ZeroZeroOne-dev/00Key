package main

import (
	"bytes"
	"encoding/json"
	"io/ioutil"
	"log"

	"github.com/swill/kad"
)

func main() {
	cad := kad.New()

	cad.Hash = "00Key"
	cad.Case.Type = "sandwich"

	cad.SwitchType = 3
	cad.StabType = 1

	cad.Case.Holes = 10
	cad.Case.HoleDiameter = 3

	cad.Case.EdgeWidth = 6
	cad.TopPad = 64
	cad.RightPad = 6
	cad.BottomPad = 6
	cad.LeftPad = 6

	cad.Fillet = 2
	cad.Case.UsbWidth = 0

	//layout stuff
	jsonLayout, err := ioutil.ReadFile("layout.json")
	if err != nil {
		log.Fatal(err)
	}

	decoder := json.NewDecoder(bytes.NewReader(jsonLayout))
	err = decoder.Decode(cad)

	cad.FileDirectory = "./output/"

	err = cad.Draw()
	if err != nil {
		log.Fatalf("Failed to Draw the KAD file\nError: %s", err.Error())
	}
}
