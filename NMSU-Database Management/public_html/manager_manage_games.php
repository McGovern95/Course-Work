<?php
session_start();
include('utility.php');

// this page should show result for authenticated managers only
if(isset($_SESSION["login_id"]) && !empty($_SESSION["login_id"]) &&
   isset($_SESSION["account_type"]) && !empty($_SESSION["account_type"]) && $_SESSION["account_type"] == "manager"){
	
	$game_add_msg = $game_delete_msg = $game_update_msg = "";
	
	if ($_SERVER["REQUEST_METHOD"] == "POST"){
	if($_POST["action"] == "add_game"){		// adding a new game
		
		$g_date = $_POST["game_date"];
		$g_venue = $_POST["game_venue"];
		$g_opponent = $_POST["game_opponent"];
		
		
		if(empty($g_date) || !isset($_POST["game_result"]) || empty($g_venue) || empty($g_opponent)){
			$game_add_msg = "All fields must be filled";
		}
		else if(!is_valid_date($g_date)){
			$game_add_msg = "Invalid date";
		}
		else{
		if($_POST["game_result"] == "win")
			$g_result = "Win";
		else if($_POST["game_result"] == "lose")
			$g_result = "Lose";
		else if($_POST["game_result"] == "tie")
			$g_result = "Tie";
		else if($_POST["game_result"] == "TBD")
			$g_result = "TBD";
		
		$query_string = "insert into game(date, result, playingvenue, opponentteam) values(STR_TO_DATE('".$g_date."', '%m-%d-%Y'),'".$g_result."','".$g_venue."','".$g_opponent."')";
		
		if ($conn->query($query_string) === TRUE) {
				$game_add_msg = "New game added";
			
				$conn->commit();
			} else {
				$game_add_msg = "Error: " . $query_string . "<br>" . $conn->error;
			}	
		}
	}
		else if($_POST["action"] == "delete_game"){
			if(isset($_POST['checked_games'])){		// makes sure at least one item is checked
				$games_list = "";
				 $checkbox = $_POST['checked_games'];
				 $games_list = "'" . $checkbox[0] . "'";
				 for($i=1;$i<count($checkbox);$i++){
					 $del_id = $checkbox[$i];
					 $games_list = $games_list . ",'" . $checkbox[$i] . "'";
				}
				$query_string = "delete from game where gameid in ($games_list);";
				
				if ($conn->query($query_string) === TRUE) {
					$game_delete_msg = count($checkbox) . " record(s) deleted";
					$conn->commit();
			} else {
				$game_delete_msg = "Error: " . $query_string . "<br>" . $conn->error;
			}
		    }
			else{
				$game_delete_msg = "At least one record must be checked for deletion";
			}
		}
		else if($_POST["action"] == "update_game"){
			$g_id = validate_input($_POST["id"]);
			$g_date = validate_input($_POST["date"]);
			$g_result = validate_input($_POST["update_game_result"]);
			$g_venue = validate_input($_POST["venue"]);
			$g_opponent = validate_input($_POST["opponent"]);
			
			if(empty($g_id) || empty($g_date) || empty($g_result) || empty($g_venue) || empty($g_opponent)){
				$game_update_msg = "All fileds must be filled";
				$game_delete_msg = $game_update_msg;
			}
			else if(!is_valid_date($g_date)){
				$game_update_msg = "Invalid date (use format mm-dd-yyyy)";
				$game_delete_msg = $game_update_msg;
			}
			else{
				$query_string = "update game set date=STR_TO_DATE('".$g_date."','%m-%d-%Y'), result='".$g_result."', playingvenue='".$g_venue."', opponentteam='".$g_opponent."' where gameid='".$g_id."';";
				if ($conn->query($query_string) === TRUE){
					$game_update_msg = "Game updated";
					$game_delete_msg = "Game updated";
					$conn->commit();
				}else{
					$game_update_msg = "Error: " . $query_string . "<br>" . $conn->error;
					$game_delete_msg = $game_update_msg;
				}
			}
		}
	}
	
	$query = "select * from game order by date asc;";
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
<title>Manage Games</title>
</head>

<body>
<div>Games List</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table border="1">
		<thead>
		<td></td>
		<td>ID</td>
		<td>Date</td>
		<td>Result</td>	
		<td>Playing Venue</td>
		<td>Opponent Team</td>	
		</thead>
	
		<tbody>
	<?php
	if($query_result->num_rows > 0){
		while($r = $query_result->fetch_assoc()){
	?>
	<tr>
		<td><input name="checked_games[]" type="checkbox" value="<?php echo $r["gameid"]?>"</td>
		<td><?php echo $r["gameid"]?></td>
		<td><?php echo DateTime::createFromFormat('Y-m-d', $r["date"])->format('m-d-Y')?></td>
		<td><?php echo $r["result"]?></td>
		<td><?php echo $r["playingvenue"]?></td>
		<td><?php echo $r["opponentteam"]?></td>
	</tr>
			
	<?php
		}
	}
	else{		// no games to show
		echo "<td colspan=\"5\" style=\"text-align: center;\">no games available</td>";
	}
	?>
	
	<tr align="right">
		<td colspan="6"><input type="submit" name="delete_form" value="Delete selected games"></td>
	</tr>
			
	<tr align="center">
		<td colspan="6">&nbsp;<?php echo $game_delete_msg?></td>
	</tr>
			
	</tbody>
	</table>
	<input type="hidden" name="action" value="delete_game"/>
	</form>
	<br/><br/>
			<div>Add Game</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table>
		
		<tr>
			<td>Date (mm-dd-yyyy)</td>
			<td><input required type="text" name="game_date"/></td>
		</tr>
		
		<tr>
			<td>Result</td>
			<td>
				<input type="radio" name="game_result" value="win"> Win
  				<input type="radio" name="game_result" value="lose"> Lose
				<input type="radio" name="game_result" value="tie"> Tie
				<input type="radio" name="game_result" value="TBD"> TBD
			</td>
		</tr>
		
		<tr>
			<td>Playing Venue</td>
			<td><input required type="text" name="game_venue"/></td>
		</tr>
		
		<tr>
			<td>Opponent Team</td>
			<td><input required type="text" name="game_opponent"/></td>
		</tr>
		
		<tr>
			<td colspan="2">
						<input type="submit" value="Add" name="submit">
						<input type="reset" value="Clear">
			</td>
		</tr>
		
		<tr align="center">
				<td colspan="2">&nbsp;<?php echo $game_add_msg?></td>
		  </tr>
		
	</table>
		<input type="hidden" name="action" value="add_game"/>
	</form>
	
	<!-- games dropbox selection (for update) -->
	<br/><br/>
	<?php
	if($query_result->num_rows > 0){
	?>
	<div>Update Game</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		<select name="select_game" onchange="this.form.submit()">
			<option disabled selected value> -- select a game to update -- </option>
	<?php
		mysqli_data_seek($query_result, 0);
		while($r = $query_result->fetch_assoc()){
			echo  "<option value=\"" . $r["gameid"] . "\">".$r["gameid"]."</option>";
		}
	?>
	</select>
	<input type="hidden" name="action" value="update_game_list"/>
	</form>
	<?php 
	}
	if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["action"]) && $_POST["action"] == "update_game_list"){
		$selected_game_id = $_POST["select_game"];
		$selected_game_date = "";
		$selected_game_result = "";
		$selected_game_venue = "";
		$selected_game_opponent = "";
		mysqli_data_seek($query_result, 0);
		while($r = $query_result->fetch_assoc()){
			if($r["gameid"] == $selected_game_id){
			$selected_game_date = $r["date"];
				$selected_game_result =$r["result"];
				$selected_game_venue = $r["playingvenue"];
				$selected_game_opponent = $r["opponentteam"];
				break;
			}
		}
	?>
	<br/><br/>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		<table>
			<tr>
				<td>ID</td>
				<td>Date</td>
				<td>Result</td>
				<td>Playing Venue</td>
				<td>Opponent Team</td>
			</tr>
			
			<tr>
				<td><input readonly name="id" value="<?php echo $selected_game_id?>"/></td>	
				<td><input required name="date" value="<?php echo DateTime::createFromFormat('Y-m-d', $selected_game_date)->format('m-d-Y');?>"/></td>	
				
				<td>
				<?php
				$results_array = ["Win","Lose","Tie","TBD"];
				for($i=0; $i<4; $i++){
					if($selected_game_result == $results_array[$i]){
						echo "<input checked type=\"radio\" name=\"update_game_result\" value=\"$results_array[$i]\"> $results_array[$i]<br/>";
					}
					else{
						echo "<input type=\"radio\" name=\"update_game_result\" value=\"$results_array[$i]\"> $results_array[$i]<br/>";
					}
				}
				?>
				</td>
				
				<td><input required name="venue" value="<?php echo $selected_game_venue?>"/></td>	
				<td><input required name="opponent" value="<?php echo $selected_game_opponent?>"/></td>	
			</tr>
			
			<tr>
				<td align="right" colspan="5">
					<input type="submit" value="Update" name="submit"/>
				</td>
			</tr>
			
			<tr align="center">
				<td colspan="5">&nbsp;<?php echo $game_update_msg?></td>
		    </tr>
		</table>
		<input type="hidden" name="action" value="update_game"/>
	</form>
	<?php
	}
	?>
	<!-- games dropbox selection (for update) -->
	
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