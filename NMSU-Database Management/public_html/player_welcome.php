<?php
session_start();
include('utility.php');

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["action"]) && $_POST["action"] == "logout"){ // logout request
	session_destroy();
	header("Location: index.php"); 
	exit;
}

// this page should show result for authenticated players only
if(isset($_SESSION["login_id"]) && !empty($_SESSION["login_id"]) &&
   isset($_SESSION["account_type"]) && !empty($_SESSION["account_type"]) && $_SESSION["account_type"] == "player"){
	
	$player_id = $player_name = $player_birthday = $player_address = $player_email = $manger_phone_number = "";
	$profile_update_msg = $change_password_msg = "";
	
	if(isset($_POST["action"]) && $_POST["action"] == "update_profile"){
		$update_id = validate_input($_POST["id"]);
		$update_name = validate_input($_POST["name"]);
		$update_birthday = validate_input($_POST["birthday"]);
		$update_address = validate_input($_POST["address"]);
		$update_email = validate_input($_POST["email"]);
		$update_phone_number = validate_input($_POST["phone_number"]);
		
		if(empty($update_birthday) || empty($update_address) || empty($update_email) || empty($update_phone_number)){
			$profile_update_msg = "All fields must be filled";
		}
		else if(!is_valid_date($update_birthday)){
			$profile_update_msg = "Invalid date (use format mm-dd-yyyy)";
		}
		else{
			$query_string = "update player set name= '".$update_name."', birthday = STR_TO_DATE('".$update_birthday."','%m-%d-%Y')"
				.", address='".$update_address."', email='".$update_email."', phonenumber='".$update_phone_number."' where playerid='".$update_id."';";
		
			if ($conn->query($query_string) === TRUE) {
				$profile_update_msg = "Profile updated";
				$conn->commit();
			} else {
				$profile_update_msg = "Error: " . $query_string . "<br>" . $conn->error;
			}
		}
	}
	
	if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["change_password"])){
		$current_password = validate_input($_POST["current_password"]);
		$confirmed_password = validate_input($_POST["current_password_confirm"]);
		$new_password = validate_input($_POST["new_password"]);
		
		if($current_password != $confirmed_password){
			$change_password_msg = "Passwords mismatched";
		}
		else{
			$query = "select * from player where playerid='{$_SESSION["user_id"]}' and password='{$current_password}';";
			$query_result = $conn->query($query) or die(mysqli_error($conn));
			if($query_result->num_rows == 1){
				$query = "update player set password='{$new_password}' where playerid='{$_SESSION["user_id"]}';";
				if ($conn->query($query) === TRUE) {
					$change_password_msg = "Password Changed";
					$conn->commit();
			} else {
				$change_password_msg = "Error: " . $query . "<br>" . $conn->error;
			}
			}
			else{
				$change_password_msg = "Incorrect password";
			}
		}
	}
	
	$query = "select * from player where loginid ='".$_SESSION["login_id"]."';";
	$query_result = $conn->query($query) or die(mysqli_error($conn));
	if($query_result->num_rows == 1){
		$r = mysqli_fetch_assoc($query_result);
		$player_id = $r["playerid"];
		$player_name = $r["name"];
		$player_birthday = $r["birthday"];
		$player_address = $r["address"];
		$player_email = $r["email"];
		$player_phone_number = $r["phonenumber"];
		
	}
	
}
else{
	header("Location: player.php"); 
	exit;
}
?>
<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Profile</title>
</head>

<body>
	<h2>Welcome, <?php echo $_SESSION["login_id"]?>!</h2>
	<br>
	<br>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table>
		<tr>
			<td style="text-align: ">ID</td>
			<td style="text-align: left"><?php echo $player_id?></td>
			<td><input readonly="readonly" name="id" value="<?php echo $player_id?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Name</td>
			<td style="text-align: left"><?php echo $player_name?></td>
			<td><input name="name" value="<?php echo $player_name?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Birthdate</td>
			<td style="text-align: left">
				<?php echo date('F d, Y', strtotime($r["birthday"]))?>
			</td>
			<td><input name="birthday" value="<?php echo date("m-d-Y", strtotime($player_birthday))?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Address</td>
			<td style="text-align: left"><?php echo $player_address?></td>
			<td><input name="address" value="<?php echo $player_address?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Email</td>
			<td style="text-align: left"><?php echo $player_email?></td>
			<td><input name="email" value="<?php echo $player_email?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Phone#</td>
			<td style="text-align: left"><?php echo $player_phone_number?></td>
			<td><input name="phone_number" value="<?php echo $player_phone_number?>"></td>
		</tr>
		
		<tr>
			<td align="right" colspan="3">
			<input type="reset" value="Reset">
			<input type="submit" value="Update" name="submit">
			</td>
		</tr>
		
		<tr align="center">
			<td colspan="3">&nbsp;<?php echo $profile_update_msg?></td>
		</tr>
		
	</table>
		<input type="hidden" name="action" value="update_profile"/>
	</form>
	
	
	<!-- change password start-->
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table>
		<tr>
			<td align="right">Current Password</td>
			<td><input required name="current_password" type="password" /></td>
		</tr>
		
		<tr>
			<td align="right">Re-enter Current Password<br/></td>
			<td><input required name="current_password_confirm" type="password" /></td>
		</tr>
		
		<tr>
			<td align="right">New Password<br/></td>
			<td><input required name="new_password" type="password" /></td>
		</tr>
		
		<tr>
			<td colspan="2" align="right">
				<input type="reset" value="Reset" />
				<input type="submit" name="change_password" value="Change" />
			</td>
		</tr>
		
		<tr>
			<td colspan="2" align="center"><?php echo $change_password_msg;?></td>
		</tr>
	</table>
	</form>
	<!-- change password end-->

	
	<!--player's services start-->
	<br/><br/>
	<form id="logout_form" method=post action="player_welcome.php">
	<a href="player_welcome.php">Manage Profile</a><br/>
	<a href="player_games_stats_trainings.php">Player Details</a><br>
	<a href="#" onclick="document.forms['logout_form'].submit();">Logout</a>
	<input type="hidden" name="action" value="logout"/>
	</form>
	<br>
	<!--player's services end-->
</body>
</html>