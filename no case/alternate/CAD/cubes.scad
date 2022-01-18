//dimensionType -- "inner" if the passed in dimensions are for the inside of the box i.e. the hollow parts (default), 
//  "outer" if the passed in dimensions are for the outside of the box. In this case the dimensions of the hollow part
//  will be calculated taking into account the passed in wallThickness
//hasFloor = true to make it a box with a floor, false to make the hole all the way through
module hollowCube(length = 10, width = 10, height = 10, wallThickness = 3, hasFloor = true, dimensionType = "inner", center = false, debug = false) {
    doubleWallThickness = wallThickness * 2;

    if (dimensionType == "inner") {
        echo("InnerDimensioned Hollow Cube");
        innerDimensioned();
    } else {
        echo("OuterDimensioned Hollow Cube");
        outerDimensioned();
    }

    module innerDimensioned() {
        difference() {
            //Exterior
            exteriorLength = length + doubleWallThickness;
            exteriorWidth = width + doubleWallThickness;
            if (debug) {
                echo("Wall Thickess: ", wallThickness);
                echo("Double Wall Thickess: ", doubleWallThickness);
                echo("Inner Length: ", length);
                echo("Inner Width: ", width);
                echo("Exterior Length: ", exteriorLength);
                echo("Exterior Width: ", exteriorWidth);
            }

            cube([exteriorLength, exteriorWidth, height], center = center);

            //Hollow interior
            x = center == true ? 0 : wallThickness;
            y = center == true ? 0 : wallThickness;
            if (hasFloor == true) {
                translate([x, y, wallThickness]) cube([length, width, height], center = center);
            } else {
                translate([x, y, -1]) cube([length, width, height + 10], center = center);
            }
        }
    }

    module outerDimensioned() {
        difference() {
            //Exterior
            innerLength = length - doubleWallThickness;
            innerWidth = width - doubleWallThickness;
            echo("Wall Thickess: ", wallThickness);
            echo("Double Wall Thickess: ", doubleWallThickness);
            echo("Exterior Length: ", length);
            echo("Exterior Width: ", width);
            echo("Inner Length: ", innerLength);
            echo("Inner Width: ", innerWidth);

            cube([length, width, height], center = center);

            //Hollow interior
            x = center ? 0 : wallThickness;
            y = center ? 0 : wallThickness;
            if (hasFloor) {
                translate([x, y, wallThickness]) cube([innerLength, innerWidth, height], center = center);
            } else {
                translate([x, y, -1]) cube([innerLength, innerWidth, height + 10], center = center);
            }
        }
    }
}

//dimensionType -- "inner" if the passed in dimensions are for the inside of the box i.e. the hollow parts (default), 
//  "outer" if the passed in dimensions are for the outside of the box. In this case the dimensions of the hollow part
//  will be calculated taking into account the passed in wallThickness
//hasFloor = true to make it a box with a floor, false to make the hole all the way through
//roundingShape = one of "sphere" or "circle", a sphere rounds the object along all edges, circle rounds just the corners
//  if topRoundingShape is undef this applies to all edges
//topRoundingShape = one of "sphere" or "circle", a sphere rounds the object along all edges, circle rounds just the corners
//  if defined is the rounding shape of the top edges in case you want top edges rounded differently (can be handy for lids)
module hollowRoundedCube(length = 10, width = 10, height = 10, radius = 1, wallThickness = 3, floorThickness = 3, hasFloor = true, 
    roundingShape = "sphere", topRoundingShape = undef, dimensionType = "inner", roundedInterior = false, center = false) {

    topRoundingShape = topRoundingShape == undef ? roundingShape : topRoundingShape;
    echo("TopRoundingShape: ", topRoundingShape);

    doubleWallThickness = wallThickness * 2;
    if (dimensionType == "inner") {
        innerDimensioned();
    } else {
        outerDimensioned();
    }

    module innerDimensioned() {
        difference() {
            //Exterior
            roundedCube(length + doubleWallThickness, width + doubleWallThickness, height, radius, roundingShape = roundingShape, 
                topRoundingShape = topRoundingShape, center = center);

            //Hollow interior
            x = center ? 0 : wallThickness;
            y = center ? 0 : wallThickness;
            if (hasFloor) {
                translate([x, y, floorThickness]) hollowInterior(length, width, height, center = center);
            } else {
                translate([x, y, -1]) hollowInterior(length, width, height + 10, center = center);
            }
        }
    }

    module outerDimensioned() {
        innerLength = length - doubleWallThickness;
        innerWidth = width - doubleWallThickness;
        difference() {
            //Exterior
            roundedCube(length, width, height, radius, roundingShape = roundingShape, topRoundingShape = topRoundingShape, center = center);

            //Hollow interior
            x = center ? 0 : wallThickness;
            y = center ? 0 : wallThickness;
            if (hasFloor) {
                translate([x, y, floorThickness]) hollowInterior(innerLength, innerWidth, height, center = center);
            } else {
                translate([x, y, -1]) hollowInterior(innerLength, innerWidth, height + 10, center = center);
            }
        }
    }

    module hollowInterior(length, width, height, center = center) {
        if (roundedInterior) {
            roundedCube(length, width, height, radius, roundingShape = roundingShape, topRoundingShape = topRoundingShape, center = center);
        } else {
            cube([length, width, height], center = center);
        }
    }
}

