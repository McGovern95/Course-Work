
<?php
$servername = "dbclass.cs.nmsu.edu";
$username = "cmcgover";
$password = "q4tSdx69";
$dbname = "test";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
?>