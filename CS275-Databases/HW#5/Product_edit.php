<!doctype html>
<html lang="en">
<head>  
  <meta charset="utf-8" />
  <title>Edit</title>
</head>
<body>
<table border="1">
  <tr>
    <th>Product Name</th>
    <th>Brand</th>
	<th>Item ID</th>
    <th>Transaction#</th>
	<th>Price</th>
	<th>Rating</th>
	<th># Purchased</th>
  </tr>
  
 </table>

<table border="0" >
<tr>
<td>
<FORM ACTION="Product_edit.php" METHOD="get" >
<input type="hidden" name="Item_ID" value="">
	Name: <input type="text" name="_name">
	Brand: <input type="text" name="_brand">
	Transaction #: <input type="int" name="_trans">
	</td>
	</tr>
	<tr>
	<td>
	Price: <input type="double" name="_price">
		Rating: <input type="int" name="_rate">
		# Purchased: <input type="int" name="_num">
  <INPUT TYPE="SUBMIT" VALUE = "Edit">
	</FORM>
</td>
</tr>
<tr>
<td>
<a href="http://web.engr.oregonstate.edu/~quinnsa/Products.php">Go Back</a>
</td>
</tr>
</table>
</body>
</html>
