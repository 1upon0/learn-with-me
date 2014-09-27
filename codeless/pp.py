for x in range(input()):
  n=int(input())-1
  while 1:
    n+=1;
    if str(n)==str(n)[::-1] and all(n%i for i in range(2,n**0.5+1,1)):print n;break

127
24.4