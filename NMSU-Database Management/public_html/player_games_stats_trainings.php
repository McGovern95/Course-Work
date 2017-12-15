<?php
session_start();
include('utility.php');

// this page should show result for authenticated managers only
if(isset($_SESSION["login_id"]) && !empty($_SESSION["login_id"]) &&
   isset($_SESSION["account_type"]) && !empty($_SESSION["account_type"]) && $_SESSION["account_type"] == "player"){
	
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
<title>Player Information</title>
</head>

<body>
	<!--view games start-->
	<div>Games</div>
	<table>
		<tr>
			<td>ID</td>
			<td>Date</td>
			<td>Result</td>	
			<td>Playing Venue</td>
			<td>Opponent Team</td>
		</tr>
		<?php 
		$query = "select g.* from play p, game g where p.gameid=g.gameid and p.playerid='{$_SESSION["user_id"]}' order by g.date asc;";
		$query_result = $conn->query($query) or die(mysqli_error($conn));
		if($query_result->num_rows > 0){
			while($r = $query_result->fetch_assoc()){
		?>
		<tr>
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
	</table>
	<!--view games end-->
	
	<!--view stats start-->
	<br/><br/>
	<div>Stats</div>
	<table>
		<tr>
			<td>Year</td>
			<td>Total Points</td>
			<td>ASPG</td>
		</tr>
		<?php 
		$query = "select * from stats where playerid='{$_SESSION["user_id"]}' order by year asc;";
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
	else{		// no games to show
		echo "<td colspan=\"3\" style=\"text-align: center;\">no stats available</td>";
	}
	?>
	</table>
	<!--view stats end-->
	
	<!--view training start-->
	<br/><br/>
	<div>Trainings</div>
	<table>
		<tr>
		<td>Name</td>
		<td>Hours</td>
		<td>Description</td>	
		<td>Assiged By</td>
		</tr>
	<?php
	$query = "select a.trainingname, t.timeperiodinhour, t.instruction, m.name from assigntraining a, manager m, training t where m.managerid=a.managerid and t.trainingname=a.trainingname and a.playerid='{$_SESSION["user_id"]}';";
	$query_result = $conn->query($query) or die(mysqli_error($conn));
	if($query_result->num_rows > 0){
		while($r = $query_result->fetch_assoc()){
	?>
	<tr>
		<td><?php echo $r["trainingname"]?></td>
		<td><?php echo $r["timeperiodinhour"]?></td>
		<td><?php echo $r["instruction"]?></td>
		<td><?php echo $r["name"]?></td>
	</tr>
	<?php
		}
	}
	else{		// no trainings to show
		echo "<tr><td colspan=\"4\" style=\"text-align: center;\">no trainings available</td></tr>";
	}
	?>
	</table>
	<!--view training end-->
	
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