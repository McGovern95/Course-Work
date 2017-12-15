<?php
session_start();
include('utility.php');

// this page should show result for authenticated managers only
if(isset($_SESSION["login_id"]) && !empty($_SESSION["login_id"]) &&
   isset($_SESSION["account_type"]) && !empty($_SESSION["account_type"]) && $_SESSION["account_type"] == "manager"){
	
	$assign_training_msg = $assign_game_msg = "";
	
	if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["assign_training"])){
		if(isset($_POST["players"])){
			$players_list = $_POST["players"];
			//echo count($players_list) . " players selected<br/>";
			for($i=0; $i<count($players_list); $i++){
				$query = "insert into assigntraining(playerid, managerid, trainingname) values('{$players_list[$i]}','{$_SESSION["user_id"]}','{$_POST["select_training"]}');";
				//echo $query . "<br/>";
				$conn->query($query) or die(mysqli_error($conn)); 
			}
			$conn->commit();
			$assign_training_msg = "training assigned to " . count($players_list) . " player(s)";
		}
		else{
			$assign_training_msg = "no players selected";
		}
	}
	
	if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["remove_players_from_game"])){
		if(isset($_POST["players"])){
			$players_list = $_POST["players"];
			for($i=0; $i<count($players_list); $i++){
				$query = "delete from play where gameid='{$_POST["select_game"]}' and playerid='{$players_list[$i]}';";
				//echo $query . "<br/>";
				$conn->query($query) or die(mysqli_error($conn)); 
			}
			$conn->commit();
			$assign_game_msg =  count($players_list) . " player(s) removed";
		}
		else{
			$assign_game_msg = "no players selected";
		}	
	}
	
	if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["assign_players_to_game"])){
		if(isset($_POST["players_available"])){
			$players_list = $_POST["players_available"];
			for($i=0; $i<count($players_list); $i++){
				$query = "delete from play where gameid='{$_POST["select_game"]}' and playerid='{$players_list[$i]}';";
				$query = "insert into play(playerid, gameid) values('{$players_list[$i]}','{$_POST["select_game"]}');";
				//echo $query . "<br/>";
				$conn->query($query) or die(mysqli_error($conn)); 
			}
			$conn->commit();
			$assign_game_msg =  count($players_list) . " player(s) assigned to game";
		}
		else{
			$assign_game_msg = "no players selected";
		}
	}
	
	$query = "select playerid, loginid, name, birthday, address, email, phonenumber, playpos from player order by name asc;";
	$query_result = $conn->query($query) or die(mysqli_error($conn)); 
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
<title>Manage Players</title>
</head>

