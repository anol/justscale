function main() {
    var emne = cube({size: [142, 72, 10]});
    var hull = cylinder({h: 10, r:4.5, center: true}).rotateZ(90);
    var hull1 = hull.translate([3,3,5]);
    var hull2 = hull1.translate([136.2,0,0]);
    var hull3 = hull1.translate([0,66.2,0]);
    var hull4 = hull1.translate([136.2,66.2,0]);
    var plate = difference(emne, hull1, hull2, hull3, hull4 );
    var display = union(cube({size: [61, 15, 8]}),
    cube({size: [95, 13, 4]}).translate([-10,1,6]),
    cube({size: [72, 24, 2]}).translate([-5.5,-4.5,8]));
    var knapp = union(cylinder({h: 10, r:12, center: true}).rotateZ(90),
                      cylinder({h: 14, r:8, center: true}).rotateZ(90),
		      cylinder({h: 20, r:1.5, center: true}).rotateZ(90));
    var kombo = union(display.translate([44,10,0]),knapp.translate([122, 17.5,8]));
// Placing the displays
    var display1 = kombo.translate([3,-4,0]);
    var display2 = kombo.translate([3,18.5,0]);
    var display3 = kombo.translate([3,41,0]);
// Add locators for the Launchpad
    var socket = cube({size: [27, 6, 10]});
    var locator = union(socket.translate([0,0,0]),socket.translate([0,43,0]))
	.translate([12,11.5,4]);
// And, the final result
    return difference(plate, display1, display2, display3, locator )
           .translate([-70,-36,0.1]);
}