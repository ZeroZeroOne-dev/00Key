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

	setupComponents(cad)
	setupBase(cad)
	setupHoles(cad)
	setupUsb(cad)

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

func setupComponents(cad *kad.KAD) {
	cad.SwitchType = 3
	cad.StabType = 1
}

func setupBase(cad *kad.KAD) {
	cad.Case.EdgeWidth = 7
	cad.TopPad = 63.51
	cad.RightPad = 7
	cad.BottomPad = 7
	cad.LeftPad = 7
	cad.Fillet = 3.81
}

func setupHoles(cad *kad.KAD) {
	cad.Case.Holes = 10
	cad.Case.HoleDiameter = 3.4
}

func setupUsb(cad *kad.KAD) {
	cad.Case.UsbWidth = 0
	cad.CustomPolygons = []kad.CustomPolygon{{
		Layers: []string{""},
	}}
}
