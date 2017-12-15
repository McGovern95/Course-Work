<?php
session_start();
include('utility.php');

// this page should show result for authenticated managers only
if(isset($_SESSION["login_id"]) && !empty($_SESSION["login_id"]) &&
   isset($_SESSION["account_type"]) && !empty($_SESSION["account_type"]) && $_SESSION["account_type"] == "manager"){
	
$training_delete_msg = $training_add_msg = $training_update_msg = "";
	
	if ($_SERVER["REQUEST_METHOD"] == "POST"){			// multiple post forms are handled here
	if($_POST["action"] == "add_training"){		// adding a new training
		
		$t_name = $_POST["training_name"];
		$t_hours = $_POST["training_hours"];
		$t_instructions = $_POST["training_instructions"];
		
		if(empty($t_hours))
			$t_hours = 0;
		
		if(!is_numeric($t_hours)){
			$training_add_msg = "Training hours must be a integer!";
		}
		else{
		
		$query_string = "insert into training values('".$t_name."','".$t_instructions."',".$t_hours.")";
		
		if ($conn->query($query_string) === TRUE) {
				$training_add_msg = "New training added";
			
				$conn->commit();
			} else {
				$training_add_msg = "Error: " . $query_string . "<br>" . $conn->error;
			}	
		}
	}
		else if($_POST["action"] == "delete_training"){		
			if(isset($_POST['checked_trainings'])){		// makes sure at least one item is checked
				$trainings_list = "";
				 $checkbox = $_POST['checked_trainings'];
				 $trainings_list = "'" . $checkbox[0] . "'";
				 for($i=1;$i<count($checkbox);$i++){
					 $del_id = $checkbox[$i];
					 $trainings_list = $trainings_list . ",'" . $checkbox[$i] . "'";
			}
			// make sure no players are assigned any of the trainings we're about to delete
			$query_string = "select count(*) total from assigntraining where trainingname in ($trainings_list);";
			$q_result = $conn->query($query_string) or die(mysqli_error($conn));
			$r= mysqli_fetch_assoc($q_result);
			if((int) $r["total"] == 0){
			$query_string = "delete from training where trainingname in ($trainings_list);";
				
			if ($conn->query($query_string) === TRUE) {
				$training_delete_msg = count($checkbox) . " record(s) deleted";
				$conn->commit();
			} else {
				$training_delete_msg = "Error: " . $query_string . "<br>" . $conn->error;
			}
			}
			else{
				$training_delete_msg = "Trainings must not be assigned to any player before they can be deleted";
			}
		}
		else{
			$training_delete_msg = "At least one record must be checked for deletion";
		}
		}
		else if($_POST["action"] == "update_training"){
			$t_name = validate_input($_POST["name"]);
			$t_hours = validate_input($_POST["hours"]);
			$t_instructions = validate_input($_POST["instructions"]);
			
			if(empty($t_name) || empty($t_hours) || empty($t_instructions)){
				$training_update_msg = "All fileds must be filled";
			}
			else if(!is_numeric($t_hours)){
				$training_update_msg = "Training hours must be a integer!";
			}
			else{
				$query_string = "update training set instruction = '".$t_instructions."', timeperiodinhour=".$t_hours." where trainingname='".$t_name."';";
				if ($conn->query($query_string) === TRUE){
					$training_update_msg = "Training updated";
					$training_delete_msg = "Training updated";
					$conn->commit();
				}else{
					$training_delete_msg = "Error: " . $query_string . "<br>" . $conn->error;
				}
			}
		}
	}
	
	$query = "select * from training;";
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
<title>Manage Trainings</title>
</head>

<body>
<div>Trainings List</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table border="1">
		<thead>
		<td></td>
		<td>Name</td>
		<td>Hours</td>
		<td>Description</td>		
		</thead>
	
		<tbody>
	<?php
	if($query_result->num_rows > 0){
		while($r = $query_result->fetch_assoc()){
	?>
	<tr>
		<td><input name="checked_trainings[]" type="checkbox" value="<?php echo $r["trainingname"]?>"</td>
		<td><?php echo $r["trainingname"]?></td>
		<td><?php echo $r["timeperiodinhour"]?></td>
		<td><?php echo $r["instruction"]?></td>
	</tr>
	<?php
		}
	}
	else{		// no trainings to show
		echo "<td colspan=\"3\" style=\"text-align: center;\">no trainings available</td>";
	}
	?>
			<tr align="right">
				<td colspan="4"><input type="submit" name="delete_form" value="Delete selected trainings"></td>
			</tr>
			
			<tr align="center">
				<td colspan="4">&nbsp;<?php echo $training_delete_msg?></td>
		    </tr>
		</tbody>
	</table>
		<input type="hidden" name="action" value="delete_training"/>
	</form>
	<br/>
	<br/>
	<div>Add a New Training</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table>
		<tr>
			<td>Name</td>
			<td><input required type="text" name="training_name"/></td>
		</tr>
		
		<tr>
			<td>Hours</td>
			<td><input type="text" name="training_hours"/></td>
		</tr>
		
		<tr>
			<td>Instructions</td>
			<td><input type="text" name="training_instructions"/></td>
		</tr>
		
		<tr>
			<td colspan="2">
						<input type="submit" value="Add" name="submit">
						<input type="reset" value="Clear">
			</td>
		</tr>
		
		<tr align="center">
				<td colspan="2">&nbsp;<?php echo $training_add_msg?></td>
		  </tr>
		
	</table>
		<input type="hidden" name="action" value="add_training"/>
	</form>
	
	<!-- trainings dropbox selection (for update) -->
	<br/><br/>
	<?php
	if($query_result->num_rows > 0){
	?>
	<div>Update Training</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		<select name="select_training" onchange="this.form.submit()">
			<option disabled selected value> -- select a training to update -- </option>
	<?php
		mysqli_data_seek($query_result, 0);
		while($r = $query_result->fetch_assoc()){
			echo  "<option value=\"" . $r["trainingname"] . "\">".$r["trainingname"]."</option>";
		}
	?>
	</select>
	<input type="hidden" name="action" value="update_training_list"/>
	</form>
	<?php 
	}
	if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["action"]) && $_POST["action"] == "update_training_list"){
		$selected_training_name = $_POST["select_training"];
		$selected_training_hours = "";
		$selected_training_instructions = "";
		mysqli_data_seek($query_result, 0);
		while($r = $query_result->fetch_assoc()){
			if($r["trainingname"] == $selected_training_name){
				$selected_training_hours = $r["timeperiodinhour"];
				$selected_training_instructions = $r["instruction"];
				break;
			}
		}
	?>
	<br/><br/>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		<table>
			<tr>
				<td>Training Name</td>
				<td>Hours</td>
				<td>Instructions</td>
			</tr>
			
			<tr>
				<td><input readonly name="name" value="<?php echo $selected_training_name?>"/></td>
				<td><input required name="hours" value="<?php echo $selected_training_hours?>"/></td>
				<td><input required name="instructions" value="<?php echo $selected_training_instructions?>"/></td>				
			</tr>
			
			<tr>
				<td align="right" colspan="3">
					<input type="submit" value="Update" name="submit"/>
				</td>
			</tr>
			
			<tr align="center">
				<td colspan="3">&nbsp;<?php echo $training_update_msg?></td>
		    </tr>
		</table>
		<input type="hidden" name="action" value="update_training"/>
	</form>
	<?php
	}
	?>
	<!-- trainings dropbox selection (for update) -->
	
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