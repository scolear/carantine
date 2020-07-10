let app = angular.module('CarantineApp', []);

app.controller('CarantineController', function() {

    this.state = "STOPPED";

    // TODO: values to be updated from actual readings.
    this.sensors = [
        {
            pos: "left",
            value: 12.34
        }, 
        {
            pos: "center",
            value: 56.78
        }, 
        {
            pos: "right",
            value: 90.12
        }
    ];


});