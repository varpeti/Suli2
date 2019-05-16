function [c,d,e,f,g,h,k,l,m,n,o,p]=gyak1_BUGE0Q(a,b)
  c = b^(1/a);
  d = a^b;
  e = log(b)/log(a);
  f = 5.21^((log(pi^(1/3))/log(b))^a);
  g = atan(a/b);
  h = g*180/pi;
  k = pi/2-g;
  l = 90-h;
  m = primes(b^a);
  n = factorial(a*b);
  o = factor(10*(a*b));
  p = b^2*pi;
end