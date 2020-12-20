<?php

   	$jsonString = file_get_contents("test/tuan.json");
	$data = json_decode($jsonString, true);
 
	
if(isset($_POST["pwm"]))
{
	
	$data_post = $_POST["pwm"];

	$data['led1'] = $data_post;	
	   
	echo"";	
	
} 

// ################## Ghi gia trị vào file json ##################################		
	
	$newJsonString = json_encode($data);
	file_put_contents("test/tuan.json", $newJsonString);

?>

    

