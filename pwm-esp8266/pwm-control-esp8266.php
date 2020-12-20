<!DOCTYPE html>
<html lang="en">
<head>
 <?php require "layout/header.php"  ?>

    <style>
  /* Note: Try to remove the following lines to see the effect of CSS positioning */
  .affix {
    bottom:1px;
	position:fixed;
	right:2px;
    z-index: 9999 !important;
  }
  
  .center {
  margin: auto;
  width: 60%;
  border: 3px solid #73AD21;
  padding: 10px;
  text-align: center;
  border: 3px solid green;
}
  
  /* style for slider */
  
  .slidecontainer {
  width: 50%;
  margin: auto;
}

.slider {
  -webkit-appearance: none;
  width: 100%;
  height: 25px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
}

.slider:hover {
  opacity: 1;
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  background: #4CAF50;
  cursor: pointer;
}

.slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  background: #4CAF50;
  cursor: pointer;
}

  </style>
  
  </head>
<body>	

  <h2 class="center" > COTROL PWM ESP8266 OVER INTERNET </h2>
</div>
<br>


<div class="slidecontainer">
  <input type="range" min="1" max="1023" value="0" class="slider" id="myRange">
  <p>PWM ESP8266 Value: <span id="demo"></span></p>
</div>

<script>
var slider = document.getElementById("myRange");
var output = document.getElementById("demo");
output.innerHTML = slider.value;

slider.oninput = function() {
  output.innerHTML = this.value;
  
  id = $(this).val();
  //alert (id);
  $.ajax({
				url:"process.php",
				type:"post",
				data:"pwm="+id,
				async:true,
				success:function(kq){
			//	alert ("Sending PWM Value:"+id);
				}
				
			});	
}
</script>

</body>
</html>

