<?php
include('session.php');
include('utility.php');

$birthday_msg = "mm-dd-yyyy";
$login_id_msg = $full_name_msg = $password_msg = $address_msg = $email_msg = $phone_number_msg = $request_msg = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {			// create manager account request
	$login_id = validate_input($_POST["uname"]);
	$full_name = validate_input($_POST["full_name"]);
	$login_password = validate_input($_POST["pword"]);
	// todo must use a function here to make sure the date is valid?
	//$time = strtotime(validate_input($_POST["birthday"]));
	//$birthday = date('Y-m-d',$time);
	$birthday = validate_input($_POST["birthday"]);
	$address = validate_input($_POST["address"]);
	$email = validate_input($_POST["email"]);
	$phone_number = validate_input($_POST["phone_number"]);
	
	// make sure no field is empty in the submitted form
	$valid_form = true;
	if(empty($_POST['uname'])){
		$login_id_msg = "required field!";
		$valid_form = false;
	}
	
	if(empty($_POST['full_name'])){
		$full_name_msg = "required field!";
		$valid_form = false;
	}
	
	if(empty($_POST['pword'])){
		$password_msg = "required field!";
		$valid_form = false;
	}
	
	if(empty($_POST['birthday'])){
		$birthday_msg = "required field! ".$birthday_msg;
		$valid_form = false;
	}
	
	if(empty($_POST['address'])){
		$address_msg = "required field!";
		$valid_form = false;
	}
	
	if(empty($_POST['email'])){
		$email_msg = "required field!";
		$valid_form = false;
	}
	
	if(empty($_POST['phone_number'])){
		$phone_number_msg = "required field!";
		$valid_form = false;
	}
	
	// validate the date
	if(is_valid_date($birthday)){
		//$birthday = date("Y-m-d", strtotime($birthday)); bug
	}
	else{
		$birthday_msg = "invalid date! " . $birthday_msg;
		$valid_form = false;
	}
	
	if($valid_form){
		// check if the choosen login id is already taken
		$query_string = "select managerid from manager where loginid = '".$login_id."' "
			."union select playerid from player where loginid = '".$login_id."';";

		$query_result = $conn->query($query_string) or die(mysqli_error($conn));
		if($query_result->num_rows > 0){		// this login id already taken!
			$login_id_msg = "login id already taken!";
		}
		else{
			// insert a new record into the manager table
			$query_string = "insert into Manager(loginid, name, password, birthday, address, email, phonenumber)"
				." value('".$login_id."','".$full_name."','".$login_password."',STR_TO_DATE('".$birthday."', '%m-%d-%Y'),'".$address
				."','".$email."','".$phone_number."')";

			if ($conn->query($query_string) === TRUE) {
				$request_msg = "Account created, redirecting to login page...";
				$conn->commit();
				header( "refresh:3;url=manager.php" );
				//header("Location: manager.php"); 
				//exit;
			} else {
				$request_msg = "Error: " . $query_string . "<br>" . $conn->error;
			}	
		}
	}
	
}
?>

<html>
	<header>
		<h2>Create Manager Account</h2>
	</header>
<body>
		<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		  <table align="center">
				<tr>
					<td style="text-align: right">LoginID</td>
				  <td><input required type="text" name="uname" value="<?php echo isset($_POST["uname"])? validate_input($_POST["uname"]) : ''; ?>"></td>
					<td><?php echo $login_id_msg?></td>
			  </tr>
				
				<tr>
					<td style="text-align: right">Full Name</td>
				  <td><input required type="text" name="full_name" value="<?php echo isset($_POST["full_name"])? validate_input($_POST["full_name"]) : ''; ?>"></td>
					<td><?php echo $full_name_msg?></td>
			  </tr>
				
				<tr>
					<td style="text-align: right">Password</td>
				  <td><input required type="password" name="pword" value="<?php echo isset($_POST["pword"])? validate_input($_POST["pword"]) : ''; ?>"></td>
					<td><?php echo $password_msg?></td>
			  </tr>
				
				<tr>
				  <td style="text-align: right">Birthday</td>
				  <td><input required type="text" name="birthday" value="<?php echo isset($_POST["birthday"])? validate_input($_POST["birthday"]) : ''; ?>"></td>
					<td><?php echo $birthday_msg?></td>
			  </tr>
				
				<tr>
				  <td style="text-align: right">Address</td>
				  <td><input required type="text" name="address" value="<?php echo isset($_POST["address"])? validate_input($_POST["address"]) : ''; ?>"></td>
					<td><?php echo $address_msg?></td>
			  </tr>
				
				<tr>
					<td style="text-align: right">Email</td>
				  <td><input required type="text" name="email" value="<?php echo isset($_POST["email"])? validate_input($_POST["email"]) : ''; ?>"></td>
					<td><?php echo $email_msg?></td>
			  </tr>
				
				<tr>
					<td style="text-align: right">Phone#</td>
				  <td><input required type="text" name="phone_number" value="<?php echo isset($_POST["phone_number"])? validate_input($_POST["phone_number"]) : ''; ?>"></td>
					<td><?php echo $phone_number_msg?></td>
			  </tr>
				<tr>
					<td colspan="3">
						<input type="submit" value="Create Account" name="submit">
						<input type="reset" value="Clear">
					</td>
				</tr>
			</table>
		 </form>
			<table width="60%" align="center">
				<tr>
					<td width="100%" style="text-align: center"><?php echo $request_msg?></td>
			  </tr>
			</table>
<a href="manager.php">Manager Login</a><br>
<a href="index.php">Back to index</a><br>
</body>
</html>

