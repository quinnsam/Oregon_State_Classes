
<!doctype html>
<html lang="en">
<head>  
  <meta charset="utf-8" />
  <title>Spending Analysis</title>
</head>
<body>
<h1>Products</h1>

<table border="0">
<tr>
<td>
	<FORM ACTION="Products.php" METHOD="GET" NAME = "Trans">
  Select Transaction:
  <select NAME ='Trans_ID' >
	  <option value="0">0</option>  
	  <option value="1">1</option>  
	  <option value="2">2</option>  
	  <option value="3">3</option>  
	  <option value="4">4</option>  
	  <option value="6">6</option>  
	  <option value="7">7</option>  
	  <option value="8">8</option>  
		</select>
  <INPUT TYPE="SUBMIT" VALUE = "Search">
	</FORM>
</td>
<td>
<FORM ACTION="Products.php" METHOD="GET" NAME = "Order">
  Select Order:
   <select NAME ="_list" >
		<option value="I">Item ID</option>
		<option value="P">Price</option>
		<option value="R">Rating</option>
		<option value="N">Number Purchased</option>
	</select>
  <select NAME ='_order' >
  	<option value="A">Ascending</option>
		<option value="D">Descending</option>
		</select>
  <INPUT TYPE="SUBMIT" VALUE = "Search">
	</FORM>
	</td>
<td><a href="http://web.engr.oregonstate.edu/~quinnsa/Products.php">Go Back</a></td>
</tr>
<tr>
</tr>
</table>




<table border="1">
  <tr>
    <th>Options</th>
    <th>Product Name</th>
    <th>Brand</th>
	<th>Item ID</th>
    <th>Transaction#</th>
	<th>Price</th>
	<th>Rating</th>
	<th># Purchased</th>
	<th>Action</th>
  </tr>
  
   
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="1">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Kendama</td>
    <td>Sweets</td>
    	<td>1</td>
    <td>4</td>
	<td>$28.98</td>
	<td>5</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=1">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="2">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Club Tuna</td>
    <td>Jimmy Johns</td>
    	<td>2</td>
    <td>1</td>
	<td>$6.55</td>
	<td>4</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=2">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="3">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Hunters Club</td>
    <td>Jimmy Johns</td>
    	<td>3</td>
    <td>1</td>
	<td>$6.55</td>
	<td></td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=3">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="4">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Deli Turkey Wrap</td>
    <td>Fred Myers</td>
    	<td>4</td>
    <td>2</td>
	<td>$4.49</td>
	<td>4</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=4">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="5">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Cash Withdraw</td>
    <td>Cash</td>
    	<td>5</td>
    <td>2</td>
	<td>$50</td>
	<td></td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=5">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="6">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Tortilla Chips</td>
    <td>Fred Myers</td>
    	<td>6</td>
    <td>3</td>
	<td>$1</td>
	<td>4</td>
	<td>2</td>
    
	<td><a href="Product_edit.php?Item_ID=6">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="7">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Extra Gum</td>
    <td>Extra</td>
    	<td>7</td>
    <td>3</td>
	<td>$1</td>
	<td>5</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=7">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="8">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Burrito Tortilla</td>
    <td>Mission</td>
    	<td>8</td>
    <td>3</td>
	<td>$3.59</td>
	<td>4</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=8">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="9">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Fresh Cut Salsa - Me</td>
    <td>RoJo</td>
    	<td>9</td>
    <td>3</td>
	<td>$4.99</td>
	<td>5</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=9">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="10">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Medium Cheddar Chees</td>
    <td>Brandon</td>
    	<td>10</td>
    <td>3</td>
	<td>$5.49</td>
	<td>5</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=10">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="11">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Jolly Rancher - Hard</td>
    <td>Jolly Rancher</td>
    	<td>11</td>
    <td>3</td>
	<td>$2.5</td>
	<td>5</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=11">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="12">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Fred Myers Skim Milk</td>
    <td>Fred Myers</td>
    	<td>12</td>
    <td>6</td>
	<td>$2.99</td>
	<td>4</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=12">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="13">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Low Fat Yogurt (Rasp</td>
    <td>Fed Myers</td>
    	<td>13</td>
    <td>3</td>
	<td>$1.79</td>
	<td>4</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=13">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="14">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Fuji Apple</td>
    <td>Apple Country</td>
    	<td>14</td>
    <td>6</td>
	<td>$1.56</td>
	<td>4</td>
	<td>5</td>
    
	<td><a href="Product_edit.php?Item_ID=14">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="15">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Low Fat Yogurt (Rasp</td>
    <td>Fed Myers</td>
    	<td>15</td>
    <td>6</td>
	<td>$1.79</td>
	<td>4</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=15">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="16">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Hoddie Allen Ticket</td>
    <td>Ticket</td>
    	<td>16</td>
    <td>7</td>
	<td>$5</td>
	<td></td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=16">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="17">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>511 Khaki Jeans</td>
    <td>Levi's</td>
    	<td>17</td>
    <td>8</td>
	<td>$88</td>
	<td>5</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=17">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="18">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Adio Skate Shoes</td>
    <td>Adio</td>
    	<td>18</td>
    <td>8</td>
	<td>$22</td>
	<td>3</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=18">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="19">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>High-Top Skate Shoes</td>
    <td>Lakai</td>
    	<td>19</td>
    <td>8</td>
	<td>$20</td>
	<td>4</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=19">Edit</a></td>
  </tr>
    
  <tr>
	<td>
	<form ACTION="Products_Del.php" METHOD="GET" NAME = "del">
	<input type="hidden" name="Item_ID" value="21">
<input type="checkbox" name="check_option" value="_Delete">Delete
<INPUT TYPE="SUBMIT" VALUE = "Update">
</form>
</td>
    <td>Tjing</td>
    <td>some</td>
    	<td>21</td>
    <td>0</td>
	<td>$2.26</td>
	<td>3</td>
	<td>1</td>
    
	<td><a href="Product_edit.php?Item_ID=21">Edit</a></td>
  </tr>
  </table>

</body>
</html>
