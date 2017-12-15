<?php
include('session.php');
include('utility.php');

$login_id = $login_password = "";
$login_id_msg = $login_password_msg = $login_result_message = "";

if ($_SERVER["REQUEST_METHOD"] == "POST"){
	if(isset($_POST["submit"])){
	  $login_id = validate_input($_POST["uname"]);
	  $login_password = validate_input($_POST["pword"]);
	  $user_id = "";

		if(empty($_POST["uname"])){
			$login_id_msg = "required field!";
		}

		if(empty($_POST["pword"])){
			$login_password_msg = "required field!";
		}

			$query_string = "SELECT * FROM manager WHERE loginid = '".$_POST["uname"]."' and password = '".$_POST["pword"]."';";

			$query_result = $conn->query($query_string) or die(mysqli_error($conn));
			if($query_result->num_rows == 1){
				$r = $query_result->fetch_assoc();
				$login_result_message = "login successful!";
				// Set session variables
				$_SESSION["login_id"] = $_POST["uname"];
				$_SESSION["account_type"] = "manager";
				$_SESSION["user_id"] = $r["managerid"];
				header("Location: manager_welcome.php"); 
				exit;
			}
			else{
				$login_result_message = "invalid login name or password";
			}
	}
	else if(isset($_POST["reset"])){
		header("Location: manager_reset_password.php"); 
		exit;
	}
}
?>

<html>
<body>
<h2>Manager Login</h2>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		<table align="center">
<td>LoginID</td>
<td><input type="text" name="uname"></td>
<td><?php echo $login_id_msg?></td>
			</tr>
			<tr>
<td>Password</td>
<td><input type="password" name="pword"></td>
<td><?php echo $login_password_msg?></td>
			</tr>
			<tr>
				<td colspan=3 align="center">
					<input type="submit" value="Login" name="submit"/>
					<input type="submit" value="Forgot Password?" name="reset"/>
				</td>
			</tr>
			<tr><td colspan=3 align="center"><?php echo $login_result_message?></td></tr>
		</table>
	</form>

<a href="manager_create.php">Create an account</a><br>
<a href="index.php">Back to index</a><br>
</body>
</html>