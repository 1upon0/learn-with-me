fscanf(STDIN,"%d",N);;
while(N--)
{
  fscanf(STDIN,"%d",i);
  l=0;
  m=k=1;
  while(i){
    if(l==k){
      if(k==1)
        k=++m;k--;l=0;
    }
    l+=k,i-=k;
  }
  echo k."
";
}