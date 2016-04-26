<?php 
  define("DB_SERVER", "mysql.cs.orst.edu");
  define("DB_USER", "cs275_quinnsa");  
  define("DB_PASSWORD", "7154");
  define("DB_NAME", "cs275_quinnsa"); 
  
  $link = mysqli_connect(DB_SERVER, DB_USER, DB_PASSWORD) 
    or die ("Unable to connect to server<br>");
	
  mysqli_select_db($link, DB_NAME) 
   or die ("Unable to select database " . DB_NAME . "<br>");   
?>