/*
    Creates rounded cube without minkowsi, this one performs a lot better than minowski cube which may be important 
    in larger designs

    roundingSphere = one of "sphere" or "circle", a sphere rounds the object along all edges, circle rounds just the corners
*/
module roundedCube(length = 10, width = 10, height = 10, radius = 1, center = false, roundingShape = "sphere", topRoundingShape = undef) {
    topRoundingShape = topRoundingShape == undef ? roundingShape : topRoundingShape;
    echo("roundedCube(), TopRoundingShape: ", topRoundingShape);
    if (center) {
        centeredRoundedCube();
    } else {
        nonCenteredRoundedCube();
    }

    module centeredRoundedCube() {
        bottomZ = roundingShape == "sphere" ? -(height - (radius * 2)) / 2 : -height / 2;
        topZ = topRoundingShape == "sphere" ? (height - (radius * 2)) / 2 : height / 2;

        echo("Centered Rounded Cube");
        echo("height: ", height);
        echo("BottomZ: ", bottomZ);
        echo("TopZ: ", topZ);

        hull() {
            translate([0, 0, bottomZ]) rectangle(length, width, radius, roundingShape);
            translate([0,0, topZ]) rectangle(length, width, radius, topRoundingShape);
        }
    }

    module nonCenteredRoundedCube() {
        z1 = topRoundingShape == "sphere" ? height - radius : height ;
        z2 = roundingShape == "sphere" ? radius : 0;
        x = length / 2;
        y = width / 2;
        echo("Non-Centered Rounded Cube");
        echo("length: ", length);
        echo("width: ", width);
        echo("height: ", height);
        echo("radius: ", radius);
        echo("x: ", x);
        echo("y: ", y);
        echo("Z1: ", z1);
        echo("Z2: ", z2);

        hull() {
            //Top
            translate([x, y, z1]) rectangle(length, width, radius, topRoundingShape);
            //Bottom
            translate([x, y, z2]) rectangle(length, width, radius, roundingShape);
        }
    }

    module rectangle(length, width, radius, roundingShape) {
        x = length - radius;
        y = width - radius;
        hull() {
            translate([(-x/2)+(radius/2), (-y/2)+(radius/2), 0]) roundingShape(radius, roundingShape);
            translate([(x/2)-(radius/2), (-y/2)+(radius/2), 0]) roundingShape(radius, roundingShape);
            translate([(-x/2)+(radius/2), (y/2)-(radius/2), 0]) roundingShape(radius, roundingShape);
            translate([(x/2)-(radius/2), (y/2)-(radius/2), 0]) roundingShape(radius, roundingShape);
        }

