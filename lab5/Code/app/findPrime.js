function isPrime (v) {
    let i = 2, len = Math.sqrt(v)
    for (; i <= len; i++) {
      if (v % i === 0) return false
    }
    return true
  }
  
function getPrime (limit = 1e2) {
    let n = 1, numArr = []
    while(n++ < limit) numArr.push(n)
    document.getElementById("result").innerHTML = String(numArr.filter(isPrime))
}