use <../bosl/constants.scad>
include <../bosl/threading.scad>
use <shapes.scad>

//Creates a rod with threads on one or both ends. These rods can be threaded into each other
//
// endType -- one of "both", "male", or "female". If "both" the rod with have a female thread on one end and a male thread
//  on the other. If "male" one end with have a male thread and the other end will be flat. If "female" one end will have a 
//  female thread and the other end will be flat.
module rodWithThreads(diameter = 10, height = 100, endType = "both", threadDiameter = undef, threadLength = 5, threadPitch = 1, threadHoleAdjustment = 0.5, $fn = undef) {
    //For female threads difference this out of an object, send in a positive threadHoleAdjustment to make
    //the female hole bigger than the male threads
    threadDiameter = threadDiameter == undef ? diameter / 2 : threadDiameter;
    echo("Thread Diameter: ", threadDiameter);
    $fn = $fn == undef ? diameter * 2 : $fn;
    echo("$fn: ", $fn);
    difference() {

        union() {
            cylinder(d = diameter, h = height, center = false);

            //Create male thread if requested
            if (endType == "both" || endType == "male") {
                echo("****male****");
                translate([0, 0, height - 0.01]) thread(threadDiameter, threadLength, threadPitch);
            } 
        }

        //Create female thread if requested
        if (endType == "both" || endType == "female") {
            echo("****female****");
            translate([0, 0, -1]) thread(threadDiameter, threadLength + 2, threadPitch, threadHoleAdjustment, internal = true);
        }
    }

    module thread(threadDiameter, threadLength, threadPitch,  threadHoleAdjustment = 0, internal = false) {
        echo("ThreadHoleAdjustement: ", threadHoleAdjustment);
        threaded_rod(d = threadDiameter, l = threadLength, pitch = threadPitch, internal = internal, slop = threadHoleAdjustment, orient=ORIENT_Z, align=V_UP);
    }
}

// floorThickness - how thick the floor is if hasFloor is true, if left undefined then floor thickness is (outerDiameter - innerDiamter) / 2
module hollowCylinder(outerDiameter = 5, innerDiameter = 4, topOuterDiameter = undef, topInnerDiameter = undef, height = 10, center = false, hasFloor = false, 
    rounded = undef, floorThickness = undef) {
    topOuterDiameter = topOuterDiameter == undef ? outerDiameter : topOuterDiameter;
    topInnerDiameter = topInnerDiameter == undef ? innerDiameter : topInnerDiameter;
    echo("OuterDiameter: ", outerDiameter);
    echo("TopOuterDiameter: ", topOuterDiameter);
    echo("InnerDiameter: ", innerDiameter);
    echo("TopInnerDiameter: ", topInnerDiameter);
    echo("Rounded: ", rounded);
    echo("HasFloor: ", hasFloor);

    floorThickness = floorThickness == undef ? (outerDiameter - innerDiameter) / 2 : floorThickness;
    echo("FloorThickness (if hasFloor = true): ", floorThickness);


    if (rounded == undef) {
        nonRoundedTop();
    } else if (rounded == "top") {
        roundedTop();
    } else {
        roundedBottom();
    }

    z = hasFloor ? floorThickness : -0.01; 
    echo("Z: ", z);

    module nonRoundedTop() {
        difference() {
            cylinder(d1 = outerDiameter, d2 = topOuterDiameter, height, center = center);
            translate([0, 0, z]) cylinder(d1 = innerDiameter, d2 = topInnerDiameter, height + 1, center = center);
        }
    }

    //Center = true doesn't yet work with rounded cylinders
    module roundedTop() {
        //Wall thickness is the diameter of the circle that makes up the torus, so substract that from the height so we get the right height
        difference() {
            hull() {
                translate([0, 0, height - floorThickness]) torus(radiusOfTorus = topOuterDiameter / 2, diameterOfCircle = floorThickness, dimensionType = "outer", center = center);
                cylinder(d = outerDiameter, h = 1, center = center);
            }

            translate([0, 0, z]) cylinder(d1 = innerDiameter, d2 = topInnerDiameter, h = height + 1, center = center);
        }
    }

    //Center = true doesn't yet work with rounded cylinders
    module roundedBottom() {
        //Wall thickness is the diameter of the circle that makes up the torus, so substract that from the height so we get the right height
        difference() {
            hull() {
                translate([0, 0, height - 1]) cylinder(d1 = outerDiameter, d2 = topOuterDiameter, h = 1, center = center);
                torus(radiusOfTorus = outerDiameter / 2, diameterOfCircle = floorThickness, dimensionType = "outer", center = center);
            }

            translate([0, 0, z]) cylinder(d1 = innerDiameter, d2 = topInnerDiameter, h = height + 1, center = center);
        }
    }
}

//A cylinder with rouned edges on top and bottom
module roundedCylinder(diameter = 10, roundedRadius = 2, height = 20, center = false) {
    radius = diameter / 2;
    hull() {
        torus(radiusOfTorus = radius, diameterOfCircle = roundedRadius, dimensionType = "outer", center = center);
        translate([0, 0, height - roundedRadius]) torus(radiusOfTorus = diameter / 2, diameterOfCircle = roundedRadius, dimensionType = "outer", center = center);
    }
}

//Test
//rodWithThreads(diameter = 23, height = 100, endType = "both", threadLength = 20, threadPitch = 2, threadHoleAdjustment = 0.8);
//roundedCylinder(diameter = 20, roundedRadius = 4, center = false);
$fn = 100;
hollowCylinder(outerDiameter = 84, innerDiameter = 81, topOuterDiameter = 125, topInnerDiameter = 122, height = 113, center = false, hasFloor = true, rounded = "top", floorThickness = 3);