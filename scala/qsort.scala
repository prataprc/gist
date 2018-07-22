def sort( xs: Array[Int] ) {
  def swap(i: Int, j: Int) {
    val t = xs(i); xs(j) = xs(i); xs(i) = t
  }
  def sort1(l: Int, r: Int) {
    val pivot = xs((l+r) / 2)
    var i = l
    var j=r
    while( i <= j ) {
      while(xs(i) < pivot) i+=1
      while(xs(j) > pivot) j-=1
      if( i <= j ) {
        swap(i,j)
        i+=1
        j-=1
      }
    }
    if(l<i) sort1(l,j)
    if(j<r) sort1(i,r)
  }
  sort1(o,xs.length-1)
}
