<?php
$raw_data=fgets(STDIN);
$raw_data=trim($raw_data,'[()]');
$raw_data=explode('),(',$raw_data);
$data=array();
$out=array();
foreach($raw_data as $row){
  $row=explode(',',$row);
  $data[]=$row[1];
}
// Function to calculate square of value - mean
function sd_square($x, $mean) { return pow($x - $mean,2); }

// Function to calculate standard deviation (uses sd_square)    
function sd($array,$mean) {
    // square root of sum of squares devided by N-1
    return sqrt(array_sum(array_map("sd_square", $array, array_fill(0,count($array), $mean ) ) ) / (count($array)-1) );
}
$mean=array_sum($data)/count($data);

$sigma=sd($data,$mean);
$started=0;
foreach($data as $x=>&$y){
  $y-=$mean;
  if($y>$sigma||$y<-$sigma){
    if(!$started)
      $out[]=$x+1;
    $started=1;
  }else if($started){
    $out[count($out)-1].=','.$x;
    $started=false;
  }
}
if($out){
  echo '[('.implode('),(',$out).')]';
}else echo '[]';