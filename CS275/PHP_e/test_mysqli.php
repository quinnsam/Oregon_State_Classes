<?php 
  define("DB_SERVER", "mysql.cs.orst.edu");
  define("DB_USER", "cs275_quinnsa");  
  define("DB_PASSWORD", "7154")
  define("DB_NAME", "cs275_quinnsa");  
  
  $link = mysqli_connect(DB_SERVER, DB_USER, DB_PASSWORD) 
    or die ("Unable to connect to server<br>\n");
	
  mysqli_select_db($link, DB_NAME) 
   or die ("Unable to select database " . DB_NAME . "<br>\n"); 
  echo "Connected to database! <br>\n <br>\n";
  
  $query = "select * from Product";
  $result = mysqli_query($link, $query);
  
  while ($record = mysqli_fetch_array($result)) {
     print_r($record);
    echo "Product Number: " . $record['Item_ID'] . "<br>\n";
   echo "Product Name: " . $record['Name'] . "<br>\n";
    echo "Product Price: " . $record['Price'] . "<br>\n<br>\n";
 }
  
  mysqli_free_result($result);
  
?>
