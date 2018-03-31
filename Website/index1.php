<?php
$light = $_GET['light'];
if($light == "on") {
  $file = fopen("light.json", "w") or die("can't open file");
  fwrite($file, '{"light": "on"}');
  fclose($file);
}
else if ($light == "off") {
  $file = fopen("light.json", "w") or die("can't open file");
  fwrite($file, '{"light": "off"}');
  fclose($file);
}
?>

<!DOCTYPE html>
<html>

<head>
  <!-- using meta viewport for responsive website design -->
  <meta name="viewport" content="width = device-width, initial-scale = 1.0" />
  <title>Led Control</title>
  <!-- linking style.css file -->
  <link type="text/css" rel="stylesheet" href="style.css" />
</head>

<!-- setting background image -->

<body background="Images/back4.jpg" width=1024px>
  <!-- div block contains the header, underline block element and two buttons -->
  <div>
    <h1>Led Control</h1>
    <center><span class="line"></span></center>
    <!-- On and Off Button with styles-->
    <a href="?light=on"><button class="btn On" >On</button></a>
    <a href="?light=off"><button class="btn Off" >Off</button></a>
  </div>
  <!-- this div contains the message block which tell current led status -->
  <div>

    <?php
      if($light=='on'){
        echo "<p style='font-family:monospace;text-transform:uppercase' id='message'>Led On</p>";
      }else{
        echo "<p style='font-family:monospace;text-transform:uppercase' id='message'>Led Off</p>";
      }
    ?>

  </div>
  <!--  this div contains the image -->
  <div style="text-align:center">
    <!-- displaying both image of bulb -->
    <img id="light_img_off" src="Images/off1.png" title="LED" style="padding:1px" width="200" height=auto>
    <img id="light_img_on" src="Images/on1.png" title="LED" style="padding:1px" width="200" height=auto>
  </div>
  <!-- div contains copyright claim -->
  <div style="color:#fff;text-align:right;font-size=10px;padding-top:80px">
    <p color=#fff>Copyright @ Subham_Kumar</p>
  </div>
  <!-- javascript function myfunc() called whenever a button is pressed -->
    <script src="https://code.jquery.com/jquery-2.1.4.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js"></script>
  <script>
    jQuery(function($) {
      $.urlParam = function(name) {
        var results = new RegExp('[\?&]' + name + '=([^&#]*)').exec(window.location.href);
        if (results == null) {
          return null;
        } else {
          return results[1] || 0;
        }
      }
      if ($.urlParam('light') == 'on') {
        $('#light_img_on').show();
        $('#light_img_off').hide();
      } else {
        $('#light_img_off').show();
        $('#light_img_on').hide();
      }
    });
  </script>
  <!-- end -->
</body>

</html>
