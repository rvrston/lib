inline int64_t ceiling_div(int64_t a, int64_t b){ // ceiling(a/b)= floor((a+b-1)/b)
  return (a+b-1)/b;
}

int64_t gcd(int64_t a, int64_t b){
  int64_t buf;
  while(b > 0){
    buf= a;
    a= b;
    b= buf%b;
  }
  return a;
}
 
int64_t lcm(int64_t a, int64_t b){
  return a/gcd(a,b)* b;
}

void SieveOfEratosthenes(){
  const int Nmax= 100000;
  const int Nbit= Nmax+ 1;
  //// -素数判定
  bitset<Nbit> bits;
  bits.set(); bits.reset(0); bits.reset(1);
 
  int div= 2;
  while( div*div <= Nmax ){
    if( bits.test(div) ){
      for(int i=2*div; i<=Nmax; i+=div){
        bits.reset(i);
      }
    }
    div++;
  }
}

auto comp_frac = [](int numer1, int denom1, int numer2, int denom2) { return numer1* denom2 < numer2* denom1; };