        module roundingShape(radius, roundingShape) {
            if (roundingShape == "sphere") {
                sphere(r = radius);
            } else {
                //make the extrusion small to make it a 3d object but don't add any size to the requested dimensions
                linear_extrude(0.000000000001) circle(r = radius);
            }
        }
    }
}

//Produces a 2D rounded square
module roundedSquare(length = 10, width = 10, radius = 1.0) {
    x = length - radius;
    y = width - radius;

    hull() {
        translate([(-x/2)+(radius/2), (-y/2)+(radius/2), 0])
        circle(r=radius);

        translate([(x/2)-(radius/2), (-y/2)+(radius/2), 0])
        circle(r=radius);

        translate([(-x/2)+(radius/2), (y/2)-(radius/2), 0])
        circle(r=radius);

        translate([(x/2)-(radius/2), (y/2)-(radius/2), 0])
        circle(r=radius);
    }
}

module taperedCube(bottomLength = 10, bottomWidth = 10, topLength = 20, topWidth = 20, height = 20, wallThickness = 3, rounded = false, roundingRadius = 1, 
    dimensionType = "inner", hollow = false, hasFloor = true, floorThickness = undef) {
    floorThickness = floorThickness == undef ? wallThickness : floorThickness;
    echo("DimensionType: ", dimensionType);
    echo("Hollow: ", hollow);
    echo("FloorThickness: ", floorThickness);
    
    doubleWallThickness = wallThickness * 2;

    if (dimensionType == "inner") {
        if (hollow) {
            echo("InnerDimensioned Hollow Tapered Cube");
            innerDimensioned();
        } else {
            assert(false, "A dimensionType of \"inner\", doesn't make sense when requesting a non-hollow tapered cube, aborting. Use dimensionType = \"outer\" instead");
        }
    } else {
        echo("OuterDimensioned Tapered Cube");
        outerDimensioned();
    }

    module innerDimensioned() {
        difference() {
            solidTaperedCube(bottomLength + doubleWallThickness, bottomWidth + doubleWallThickness, topLength + doubleWallThickness, topWidth + doubleWallThickness, height, rounded = rounded, roundingRadius = roundingRadius);

            //Can't get here if it wasn't hollow, so no need to check
            if (hasFloor) {
                echo("Hollow tapered cube has floor");
                translate([wallThickness, wallThickness, floorThickness]) solidTaperedCube(bottomLength, bottomWidth, topLength, topWidth, height, rounded = rounded, roundingRadius = roundingRadius);
            } else {
                echo("Hollow tapered cube no floor");
                translate([wallThickness, wallThickness, -0.01]) solidTaperedCube(bottomLength, bottomWidth, topLength, topWidth, height + 0.02, rounded = rounded, roundingRadius = roundingRadius);
            }
        }
    }

    module outerDimensioned() {
        halfWallThickness = wallThickness / 2;
        adjustedBottomLength = bottomLength - wallThickness;
        adjustedBottomWidth = bottomWidth - wallThickness;
        adjustedTopLength = topLength - wallThickness;
        adjustedTopWidth = topWidth - wallThickness;
        difference() {
            solidTaperedCube(bottomLength, bottomWidth, topLength, topWidth, height, rounded = rounded, roundingRadius = roundingRadius);

            if (hollow) {
                if (hasFloor) {
                    echo("Hollow tapered cube has floor");
                    translate([halfWallThickness, halfWallThickness, floorThickness]) solidTaperedCube(adjustedBottomLength, adjustedBottomWidth, adjustedTopLength, adjustedTopWidth, height, rounded = rounded, roundingRadius = roundingRadius);
                } else {
                    echo("Hollow tapered cube no floor");
                    translate([halfWallThickness, halfWallThickness, -0.01]) solidTaperedCube(adjustedBottomLength, adjustedBottomWidth, adjustedTopLength, adjustedTopWidth, height + 0.02, rounded = rounded, roundingRadius = roundingRadius);
                }
            }
        }
    }

    //A rounded taperedCube can only be rounded with circles, not spheres because sphere radius adds dimension making everything all wonky
    module solidTaperedCube(bottomLength = 10, bottomWidth = 10, topLength = 20, topWidth = 20, height = 20, rounded = false, roundingRadius = 1, center = false) {
        cubeHeight = 0.01;
        if (center) {
            z = height / 2;
            hull() {
                if (rounded) {
                    translate([0, 0, -z]) roundedCube(length = bottomLength, width = bottomWidth, height = cubeHeight, radius = roundingRadius, center = center, roundingShape = "circle");
                    translate([0, 0, z]) roundedCube(length = topLength, width = topWidth, height = cubeHeight, radius = roundingRadius, center = center, roundingShape = "circle");
                } else {
                    translate([0, 0, -z]) cube([bottomLength, bottomWidth, cubeHeight], center = center);
                    translate([0, 0, z]) cube([topLength, topWidth, cubeHeight], center = center);
                }
            }
        } else {
            hull() {
                topX = bottomLength / 2 - topLength / 2;
                topY = bottomWidth / 2 - topWidth / 2;
                topZ = height;
                if (rounded) {
                    roundedCube(length = bottomLength, width = bottomWidth, height = cubeHeight, radius = roundingRadius, center = false, roundingShape = "circle");
                    translate([topX, topY, topZ]) roundedCube(length = topLength, width = topWidth, height = cubeHeight, radius = roundingRadius, center = false, roundingShape = "circle");
                } else {
                    cube([bottomLength, bottomWidth, cubeHeight], center = center);
                    translate([topX, topY, topZ]) cube([topLength, topWidth, cubeHeight], center = center);
                }
            }
        }
    }
}

