<?php
session_start();
include('utility.php');

// this page should show result for authenticated managers only
if(isset($_SESSION["login_id"]) && !empty($_SESSION["login_id"]) &&
   isset($_SESSION["account_type"]) && !empty($_SESSION["account_type"]) && $_SESSION["account_type"] == "manager"){
	
	$players_accounts_approve_msg = $reset_players_password_msg = "";
	
	if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["approve"])){
		
		if(isset($_POST["checked_accounts"])){		// make sure at least one account is checked
			$selected_accounts = $_POST["checked_accounts"];
			$selected_accounts_list = "'{$selected_accounts[0]}'";
			for($i=1; $i<count($selected_accounts); $i++){
				$selected_accounts_list .= ",'{$selected_accounts[$i]}'";
			}
			$query = "update player set accountstatus='active' where playerid in ({$selected_accounts_list});";
			if ($conn->query($query) === TRUE) {
					$players_accounts_approve_msg = count($selected_accounts) . " account(s) approved";
					$conn->commit();
			} else {
				$players_accounts_approve_msg = "Error: " . $query . "<br>" . $conn->error;
			}
		}
		else{
			$players_accounts_approve_msg = "No account selected for approval";
		}
	}
	
	if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["reject"])){
		if(isset($_POST["checked_accounts"])){		// make sure at least one account is checked
			$selected_accounts = $_POST["checked_accounts"];
			$selected_accounts_list = "'{$selected_accounts[0]}'";
			for($i=1; $i<count($selected_accounts); $i++){
				$selected_accounts_list .= ",'{$selected_accounts[$i]}'";
			}
			$query = "update player set accountstatus='rejected' where playerid in ({$selected_accounts_list});";
			if ($conn->query($query) === TRUE) {
					$players_accounts_approve_msg = count($selected_accounts) . " account(s) approved";
					$conn->commit();
			} else {
				$players_accounts_approve_msg = "Error: " . $query . "<br>" . $conn->error;
			}
		}
		else{
			$players_accounts_approve_msg = "No account selected for rejection";
		}
	}
	
	if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["reset_password"])){
		$new_password = random_string(8);
		$query = "update player set password='{$new_password}' where loginid='{$_POST["select_player"]}';";
		if ($conn->query($query) === TRUE) {
			$conn->commit();
			$reset_players_password_msg = "Password reset, new password: " . "<b>{$new_password}</b>";
			}
		else {
			$reset_players_password_msg = "Error: " . $query . "<br>" . $conn->error;
		}
	}
	
}
else{
	header("Location: manager.php"); 
	exit;
}
?>

<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Manage Players Accounts</title>
</head>

<body>

	<!--view pending accounts requests start-->
	<?php
	$query = "select playerid, loginid, name, birthday, address, email, phonenumber, playpos from player where accountstatus='pending';";
	$query_result = $conn->query($query) or die(mysqli_error($conn));
	?>
	<div>Pending Requests</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table>
	<tr>
		<td>&nbsp;</td>
		<td>Player ID</td>
		<td>Login ID</td>
		<td>Name</td>
		<td>Birthday</td>
		<td>Address</td>
		<td>Email</td>
		<td>Phone#</td>
		<td>Play Position</td>
	</tr>
	<?php
		if($query_result->num_rows > 0){		// there are pending requests 
			while($r = mysqli_fetch_assoc($query_result)){
				?>
		<tr>
			<td><input name="checked_accounts[]" type="checkbox" value="<?php echo $r["playerid"]?>"</td>
			<td><?php echo $r["playerid"]?></td>
			<td><?php echo $r["loginid"]?></td>
			<td><?php echo $r["name"]?></td>
			<td><?php echo $r["birthday"]?></td>
			<td><?php echo $r["address"]?></td>
			<td><?php echo $r["email"]?></td>
			<td><?php echo $r["phonenumber"]?></td>
			<td><?php echo $r["playpos"]?></td>
		</tr>
		
				<?php
			}
		?>
		<tr>
			<td colspan="9" align="right">
				<input type="submit" name="reject" value="Reject" />
				<input type="submit" name="approve" value="Approve" />
			</td>
		</tr>
		<?php
		}
		else{				// no pending requests found
			echo "<tr><td colspan=\"9\" align=\"center\">No pending requests</td></tr>";
		}
	?>
		
	<tr>
		<td colspan="9" align="center">&nbsp;<?php echo $players_accounts_approve_msg;?></td>
	</tr>
	</table>
	</form>
	<!--view pending accounts requests end-->
	
	<!--reset players password start-->
	<?php
	$query = "select playerid, loginid, name from player where accountstatus='active';";
	$query_result = $conn->query($query) or die(mysqli_error($conn));
	?>
	<br/><br/>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<div>Reset Players Password</div>
	<table>
		<tr>
			<td>
				<select name="select_player">
				<option disabled selected value> -- select a player's account -- </option>
	<?php
	if($query_result->num_rows > 0){
		while($r = $query_result->fetch_assoc()){
			if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["reset_password"]) && $_POST["select_player"] == $r["playerid"])
				echo  "<option selected value=\"" . $r["playerid"] . "\">(".$r["loginid"].") {$r['name']}</option>";
			else
				echo  "<option value=\"" . $r["playerid"] . "\">(".$r["loginid"].") {$r['name']}</option>";
		}
	}
	?>
	</select>
	<input type="submit" name="reset_password" value="Reset Password"/>
			</td>
		</tr>
		<tr><td><?php echo $reset_players_password_msg;?></td></tr>
	</table>
	</form>
	<!--reset players password end-->
	
	<!--Manager's services start-->
	<br/><br/>
	<form id="logout_form" method=post action="manager_welcome.php">
	<a href="manager_manage_players.php">Manage Players</a><br/>
	<a href="manager_manage_players_accounts.php">Manage Players Accounts</a><br/>
	<a href="manager_manage_trainings.php">Manage Trainings</a><br/>
	<a href="manager_manage_games.php">Manage Games</a><br/>
	<a href="manager_welcome.php">Manage Profile</a><br/>
	<a href="#" onclick="document.forms['logout_form'].submit();">Logout</a>
	<input type="hidden" name="action" value="logout"/>
	</form>
	<br>
	<!--Manager's services end-->
</body>
</html>