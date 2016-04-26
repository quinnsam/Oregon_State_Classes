<!doctype html>
<html lang="en">
<head>  
  <meta charset="utf-8" />
  <title>Form Submission</title>
</head>
<body>
<h1> Result of Form Submission </h1>
<hr />
<?php
// submit_form.php
$first_name = $_GET['first_name'];
$last_name = $_GET['last_name'];
$remote_addr = $_SERVER['REMOTE_ADDR'];
echo "First Name = $first_name <br />";
echo "Last Name = $last_name <br />";
echo "Client IP Address = $remote_addr <br />";
echo "BYE <br />";
?>
<hr />
</body>
</HTML>

