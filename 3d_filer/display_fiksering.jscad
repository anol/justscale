function main() {
    var emne = cube({size: [112, 57, 10]});
    var hull = cylinder({h: 10, r:4.5, center: true}).rotateZ(90);
    var hull1 = hull.translate([3,3,5]);
    var hull2 = hull1.translate([106,0,0]);
    var hull3 = hull1.translate([0,51,0]);
    var hull4 = hull1.translate([106,51,0]);
    var plate = difference(emne, hull1, hull2, hull3, hull4 );
    var display = union(cube({size: [61, 15, 8]}),
    cube({size: [100, 13, 4]}).translate([-10,1,6]),
    cube({size: [72, 24, 2]}).translate([-5.5,-4.5,8]));
    var display1 = display.translate([16,8,0]);
    var display2 = display.translate([16,34,0]);
    var knapp = union(cylinder({h: 8, r:8, center: true}).rotateZ(90),
                      cylinder({h: 12, r:1, center: true}).rotateZ(90));
    var knapp1 = knapp.translate([93, 15.5,6]);
    var knapp2 = knapp.translate([93, 41.5,6]);
   return difference(plate, display1, display2, knapp1, knapp2 )
           .translate([0, 0,0.1]);;
}
