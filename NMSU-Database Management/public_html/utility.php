<?php
$servername = "dbclass.cs.nmsu.edu";
$username = "cmcgover";
$password = "q4tSdx69";
$dbname = "test";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname, $port);

// Check connection
if ($conn->connect_error) {
	die("Connection failed: " . $conn->connect_error);
}


function validate_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

function is_valid_date($date, $format = 'm-d-Y'){
	$d = DateTime::createFromFormat($format, $date);
    return $d && $d->format($format) == $date;
}

function random_string($len = 10) {
    $chars = '@#$_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $chars_len = strlen($chars);
    $random_str = '';
    for ($i = 0; $i < $len; $i++) {
        $random_str = $random_str . $chars[rand(0, $chars_len - 1)];
    }
    return $random_str;
}
?>