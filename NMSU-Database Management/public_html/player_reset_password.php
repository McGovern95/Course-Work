<?php
include('session.php');
include('utility.php'); 

$login_id_msg = $password_reset_msg = "";

if ($_SERVER["REQUEST_METHOD"] == "POST"){
	if(isset($_POST["submit"])){
		
		if(empty($_POST["uname"])){
			$login_id_msg = "required field!";
		}
		else{
			$login_id = validate_input($_POST["uname"]);
			// make sure the user exists in the database
			$query = "select playerid from player where loginid='{$login_id}';";
			$query_result = $conn->query($query) or die(mysqli_error($conn));
			if($query_result->num_rows == 1){
				$new_password = random_string(8);
				$query = "update player set password='{$new_password}' where loginid='{$login_id}';";
				if ($conn->query($query) === TRUE) {
					$conn->commit();
					$password_reset_msg = "Password reset, new password: " . "<b>{$new_password}</b>";
				}else {
				$password_reset_msg = "Error: " . $query . "<br>" . $conn->error;
				}
			}
			else{
				$password_reset_msg = "Invalid Login ID";
			}
		}
	}
}

?>

<html>
<body>
<h2>Player Password Reset</h2>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		<table align="center">
<td>LoginID</td>
<td><input type="text" name="uname"></td>
<td><?php echo $login_id_msg?></td>
			</tr>
			<tr>
				<td colspan=3 align="center">
					<input type="submit" value="Reset" name="submit"/>
				</td>
			</tr>
			<tr><td colspan=3 align="center">&nbsp;<?php echo $password_reset_msg?></td></tr>
		</table>
	</form>

<a href="player.php">Player Login</a><br/>
<a href="player_create.php">Create an account</a><br>
<a href="index.php">Back to index</a><br>
</body>
</html>