<body>
<div>Players List</div>
	<table border="1">
		<thead>
		<td>ID</td>
		<td>Name</td>
		<td>LoginID</td>
		<td>Birthdate</td>
		<td>Address</td>
		<td>Email</td>
		<td>Phone#</td>
		<td>Play Position</td>			
		</thead>
	
		<tbody>
	<?php
	if($query_result->num_rows > 0){
		while($r = $query_result->fetch_assoc()){
	?>
	<tr>
		<td><?php echo $r["playerid"]?></td>
		<td><?php echo $r["name"]?></td>
		<td><?php echo $r["loginid"]?></td>
		<td><?php echo $r["birthday"]?></td>
		<td><?php echo $r["address"]?></td>
		<td><?php echo $r["email"]?></td>
		<td><?php echo $r["phonenumber"]?></td>
		<td><?php echo $r["playpos"]?></td>
	</tr>
	<?php
		}
	}
	else{		// no players to show
		echo "<td colspan=\"8\" style=\"text-align: center;\">no players to show</td>";
	}
	?>
	</tbody>
	</table>
	
	<!-- Assign game to players start-->
	<br/><br/>
	<?php
	$query = "select gameid from game;";
	$result = $conn->query($query) or die(mysqli_error($conn));
	if($result->num_rows > 0){
	?>
	<div>Assign Game to Players</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table>
	<tr>
	<td valign="top">Games<br/>
	<select onchange="this.form.submit()" name="select_game">
		<option disabled selected value> -- select a game -- </option>
		<?php
		while($r2 = $result->fetch_assoc()){
			if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["action"]) && $_POST["action"] == "game_selected" && $_POST["select_game"] == $r2["gameid"])
				echo  "<option selected value=\"" . $r2["gameid"] . "\">".$r2["gameid"]."</option>";
			else
				echo  "<option value=\"" . $r2["gameid"] . "\">".$r2["gameid"]."</option>";
		}
		?>
	</select>
	</td>
	
	<?php
		// todo check if there are any players before showing the droplist
		if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["action"]) && $_POST["action"] == "game_selected"){
			//$query = "select * from game where gameid='{$_POST["select_game"]}');";
			$query = "select p.playerid, p.name from play y, player p where p.playerid=y.playerid and gameid='{$_POST["select_game"]}';";
			$result = $conn->query($query) or die(mysqli_error($conn));
			echo "<td valign=\"top\" align=\"right\">Participating Players<br/>";
			if($result->num_rows > 0){
				echo "<select name=\"players[]\" multiple>";
				//echo "there are {$result->num_rows} players to show";
				while($r3 = $result->fetch_assoc()){
					echo "<option value=\"{$r3["playerid"]}\">{$r3["name"]}</option>";
				}
				echo "</select>";
				echo "<br/><input type=\"submit\" name=\"remove_players_from_game\" value=\"Remove\" />";
			}
			else{
				echo "No players assigned to this game yet";
			}
	?>
		</td>
	<?php
			$query = "select p.playerid, p.name from player p where not exists (select null from play y where y.playerid=p.playerid and y.gameid='{$_POST["select_game"]}');";
			$result = $conn->query($query) or die(mysqli_error($conn));
			echo "<td valign=\"top\" align=\"right\">Available Players<br/>";
			if($result->num_rows > 0){
				echo "<select name=\"players_available[]\" multiple>";
				//echo "there are {$result->num_rows} players to show";
				while($r3 = $result->fetch_assoc()){
					echo "<option value=\"{$r3["playerid"]}\">{$r3["name"]}</option>";
				}
				echo "</select>";
				echo "<br/><input type=\"submit\" name=\"assign_players_to_game\" value=\"Assign\" />";
			}
			else{
				echo "No players available for this game";
			}
		}
	?>

	</tr>
	<tr><td colspan="3" align="center">&nbsp;<?php echo $assign_game_msg;?></td></tr>
	</table>
	<input type="hidden" name="action" value="game_selected"/>
	</form>
	<br/><br/>
	<?php
	}
	?>
	<!-- Assign game to players start-->
	
	<!-- Assign training to players start-->
	<br/><br/>
	<?php
	$query = "select trainingname from training;";
	$result = $conn->query($query) or die(mysqli_error($conn));
	if($result->num_rows > 0){
	?>
	<div>Assign Training to Players</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table>
	<tr>
	<td valign="top">Trainings<br/>
	<select onchange="this.form.submit()" name="select_training">
		<option disabled selected value> -- select a training -- </option>
		<?php
		while($r2 = $result->fetch_assoc()){
			if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["action"]) && $_POST["action"] == "training_selected" && $_POST["select_training"] == $r2["trainingname"])
				echo  "<option selected value=\"" . $r2["trainingname"] . "\">".$r2["trainingname"]."</option>";
			else
				echo  "<option value=\"" . $r2["trainingname"] . "\">".$r2["trainingname"]."</option>";
		}
		?>
	</select>
	</td>
	
	<?php
		// todo check if there are any players before showing the droplist
		if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["action"]) && $_POST["action"] == "training_selected"){
			$query = "select playerid, name from player where playerid not in(select distinct playerid from assigntraining where managerid='{$_SESSION["user_id"]}' and trainingname='{$_POST["select_training"]}');";
			$result = $conn->query($query) or die(mysqli_error($conn));
			echo "<td>Players<br/>";
			if($result->num_rows > 0){
				echo "<select name=\"players[]\" multiple>";
				//echo "there are {$result->num_rows} players to show";
				while($r3 = $result->fetch_assoc()){
					echo "<option value=\"{$r3["playerid"]}\">{$r3["name"]}</option>";
				}
				echo "</select>";
			}
			else{
				echo "No candidate players";
			}
	?>
		</td>
		<td align="left" valign="top">&nbsp;<br/>
			<?php if($result->num_rows > 0){
				echo "<input type=\"submit\" value=\"Assign\" name=\"assign_training\">";
			}?>
		&nbsp;</td>
	<?php
		}
	?>

	</tr>
	<tr><td colspan="3" align="center"><?php echo $assign_training_msg;?></td></tr>
	</table>
	<input type="hidden" name="action" value="training_selected"/>
	</form>
	<br/><br/>
	<?php
	}
	?>
	<!-- Assign training to players end -->
	
	<!-- select a player to show details -->
	<br/><br/>
	<?php
	if($query_result->num_rows > 0){
	?>
	<div>Show more details for:</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<select name="select_player" onchange="this.form.submit()">
		<option disabled selected value> -- select a player -- </option>
		<?php
		mysqli_data_seek($query_result, 0);
		while($r = $query_result->fetch_assoc()){
			echo  "<option value=\"" . $r["playerid"] . "\">(".$r["playerid"].") ".$r["name"]."</option>";
		}
		?>
	</select>
	</form>
	<br/><br/>
	<?php
		if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["select_player"])){
			$selected_player_id = $_POST["select_player"];
			// find player's name from previous result set
			mysqli_data_seek($query_result, 0);
			$selected_player_name = "";
			while($r = $query_result->fetch_assoc()){
				if($r["playerid"] == $selected_player_id){
					$selected_player_name = $r["name"];
					break;
				}
			}
	?>
	<br/><br/><h2><?php echo $selected_player_name?>'s Profile</h2>
	
	<!-- Display games for one player-->
	<div>Games Played</div>
	<table border="1">
		<thead>
		<td>ID</td>
		<td>Date</td>
		<td>Result</td>	
		<td>Playing Venue</td>
		<td>Opponent Team</td>	
		</thead>
	
		<tbody>
	<?php
	$query = "select g.* from game g, play p where p.GameID=g.GameID and p.PlayerID='".$selected_player_id."';";	
	$query_result = $conn->query($query) or die(mysqli_error($conn));
	if($query_result->num_rows > 0){
		while($r = $query_result->fetch_assoc()){
	?>
	<tr>
		<td><?php echo $r["gameid"]?></td>
		<td><?php echo $r["date"]?></td>
		<td><?php echo $r["result"]?></td>
		<td><?php echo $r["playingvenue"]?></td>
		<td><?php echo $r["opponentteam"]?></td>
	</tr>
	</tbody>
	</table>
	<?php
		}
	}
	else{		// no players to show
		echo "<td colspan=\"5\" style=\"text-align: center;\">no games available</td>";
	}
	?>
	
	<!-- Display stats for one player-->
	<br/><br/>
	<div>Stats</div>
	<table border="1">
		<thead>
		<td>Year</td>
		<td>Total Points</td>
		<td>ASPG</td>
		</thead>
		<tbody>
	<?php
	$query = "select s.year, s.totalpoints, s.aspg from stats s, player p where s.PlayerID=p.PlayerID and p.PlayerID = '".$selected_player_id."';";
	$query_result = $conn->query($query) or die(mysqli_error($conn));
	if($query_result->num_rows > 0){
		while($r = $query_result->fetch_assoc()){
	?>
	<tr>
		<td><?php echo $r["year"]?></td>
		<td><?php echo $r["totalpoints"]?></td>
		<td><?php echo $r["aspg"]?></td>
	</tr>
	<?php
		}
	}
	else{		// no players to show
		echo "<td colspan=\"3\" style=\"text-align: center;\">no stats available</td>";
	}
	?>
	</tbody>
	</table>
	
	
	<!-- Display trainings for one player-->
	<br/><br/>
	<div>Trainings</div>
	<table border="1">
		<thead>
		<td>Training Name</td>
		<td>Hours</td>
		<td>Assiged By</td>
		</thead>
		<tbody>
	<?php
	$query = "select asst.trainingname, t.timeperiodinhour, m.name "
		."from assigntraining asst, player p, manager m, training t "
		."where asst.PlayerID=p.PlayerID and asst.ManagerID=m.ManagerID and asst.trainingname=t.TrainingName "
		."and p.playerid = '".$selected_player_id."';";
	$query_result = $conn->query($query) or die(mysqli_error($conn));
	if($query_result->num_rows > 0){
		while($r = $query_result->fetch_assoc()){
	?>
	<tr>
		<td><?php echo $r["trainingname"]?></td>
		<td><?php echo $r["timeperiodinhour"]?></td>
		<td><?php echo $r["name"]?></td>
	</tr>
	<?php
		}
	}
	else{		// no players to show
		echo "<td colspan=\"3\" style=\"text-align: center;\">no trainings available</td>";
	}
	?>
	</tbody>
	</table>
	
	
	<?php
		}
	}
	?>
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