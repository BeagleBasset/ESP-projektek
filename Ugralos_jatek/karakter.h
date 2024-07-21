///////////////////////////////////////////////////
// A JÁTÉKOS KARAKTEREK
///////////////////////////////////////////////////

/*

A játékos az alábbi bitmap alapján lesz ábrázolva.
Két féle stádiumban történt az ábrázolása, ezáltal elérhető egy kvázi futás animáció,
illetve felhasználható az ugráshoz is.

*/

byte Player[8] = {
	0b00100,
	0b01010,
	0b01010,
	0b00100,
	0b01110,
	0b00100,
	0b01010,
	0b10001
};

byte Player2[8]
{
	0b00100,
	0b01010,
	0b01010,
	0b00100,
	0b01110,
	0b00100,
	0b00100,
	0b00100
};