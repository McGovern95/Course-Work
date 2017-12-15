<?php
session_start();
include('utility.php');

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["action"]) && $_POST["action"] == "logout"){ // logout request
	session_destroy();
	header("Location: index.php"); 
	exit;
}

// this page should show result for authenticated managers only
if(isset($_SESSION["login_id"]) && !empty($_SESSION["login_id"]) &&
   isset($_SESSION["account_type"]) && !empty($_SESSION["account_type"]) && $_SESSION["account_type"] == "manager"){
	
	$manager_id = $manager_name = $manager_birthday = $manager_address = $manager_email = $manger_phone_number = "";
	$profile_update_msg = $upload_certificate_msg = $delete_certificate_msg = $change_password_msg = "";
	
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
			$query_string = "update manager set name= '".$update_name."', birthday = STR_TO_DATE('".$update_birthday."','%m-%d-%Y')"
				.", address='".$update_address."', email='".$update_email."', phonenumber='".$update_phone_number."' where managerid='".$update_id."';";
		
			if ($conn->query($query_string) === TRUE) {
				$profile_update_msg = "Profile updated";
				$conn->commit();
			} else {
				$profile_update_msg = "Error: " . $query_string . "<br>" . $conn->error;
			}
		}
	}
	else if(isset($_POST["action"]) && $_POST["action"] == "upload_certificate"){
		try{
			if (
				!isset($_FILES['certificate']['error']) ||
				is_array($_FILES['certificate']['error'])
			) {
				throw new RuntimeException('Invalid parameters');
			}
			switch ($_FILES['certificate']['error']) {
			case UPLOAD_ERR_NO_FILE:
				throw new RuntimeException('Choose a certificate to upload!');
			case UPLOAD_ERR_OK:
				break;
			case UPLOAD_ERR_INI_SIZE:
			case UPLOAD_ERR_FORM_SIZE:
				throw new RuntimeException('Certificate size too large (max size: 5 MB)');
			default:
				throw new RuntimeException('Unknown errors.');
			}
			
			if ($_FILES['certificate']['size'] > (5 * 1024 * 1024)) {		// 5 MB
				throw new RuntimeException('Certificate size too large (max size 5 MB)');
			}
			
			$finfo = new finfo(FILEINFO_MIME_TYPE);
			if (false === $ext = array_search(
				$finfo->file($_FILES['certificate']['tmp_name']),
				array(
					'jpg' => 'image/jpeg',
					'png' => 'image/png',
				),
				true
			)) {
				throw new RuntimeException('Invalid file format (acceptable formats: jpg/png)');
			}
			
			$imgData =addslashes(file_get_contents($_FILES['certificate']['tmp_name']));
			$imageInfo = getimageSize($_FILES['certificate']['tmp_name']);
			$sql = "select max(certificateid) id from managercertificate where managerid='".$_SESSION["user_id"]."';";
			$cert_id = 1;
			$query_result = $conn->query($sql) or die(mysqli_error($conn));
			if($query_result->num_rows == 1){
				$r = $query_result->fetch_assoc();
				$cert_id = (int)$r["id"] + 1;
			}
			$sql = "INSERT INTO managercertificate VALUES('".$_SESSION["user_id"]."','".$cert_id."', '{$imgData}', '{$_FILES['certificate']['name']}','{$imageInfo['mime']}')";
			if ($conn->query($sql) === TRUE) {
				$upload_certificate_msg = "New Certificate Added";
				$conn->commit();
			} else {
				$upload_certificate_msg = "Error: " . $sql . "<br>" . $conn->error;
			}
			
		}catch (RuntimeException $e){
			$upload_certificate_msg = $e->getMessage();
		}
	}
	else if(isset($_POST["action"]) && $_POST["action"] == "download_certificate"){
		$query_string = "select * from managercertificate where managerid='".$_SESSION["user_id"]."' and certificateid='".$_POST["id"]."';";
		$query_result = $conn->query($query_string) or die(mysqli_error($conn));
		if($query_result->num_rows == 1){
			$r = mysqli_fetch_assoc($query_result);
			header("Content-type: ".$r["blobtype"]);
			header("Content-Disposition: attachment; filename=".$r["blobname"]);
			header("Content-Transfer-Encoding: binary"); 
			header('Pragma: no-cache'); 
			header('Expires: 0');
			// Send the file contents.
			set_time_limit(0); 
			echo $r["certificate"];
		}
	}
	else if(isset($_POST["action"]) && $_POST["action"] == "delete_certificate"){
		$selected_certificate_id = $_POST["select_certificate"];
		$query_string = "delete from managercertificate where managerid='{$_SESSION["user_id"]}' and certificateid='{$selected_certificate_id}';";
		if ($conn->query($query_string) === TRUE) {
				$delete_certificate_msg = "Certificate Deleted";
				$conn->commit();
			} else {
				$delete_certificate_msg = "Error: " . $sql . "<br>" . $conn->error;
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
			$query = "select * from manager where managerid='{$_SESSION["user_id"]}' and password='{$current_password}';";
			$query_result = $conn->query($query) or die(mysqli_error($conn));
			if($query_result->num_rows == 1){
				$query = "update manager set password='{$new_password}' where managerid='{$_SESSION["user_id"]}';";
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
	
	$query = "select * from manager where loginid ='".$_SESSION["login_id"]."';";
	$query_result = $conn->query($query) or die(mysqli_error($conn));
	if($query_result->num_rows == 1){
		$r = mysqli_fetch_assoc($query_result);
		$manager_id = $r["managerid"];
		$manager_name = $r["name"];
		$manager_birthday = $r["birthday"];
		$manager_address = $r["address"];
		$manager_email = $r["email"];
		$manager_phone_number = $r["phonenumber"];
		//todo certificate
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
			<td style="text-align: left"><?php echo $manager_id?></td>
			<td><input readonly="readonly" name="id" value="<?php echo $manager_id?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Name</td>
			<td style="text-align: left"><?php echo $manager_name?></td>
			<td><input name="name" value="<?php echo $manager_name?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Birthdate</td>
			<td style="text-align: left">
				<?php echo date('F d, Y', strtotime($r["birthday"]))?>
			</td>
			<td><input name="birthday" value="<?php echo date("m-d-Y", strtotime($manager_birthday))?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Address</td>
			<td style="text-align: left"><?php echo $manager_address?></td>
			<td><input name="address" value="<?php echo $manager_address?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Email</td>
			<td style="text-align: left"><?php echo $manager_email?></td>
			<td><input name="email" value="<?php echo $manager_email?>"></td>
		</tr>
		
		<tr>
			<td style="text-align: ">Phone#</td>
			<td style="text-align: left"><?php echo $manager_phone_number?></td>
			<td><input name="phone_number" value="<?php echo $manager_phone_number?>"></td>
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
	
	<!-- view manager's certificates start-->
	<br/><br/>
	<div>Certificates</div>
	<table border="1">
		<tr>
		<td>ID</td>
		<td>Certificate</td>
		</tr>
	<?php
	$query = "select certificateid, blobname from managercertificate where managerid='".$_SESSION["user_id"]."';";
	$query_result = $conn->query($query) or die(mysqli_error($conn));
	if($query_result->num_rows > 0){
		while($r = $query_result->fetch_assoc()){
	?>
	<form id="<?php echo $r["certificateid"];?>" method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<tr>
		<td><?php echo $r["certificateid"]?></td>
		<td><a href="#" onclick="document.forms['<?php echo $r["certificateid"];?>'].submit();">Download</a>
			<input type="hidden" name="id" value="<?php echo $r["certificateid"];?>"/>
			<input type="hidden" name="action" value="download_certificate" />
		</td>
	</tr>
		
	</form>
	<?php
		}
	}
	else{
		echo "<td colspan=\"2\" style=\"text-align: center;\">no certificates available</td>";
	}
	?>
	</table>
	<!-- view manager's certificates end-->
			
	<!-- add  certificates start-->
	<br/><br/>
	<form method=post enctype='multipart/form-data' action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
		<table>
			<tr>
				<td>Upload a New Certificate</td>
				<td>
					<input type="hidden" name="MAX_FILE_SIZE" value="5242880" />
					<input type="file" name="certificate" />
				</td>
				<td><input type="submit" name="Submit" value="Upload" /></td>
			</tr>
			
			<tr>
				<td align="center" colspan="3">&nbsp;<?php echo $upload_certificate_msg?></td>
			</tr>
		</table>
		<input type="hidden" name="action" value="upload_certificate"/>
	</form>
	<!-- add  certificates end-->
	
	
	<!-- delete  certificates start-->
	<br/><br/>
	<?php
	if($query_result->num_rows > 0){
	?>
	<div>Delete Certificate</div>
	<form method=post action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<table>
	<tr>
	<td>
	<select name="select_certificate">
		<option disabled selected value> -- select a certificate -- </option>
		<?php
		mysqli_data_seek($query_result, 0);
		while($r = $query_result->fetch_assoc()){
			echo  "<option value=\"" . $r["certificateid"] . "\">(".$r["certificateid"].") ".$r["blobname"]."</option>";
		}
		?>
	</select>
	</td>
	<td><input type="submit" value="Delete" name="submit"></td>
	</tr>
	<tr><td colspan="2" align="center"><?php echo $delete_certificate_msg;?></td></tr>
	</table>
	<input type="hidden" name="action" value="delete_certificate"/>
	</form>
	<br/><br/>
	<?php
	}
	?>
	<!-- delete  certificates end-->
	
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