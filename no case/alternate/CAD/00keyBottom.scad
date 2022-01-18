use <cubes.scad>
 
$fn = 100;

//Length is x-axis and width is y-axis prior to to any rotation
length = 304.8;
width = 170.69;
height = 5;

//My radius gauge put the radius of the PCB corners somwhere betwen 3 and 4, went with 3.5 
//and it seems to match up pretty good
cornerRadius = 3.5;

//The outside diamter of the heatset insert you are using. I find it easier to insert these if the hole
//is tapered. So this value will be the diameter of the bottom of the hole. The diameter of the 
//top of the hole will be (heatsertOutsideDiameter + topHoleDelta). If you just want a non-tapered hole
//of a certain size just set the diameter appropriately and set topHoleDelta to 0
heatsertOutsideDiameter = 3.4;
topHoleDelta = 0.4;

//The height of the rear of the case, percent slope is (rearHeight / width * 100). 6-8% slope is common for keyboards. 
//10.5 gives ~6%, 
//12 gives ~7% slope.
//13.7 gives ~8%
//The calculated slope is printed in the console for convenience
rearHeight = 12;

//If you want to include the slots for the RGB lights this should be true, false otherwise
includeRgbLightHoles = true;

//The length (x-axis) of the RGB slot, make it long enough so all the LEDs are visible. The default 
//value should be good for 30 LED/meter strips. 
lightHoleLength = 245;

//The width (y-axis) of the RGB slot. This value is probably good to leave alone but you can adjust if you want
lightHoleWidth = 8.5;

//The y-axis position of the 1st RGB slot
lightHoleY1 = 40;

//The y-axis position of the 2nd RGB slot. Its default value will keep it equidistant from the edge as the 
//position of the 1st RGB slot
lightHoleY2 = width - lightHoleY1;

//How wide to make the anti-flex support. 
antiFlexWidth = 10;

//The position of the anti-flex support. The default value covers the holes a bit but the heatset inserts 
//don't come out the bottom so it doesn't matter. Can subtract antiFlexWidth from this if that bothers you 
antiFlexPosition = width / 2;

//Measured the hole distances on the PCB in KiCad with the measure tool. 
holeEdgeDistance = 3.81;
y1 = width - holeEdgeDistance;
y2 = 118.2;
y3 = 95.25;
y4 = 9.53;
holePositions = [
    //Row 1 (from top)
    [holeEdgeDistance, y1],
    [154.94, y1],
    [length - holeEdgeDistance, y1],
    //Row 2 (from top)
    [holeEdgeDistance, y2],
    [154.94, y2],
    [length - holeEdgeDistance, y2],
    //Row 3 (from top)
    [19.05, y3],
    [152.4, y3],
    [length - 19.05, y3],
    //Row 4 (from top)
    [23.88, y4],
    [152.4, y4],
    //The one-off hole in bottom right
    [length - 19.05, 19.05]
];

heatsertHoleTopDiameter = heatsertOutsideDiameter + topHoleDelta;

echo("Percent Slope: ", rearHeight / width * 100);
echo("LightHoleY1: ", lightHoleY1);
echo("LightHoleY2: ", lightHoleY2);

//Translating and rotating to get it in print orientation at the origin
//If you make changes comment out the translate/rotate line until you are ready to render/export
//as it gets confusing if you don't
translate([0, width, 0])  rotate([180, 0, 0]) 
main();

module main() {
    difference() {
        roundedCube(length = length, width = width, height = height, radius = cornerRadius, center = false, roundingShape = "circle", topRoundingShape = undef);
        screwHoles();
        if (includeRgbLightHoles) {
            rgbLightHoles();
        }
    }

    slant();
    //This will give additional support in the middle of the case, especially if RGB holes are included. If no RGB holes are included
    //you might be able to get away with not having this if you want.
    antiFlex();
}

module screwHoles() {
    for (pos = holePositions) {
       translate(concat(pos, -0.01)) cylinder(d1 = heatsertOutsideDiameter, d2 = heatsertHoleTopDiameter, h = height + 0.02, center = false);
    }
}

module slant() {
    slantPoints = [
        [cornerRadius, cornerRadius], //bottom left
        [cornerRadius, width - cornerRadius], //top left
        [length - cornerRadius, width - cornerRadius], //top right
        [length - cornerRadius, cornerRadius] //bottom right
    ];

    //Basically drawing a polyline with the rear/front objects hulled together
    hull() {
        translate(slantPoints[0]) frontObject();
        translate(slantPoints[1]) rearObject();
    }

    hull() {
        translate(slantPoints[1]) rearObject();
        translate(slantPoints[2]) rearObject();
    }

    hull() {
        translate(slantPoints[2]) rearObject();
        translate(slantPoints[3]) frontObject();
    }

    module rearObject() {
        //The radius of the sphere is effectively added to the height of the cylinder so to make the rear be the height we 
        //actually want need to subtract the radius
        cylinderHeight = rearHeight - cornerRadius;

        translate([0, 0, -cylinderHeight]) {
            cylinder(r = cornerRadius, h = cylinderHeight);
            sphere(r = cornerRadius);
        }
    }

    module frontObject() {
        //Don't want to add any meaningful dimension to the front of the case so make this
        //super thin just so we have something to hull with
        bottomHeight = 0.01;
        translate([0, 0, -bottomHeight]) cylinder(r = cornerRadius, h = bottomHeight);
    }
}

module rgbLightHoles() {
    x = length / 2 - lightHoleLength / 2;
    translate([x, lightHoleY1, -0.5]) rgbLightHole();
    translate([x, lightHoleY2, -0.5]) rgbLightHole();

    module rgbLightHole() {
        adjustedLength = lightHoleLength - lightHoleWidth;
        
        //Translate the radius of the hole so it is at the origin
        translate([lightHoleWidth / 2, 0, 0]) hull() {
            cylinder(d = lightHoleWidth, h = height + 1);
            translate([adjustedLength, 0, 0]) cylinder(d = lightHoleWidth, h = height + 1);
        }
    }
}

module antiFlex() {
    //We want the antiflex support to be the same height as the slanted walls at its position. So 
    //we will draw the slant again and intersect a cube with it, then hull the result of the intersection.
    //I normally like drawing my objects at the origin in modules and them moving them into position where they 
    //are used; however, in this case the height of the antiFlex object depends on where it is positioned on the y-axis 
    //so have to move it into position here as well
    height = rearHeight + 10;
    hull() {
        intersection() {
            slant();
            translate([0, antiFlexPosition, -height]) cube([length, antiFlexWidth, height]);
        }
    }
}
