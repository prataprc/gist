function fn() {
    var res = SELECT 
    xs: {
        for (var r of res) {
            xfn = function(r) {
               console.log(r) 
            }(r)
        }
    }
}
