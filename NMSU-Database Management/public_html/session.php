<?php
/* 
This file should be included by the following pages:
	index.php
	player.php
	manager.php
	
List of global session variables used so far:
	login_id		id of the user
	account_type	type of the user (manager or player)

*/

// Check to see whether a session exists. If it does, this means this is a returning user which 
// has to be redirected to the appropriate page depending on account type (player or manager)
session_start();

if(isset($_SESSION["login_id"]) && !empty($_SESSION["login_id"]) &&
   isset($_SESSION["account_type"]) && !empty($_SESSION["account_type"])){
	// a session already exists for this user
	if($_SESSION["account_type"] == "manager"){		// redirect to manager welcome page
		header("Location: manager_welcome.php"); 
		exit;
	}
	else if($_SESSION["account_type"] == "player"){	// redirect to player welcome page
		header("Location: player_welcome.php"); 
		exit;
	}
	
}
?>