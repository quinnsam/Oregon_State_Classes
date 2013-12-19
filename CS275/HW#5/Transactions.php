
<!doctype html>
<html lang="en">
<head>  
  <meta charset="utf-8" />
  <title>Spending Analysis</title>
</head>
<body>
<h1>Products</h1>

<FORM ACTION="Transactions.php" METHOD="GET" NAME = "TestForm">
  Select Store:
  <select NAME ='Store' >
  <option value="Jimmy Johns">Jimmy Johns</option>  
  <option value="Fred Myers">Fred Myers</option>  
  <option value="Sweets.com">Sweets.com</option>  
  <option value="Carmike Twelve Movie Theater">Carmike Twelve Movie Theater</option>  
  <option value="OSU">OSU</option>  
  <option value="Ross">Ross</option>  
</select>
  <INPUT TYPE="SUBMIT" VALUE = "Search">
</FORM>
<a href="http://web.engr.oregonstate.edu/~quinnsa/Transactions.php">Go Back</a>

<table border="1">
  <tr>
    <th>Select</th>
    <th>Transaction#</th>
	<th>Store</th>
	<th>Type</th>
	<th>Date</th>
	<th>Total</th>
	<th>Action</th>
  </tr>
  
   
  <tr>
	<td>[checkbox]</td>
    
    <td>1</td>
	<td>Jimmy Johns</td>
	<td>W</td>
	<td>2013-05-25 22:09:00</td>
		<td>$13.1</td>
	
    
	<td><a href="supplier_edit.php?sno=">Edit</a></td>
  </tr>
    
  <tr>
	<td>[checkbox]</td>
    
    <td>2</td>
	<td>Fred Myers</td>
	<td>W</td>
	<td>2013-05-20 16:54:00</td>
		<td>$54.49</td>
	
    
	<td><a href="supplier_edit.php?sno=">Edit</a></td>
  </tr>
    
  <tr>
	<td>[checkbox]</td>
    
    <td>3</td>
	<td>Fred Myers</td>
	<td>W</td>
	<td>2013-05-08 07:07:00</td>
		<td>$44.3</td>
	
    
	<td><a href="supplier_edit.php?sno=">Edit</a></td>
  </tr>
    
  <tr>
	<td>[checkbox]</td>
    
    <td>4</td>
	<td>Sweets.com</td>
	<td>W</td>
	<td>2013-05-08 09:14:00</td>
		<td>$27.94</td>
	
    
	<td><a href="supplier_edit.php?sno=">Edit</a></td>
  </tr>
    
  <tr>
	<td>[checkbox]</td>
    
    <td>5</td>
	<td>Carmike Twelve Movie Theater</td>
	<td>W</td>
	<td>2013-05-31 22:00:00</td>
		<td>$10</td>
	
    
	<td><a href="supplier_edit.php?sno=">Edit</a></td>
  </tr>
    
  <tr>
	<td>[checkbox]</td>
    
    <td>6</td>
	<td>Fred Myers</td>
	<td>W</td>
	<td>2013-05-14 04:35:00</td>
		<td>$48.56</td>
	
    
	<td><a href="supplier_edit.php?sno=">Edit</a></td>
  </tr>
    
  <tr>
	<td>[checkbox]</td>
    
    <td>7</td>
	<td>OSU</td>
	<td>W</td>
	<td>2013-06-01 08:00:00</td>
		<td>$5</td>
	
    
	<td><a href="supplier_edit.php?sno=">Edit</a></td>
  </tr>
    
  <tr>
	<td>[checkbox]</td>
    
    <td>8</td>
	<td>Ross</td>
	<td>W</td>
	<td>2013-05-10 04:04:00</td>
		<td>$128</td>
	
    
	<td><a href="supplier_edit.php?sno=">Edit</a></td>
  </tr>
  </table>
</body>
</html>
