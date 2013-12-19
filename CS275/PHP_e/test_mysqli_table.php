<?php require_once("common_db.inc.php") ?>
<?php   
  $query = "select * from s";
  $result = mysqli_query($link, $query);  
?>

<!doctype html>
<html lang="en">
<head>  
  <meta charset="utf-8" />
  <title>Suppliers</title>
</head>
<body>
<h1>Suppliers</h1>
<table border="1">
  <tr>
    <th>Select</th>
	<th>Supplier#</th>
    <th>Name</th>
	<th>Status</th>
	<th>Action</th>
  </tr>
  <?php while ($record = mysqli_fetch_array($result)): ?>  
  <tr>
	<td></td>
    <td><?php print $record['sno'];?></td>
    <td><?php print $record['sname'];?></td>
	<td><?php print $record['status'];?></td>
	<td><a href="supplier_edit.php?sno=<?php print $record['sno'];?>">Edit</a></td>
  </tr>
  <?php endwhile; mysqli_free_result($result);?>
</table>
</body>
</html>
