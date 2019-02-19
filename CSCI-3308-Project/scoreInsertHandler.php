<?php
	$username = $_REQUEST['username'];
	$score = $_REQUEST['score'];
	$connection = @mysqli_connect(localhost, root, luckiest, finalproject);
	$result = mysqli_query($connection, "SELECT username FROM users WHERE username = '$username';");
	if(!$result)
	{
		echo "Inside if statement.";
		$result = mysqli_query($connection, "SELECT id FROM users WHERE username = '$username'");
		$row = mysqli_fetch_array($result,MYSQL_ASSOC);
		$Id = $row['id'];
	}
	else
	{
		echo "Inside else statement";
		$result = mysqli_query($connection, "INSERT INTO users (username) VALUES ('$username')");
		$query = "SELECT id FROM users WHERE username = '$username';";
		$result = mysqli_query($connection, $query);
		if(mysqli_num_rows($result) > 0)
		{
			$row = mysqli_fetch_array($result,MYSQL_ASSOC);
			$Id = $row['id'];
		}
	}
	$query = "INSERT INTO scores (id, score) VALUES ('$Id', '$score');";
	$result = mysqli_query($connection,$query);
	include 'score.php';
?>