/**
    This module creates a cube with minkowski applied to it with a sphere resulting in a rounded cube. This
    module accepts desired measurments and makes adjustments based on the requested minkowski 
    radius to make sure the cube is that size  (minkowski results in sizes increasing)

    The quality of the sphere used for rounding will be controlled by the $fn variable which 
    should be set prior to calling this module.

    NOTE: Minkowski is a giant pain in the ass to deal with because it adds dimensions equal to
      2 * minkowskiRadius. Use one of the other rounded cubes instead

    * desiredLength -- length refers to X axis dimension, defaults to 10
    * desiredWidth -- width refers to Y axis dimension, defaults to 10
    * desiredHeight -- height refers to Z axis dimension, defaults to 10
    * minkowskiRadius -- how rounded the sides are, bigger radius is more rounded, defaults to 2
    * center -- same as center parameter on normal cube, defaults to true
*/
module minkowskiCube(desiredLength = 10, desiredWidth = 10, desiredHeight = 10, minkowskiRadius = 2, center = false) {
    adjustedLength = desiredLength - (minkowskiRadius * 2);
    adjustedWidth = desiredWidth - (minkowskiRadius * 2);
    adjustedHeight = desiredHeight - (minkowskiRadius * 2);
    echo("Mink Cube AdjustedLength: ", adjustedLength);
    echo("Mink Cube AdjustedWidth: ", adjustedWidth);
    echo("Mink Cube AdjustedHeight: ", adjustedHeight);
    echo("Mink Cube Center: ", center);

    minkowski() {
        translate([0, 0, minkowskiRadius]) cube([adjustedLength, adjustedWidth, adjustedHeight], center = center);
        sphere(minkowskiRadius);
    }
}

////////////////Test/////////////////
$fn = 60;
//roundedCube(length = 40, width = 30, height = 20, center = false, roundingShape = "sphere", radius = 2.5);
//hollowRoundedCube(length = 40, width = 30, height = 20, roundingShape = "sphere", topRoundingShape = "sphere", 
//    dimensionType = "inner", radius = 1.5, wallThickness = 3, floorThickness = 3, hasFloor = true, roundedInterior = true, center = false);
taperedCube(bottomLength = 40, bottomWidth = 40, topLength = 60, topWidth = 60, height = 20, wallThickness = 2, rounded = true, roundingRadius = 2, 
    dimensionType = "inner", hollow = true, hasFloor = true, floorThickness = 2);